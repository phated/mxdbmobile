module Comparator =
  Belt.Id.MakeComparable({
    type t = Card.t;

    let getType = card =>
      switch (card) {
      | Card.Character(_) => CardType.Character
      | Card.Event(_) => CardType.Event
      | Card.Battle(_) => CardType.Battle
      };

    let getUid = card =>
      switch (card) {
      | Card.Character({uid}) => uid
      | Card.Event({uid}) => uid
      | Card.Battle({uid}) => uid
      };

    let cmp = (first, second) => {
      let cardType1 = getType(first);
      let cardType2 = getType(second);

      if (cardType1 == cardType2) {
        let uid1 = getUid(first);
        let uid2 = getUid(second);
        compare(uid1, uid2);
      } else {
        /* Compare works on Variants in ocaml so no need for toInt??? */
        compare(
          cardType1,
          cardType2,
        );
      };
    };
  });

type t = Belt.Map.t(Comparator.t, int, Comparator.identity);

let empty: t = Belt.Map.make(~id=(module Comparator));

let toArray = deck => Belt.Map.toArray(deck);

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
      backgroundColor(Colors.Css.primary),
      alignItems(Center),
      justifyContent(Center),
    ]);
  let headerText =
    style([
      color(Colors.Css.white),
      fontSize(20.0 |. Float),
      fontWeight(`_800),
    ]);

  let loadingContainer =
    style([flex(1.), alignItems(Center), justifyContent(Center)]);
  let separator =
    style([
      flex(1.0),
      height(1.0 |. Pt),
      backgroundColor(Colors.Css.gray),
    ]);
};

let component = ReasonReact.statelessComponent("Deck");

let make = (~deck, renderChild) => {
  let toHeader = card =>
    switch (card) {
    | Card.Character(_) =>
      let characterCount = countCharacters(deck);
      CustomList.Header({j|Characters ($characterCount)|j});
    | Card.Event(_) =>
      let eventCount = countEvents(deck);
      CustomList.Header({j|Events ($eventCount)|j});
    | Card.Battle(_) =>
      let battleCount = countBattles(deck);
      CustomList.Header({j|Battle Cards ($battleCount)|j});
    };

  let init = ((card, count)) => [|
    toHeader(card),
    CustomList.Item(card, count),
  |];

  let mapper = ((prevCard, _), (nextCard, count)) =>
    Card.sameType(prevCard, nextCard) ?
      [|CustomList.Item(nextCard, count)|] :
      [|toHeader(nextCard), CustomList.Item(nextCard, count)|];

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
      BsReactNative.(
        <View style=Styles.container>
          <CustomList data=cards renderItem renderHeader />
        </View>
      ),
  };
};
