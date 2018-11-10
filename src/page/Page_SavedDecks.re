type t =
  | Public(PublicDeck.t)
  | Private(PrivateDeck.t);

let toPublic = deck => Public(deck);
let toPrivate = deck => Private(deck);

module Styles = {
  open BsReactNative.Style;

  let header =
    style([
      height(40.0->Pt),
      backgroundColor(Colors.Css.ourBlueDark),
      alignItems(Center),
      justifyContent(Center),
    ]);
  let headerText =
    style([
      color(Colors.Css.white),
      fontSize(20.0->Float),
      fontWeight(`_800),
    ]);
};

let toItem = savedDeck =>
  switch (savedDeck) {
  | Public({name, author}) =>
    let key = name ++ " by " ++ author;
    PositionedList.Item({key, value: savedDeck, size: 41});
  | Private({key}) => PositionedList.Item({key, value: savedDeck, size: 41})
  };

let keyExtractor = (item, _idx) =>
  switch (item) {
  | PositionedList.Header(title) => title
  | PositionedList.Item({key}) => key
  };

let toListItems = (privateDecks, publicDecks) => {
  let data = Belt.MutableQueue.make();

  if (Belt.Array.length(privateDecks) > 0) {
    Belt.MutableQueue.add(data, PositionedList.Header("Saved Decks"));
    Belt.Array.forEach(privateDecks, deck =>
      Belt.MutableQueue.add(data, toItem(deck))
    );
  };

  if (Belt.Array.length(publicDecks) > 0) {
    Belt.MutableQueue.add(data, PositionedList.Header("Public Decks"));
    Belt.Array.forEach(publicDecks, deck =>
      Belt.MutableQueue.add(data, toItem(deck))
    );
  };

  Belt.MutableQueue.toArray(data);
};

let renderHeader = title =>
  BsReactNative.(
    <View style=Styles.header>
      <Text style=Styles.headerText> <S> title </S> </Text>
    </View>
  );

module DeckList = Apollo.CreateQuery(DeckList);

let component = ReasonReact.statelessComponent("Page.SavedDecks");

let make = (~client, ~position, ~onPersistPosition, renderItem) => {
  ...component,
  render: _self =>
    <DeckList client>
      ...{
           ({result}) =>
             switch (result) {
             | Loading => <Loading />
             | Error(error) =>
               BsReactNative.(
                 <View>
                   <Text> {ReasonReact.string(error##message)} </Text>
                 </View>
               )
             | Data(decks) =>
               let public = Belt.Array.map(decks.public, toPublic);
               let private = Belt.Array.map(decks.private, toPrivate);
               let data = toListItems(private, public);

               <PositionedList
                 data
                 renderItem
                 renderHeader
                 position
                 onPersistPosition
                 initialNumToRender=15
                 keyExtractor
               />;
             }
         }
    </DeckList>,
};
