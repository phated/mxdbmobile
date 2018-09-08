type publicDeck = {
  author: string,
  name: string,
  /* date: string, */
  hash: string,
  /* source: string, */
};

type privateDeck = {
  key: string,
  name: string,
  hash: string,
};

type t =
  | Public(publicDeck)
  | Private(privateDeck);

let isPrivate = savedDeck =>
  switch (savedDeck) {
  | Public(_) => false
  | Private(_) => true
  };

let isPublic = savedDeck =>
  switch (savedDeck) {
  | Public(_) => true
  | Private(_) => false
  };

let decode = json =>
  Public({
    author: json |> Json.Decode.field("author", Json.Decode.string),
    name: json |> Json.Decode.field("name", Json.Decode.string),
    hash: json |> Json.Decode.field("hash", Json.Decode.string),
  });

let fetch = () => {
  let toSavedDeck = record =>
    Private({
      key: Database.Decks.keyGet(record),
      name: Database.Decks.nameGet(record),
      hash: Database.Decks.hashGet(record),
    });

  Database.Decks.getAll()
  |> Repromise.map(records => Belt.Array.map(records, toSavedDeck))
  |> Repromise.map(decks => Belt.Result.Ok(decks));
};

let persist = deck => {
  let maybeKey = Deck.keyGet(deck);
  let maybeName = Deck.nameGet(deck);
  let maybeHash = Deck.hash(deck);

  /* TODO: What should happen if the hash is empty? This is basically when a user removes the last card from a deck */
  switch (maybeKey, maybeName, maybeHash) {
  | (_, _, None) => Repromise.resolved(Belt.Result.Error("Unable to Hash"))
  | (None, Some(name), Some(hash)) => Database.Decks.insert(~name, ~hash)
  | (Some(key), Some(name), Some(hash)) =>
    Database.Decks.update(~key, ~name, ~hash)
  | _ => Repromise.resolved(Belt.Result.Error("Invalid configuration"))
  };
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

let make = (~decks, ~position, ~onPersistPosition, renderChild) => {
  let renderItem = (deck, hash) => renderChild(deck, hash);
  let renderHeader = title =>
    BsReactNative.(
      <View style=Styles.header>
        <Text style=Styles.headerText> <S> title </S> </Text>
      </View>
    );

  let data = Belt.MutableQueue.make();

  let (private, public) = Belt.Array.partition(decks, isPrivate);
  if (Belt.Array.length(private) > 0) {
    Belt.MutableQueue.add(data, PositionedList.Header("Saved Decks"));
    Belt.Array.forEach(private, deck =>
      Belt.MutableQueue.add(data, toItem(deck))
    );
  };

  if (Belt.Array.length(public) > 0) {
    Belt.MutableQueue.add(data, PositionedList.Header("Public Decks"));
    Belt.Array.forEach(public, deck =>
      Belt.MutableQueue.add(data, toItem(deck))
    );
  };

  {
    ...component,
    render: _self => {
      let loading = Belt.MutableQueue.size(data) === 0;

      if (loading) {
        <Loading />;
      } else {
        <PositionedList
          data={Belt.MutableQueue.toArray(data)}
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
