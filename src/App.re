open BsReactNative;

module Routes = {
  type route =
    | CardList
    | DeckList;
};

include RerouteNative.ReRoute.CreateNavigation(Routes);

module CardEffect = {
  let component = ReasonReact.statelessComponent("CardEffect");

  module Styles = {
    open Style;
    let container =
      style([
        flex(1.),
        justifyContent(FlexEnd),
        flexDirection(Row),
        alignItems(Center),
        marginTop(Auto),
      ]);

    let effectWithoutSymbol = style([flex(1.)]);
    let effectWithSymbol =
      style([
        flex(1.),
        paddingLeft(Pt(4.)),
        marginLeft(Pt(4.)),
        borderLeftWidth(2.),
        borderLeftColor(String("#d3d3d3")),
        borderStyle(Solid),
      ]);
  };

  let make = (~symbol, ~effect, _children) => {
    let symbolImage =
      switch (symbol) {
      | `NONE => ReasonReact.null
      | `ATTACK => <AttackIcon />
      | `DEFEND => <DefendIcon />
      | `CONSTANT => <ConstantIcon />
      | `PLAY => <PlayIcon />
      | `PUSH => <PushIcon />
      };

    let effectStyle =
      switch (symbol) {
      | `NONE => Styles.effectWithoutSymbol
      | _ => Styles.effectWithSymbol
      };

    let c = {
      ...component,
      render: _self =>
        <View style=Styles.container>
          symbolImage
          <View style=effectStyle>
            <Text> (ReasonReact.string(effect)) </Text>
          </View>
        </View>,
    };

    c;
  };
};

module CardDetails = {
  let component = ReasonReact.statelessComponent("CardDetails");

  module Styles = {
    open Style;
    let container =
      style([flex(1.), flexDirection(Column), paddingLeft(Pt(8.))]);

    let title = style([fontWeight(`Bold)]);
  };

  let make = (~title, ~subtitle, ~effect, ~symbol, _children) => {
    ...component,
    render: _self =>
      <View style=Styles.container>
        <Text style=Styles.title> (ReasonReact.string(title)) </Text>
        <Text> (ReasonReact.string(subtitle)) </Text>
        <CardEffect effect symbol />
      </View>,
  };
};

module CardListItem = {
  let component = ReasonReact.statelessComponent("CardListItem");

  module Styles = {
    open Style;

    let cardListItem =
      style([
        flex(1.),
        flexDirection(Row),
        marginLeft(Pt(8.)),
        marginRight(Pt(8.)),
        marginTop(Pt(4.)),
        marginBottom(Pt(4.)),
        padding(Pt(4.)),
        borderStyle(Solid),
        borderWidth(1.),
        borderColor(String("#d3d3d3")),
        borderRadius(3.),
      ]);

    let thumbnail = style([height(Pt(100.)), width(Pt(72.))]);
  };

  let make = (~title, ~subtitle, ~thumbnail, ~effect, ~symbol, _children) => {
    ...component,
    render: _self => {
      let leftElement = <CardImage src=thumbnail style=Styles.thumbnail />;
      let centerElement = <CardDetails title subtitle effect symbol />;

      <MaterialListItem leftElement centerElement divider=true />;
    },
  };
};

module ListOfCards = {
  type image = {. "thumbnail": string};
  type effect = {
    .
    "symbol": [ | `ATTACK | `CONSTANT | `DEFEND | `NONE | `PLAY | `PUSH],
    "text": option(string),
  };
  type card = {
    .
    "uid": string,
    "title": string,
    "subtitle": option(string),
    "effect": option(effect),
    "image": option(image),
  };

  module CardQuery = [%graphql
    {|
    {
      characters: allCards(filter: { type: Character }, orderBy: title_ASC) {
        uid
        title
        subtitle
        effect {
          symbol
          text
        }
        image {
          thumbnail
        }
      }
      events: allCards(filter: { type: Event }, orderBy: title_ASC) {
        uid
        title
        subtitle
        effect {
          symbol
          text
        }
        image {
          thumbnail
        }
      }
      battles: allCards(filter: { type: Battle }, orderBy: title_ASC) {
        uid
        title
        subtitle
        effect {
          symbol
          text
        }
        image {
          thumbnail
        }
      }
    }
    |}
  ];

  type cardSections = {
    .
    "characters": array(card),
    "events": array(card),
    "battles": array(card),
  };

  type state = {
    characters: option(array(card)),
    events: option(array(card)),
    battles: option(array(card)),
  };
  type action =
    | FetchCards
    | StoreCards(cardSections);

  let component = ReasonReact.reducerComponent("ListOfCards");

  module Styles = {
    open Style;
    let container =
      style([
        flex(1.),
        /* justifyContent(Center), */
        /* alignItems(Center), */
        /* backgroundColor(String("tomato")), */
      ]);
  };

  let renderSectionHeader =
    SectionList.renderAccessoryView(({section}) => {
      let title =
        switch (section.key) {
        | Some(key) => key
        | None => ""
        };
      <MaterialSubheader text=title />;
    });

  let renderItem =
    SectionList.renderItem(({item}) => {
      let thumbnail =
        switch (item##image) {
        | Some(image) => image##thumbnail
        | None => ""
        };
      let title = item##title;
      let subtitle =
        switch (item##subtitle) {
        | Some(subtitle) => subtitle
        | None => ""
        };
      let effect =
        switch (item##effect) {
        | Some(effect) =>
          switch (effect##text) {
          | Some(text) => text
          | None => ""
          }
        | None => ""
        };
      let symbol =
        switch (item##effect) {
        | Some(effect) => effect##symbol
        | None => `NONE
        };
      <CardListItem title subtitle thumbnail effect symbol />;
    });

  let maybeCards = cards =>
    switch (Belt.Array.length(cards)) {
    | 0 => None
    | _ => Some(cards)
    };

  let make = _children => {
    ...component,
    initialState: () => {characters: None, events: None, battles: None},
    didMount: self => self.send(FetchCards),
    reducer: (action, state) =>
      switch (action) {
      | StoreCards(cards) =>
        ReasonReact.Update({
          characters: maybeCards(cards##characters),
          events: maybeCards(cards##events),
          battles: maybeCards(cards##battles),
        })
      | FetchCards =>
        ReasonReact.SideEffects(
          (
            self =>
              Query.send(CardQuery.make())
              |> Js.Promise.then_(Utils.tapLog)
              |> Js.Promise.then_(cards => {
                   self.send(StoreCards(cards));
                   Js.Promise.resolve(cards);
                 })
              |> ignore
          ),
        )
      },
    render: self => {
      let sections =
        [|
          Belt.Option.map(self.state.characters, data =>
            SectionList.section(~key="Characters", ~data, ())
          ),
          Belt.Option.map(self.state.events, data =>
            SectionList.section(~key="Events", ~data, ())
          ),
          Belt.Option.map(self.state.battles, data =>
            SectionList.section(~key="Battle Cards", ~data, ())
          ),
        |]
        |. Belt.Array.keep(Belt.Option.isSome)
        |. Belt.Array.map(Belt.Option.getExn)
        |. SectionList.sections;

      <View style=Styles.container>
        <SectionList
          sections
          stickySectionHeadersEnabled=true
          keyExtractor=((item, int) => item##uid)
          renderItem
          renderSectionHeader
        />
      </View>;
    },
  };
};

module CardList = {
  let component = ReasonReact.statelessComponent("CardList");

  let tabItem = ({isActive}: TabNavigator.tabItemProps) =>
    <TabNavigator.TabBar.Item
      label="Cards"
      style=(Style.style([Style.color(String(isActive ? "blue" : "gray"))]))
    />;

  let make = (~navigation, _children) => {
    ...component,
    render: _self =>
      <TabNavigator.Screen navigation tabItem>
        ...(
             () =>
               if (false) {
                 <GridOfCards />;
               } else {
                 <ListOfCards />;
               }
           )
      </TabNavigator.Screen>,
  };
};

module DeckList = {
  let component = ReasonReact.statelessComponent("DeckList");

  module Styles = {
    open Style;
    let container = style([flex(1.)]);
  };

  let tabItem = ({isActive}: TabNavigator.tabItemProps) =>
    <TabNavigator.TabBar.Item
      label="Deck (0)"
      style=(Style.style([Style.color(String(isActive ? "blue" : "gray"))]))
    />;

  let make = (~navigation, _children) => {
    ...component,
    render: _self =>
      <TabNavigator.Screen navigation tabItem>
        ...(() => <Text> (ReasonReact.string("Deck")) </Text>)
      </TabNavigator.Screen>,
  };
};

module AppContainer = {
  let component = ReasonReact.statelessComponent("AppContainer");

  module Styles = {
    open Style;
    let container = style([flex(1.)]);
  };

  let make = children => {
    ...component,
    render: _self =>
      <MaterialThemeProvider>
        <SafeAreaView style=Styles.container> ...children </SafeAreaView>
      </MaterialThemeProvider>,
  };
};

let app = () =>
  <AppContainer>
    <MaterialToolbar
      centerElement="MetaX Deck Builder"
      rightElement="view-list"
      search=true
    />
    <TabNavigator
      initialRoute=Routes.CardList
      routes=[|Routes.CardList, Routes.DeckList|]>
      ...(
           (~navigation) =>
             switch (navigation.currentRoute) {
             | Routes.CardList => <CardList navigation />
             | Routes.DeckList => <DeckList navigation />
             }
         )
    </TabNavigator>
  </AppContainer>;
