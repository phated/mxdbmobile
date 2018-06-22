open BsReactNative;

type image = {. "small": string};
type card = {
  .
  "uid": string,
  "image": option(image),
};

module CardQuery = [%graphql
  {|
    {
      characters: allCards(filter: { type: Character }, orderBy: title_ASC) {
        uid
        image {
          small
        }
      }
      events: allCards(filter: { type: Event }, orderBy: title_ASC) {
        uid
        image {
          small
        }
      }
      battles: allCards(filter: { type: Battle }, orderBy: title_ASC) {
        uid
        image {
          small
        }
      }
    }
    |}
];

type cardSections = {
  .
  "characters": array(card),
  "events": array(card),
  "battles": array(card),
};

type state = {
  characters: array(card),
  events: array(card),
  battles: array(card),
};
type action =
  | FetchCards
  | StoreCards(cardSections);

let component = ReasonReact.reducerComponent("GridOfCards");

module Styles = {
  open Style;
  let container = style([flex(1.), alignItems(Stretch)]);

  let small = style([height(Pt(100.)), width(Pt(72.))]);
};

let getUri = card =>
  switch (card##image) {
  | Some(image) => image##small
  | None => ""
  };

let renderItem =
  FlatList.renderItem(({item}) => {
    let small = getUri(item);

    <View style=Styles.container> <FastImage uri=small /> </View>;
  });

let make = _children => {
  ...component,
  initialState: () => {characters: [||], events: [||], battles: [||]},
  didMount: self => self.send(FetchCards),
  reducer: (action, state) =>
    switch (action) {
    | StoreCards(cards) =>
      ReasonReact.Update({
        characters: cards##characters,
        events: cards##events,
        battles: cards##battles,
      })
    | FetchCards =>
      ReasonReact.SideEffects(
        (
          self =>
            Query.send(CardQuery.make())
            |> Js.Promise.then_(Utils.tapLog)
            |> Js.Promise.then_(cards => {
                 self.send(StoreCards(cards));
                 Js.Promise.resolve(cards);
               })
            |> ignore
        ),
      )
    },
  render: self => {
    let uris =
      Belt.Array.concatMany([|
        self.state.characters,
        self.state.events,
        self.state.battles,
      |])
      |. Belt.Array.map(getUri);

    let data =
      Belt.Array.concatMany([|
        self.state.characters,
        self.state.events,
        self.state.battles,
      |]);

    <View style=Styles.container>
      <FlatList
        data
        renderItem
        numColumns=3
        style=Styles.container
        keyExtractor=((item, int) => item##uid)
      />
    </View>;
  },
};
