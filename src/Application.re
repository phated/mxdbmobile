module Styles = {
  open BsReactNative.Style;

  /* backgroundColor is set to avoid showing the splash logo during app use */
  let container = style([flex(1.), backgroundColor(Colors.Css.white)]);

  let title =
    style([
      color(Colors.Css.white),
      fontSize(20.0 |. Float),
      margin(8.0 |. Pt),
      fontWeight(`Bold),
      flex(1.0),
    ]);
};

type action =
  | NavigateTo(Page.t)
  | Search(string)
  | RenameDeck(string)
  | Increment(Card.t)
  | Decrement(Card.t)
  | PersistCardListPosition(float)
  | PersistDeckPosition(float)
  | StoreCards(CardList.t);
type state = {
  page: Page.t,
  filter: Filter.t,
  cards: CardList.t,
  deck: Deck.t,
  deckSize: int,
  deckName: string,
  cardListPosition: float,
  deckPosition: float,
};

let create = () => {
  let program = ReasonTea.Program.routerProgram("Main App");

  let search = (text, self) => self.ReasonTea.Program.send(Search(text));
  let renameDeck = (text, self) =>
    self.ReasonTea.Program.send(RenameDeck(text));
  let increment = (card, self) =>
    self.ReasonTea.Program.send(Increment(card));
  let decrement = (card, self) =>
    self.ReasonTea.Program.send(Decrement(card));
  let toCards = (_, self) => self.ReasonTea.Program.send(NavigateTo(Cards));
  let toDeck = (_, self) => self.ReasonTea.Program.send(NavigateTo(Deck));
  let toSettings = (_, self) =>
    self.ReasonTea.Program.send(NavigateTo(Settings));
  let toStats = (_, self) => self.ReasonTea.Program.send(NavigateTo(Stats));
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
        let todayDate = Js.Date.toLocaleDateString(now);
        let todayTime = Js.Date.toLocaleTimeString(now);
        ReasonTea.Program.UpdateWithSideEffects(
          {
            /* page: Page.fromPath(route.path), */
            page: Page.Settings,
            filter: Filter.Empty,
            cards: CardList.empty,
            deck: Deck.empty,
            deckSize: 0,
            deckName: {j|Untitled - $todayDate $todayTime|j},
            cardListPosition: 0.0,
            deckPosition: 0.0,
          },
          (
            self =>
              Query.send(CardList.query, self.state.filter)
              /* |> Js.Promise.then_(Utils.tapLog) */
              |> Js.Promise.then_(cards => {
                   self.send(StoreCards(cards));
                   Js.Promise.resolve(cards);
                 })
              |> ignore
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
      | Increment(card) =>
        let deck = Deck.increment(state.deck, card);
        let deckSize = Deck.total(deck);
        ReasonTea.Program.Update({...state, deck, deckSize});
      | Decrement(card) =>
        let deck = Deck.decrement(state.deck, card);
        let deckSize = Deck.total(deck);
        ReasonTea.Program.Update({...state, deck, deckSize});
      | RenameDeck(deckName) =>
        ReasonTea.Program.Update({...state, deckName})
      | PersistCardListPosition(position) =>
        ReasonTea.Program.Update({...state, cardListPosition: position})
      | PersistDeckPosition(position) =>
        ReasonTea.Program.Update({...state, deckPosition: position})
      | Search(filter) =>
        ReasonTea.Program.UpdateWithSideEffects(
          {...state, cards: CardList.empty, filter: FreeText(filter)},
          (
            self =>
              Query.send(CardList.query, self.state.filter)
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

      let {cards, deck, filter, deckSize, page, deckName} = state;

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
          onIncrement=(handle(increment))
          onDecrement=(handle(decrement))
        />;

      let cardListToolbarRender = (~enable, ~disable, mode) =>
        switch (mode) {
        | Toolbar.Enabled => [|
            <IconButton icon="arrow-back" onPress=disable />,
            <ToolbarInput
              placeholder="Search"
              previous=(Filter.toString(filter))
              onBlur=disable
              onSubmit=(handle(search))
            />,
          |]
        | Toolbar.Disabled => [|
            <Text style=Styles.title>
              (ReasonReact.string("MetaX Deck Builder"))
            </Text>,
            /* <IconButton icon="view-module" />, */
            <IconButton icon="search" onPress=enable />,
          |]
        };
      let deckListToolbarRender = (~enable, ~disable, mode) =>
        switch (mode) {
        | Toolbar.Enabled => [|
            <IconButton icon="arrow-back" onPress=disable />,
            <ToolbarInput
              placeholder="Deck Name"
              previous=deckName
              onBlur=disable
              onSubmit=(handle(renameDeck))
            />,
          |]
        | Toolbar.Disabled => [|
            <Text
              ellipsizeMode=`tail
              numberOfLines=1
              style=Styles.title
              onPress=enable>
              <Icon name="edit" size=16 />
              (ReasonReact.string(deckName))
            </Text>,
            /* <IconButton icon="view-module" />, */
            <IconButton icon="clear-all" />,
          |]
        };

      let settingsToolbarRender = (~enable, ~disable, _mode) => [|
        <Text style=Styles.title> (ReasonReact.string("Settings")) </Text>,
      |];

      let emptyToolbarRender = (~enable, ~disable, _mode) => [|
        <Text style=Styles.title>
          (ReasonReact.string("MetaX Deck Builder"))
        </Text>,
      |];

      let toolbarRender =
        switch (page) {
        | Cards => cardListToolbarRender
        | Deck => deckListToolbarRender
        | Settings => settingsToolbarRender
        | _ => emptyToolbarRender
        };

      let page =
        switch (state.page) {
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
        | Page.Stats => <Stats />
        | Page.Settings => <Settings />
        };

      <SafeAreaView style=Styles.container>
        <StatusBar backgroundColor=Colors.ourBlueDark />
        <Toolbar> ...toolbarRender </Toolbar>
        page
        <NavigationBar>
          <NavigationButton
            icon="cards"
            label="Cards"
            active=(state.page === Cards)
            onPress=(handle(toCards))
          />
          <NavigationButton
            icon="deck"
            label={j|Deck ($deckSize)|j}
            active=(state.page === Deck)
            onPress=(handle(toDeck))
          />
          <NavigationButton
            icon="chart-bar"
            label="Stats"
            active=(state.page === Stats)
            onPress=(handle(toStats))
          />
          <NavigationButton
            icon="settings"
            label="Settings"
            active=(state.page === Settings)
            onPress=(handle(toSettings))
          />
        </NavigationBar>
      </SafeAreaView>;
    },
  };
};
