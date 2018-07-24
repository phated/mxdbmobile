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
    |> Json.Decode.field(
         "characters",
         Json.Decode.array(Character.decoder),
       ),
  events:
    json |> Json.Decode.field("events", Json.Decode.array(Event.decoder)),
  battles:
    json |> Json.Decode.field("battles", Json.Decode.array(Battle.decoder)),
};

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
      /* marginLeft(16.0 |. Pt), */
    ]);
};
let getItemLayout = (_data, idx) => {
  "length": 183,
  "offset": 183 * idx,
  "index": idx,
};

let getUid = card =>
  switch (card) {
  | Card.Character(character) => character.uid
  | Card.Event(event) => event.uid
  | Card.Battle(battle) => battle.uid
  };

let component = ReasonReact.statelessComponent("CardList");

let make = (~cards, renderChild) => {
  let itemSeparatorComponent =
    BsReactNative.FlatList.separatorComponent(_ =>
      BsReactNative.(<View style=Styles.separator />)
    );

  {
    ...component,
    render: _self => {
      /* Js.log("rendering card list"); */

      open BsReactNative;

      let children =
        if (Belt.Array.length(cards) == 0) {
          <View style=Styles.loadingContainer>
            <ActivityIndicator size=`large color=Colors.ourBlue />
          </View>;
        } else {
          let renderItem =
            FlatList.renderItem(
              ({item}) => {
                let (card, count) = item;
                renderChild(card, count);
              },
            );
          <FlatList
            data=cards
            getItemLayout
            initialNumToRender=4
            keyExtractor=(
              (item, _idx) => {
                let (card, _count) = item;
                getUid(card);
              }
            )
            renderItem
            itemSeparatorComponent
          />;
        };

      <View style=Styles.container> children </View>;
    },
  };
};

let query = {|
query CardList($title: String, $subtitle: String, $trait: String, $mp: Int, $effect: String, $symbol: CardSymbol) {
  characters: allCards(filter: {
    AND: [
      { type: Character },
      { OR: [
          { title_contains: $title },
          { subtitle_contains: $subtitle },
          { trait: { name_contains: $trait } },
          { mp: $mp },
          { effect: { text_contains: $effect } },
        ]
      },
      { effect: { symbol: $symbol } }
    ]
  }, orderBy: title_ASC) {
    uid
    title
    subtitle
    trait {
      name
    }
    mp
    stats {
      type
      rank
    }
    effect {
      symbol
      text
    }
    image {
      thumbnail
      small
    }
  }
  events: allCards(filter: {
    AND: [
      { type: Event },
      { OR: [
          { title_contains: $title },
          { mp: $mp },
          { effect: { text_contains: $effect } }
        ]
      },
      { effect: { symbol: $symbol } }
    ]
  }, orderBy: title_ASC) {
    uid
    title
    mp
    effect {
      symbol
      text
    }
    image {
      thumbnail
      small
    }
  }
  battles: allCards(filter: {
    AND: [
      { type: Battle },
      { OR: [
          { title_contains: $title },
          { mp: $mp },
          { effect: { text_contains: $effect } }
        ]
      },
      { effect: { symbol: $symbol } }
    ]
  }, orderBy: title_ASC) {
    uid
    title
    mp
    stats(orderBy: type_ASC) {
      type
      rank
    }
    effect {
      symbol
      text
    }
    image {
      thumbnail
      small
    }
  }
}
|};
