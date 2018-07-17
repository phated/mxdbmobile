let cardQuery = {|
    query CardList($query: CardFilter!) {
      characters: allCards(filter: { AND: [{ type: Character }, $query] }, orderBy: title_ASC) {
        uid
        title
        subtitle
        mp
        stats {
          type
          rank
        }
        effect {
          symbol
          text
        }
        image {
          thumbnail
        }
      }
      events: allCards(filter: { AND: [{ type: Event }, $query] }, orderBy: title_ASC) {
        uid
        title
        mp
        effect {
          symbol
          text
        }
        image {
          thumbnail
        }
      }
      battles: allCards(filter: { AND: [{ type: Battle }, $query] }, orderBy: title_ASC) {
        uid
        title
        mp
        stats(orderBy: type_ASC) {
          type
          rank
        }
        effect {
          symbol
          text
        }
        image {
          thumbnail
        }
      }
    }
    |};

module ListOfCards = {
  /* type state = {
       query: option(string),
       cards: CardList.t,
     };
     type action =
       | FetchCards
       | StoreCards(CardList.t); */

  let component = ReasonReact.statelessComponent("ListOfCards");

  module Styles = {
    open BsReactNative.Style;
    let container = style([flex(1.)]);

    let separator =
      style([
        flex(1.0),
        height(1.0 |. Pt),
        backgroundColor(Colors.Css.gray),
        /* marginLeft(16.0 |. Pt), */
      ]);
  };
  let itemSeparatorComponent =
    BsReactNative.FlatList.separatorComponent(_ =>
      BsReactNative.(<View style=Styles.separator />)
    );
  let renderItem =
    BsReactNative.FlatList.renderItem(bag => {
      let card: Card.t = bag.item;
      switch (card) {
      | Character({title, subtitle, mp, stats, image, effect}) =>
        <Character title subtitle mp stats image effect />
      | Event({title, mp, image, effect}) => <Event title mp image effect />
      | Battle({title, mp, stat, image, effect}) =>
        <Battle title mp stat image effect />
      };
    });

  let getItemLayout = (_data, idx) => {
    "length": 170,
    "offset": 170 * idx,
    "index": idx,
  };

  let getUid = card =>
    switch (card) {
    | Card.Character(character) => character.uid
    | Card.Event(event) => event.uid
    | Card.Battle(battle) => battle.uid
    };

  let make = (~cards, _children) => {
    ...component,
    render: self => {
      open BsReactNative;
      let sections = CardList.toArray(cards);

      <View style=Styles.container>
        <FlatList
          data=sections
          getItemLayout
          keyExtractor=((card, _idx) => getUid(card))
          renderItem
          itemSeparatorComponent
        />
      </View>;
    },
  };
};

module AppContainer = {
  let component = ReasonReact.statelessComponent("AppContainer");

  module Styles = {
    open BsReactNative.Style;
    let container = style([flex(1.)]);
  };

  let make = children => {
    ...component,
    render: _self =>
      BsReactNative.(
        <SafeAreaView style=Styles.container> ...children </SafeAreaView>
      ),
  };
};

module SearchInput = {
  module Styles = {
    open BsReactNative.Style;

    let search =
      style([
        flex(1.0),
        color(Colors.Css.white),
        fontSize(20.0 |. Float),
        paddingVertical(8.0 |. Pt),
      ]);
  };

  type state = string;
  type action =
    | UpdateText(string)
    | SubmitAndClear;

  let component = ReasonReact.reducerComponent("SearchInput");

  let noop = _text => ();
  let make = (~onSearch=noop, _children) => {
    ...component,
    initialState: () => "",
    reducer: (action, state) =>
      switch (action) {
      | UpdateText(text) => ReasonReact.Update(text)
      | SubmitAndClear =>
        ReasonReact.UpdateWithSideEffects("", (_self => onSearch(state)))
      },
    render: self =>
      BsReactNative.(
        <TextInput
          style=Styles.search
          autoFocus=true
          autoCorrect=false
          spellCheck=false
          autoCapitalize=`none
          underlineColorAndroid="transparent"
          placeholder="Search"
          placeholderTextColor=Colors.gray
          onChangeText=(text => self.send(UpdateText(text)))
          onSubmitEditing=(_ => self.send(SubmitAndClear))
        />
      ),
  };
};

module Toolbar = {
  module Styles = {
    open BsReactNative.Style;

    let container =
      style([
        flexDirection(Row),
        padding(8.0 |. Pt),
        height(60.0 |. Pt),
        backgroundColor(Colors.Css.primary),
      ]);

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

  type searchMode =
    | Enabled
    | Disabled;

  type action =
    | SearchMode(searchMode);

  type state = {search: searchMode};

  let component = ReasonReact.reducerComponent("Toolbar");

  let make = (~onSearch, _children) => {
    ...component,
    initialState: () => {search: Disabled},
    reducer: (action, _state) =>
      switch (action) {
      | SearchMode(mode) => ReasonReact.Update({search: mode})
      },
    render: self =>
      BsReactNative.(
        switch (self.state.search) {
        | Enabled =>
          let disableSearch = () => self.send(SearchMode(Disabled));
          let performSearchAndHide = text => {
            disableSearch();
            onSearch(text);
          };
          <View style=Styles.container>
            <Icon name="arrow-back" style=Styles.icon onPress=disableSearch />
            <SearchInput onSearch=performSearchAndHide />
          </View>;
        | Disabled =>
          let enableSearch = () => self.send(SearchMode(Enabled));

          <View style=Styles.container>
            <Text style=Styles.title>
              (ReasonReact.string("MetaX Deck Builder"))
            </Text>
            <Icon name="search" style=Styles.icon onPress=enableSearch />
          </View>;
        }
      ),
  };
};

module NavigationButton = {
  module Styles = {
    open BsReactNative.Style;

    let container =
      style([flex(1.0), alignItems(Center), padding(8.0 |. Pt)]);

    let icon = style([color(Colors.Css.white)]);
    let label = style([fontSize(12.0 |. Float), color(Colors.Css.white)]);
  };

  let component = ReasonReact.statelessComponent("NavigationButton");

  let make = (~icon, ~label, _children) => {
    ...component,
    render: _self =>
      BsReactNative.(
        <View style=Styles.container>
          <Icon name=icon style=Styles.icon />
          <Text style=Styles.label> (ReasonReact.string(label)) </Text>
        </View>
      ),
  };
};

module NavigationBar = {
  module Styles = {
    open BsReactNative.Style;

    let container =
      style([
        justifyContent(Center),
        alignContent(Center),
        flexDirection(Row),
        backgroundColor(Colors.Css.primary),
      ]);
  };
  let component = ReasonReact.statelessComponent("NavigationBar");

  let make = children => {
    ...component,
    render: _self =>
      BsReactNative.(<View style=Styles.container> ...children </View>),
  };
};

type action =
  | Search(string)
  | StoreCards(CardList.t);
type state = {
  query: option(string),
  cards: CardList.t,
};

let application = () => {
  let program = ReasonTea.Program.routerProgram("Main App");
  {
    ...program,
    fromRoute: (action, route) =>
      switch (route.path) {
      | [""] =>
        ReasonTea.Program.Update({query: None, cards: CardList.empty})
      | _ => ReasonTea.Program.NoUpdate
      },
    toRoute: ({previous, next}) =>
      if (previous == next) {
        ReasonTea.Program.NoTransition;
      } else {
        let search =
          switch (next.query) {
          | Some(query) => query
          | None => ""
          };
        ReasonTea.Program.Push(
          ReasonTea.Route.make(~path=[""], ~search, ~hash=""),
        );
      },
    update: (action, state) =>
      switch (action) {
      | StoreCards(cards) => ReasonTea.Program.Update({...state, cards})
      | Search(query) =>
        ReasonTea.Program.UpdateWithSideEffects(
          {...state, query: Some(query)},
          (
            self => {
              let _ = ();
              /* didMount: self => self.send(FetchCards),
                 reducer: (action, state) =>
                   switch (action) { */
              /* | FetchCards => */
              /* ReasonReact.SideEffects
                 ( */
              Query.send(cardQuery, Filter.create(self.state.query))
              |> Js.Promise.then_(Utils.tapLog)
              |> Js.Promise.then_(cards => {
                   self.send(StoreCards(cards));
                   Js.Promise.resolve(cards);
                 })
              |> ignore;
            }
          ),
        )
      },
    view: self =>
      BsReactNative.(
        <AppContainer>
          <Toolbar onSearch=(query => self.send(Search(query))) />
          <ListOfCards cards=self.state.cards />
          <NavigationBar>
            <NavigationButton icon="cards" label="Cards" />
            <NavigationButton icon="deck" label="Deck" />
            <NavigationButton icon="info" label="Info" />
          </NavigationBar>
        </AppContainer>
      ),
  };
};

module ApplicationContainer = {
  type state = ReasonReact.reactElement;
  type action =
    | Render(ReasonReact.reactElement);

  let component = ReasonReact.reducerComponent("ApplicationContainer");

  let make = (~application, _children) => {
    ...component,
    initialState: () => ReasonReact.null,
    didMount: self =>
      ReasonTea.Program.startup(application(), view =>
        self.send(Render(view))
      ),
    reducer: (action, state) =>
      switch (action) {
      | Render(view) => ReasonReact.Update(view)
      },
    render: self => self.state,
  };
};

let app = _ => <ApplicationContainer application />;
