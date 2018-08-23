module Comparator =
  Belt.Id.MakeComparable({
    type t = Card.t;

    let cmp =
      Compare.concat([
        Compare.by(card => Card.typeGet(card) |. CardType.toInt),
        /* TODO: card stats order */
        Compare.by(card => Card.titleGet(card)),
        Compare.by(card => Card.effectGet(card) |. Effect.getText),
        Compare.by(card => Card.uidGet(card)),
      ]);
  });

type t = Belt.Map.t(Comparator.t, int, Comparator.identity);

let empty: t = Belt.Map.make(~id=(module Comparator));

let toArray = deck => Belt.Map.toArray(deck);

let reduce = Belt.Map.reduce;

let flatMap2 = (deck, init, mapper) => {
  let result =
    Belt.Map.reduce(deck, None, (wrapper, key, value) =>
      switch (wrapper) {
      | None =>
        let first = (key, value);
        let initResults = init(first);
        let flattened = Belt.Array.concat([||], initResults);
        Some((flattened, first));
      | Some((results, prev)) =>
        let next = (key, value);
        let nextResults = mapper(prev, next);
        let flattened = Belt.Array.concat(results, nextResults);
        Some((flattened, next));
      }
    );

  switch (result) {
  | Some((result, _last)) => result
  | None => [||]
  };
};

let maybeInc = maybeCount =>
  switch (maybeCount) {
  | Some(count) when count < 3 => Some(count + 1)
  | Some(count) => Some(count)
  | None => Some(1)
  };
let maybeDec = maybeCount =>
  switch (maybeCount) {
  | Some(count) when count == 1 => None
  | Some(count) => Some(count - 1)
  | None => None
  };

/* let get = (deck, card) => Belt.Map.getWithDefault(deck, card, 0); */

let count = (deck, card) => Belt.Map.getWithDefault(deck, card, 0);
let countCharacters = deck =>
  Belt.Map.reduce(deck, 0, (total, card, count) =>
    switch (card) {
    | Card.Character(_) => count + total
    | _ => total
    }
  );
let countEvents = deck =>
  Belt.Map.reduce(deck, 0, (total, card, count) =>
    switch (card) {
    | Card.Event(_) => count + total
    | _ => total
    }
  );
let countBattles = deck =>
  Belt.Map.reduce(deck, 0, (total, card, count) =>
    switch (card) {
    | Card.Battle(_) => count + total
    | _ => total
    }
  );

let total = deck =>
  Belt.Map.reduce(deck, 0, (total, _card, count) => count + total);

let increment = (deck, card) => Belt.Map.update(deck, card, maybeInc);
let decrement = (deck, card) => Belt.Map.update(deck, card, maybeDec);

module Styles = {
  open BsReactNative.Style;
  let container = style([flex(1.)]);

  let header =
    style([
      height(40.0 |. Pt),
      backgroundColor(Colors.Css.ourBlueDark),
      alignItems(Center),
      justifyContent(Center),
    ]);
  let headerText =
    style([
      color(Colors.Css.white),
      fontSize(20.0 |. Float),
      fontWeight(`_800),
    ]);
};

let component = ReasonReact.statelessComponent("Deck");

let make = (~deck, ~position, ~onPersistPosition, renderChild) => {
  let toHeader = card =>
    switch (card) {
    | Card.Character(_) =>
      let characterCount = countCharacters(deck);
      PositionedList.Header({j|Characters ($characterCount)|j});
    | Card.Event(_) =>
      let eventCount = countEvents(deck);
      PositionedList.Header({j|Events ($eventCount)|j});
    | Card.Battle(_) =>
      let battleCount = countBattles(deck);
      PositionedList.Header({j|Battle Cards ($battleCount)|j});
    };

  let init = ((card, count)) => [|
    toHeader(card),
    PositionedList.Item(card, count),
  |];

  let mapper = ((prevCard, _), (nextCard, count)) =>
    Card.sameType(prevCard, nextCard) ?
      [|PositionedList.Item(nextCard, count)|] :
      [|toHeader(nextCard), PositionedList.Item(nextCard, count)|];

  let cards = flatMap2(deck, init, mapper);

  let renderHeader = title =>
    BsReactNative.(
      <View style=Styles.header>
        <Text style=Styles.headerText> (ReasonReact.string(title)) </Text>
      </View>
    );
  let renderItem = (card, count) => renderChild(card, count);

  {
    ...component,
    render: _self =>
      <PositionedList
        data=cards
        renderItem
        renderHeader
        position
        onPersistPosition
      />,
  };
};

let hash = deck => {
  let version = 0;

  let encodedVersion = Hash.toBase64(version);

  let result = Hash.emptyResult(encodedVersion);

  let encodeResult = reduce(deck, result, Hash.encodeCard);

  let encodedDeck =
    encodedVersion ++ String.concat("", encodeResult.cardHashes);

  let base64Checksum = Hash.toBase64(encodeResult.checksum mod 64);

  let encoded = encodedDeck ++ base64Checksum;
  /* AiAASAhA */
  if (Belt.List.size(encodeResult.cardHashes) > 0) {
    Some(encoded);
  } else {
    None;
  };
};
