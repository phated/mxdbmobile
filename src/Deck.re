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

let total = deck =>
  Belt.Map.reduce(deck, 0, (total, _key, count) => count + total);

let increment = (deck, card) => Belt.Map.update(deck, card, maybeInc);
let decrement = (deck, card) => Belt.Map.update(deck, card, maybeDec);

module Styles = {
  open BsReactNative.Style;
  let container = style([flex(1.)]);

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

let getItemLayout = (_data, idx) => {
  "length": 183,
  "offset": 183 * idx,
  "index": idx,
};

let make = (~deck, renderChild) => {
  let itemSeparatorComponent =
    BsReactNative.FlatList.separatorComponent(_ =>
      BsReactNative.(<View style=Styles.separator />)
    );

  {
    ...component,
    render: _self => {
      open BsReactNative;

      let _ = ();

      let cards = toArray(deck);
      let renderItem =
        FlatList.renderItem(
          ({item}) => {
            let (card, count) = item;
            renderChild(card, count);
          },
        );

      <View style=Styles.container>
        <FlatList
          data=cards
          getItemLayout
          initialNumToRender=4
          keyExtractor=(
            (item, _idx) => {
              let (card, _count) = item;
              Card.getUid(card);
            }
          )
          renderItem
          itemSeparatorComponent
        />
      </View>;
    },
  };
};
