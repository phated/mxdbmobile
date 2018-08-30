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
  | ReplaceDeck(string, Deck.t)
  | RenameDeck(string)
  | ClearDeck
  | Increment(Card.t)
  | Decrement(Card.t)
  | PersistCardListPosition(float)
  | PersistDeckPosition(float)
  | StoreDecks(array(SavedDecks.t))
  | StoreCards(CardList.t);
type state = {
  page: Page.t,
  filter: Filter.t,
  cards: CardList.t,
  deck: Deck.t,
  deckSize: int,
  deckName: option(string),
  cardListPosition: float,
  deckPosition: float,
  savedDecks: array(SavedDecks.t),
  publicDecks: array(SavedDecks.t),
};

let create = () => {
  let program = ReasonTea.Program.routerProgram("Main App");

  let search = (text, self) => self.ReasonTea.Program.send(Search(text));
  let renameDeck = (text, self) =>
    self.ReasonTea.Program.send(RenameDeck(text));
  let loadDeck = (deckName, hash, _, self) => {
    let _ = ();

    self.ReasonTea.Program.send(NavigateTo(Loading));

    Deck.loadFromHash(hash)
    |> Repromise.wait(result =>
         switch (result) {
         | Belt.Result.Ok(deck) =>
           self.ReasonTea.Program.send(ReplaceDeck(deckName, deck))
         | Belt.Result.Error(msg) => Js.log(msg)
         }
       );
  };
  let clearDeck = (_text, self) => self.ReasonTea.Program.send(ClearDeck);
  let increment = (card, self) =>
    self.ReasonTea.Program.send(Increment(card));
  let decrement = (card, self) =>
    self.ReasonTea.Program.send(Decrement(card));
  let toCards = (_, self) => self.ReasonTea.Program.send(NavigateTo(Cards));
  let toDeck = (_, self) =>
    if (Deck.isEmpty(self.ReasonTea.Program.state.deck)) {
      self.ReasonTea.Program.send(NavigateTo(SavedDecks));
    } else {
      self.ReasonTea.Program.send(NavigateTo(Deck));
    };
  let toSettings = (_, self) =>
    self.ReasonTea.Program.send(NavigateTo(Settings));
  let toStats = (_, self) => self.ReasonTea.Program.send(NavigateTo(Stats));
  let toPatreon = (_, self) =>
    self.ReasonTea.Program.send(NavigateTo(Patreon));
  let toLegal = (_, self) => self.ReasonTea.Program.send(NavigateTo(Legal));
  let persistCardListPosition = (position, self) =>
    self.ReasonTea.Program.send(PersistCardListPosition(position));
  let persistDeckPosition = (position, self) =>
    self.ReasonTea.Program.send(PersistDeckPosition(position));

  {
    ...program,
    fromRoute: (action, route) =>
      switch (action) {
      | Init =>
        let now = Js.Date.make();
        let _todayDate = Js.Date.toLocaleDateString(now);
        let _todayTime = Js.Date.toLocaleTimeString(now);
        ReasonTea.Program.UpdateWithSideEffects(
          {
            page: Page.fromPath(route.path),
            /* page: Page.SavedDecks, */
            filter: Filter.Empty,
            cards: CardList.empty,
            deck: Deck.empty,
            deckSize: 0,
            /* deckName: Some({j|Untitled - $todayDate $todayTime|j}), */
            deckName: None,
            cardListPosition: 0.0,
            deckPosition: 0.0,
            savedDecks: [||],
            publicDecks: [||],
          },
          (
            self => {
              let _ =
                Query.send(CardList.query, Filter.encode(self.state.filter))
                /* |> Js.Promise.then_(Utils.tapLog) */
                |> Js.Promise.then_(cards => {
                     self.send(StoreCards(cards));
                     Js.Promise.resolve(cards);
                   })
                |> ignore;
              let _ =
                Netdecker.fetch()
                |> Repromise.wait(result =>
                     switch (result) {
                     | Belt.Result.Ok(decks) => self.send(StoreDecks(decks))
                     | Belt.Result.Error(msg) => Js.log(msg)
                     }
                   );
              ();
            }
          ),
        );
      | Push => ReasonTea.Program.NoUpdate
      | _ => ReasonTea.Program.NoUpdate
      },
    toRoute: ({previous, next}) =>
      if (previous == next) {
        ReasonTea.Program.NoTransition;
      } else {
        let search = Filter.toString(next.filter);
        ReasonTea.Program.Push(
          ReasonTea.Route.make(
            ~path=Page.toPath(next.page),
            ~search,
            ~hash="",
          ),
        );
      },
    update: (action, state) =>
      switch (action) {
      | NavigateTo(page) => ReasonTea.Program.Update({...state, page})
      | StoreCards(cards) =>
        ReasonTea.Program.Update({...state, cards, cardListPosition: 0.0})
      | StoreDecks(publicDecks) =>
        ReasonTea.Program.Update({...state, publicDecks})
      | Increment(card) =>
        let deck = Deck.increment(state.deck, card);
        let deckSize = Deck.total(deck);
        ReasonTea.Program.Update({
          ...state,
          deck,
          deckSize,
          deckPosition: 0.0,
        });
      | Decrement(card) =>
        let deck = Deck.decrement(state.deck, card);
        let deckSize = Deck.total(deck);
        ReasonTea.Program.Update({
          ...state,
          deck,
          deckSize,
          deckPosition: 0.0,
        });
      | ReplaceDeck(deckName, deck) =>
        ReasonTea.Program.Update({
          ...state,
          deckName: Some(deckName),
          deck,
          deckSize: Deck.total(deck),
          page: Deck,
          deckPosition: 0.0,
        })
      | RenameDeck(deckName) =>
        ReasonTea.Program.Update({...state, deckName: Some(deckName)})
      | ClearDeck =>
        ReasonTea.Program.Update({
          ...state,
          deckName: None,
          deck: Deck.empty,
          deckSize: 0,
          page: SavedDecks,
          deckPosition: 0.0,
        })
      | PersistCardListPosition(position) =>
        ReasonTea.Program.Update({...state, cardListPosition: position})
      | PersistDeckPosition(position) =>
        ReasonTea.Program.Update({...state, deckPosition: position})
      | Search(filter) =>
        ReasonTea.Program.UpdateWithSideEffects(
          {...state, cards: CardList.empty, filter: FreeText(filter)},
          (
            self =>
              Query.send(CardList.query, Filter.encode(self.state.filter))
              /* |> Js.Promise.then_(Utils.tapLog) */
              |> Js.Promise.then_(cards => {
                   self.send(StoreCards(cards));
                   Js.Promise.resolve(cards);
                 })
              |> ignore
          ),
        )
      },
    view: ({state, handle}) => {
      open BsReactNative;

      let {
        cards,
        deck,
        filter,
        deckSize,
        page,
        deckName,
        savedDecks,
        publicDecks,
      } = state;

      let cardsWithCount =
        CardList.map(
          cards,
          card => {
            let count = Deck.count(deck, card);
            (card, count);
          },
        );

      let renderCard = (card, count) =>
        <Card
          card
          count
          onIncrement={handle(increment)}
          onDecrement={handle(decrement)}
        />;

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
              previous={Belt.Option.getWithDefault(deckName, "")}
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
              <S> {Belt.Option.getWithDefault(deckName, "")} </S>
            </Text>
            /* <IconButton icon="view-module" />, */
            <IconButton icon="clear-all" onPress={handle(clearDeck)} />
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

      let renderDeck = (deckName, hash) =>
        <TouchableOpacity onPress={handle(loadDeck(deckName, hash))}>
          <View style=Styles.deck>
            <Text style=Styles.deckName numberOfLines=1>
              <S> deckName </S>
            </Text>
          </View>
        </TouchableOpacity>;

      let page =
        switch (state.page) {
        | Page.Loading => <Loading />
        | Page.Cards =>
          let position = state.cardListPosition;
          let onPersistPosition = handle(persistCardListPosition);
          <CardList cards=cardsWithCount position onPersistPosition>
            ...renderCard
          </CardList>;
        | Page.Deck =>
          let position = state.deckPosition;
          let onPersistPosition = handle(persistDeckPosition);
          <Deck deck position onPersistPosition> ...renderCard </Deck>;
        | Page.SavedDecks =>
          let position = 0.0;
          let onPersistPosition = handle((_, _) => ());
          <SavedDecks savedDecks publicDecks position onPersistPosition>
            ...renderDeck
          </SavedDecks>;
        | Page.Stats => <Stats />
        | Page.Settings =>
          let data = [|
            Settings.{title: "Patreon", onPress: handle(toPatreon)},
            Settings.{title: "Legal", onPress: handle(toLegal)},
          |];
          <Settings data />;
        | Page.Patreon => <Patreon />
        | Page.Legal => <Legal />
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
