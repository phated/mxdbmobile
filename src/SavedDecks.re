type t = {
  author: string,
  name: string,
  /* date: string, */
  hash: string,
  /* source: string, */
};

let decode = json => {
  author: json |> Json.Decode.field("author", Json.Decode.string),
  name: json |> Json.Decode.field("name", Json.Decode.string),
  hash: json |> Json.Decode.field("hash", Json.Decode.string),
};

let component = ReasonReact.statelessComponent("SavedDecks");

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

let make =
    (~savedDecks, ~publicDecks, ~position, ~onPersistPosition, renderChild) => {
  let renderItem = (deck, hash) => renderChild(deck, hash);
  let renderHeader = title =>
    BsReactNative.(
      <View style=Styles.header>
        <Text style=Styles.headerText> <S> title </S> </Text>
      </View>
    );
  let keyExtractor = (item, _idx) =>
    switch (item) {
    | PositionedList.Header(title) => title
    | PositionedList.Item({key}) => key
    };

  /* let savedHeader = [|PositionedList.Header("Saved Decks")|]; */
  let savedHeader = [||];
  let publicHeader = [|PositionedList.Header("Public Decks")|];

  let toItem = ({name, hash, author}) =>
    PositionedList.Item({key: {j|$name by $author|j}, value: hash, size: 41});

  let saved = Belt.Array.map(savedDecks, toItem);
  let public = Belt.Array.map(publicDecks, toItem);

  let data =
    Belt.Array.concatMany([|savedHeader, saved, publicHeader, public|]);

  {
    ...component,
    render: _self => {
      let loading =
        Belt.Array.length(saved) === 0 && Belt.Array.length(public) === 0;

      if (loading) {
        <Loading />;
      } else {
        <PositionedList
          data
          renderHeader
          renderItem
          position
          onPersistPosition
          initialNumToRender=15
          keyExtractor
        />;
      };
    },
  };
};
