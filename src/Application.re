module Styles = {
  open BsReactNative.Style;

  /* backgroundColor is set to avoid showing the splash logo during app use */
  let container = style([flex(1.), backgroundColor(Colors.Css.white)]);

  let title =
    style([
      color(Colors.Css.white),
      fontSize(20.0->Float),
      margin(8.0->Pt),
      fontWeight(`Bold),
      flex(1.0),
    ]);

  let deck =
    style([
      flex(1.0),
      paddingHorizontal(8.0->Pt),
      height(40.0->Pt),
      justifyContent(Center),
    ]);
  let deckName = style([fontSize(20.0->Float)]);
};

type action =
  | NavigateTo(Page.t)
  | Search(string)
  | ReplaceDeck(Deck.t)
  | RenameDeck(string)
  | ClearDeck
  | Increment(Card.t)
  | Decrement(Card.t)
  | PersistCardListPosition(float)
  | PersistDeckPosition(float)
  | Error
  | StoreDeckKey(string);
type state = {
  page: Page.t,
  filter: Filter.t,
  deck: Deck.t,
  deckSize: int,
  cardListPosition: float,
  deckPosition: float,
};

let create = () => {
  let program = Oolong.routerProgram("Main App");

  let search = (text, self) => self.Oolong.send(Search(text));
  let renameDeck = (text, self) => self.Oolong.send(RenameDeck(text));
  let loadDeck = (~key=?, deckName, hash, _, self) => {
    self.Oolong.send(NavigateTo(Loading));

    Deck.loadFromHash(~key?, ~name=deckName, hash)
    |> Repromise.wait(result =>
         switch (result) {
         | Belt.Result.Ok(deck) => self.Oolong.send(ReplaceDeck(deck))
         | Belt.Result.Error(msg) => Js.log(msg)
         }
       );
  };
  let clearDeck = (_text, self) => self.Oolong.send(ClearDeck);
  let increment = (card, self) => self.Oolong.send(Increment(card));
  let decrement = (card, self) => self.Oolong.send(Decrement(card));
  let toCards = (_, self) => self.Oolong.send(NavigateTo(Cards));
  let toDeck = (_, self) =>
    if (Deck.isEmpty(self.Oolong.state.deck)) {
      self.Oolong.send(NavigateTo(SavedDecks));
    } else {
      self.Oolong.send(NavigateTo(Deck));
    };
  let toSettings = (_, self) => self.Oolong.send(NavigateTo(Settings));
  let toStats = (_, self) => self.Oolong.send(NavigateTo(Stats));
  let toPatreon = (_, self) => self.Oolong.send(NavigateTo(Patreon));
  let toLegal = (_, self) => self.Oolong.send(NavigateTo(Legal));
  let persistCardListPosition = (position, self) =>
    self.Oolong.send(PersistCardListPosition(position));
  let persistDeckPosition = (position, self) =>
    self.Oolong.send(PersistDeckPosition(position));

  let saveDeck = self =>
    /* TODO: Indicator for saving deck (if this takes long/can fail) */
    PrivateDeck.persist(self.Oolong.state.deck)
    |> Repromise.wait(result =>
         switch (result) {
         | Belt.Result.Ok(key) => self.Oolong.send(StoreDeckKey(key))
         | Belt.Result.Error(_) => self.Oolong.send(Error)
         }
       );

  {
    ...program,
    fromRoute: (action, route) =>
      switch (action) {
      | Init =>
        Oolong.Update({
          page: Page.fromPath(route.path),
          /* page: Page.SavedDecks, */
          filter: Filter.Empty,
          deck: Deck.empty,
          deckSize: 0,
          cardListPosition: 0.0,
          deckPosition: 0.0,
        })
      | Push => Oolong.NoUpdate
      | _ => Oolong.NoUpdate
      },
    toRoute: ({previous, next}) =>
      if (previous == next) {
        Oolong.NoTransition;
      } else {
        let search = Filter.toString(next.filter);
        /* Js.log(Deck.hash(next.deck)); */
        Oolong.Push(
          Oolong.Route.make(~path=Page.toPath(next.page), ~search, ~hash=""),
        );
      },
    update: (action, state) =>
      switch (action) {
      | Error =>
        Js.log("something went terribly wrong");
        Oolong.NoUpdate;
      | StoreDeckKey(key) =>
        Oolong.Update({...state, deck: Deck.keySet(state.deck, key)})
      | NavigateTo(page) => Oolong.Update({...state, page})
      | Increment(card) =>
        let deck = Deck.increment(state.deck, card);
        let deckSize = Deck.total(deck);
        Oolong.UpdateWithSideEffects(
          {...state, deck, deckSize, deckPosition: 0.0},
          saveDeck,
        );
      | Decrement(card) =>
        let deck = Deck.decrement(state.deck, card);
        let deckSize = Deck.total(deck);
        Oolong.UpdateWithSideEffects(
          {...state, deck, deckSize, deckPosition: 0.0},
          saveDeck,
        );
      | ReplaceDeck(deck) =>
        Oolong.Update({
          ...state,
          deck,
          deckSize: Deck.total(deck),
          page: Deck,
          deckPosition: 0.0,
        })
      | RenameDeck(deckName) =>
        Oolong.UpdateWithSideEffects(
          {...state, deck: Deck.nameSet(state.deck, deckName)},
          saveDeck,
        )
      | ClearDeck =>
        Oolong.Update({
          ...state,
          deck: Deck.empty,
          deckSize: 0,
          page: SavedDecks,
          deckPosition: 0.0,
        })

      | PersistCardListPosition(position) =>
        Oolong.Update({...state, cardListPosition: position})
      | PersistDeckPosition(position) =>
        Oolong.Update({...state, deckPosition: position})
      | Search(filter) =>
        Oolong.Update({
          ...state,
          cardListPosition: 0.0,
          filter: FreeText(filter),
        })
      },
    view: ({state, handle}) => {
      open BsReactNative;

      let {deck, filter, deckSize, page} = state;

      let renderCard = (card, count) =>
        <Card
          card
          count
          onIncrement={handle(increment)}
          onDecrement={handle(decrement)}
        />;

      let cardListRender = card => {
        let count = Deck.count(deck, card);

        <Card
          card
          count
          onIncrement={handle(increment)}
          onDecrement={handle(decrement)}
        />;
      };

      let cardListToolbarRender = (~enable, ~disable, mode) =>
        switch (mode) {
        | Toolbar.Enabled =>
          <>
            <IconButton icon="arrow-back" onPress=disable />
            <ToolbarInput
              placeholder="Search"
              previous={Filter.toString(filter)}
              onBlur=disable
              onSubmit={handle(search)}
            />
          </>
        | Toolbar.Disabled =>
          <>
            <Text style=Styles.title> <S> "MetaX Deck Builder" </S> </Text>
            /* <IconButton icon="view-module" />, */
            <IconButton icon="search" onPress=enable />
          </>
        };
      let deckListToolbarRender = (~enable, ~disable, mode) =>
        switch (mode) {
        | Toolbar.Enabled =>
          <>
            <IconButton icon="arrow-back" onPress=disable />
            <ToolbarInput
              placeholder="Deck Name"
              previous={Belt.Option.getWithDefault(Deck.nameGet(deck), "")}
              onBlur=disable
              onSubmit={handle(renameDeck)}
            />
          </>
        | Toolbar.Disabled =>
          <>
            <Text
              ellipsizeMode=`tail
              numberOfLines=1
              style=Styles.title
              onPress=enable>
              <Icon name="edit" size=16 />
              <S> " " </S>
              <S> {Belt.Option.getWithDefault(Deck.nameGet(deck), "")} </S>
            </Text>
            /* <IconButton icon="view-module" />, */
            <IconButton icon="playlist-remove" onPress={handle(clearDeck)} />
          </>
        };

      let savedDecksToolbarRender = (~enable as _, ~disable as _, _mode) =>
        <> <Text style=Styles.title> <S> "Choose a Deck" </S> </Text> </>;

      let settingsToolbarRender = (~enable as _, ~disable as _, _mode) =>
        <> <Text style=Styles.title> <S> "Settings" </S> </Text> </>;

      let emptyToolbarRender = (~enable as _, ~disable as _, _mode) =>
        <> <Text style=Styles.title> <S> "MetaX Deck Builder" </S> </Text> </>;

      let toolbarRender =
        switch (page) {
        | Cards => cardListToolbarRender
        | SavedDecks => savedDecksToolbarRender
        | Deck => deckListToolbarRender
        | Settings => settingsToolbarRender
        | _ => emptyToolbarRender
        };

      let renderDeck = (_key, savedDeck) =>
        switch (savedDeck) {
        | Page.SavedDecks.Public({name, author, hash}) =>
          let deckName = name ++ " by " ++ author;
          <TouchableOpacity onPress={handle(loadDeck(deckName, hash))}>
            <View style=Styles.deck>
              <Text style=Styles.deckName numberOfLines=1>
                <S> deckName </S>
              </Text>
            </View>
          </TouchableOpacity>;
        | Page.SavedDecks.Private({key, name, hash}) =>
          <TouchableOpacity onPress={handle(loadDeck(~key, name, hash))}>
            <View style=Styles.deck>
              <Text style=Styles.deckName numberOfLines=1>
                <S> name </S>
              </Text>
            </View>
          </TouchableOpacity>
        };

      let page =
        switch (state.page) {
        | Page.Loading => <Loading />
        | Page.Cards =>
          let position = state.cardListPosition;
          let onPersistPosition = handle(persistCardListPosition);
          <Page.CardList filter position onPersistPosition>
            ...cardListRender
          </Page.CardList>;
        | Page.Deck =>
          let position = state.deckPosition;
          let onPersistPosition = handle(persistDeckPosition);
          <Deck deck position onPersistPosition> ...renderCard </Deck>;
        | Page.SavedDecks =>
          let position = 0.0;
          let onPersistPosition = handle((_, _) => ());
          <Page.SavedDecks position onPersistPosition>
            ...renderDeck
          </Page.SavedDecks>;
        | Page.Stats => <Page.Stats />
        | Page.Settings =>
          let data = [|
            Page.Settings.{title: "Patreon", onPress: handle(toPatreon)},
            Page.Settings.{title: "Legal", onPress: handle(toLegal)},
          |];
          <Page.Settings data />;
        | Page.Patreon => <Page.Patreon />
        | Page.Legal => <Page.Legal />
        };

      <SafeAreaView style=Styles.container>
        <StatusBar backgroundColor=Colors.ourBlueDark />
        <Toolbar> ...toolbarRender </Toolbar>
        page
        <NavigationBar>
          <NavigationButton
            icon="cards"
            label="Cards"
            active={state.page === Cards}
            onPress={handle(toCards)}
          />
          <NavigationButton
            icon="deck"
            label={j|Deck ($deckSize)|j}
            active={state.page === Deck || state.page === SavedDecks}
            onPress={handle(toDeck)}
          />
          <NavigationButton
            icon="chart-bar"
            label="Stats"
            active={state.page === Stats}
            onPress={handle(toStats)}
          />
          <NavigationButton
            icon="settings"
            label="Settings"
            active={state.page === Settings}
            onPress={handle(toSettings)}
          />
        </NavigationBar>
      </SafeAreaView>;
    },
  };
};
