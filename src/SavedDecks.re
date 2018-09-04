type t = {
  author: option(string),
  name: string,
  /* date: string, */
  hash: string,
  /* source: string, */
};

let namespace = "@mxdbmobile/decks/";

let decode = json => {
  author:
    json
    |> Json.Decode.field("author", Json.Decode.optional(Json.Decode.string)),
  name: json |> Json.Decode.field("name", Json.Decode.string),
  hash: json |> Json.Decode.field("hash", Json.Decode.string),
};

let fetch = () =>
  AsyncStorage.getAllKeys()
  |> Repromise.map(maybeKeys =>
       switch (maybeKeys) {
       | None => Belt.Result.Error("Unable to get decks")
       | Some(keys) =>
         let deckKeys =
           Belt.Array.keep(keys, key => Js.String.startsWith(namespace, key));
         Belt.Result.Ok(deckKeys);
       }
     )
  |> Repromise.andThen(result =>
       switch (result) {
       | Belt.Result.Error(msg) => Repromise.resolved(Belt.Result.Error(msg))
       | Belt.Result.Ok(deckKeys) =>
         let deckHashes =
           Belt.Array.map(deckKeys, key =>
             AsyncStorage.getItem(key)
             |> Repromise.map(maybeHash =>
                  switch (maybeHash) {
                  | None => None
                  | Some(hash) =>
                    let name = Js.String.replace(namespace, "", key);
                    Some({hash, name, author: None});
                  }
                )
           )
           |> Belt.List.fromArray;
         Repromise.all(deckHashes)
         |> Repromise.map(decks => {
              let decks =
                Belt.List.keepMap(decks, a => a) |> Belt.List.toArray;
              Belt.Result.Ok(decks);
            });
       }
     );

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

  /* TODO: Don't show header when no decks */
  let savedHeader = [|PositionedList.Header("Saved Decks")|];
  let publicHeader = [|PositionedList.Header("Public Decks")|];

  let toItem = ({name, hash, author}) => {
    let key =
      switch (author) {
      | Some(author) => name ++ " by " ++ author
      | None => name
      };
    PositionedList.Item({key, value: hash, size: 41});
  };

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
