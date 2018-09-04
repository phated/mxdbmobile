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
  | StoreDecks(array(SavedDecks.t), array(SavedDecks.t))
  | StoreCards(CardList.t);
type state = {
  page: Page.t,
  filter: Filter.t,
  cards: CardList.t,
  deck: Deck.t,
  deckSize: int,
  cardListPosition: float,
  deckPosition: float,
  savedDecks: array(SavedDecks.t),
  publicDecks: array(SavedDecks.t),
};

let create = () => {
  let program = Oolong.routerProgram("Main App");

  let getDecks = self => {
    let localDecks = SavedDecks.fetch();
    let netdeckerDecks = Netdecker.fetch();

    Repromise.all([localDecks, netdeckerDecks])
    |> Repromise.wait(decks =>
         switch (decks) {
         | [local, netdecker] =>
           let localDecks = Belt.Result.getWithDefault(local, [||]);
           let netdeckerDecks = Belt.Result.getWithDefault(netdecker, [||]);
           self.Oolong.send(StoreDecks(localDecks, netdeckerDecks));
         | _ => ()
         }
       );
  };

  let search = (text, self) => self.Oolong.send(Search(text));
  let renameDeck = (text, self) => self.Oolong.send(RenameDeck(text));
  let loadDeck = (deckName, hash, _, self) => {
    let _ = ();

    self.Oolong.send(NavigateTo(Loading));

    Deck.loadFromHash(~name=deckName, hash)
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
    switch (Deck.nameGet(self.Oolong.state.deck)) {
    | None => ()
    | Some(deckName) =>
      Deck.persist(deckName, self.Oolong.state.deck)
      |> Repromise.wait(Js.log)
    };

  {
    ...program,
    fromRoute: (action, route) =>
      switch (action) {
      | Init =>
        Oolong.UpdateWithSideEffects(
          {
            page: Page.fromPath(route.path),
            /* page: Page.SavedDecks, */
            filter: Filter.Empty,
            cards: CardList.empty,
            deck: Deck.empty,
            deckSize: 0,
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

              let _ = getDecks(self);
              ();
            }
          ),
        )
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
      | NavigateTo(page) => Oolong.Update({...state, page})
      | StoreCards(cards) =>
        Oolong.Update({...state, cards, cardListPosition: 0.0})
      | StoreDecks(savedDecks, publicDecks) =>
        Oolong.Update({...state, savedDecks, publicDecks})
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
          (
            self =>
              /* TODO: Indicator for saving deck (if this takes long/can fail) */
              switch (Deck.nameGet(self.state.deck)) {
              | None => ()
              | Some(deckName) =>
                Deck.persist(deckName, self.state.deck)
                |> Repromise.wait(Js.log)
              }
          ),
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
        Oolong.Update({...state, deck: Deck.nameSet(state.deck, deckName)})
      | ClearDeck =>
        Oolong.UpdateWithSideEffects(
          {
            ...state,
            deck: Deck.empty,
            deckSize: 0,
            page: SavedDecks,
            deckPosition: 0.0,
            publicDecks: [||],
            savedDecks: [||],
          },
          getDecks,
        )
      | PersistCardListPosition(position) =>
        Oolong.Update({...state, cardListPosition: position})
      | PersistDeckPosition(position) =>
        Oolong.Update({...state, deckPosition: position})
      | Search(filter) =>
        Oolong.UpdateWithSideEffects(
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

      let {cards, deck, filter, deckSize, page, savedDecks, publicDecks} = state;

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
              <S> {Belt.Option.getWithDefault(Deck.nameGet(deck), "")} </S>
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
