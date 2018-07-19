type t = {
  characters: array(Character.t),
  events: array(Event.t),
  battles: array(Battle.t),
};

let empty = {characters: [||], events: [||], battles: [||]};

let toArray = cardList =>
  Belt.Array.concatMany([|
    Belt.Array.map(cardList.characters, Card.character),
    Belt.Array.map(cardList.events, Card.event),
    Belt.Array.map(cardList.battles, Card.battle),
  |]);

let decode = json => {
  characters:
    json
    |> Json.Decode.field("characters", Json.Decode.array(Character.decoder)),
  events:
    json |> Json.Decode.field("events", Json.Decode.array(Event.decoder)),
  battles:
    json |> Json.Decode.field("battles", Json.Decode.array(Battle.decoder)),
};

module Styles = {
  open BsReactNative.Style;
  let container = style([flex(1.)]);

  let separator =
    style([
      flex(1.0),
      height(1.0 |. Pt),
      backgroundColor(Colors.Css.gray),
      /* marginLeft(16.0 |. Pt), */
    ]);
};
let itemSeparatorComponent =
  BsReactNative.FlatList.separatorComponent(_ =>
    BsReactNative.(<View style=Styles.separator />)
  );
let renderItem =
  BsReactNative.FlatList.renderItem(bag => {
    let card: Card.t = bag.item;
    switch (card) {
    | Character({title, subtitle, trait, mp, stats, image, effect}) =>
      <Character title subtitle trait mp stats image effect />
    | Event({title, mp, image, effect}) => <Event title mp image effect />
    | Battle({title, mp, stat, image, effect}) =>
      <Battle title mp stat image effect />
    };
  });

let getItemLayout = (_data, idx) => {
  "length": 170,
  "offset": 170 * idx,
  "index": idx,
};

let getUid = card =>
  switch (card) {
  | Card.Character(character) => character.uid
  | Card.Event(event) => event.uid
  | Card.Battle(battle) => battle.uid
  };

let component = ReasonReact.statelessComponent("CardList");

let make = (~cards, _children) => {
  ...component,
  render: self => {
    open BsReactNative;
    let sections = toArray(cards);

    <View style=Styles.container>
      <FlatList
        data=sections
        getItemLayout
        keyExtractor=((card, _idx) => getUid(card))
        renderItem
        itemSeparatorComponent
      />
    </View>;
  },
};
