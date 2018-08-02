module Styles = {
  open BsReactNative.Style;

  let container = style([flex(1.)]);

  let title =
    style([
      color(Colors.Css.white),
      fontSize(20.0 |. Float),
      margin(8.0 |. Pt),
      fontWeight(`Bold),
      flex(1.0),
    ]);

  let icon =
    style([
      color(Colors.Css.white),
      margin(8.0 |. Pt),
      textAlignVertical(Center),
    ]);
};

type action =
  | NavigateTo(Page.t)
  | Search(string)
  | Increment(Card.t)
  | Decrement(Card.t)
  | StoreCards(CardList.t);

type state = {
  page: Page.t,
  filter: Filter.t,
  cards: CardList.t,
  deck: Deck.t,
  deckSize: int,
};

let create = () => {
  let program = ReasonTea.Program.routerProgram("Main App");

  let search = (text, self) => self.ReasonTea.Program.send(Search(text));
  let increment = (card, self) =>
    self.ReasonTea.Program.send(Increment(card));
  let decrement = (card, self) =>
    self.ReasonTea.Program.send(Decrement(card));
  let toCards = (_, self) =>
    self.ReasonTea.Program.send(NavigateTo(Cards));
  let toDeck = (_, self) => self.ReasonTea.Program.send(NavigateTo(Deck));
  let toInfo = (_, self) => self.ReasonTea.Program.send(NavigateTo(Info));

  {
    ...program,
    fromRoute: (action, route) =>
      switch (action) {
      | Init =>
        ReasonTea.Program.UpdateWithSideEffects(
          {
            page: Page.fromPath(route.path),
            filter: Filter.Empty,
            cards: CardList.empty,
            deck: Deck.empty,
            deckSize: 0,
          },
          (
            self =>
              Query.send(CardList.query, self.state.filter)
              /* |> Js.Promise.then_(Utils.tapLog) */
              |> Js.Promise.then_(
                   cards => {
                     self.send(StoreCards(cards));
                     Js.Promise.resolve(cards);
                   },
                 )
              |> ignore
          ),
        )
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
      | StoreCards(cards) => ReasonTea.Program.Update({...state, cards})
      | Increment(card) =>
        let deck = Deck.increment(state.deck, card);
        let deckSize = Deck.total(deck);
        ReasonTea.Program.Update({...state, deck, deckSize});
      | Decrement(card) =>
        let deck = Deck.decrement(state.deck, card);
        let deckSize = Deck.total(deck);
        ReasonTea.Program.Update({...state, deck, deckSize});
      | Search(filter) =>
        ReasonTea.Program.UpdateWithSideEffects(
          {...state, cards: CardList.empty, filter: FreeText(filter)},
          (
            self =>
              Query.send(CardList.query, self.state.filter)
              /* |> Js.Promise.then_(Utils.tapLog) */
              |> Js.Promise.then_(
                   cards => {
                     self.send(StoreCards(cards));
                     Js.Promise.resolve(cards);
                   },
                 )
              |> ignore
          ),
        )
      },
    view: ({state, handle}) => {
      open BsReactNative;

      let {cards, deck, filter, deckSize} = state;

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

      let toolbarRender = (~enable, ~disable, mode) =>
        switch (mode) {
        | Toolbar.Enabled => [|
            <Icon name="arrow-back" style=Styles.icon onPress=disable />,
            <SearchInput
              previous=(Filter.toString(filter))
              onBlur=disable
              onSearch=(handle(search))
            />,
          |]
        | Toolbar.Disabled => [|
            <Text style=Styles.title>
              (ReasonReact.string("MetaX Deck Builder"))
            </Text>,
            <Icon name="search" style=Styles.icon onPress=enable />,
          |]
        };

      <SafeAreaView style=Styles.container>
        <StatusBar backgroundColor=Colors.ourBlue barStyle=`lightContent />
        <Toolbar> ...toolbarRender </Toolbar>
        <CardList cards=cardsWithCount shown=(state.page == Cards)>
          ...renderCard
        </CardList>
        <Deck deck shown=(state.page == Deck)> ...renderCard </Deck>
        <Info shown=(state.page == Info) />
        <NavigationBar>
          <NavigationButton
            icon="cards"
            label="Cards"
            onPress=(handle(toCards))
          />
          <NavigationButton
            icon="deck"
            label={j|Deck ($deckSize)|j}
            onPress=(handle(toDeck))
          />
          <NavigationButton
            icon="info"
            label="Info"
            onPress=(handle(toInfo))
          />
        </NavigationBar>
      </SafeAreaView>;
    },
  };
};
