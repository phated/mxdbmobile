let cardQuery = {|
    query CardList($title: String, $subtitle: String, $trait: String, $mp: Int, $effect: String, $symbol: CardSymbol) {
      characters: allCards(filter: {
        AND: [
          { type: Character },
          { OR: [
              { title_contains: $title },
              { subtitle_contains: $subtitle },
              { trait: { name_contains: $trait } },
              { mp: $mp },
              { effect: { text_contains: $effect } },
            ]
          },
          { effect: { symbol: $symbol } }
        ]
      }, orderBy: title_ASC) {
        uid
        title
        subtitle
        trait {
          name
        }
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
      events: allCards(filter: {
        AND: [
          { type: Event },
          { OR: [
              { title_contains: $title },
              { mp: $mp },
              { effect: { text_contains: $effect } }
            ]
          },
          { effect: { symbol: $symbol } }
        ]
      }, orderBy: title_ASC) {
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
      battles: allCards(filter: {
        AND: [
          { type: Battle },
          { OR: [
              { title_contains: $title },
              { mp: $mp },
              { effect: { text_contains: $effect } }
            ]
          },
          { effect: { symbol: $symbol } }
        ]
      }, orderBy: title_ASC) {
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
    | Submit
    | SubmitAndClear;

  let component = ReasonReact.reducerComponent("SearchInput");

  let noop = _text => ();
  let make = (~onSearch=noop, ~onBlur=noop, _children) => {
    ...component,
    initialState: () => "",
    reducer: (action, state) =>
      switch (action) {
      | UpdateText(text) => ReasonReact.Update(text)
      | SubmitAndClear =>
        ReasonReact.UpdateWithSideEffects("", (_self => onSearch(state)))
      | Submit => ReasonReact.SideEffects((self => onSearch(self.state)))
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
          onBlur
          blurOnSubmit=true
          value=self.state
          onChangeText=(text => self.send(UpdateText(text)))
          onSubmitEditing=(_ => self.send(Submit))
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
  };

  type mode =
    | Enabled
    | Disabled;

  type action =
    | ChangeMode(mode);

  let component = ReasonReact.reducerComponent("Toolbar");

  let make = renderChildren => {
    let enable = (_event, self) =>
      self.ReasonReact.send(ChangeMode(Enabled));
    let disable = (_event, self) =>
      self.ReasonReact.send(ChangeMode(Disabled));

    {
      ...component,
      initialState: () => Disabled,
      reducer: (action, _state) =>
        switch (action) {
        | ChangeMode(mode) => ReasonReact.Update(mode)
        },
      render: self => {
        let children =
          renderChildren(
            ~enable=self.handle(enable),
            ~disable=self.handle(disable),
            self.state,
          );
        BsReactNative.(<View style=Styles.container> ...children </View>);
      },
    };
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
  filter: Filter.t,
  cards: CardList.t,
};
module Styles = {
  open BsReactNative.Style;

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

let application = () => {
  let program = ReasonTea.Program.routerProgram("Main App");
  {
    ...program,
    fromRoute: (action, route) =>
      switch (action, route.path) {
      | (Init, [""]) =>
        ReasonTea.Program.UpdateWithSideEffects(
          {filter: Filter.Empty, cards: CardList.empty},
          (
            self =>
              Query.send(cardQuery, self.state.filter)
              |> Js.Promise.then_(Utils.tapLog)
              |> Js.Promise.then_(cards => {
                   self.send(StoreCards(cards));
                   Js.Promise.resolve(cards);
                 })
              |> ignore
          ),
        )
      | (Push, _) => ReasonTea.Program.NoUpdate
      | _ => ReasonTea.Program.NoUpdate
      },
    toRoute: ({previous, next}) =>
      if (previous == next) {
        ReasonTea.Program.NoTransition;
      } else {
        let search =
          switch (next.filter) {
          | FreeText(filter) => filter
          | Empty => ""
          };
        ReasonTea.Program.Push(
          ReasonTea.Route.make(~path=[""], ~search, ~hash=""),
        );
      },
    update: (action, state) =>
      switch (action) {
      | StoreCards(cards) => ReasonTea.Program.Update({...state, cards})
      | Search(filter) =>
        ReasonTea.Program.UpdateWithSideEffects(
          {...state, filter: FreeText(filter)},
          (
            self =>
              Query.send(cardQuery, self.state.filter)
              |> Js.Promise.then_(Utils.tapLog)
              |> Js.Promise.then_(cards => {
                   self.send(StoreCards(cards));
                   Js.Promise.resolve(cards);
                 })
              |> ignore
          ),
        )
      },
    view: self =>
      BsReactNative.(
        <AppContainer>
          <Toolbar>
            ...(
                 (~enable, ~disable, mode) => {
                   let onSearch = text => self.send(Search(text));

                   switch (mode) {
                   | Enabled => [|
                       <Icon
                         name="arrow-back"
                         style=Styles.icon
                         onPress=disable
                       />,
                       <SearchInput onBlur=disable onSearch />,
                     |]
                   | Disabled => [|
                       <Text style=Styles.title>
                         (ReasonReact.string("MetaX Deck Builder"))
                       </Text>,
                       <Icon name="search" style=Styles.icon onPress=enable />,
                     |]
                   };
                 }
               )
          </Toolbar>
          <CardList cards=self.state.cards />
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
