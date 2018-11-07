[%%debugger.chrome];

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

  let individualCard =
    style([
      flex(1.0),
      paddingHorizontal(16.0->Pt),
      paddingVertical(8.0->Pt),
    ]);

  let individualCardImage = style([alignItems(Center)]);
  let individualCardDetails = style([flex(1.0), paddingTop(8.0->Pt)]);
};

type action =
  | Search(string)
  | DeckLoaded(Deck.t)
  | DeckRestored(Deck.t)
  | RenameDeck(string)
  | ClearDeck
  | Increment(Card.t)
  | Decrement(Card.t)
  | PersistCardListPosition(float)
  | PersistDeckPosition(float)
  | PersistSavedDeckPosition(float)
  | Error
  | GoBack
  | StorePersistedDeck(Deck.t);
type state = {
  page: Page.t,
  filter: Filter.t,
  deck: Deck.t,
  cardListPosition: float,
  deckPosition: float,
  savedDeckPosition: float,
};

let create = () => {
  let serializeState = state => {
    Js.log(state);
    let path = Page.toPath(state.page);
    let filter = Filter.toString(state.filter);
    let hash =
      Belt.Option.getWithDefault(
        Deck.asMap(state.deck)->Deck.Hash.encode,
        "",
      );
    let deckName = Deck.nameGet(state.deck);
    let search =
      Printf.sprintf(
        "filter=%s&cardPos=%f&deckPos=%f&savedDeckPos=%f",
        filter,
        state.cardListPosition,
        state.deckPosition,
        state.savedDeckPosition,
      );
    let searchWithDeckName =
      Belt.Option.mapWithDefault(deckName, search, deckName =>
        search ++ "deckName=" ++ deckName
      );
    Oolong.Url.make(path, searchWithDeckName, hash);
  };

  let program = Oolong.routerProgram(~serializeState, "Main App");

  let search = (text, self) => self.Oolong.send(Search(text));
  let renameDeck = (text, self) => self.Oolong.send(RenameDeck(text));
  let loadDeck = (~key=?, deckName, hash, _, self) =>
    self.Oolong.send(DeckLoaded(Hashed(hash)));
  /* Deck.loadFromHash(~key?, ~name=deckName, hash)
     |> Repromise.wait(result =>
          switch (result) {
          | Belt.Result.Ok(deck) => self.Oolong.send(DeckLoaded(deck))
          | Belt.Result.Error(msg) => Js.log(msg)
          }
        ); */
  let clearDeck = (_text, self) => self.Oolong.send(ClearDeck);
  let increment = (card, _, self) => self.Oolong.send(Increment(card));
  let decrement = (card, _, self) => self.Oolong.send(Decrement(card));

  let persistCardListPosition = (position, self) =>
    self.Oolong.send(PersistCardListPosition(position));
  let persistDeckPosition = (position, self) =>
    self.Oolong.send(PersistDeckPosition(position));
  let persistSavedDeckPosition = (position, self) =>
    self.Oolong.send(PersistSavedDeckPosition(position));

  let saveDeck = self =>
    /* TODO: Indicator for saving deck (if this takes long/can fail) */
    PrivateDeck.persist(self.Oolong.state.deck)
    |> Repromise.wait(result =>
         switch (result) {
         | Belt.Result.Ok(deck) =>
           if (Deck.isEmpty(deck)) {
             self.Oolong.send(ClearDeck);
           } else {
             self.Oolong.send(StorePersistedDeck(deck));
           }
         | Belt.Result.Error(_) => self.Oolong.send(Error)
         }
       );

  {
    ...program,
    subscriptions: _state => [
      self =>
        BsReactNative.BackHandler.addEventListener("hardwareBackPress", () =>
          if (Router.router->Oolong.Router.canGo(-1)) {
            self.send(GoBack);
            true;
          } else {
            false;
          }
        ),
    ],
    init: (path, search, hash) => {
      let params = QueryString.parse(search);
      let deckName = params->QueryString.get("deckName");
      let cardListPosition =
        params->QueryString.getFloat(~default=0.0, "cardPos");
      let deckPosition =
        params->QueryString.getFloat(~default=0.0, "deckPos");
      let savedDeckPosition =
        params->QueryString.getFloat(~default=0.0, "savedDeckPos");
      let filter =
        params
        ->QueryString.getString(~default="", "filter")
        ->Filter.fromString;
      if (hash === "") {
        Oolong.State({
          page: Page.fromPath(path),
          deck: Deck.empty,
          filter,
          cardListPosition,
          deckPosition,
          savedDeckPosition,
        });
      } else {
        Oolong.StateWithSideEffects(
          {
            page: Page.fromPath(path),
            deck: Deck.empty,
            filter,
            cardListPosition,
            deckPosition,
            savedDeckPosition,
          },
          self => self.Oolong.send(DeckRestored(Hashed(hash))),
          /* Deck.loadFromHash(~name=?deckName, hash)
             |> Repromise.wait(result =>
                  switch (result) {
                  | Belt.Result.Ok(deck) =>
                    self.Oolong.send(DeckRestored(deck))
                  | Belt.Result.Error(msg) => Js.log(msg)
                  }
                ), */
        );
      };
    },
    fromRoute: (action, state) =>
      switch (action) {
      | Push(path, _search, _hash)
      | Replace(path, _search, _hash) =>
        Oolong.State({...state, page: Page.fromPath(path)})
      | Pop(path, _search, _hash) =>
        let page = Page.fromPath(path);
        /* TODO: check this logic */
        page === SavedDecks && state.page === Deck ?
          Oolong.State({...state, page, deck: Deck.empty}) :
          Oolong.State({...state, page});
      },
    toRoute: (action, state) =>
      switch (action) {
      | Error =>
        Js.log("something went terribly wrong");
        Oolong.Replace(state);
      | StorePersistedDeck(deck) => Oolong.Replace({...state, deck})
      | Increment(card) =>
        let deck = Deck.increment(state.deck, card);
        Oolong.ReplaceWithSideEffects(
          {...state, deck, deckPosition: 0.0},
          saveDeck,
        );
      | Decrement(card) =>
        let deck = Deck.decrement(state.deck, card);
        Oolong.ReplaceWithSideEffects(
          /* TODO: move all the deckPosition resetting into the Page.Deck component */
          {...state, deck, deckPosition: 0.0},
          saveDeck,
        );
      | DeckLoaded(deck) =>
        Oolong.Push({...state, page: Deck, deck, deckPosition: 0.0})
      | DeckRestored(deck) =>
        Oolong.Replace({...state, deck, deckPosition: 0.0})
      | RenameDeck(deckName) =>
        Oolong.ReplaceWithSideEffects(
          {...state, deck: Deck.nameSet(state.deck, deckName)},
          saveDeck,
        )
      | ClearDeck =>
        /* TODO: This REPLACE is overwriting the "/deck" url which causes a "double back" scenario */
        /* I might be able to solve it by combining the Deck/SavedDeck stuff and maybe creating a HashedDeck type */
        Oolong.Replace({
          ...state,
          page: state.page === Deck ? SavedDecks : state.page,
          deck: Deck.empty,
          deckPosition: 0.0,
        })
      | PersistCardListPosition(cardListPosition) =>
        Oolong.Replace({...state, cardListPosition})
      | PersistDeckPosition(deckPosition) =>
        Oolong.Replace({...state, deckPosition})
      | PersistSavedDeckPosition(savedDeckPosition) =>
        Oolong.Replace({...state, savedDeckPosition})
      | Search(filter) => Oolong.Push({...state, filter: FreeText(filter)})
      | GoBack => Oolong.Pop
      },
    render: ({state, handle}) => {
      open BsReactNative;

      let {deck, filter, page} = state;

      let deckListRender = (card, count) => {
        let renderDetails = details =>
          <>
            <Card.Image image={Card.imageGet(card)} size=Thumbnail>
              <CardCounter
                onIncrement={handle(increment(card))}
                onDecrement={handle(decrement(card))}
                value=count
              />
            </Card.Image>
            details
          </>;

        <Card card> ...renderDetails </Card>;
      };

      let cardListRender = card => {
        let count = Deck.count(deck, card);
        let uid = Card.uidGet(card);

        let renderDetails = details =>
          <>
            <Link path={Page.Path.individualCard(uid)}>
              <Card.Image image={Card.imageGet(card)} size=Thumbnail>
                <CardCounter
                  onIncrement={handle(increment(card))}
                  onDecrement={handle(decrement(card))}
                  value=count
                />
              </Card.Image>
            </Link>
            details
          </>;

        <Card card> ...renderDetails </Card>;
      };

      let cardRender = card => {
        let count = Deck.count(deck, card);

        let renderDetails = details =>
          <>
            <View style=Styles.individualCardImage>
              <Card.Image image={Card.imageGet(card)} size=Medium>
                <CardCounter
                  onIncrement={handle(increment(card))}
                  onDecrement={handle(decrement(card))}
                  value=count
                />
              </Card.Image>
            </View>
            <View style=Styles.individualCardDetails> details </View>
          </>;

        <Card card style=Styles.individualCard> ...renderDetails </Card>;
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
          let deckName = Printf.sprintf("%s by %s", name, author);
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
        | Page.IndividualCard(uid) =>
          <Page.IndividualCard uid> ...cardRender </Page.IndividualCard>
        | Page.Deck =>
          let position = state.deckPosition;
          let onPersistPosition = handle(persistDeckPosition);
          <Page.Deck deck position onPersistPosition>
            ...deckListRender
          </Page.Deck>;
        | Page.SavedDecks =>
          let position = state.savedDeckPosition;
          let onPersistPosition = handle(persistSavedDeckPosition);
          <Page.SavedDecks position onPersistPosition>
            ...renderDeck
          </Page.SavedDecks>;
        | Page.Stats => <Page.Stats deck />
        | Page.Settings =>
          /* TODO: This is gross, probably want render children */
          let data = [|
            Page.Settings.{title: "Patreon", path: Page.Path.patreon},
            Page.Settings.{title: "Legal", path: Page.Path.legal},
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
          <NavigationButton active={state.page === Cards}>
            ...{
                 style =>
                   <Link style path=Page.Path.cards>
                     <LabeledIcon icon="cards" label="Cards" />
                   </Link>
               }
          </NavigationButton>
          <NavigationButton
            active={state.page === SavedDecks || state.page === Deck}>
            ...{
                 style =>
                   if (Deck.isEmpty(deck)) {
                     <Link style path=Page.Path.savedDecks>
                       <LabeledIcon icon="view-list" label="Decks" />
                     </Link>;
                   } else if (Deck.isWaiting(deck)) {
                     <Link style path=Page.Path.deck>
                       <LabeledIcon icon="loop" label="Loading" />
                     </Link>;
                   } else {
                     <Link style path=Page.Path.deck>
                       <DeckLabeledIcon deck />
                     </Link>;
                   }
               }
          </NavigationButton>
          <NavigationButton active={state.page === Stats}>
            ...{
                 style =>
                   <Link style path=Page.Path.stats>
                     <LabeledIcon icon="chart-bar" label="Stats" />
                   </Link>
               }
          </NavigationButton>
          <NavigationButton active={state.page === Settings}>
            ...{
                 style =>
                   <Link style path=Page.Path.settings>
                     <LabeledIcon icon="settings" label="Settings" />
                   </Link>
               }
          </NavigationButton>
        </NavigationBar>
      </SafeAreaView>;
    },
  };
};
