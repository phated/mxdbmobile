type t =
  | Public(PublicDeck.t)
  | Private(PrivateDeck.t);

let toPublic = deck => Public(deck);
let toPrivate = deck => Private(deck);

type activeState =
  | Loading
  | Completed;

type state('data) = {
  activeState,
  position: float,
  data: 'data,
};

type action('data) =
  | FetchDecks
  | StoreData('data);

let component = ReasonReact.reducerComponent("Page.SavedDecks");

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

let getPrivateDecks = () =>
  PrivateDeck.getAll()
  |> Repromise.map(result =>
       switch (result) {
       | Belt.Result.Ok(decks) =>
         Belt.Array.map(decks, toPrivate)->Belt.Result.Ok
       | Belt.Result.Error(msg) => Belt.Result.Error(msg)
       }
     );
let getPublicDecks = () =>
  PublicDeck.getAll()
  |> Repromise.map(result =>
       switch (result) {
       | Belt.Result.Ok(decks) =>
         Belt.Array.map(decks, toPublic)->Belt.Result.Ok
       | Belt.Result.Error(msg) => Belt.Result.Error(msg)
       }
     );

let getDecks = self => {
  let private = getPrivateDecks();

  let public = getPublicDecks();

  Repromise.all([private, public])
  |> Repromise.map(results =>
       switch (results) {
       | [private, public] =>
         let privateDecks = Belt.Result.getWithDefault(private, [||]);
         let publicDecks = Belt.Result.getWithDefault(public, [||]);

         let data = toListItems(privateDecks, publicDecks);

         Belt.Result.Ok(data);
       | _ => Belt.Result.Error("Invalid results")
       }
     )
  |> Repromise.wait(result =>
       switch (result) {
       | Belt.Result.Ok(data) => self.ReasonReact.send(StoreData(data))
       | Belt.Result.Error(msg) => Js.log(msg)
       }
     );
};

let renderHeader = title =>
  BsReactNative.(
    <View style=Styles.header>
      <Text style=Styles.headerText> <S> title </S> </Text>
    </View>
  );

let make = (~position, ~onPersistPosition, renderItem) => {
  ...component,
  initialState: () => {data: [||], position, activeState: Loading},
  reducer: (action, state) =>
    switch (action) {
    | FetchDecks =>
      ReasonReact.UpdateWithSideEffects(
        {...state, activeState: Loading},
        getDecks,
      )
    | StoreData(data) =>
      ReasonReact.Update({...state, data, activeState: Completed})
    },
  didMount: self => self.send(FetchDecks),
  render: self => {
    let {data, activeState, position} = self.state;

    switch (activeState) {
    | Loading => <Loading />
    | Completed =>
      <PositionedList
        data
        renderHeader
        renderItem
        position
        onPersistPosition
        initialNumToRender=15
        keyExtractor
      />
    };
  },
};
