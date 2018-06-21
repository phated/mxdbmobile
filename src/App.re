open BsReactNative;

module Routes = {
  type route =
    | CardList
    | DeckList;
};

include RerouteNative.ReRoute.CreateNavigation(Routes);

exception Graphql_error(string);

let sendQuery = q =>
  Fetch.(
    fetchWithInit(
      "https://api.graph.cool/simple/v1/metaxdb",
      RequestInit.make(
        ~method_=Post,
        ~body=
          Js.Dict.fromList([
            ("query", Js.Json.string(q##query)),
            ("variables", q##variables),
          ])
          |> Js.Json.object_
          |> Js.Json.stringify
          |> BodyInit.make,
        ~credentials=Include,
        ~headers=HeadersInit.make({"Content-Type": "application/json"}),
        (),
      ),
    )
    |> Js.Promise.then_(resp =>
         if (Response.ok(resp)) {
           Response.json(resp)
           |> Js.Promise.then_(data =>
                switch (Js.Json.decodeObject(data)) {
                | Some(obj) =>
                  Js.Dict.unsafeGet(obj, "data")
                  |> q##parse
                  |> Js.Promise.resolve
                | None =>
                  Js.Promise.reject(
                    Graphql_error("Response is not an object"),
                  )
                }
              );
         } else {
           Js.Promise.reject(
             Graphql_error("Request failed: " ++ Response.statusText(resp)),
           );
         }
       )
  );

let tapLog = (res) => {
  Js.log(res);
  Js.Promise.resolve(res);
};

module CardImage = {
  let component = ReasonReact.statelessComponent("CardImage");

  module Styles = {
    open Style;

    let container = style([
      /* flex(1.), */
    ]);
    let thumbnail = style([
      height(Pt(100.)),
      width(Pt(72.)),
    ]);
  }

  let make = (~thumbnail, _children) => {
    ...component,
    render: (_self) => {
      <View style={Styles.container}>
        <Image style={Styles.thumbnail} source=Image.URI(Image.imageURISource(~uri=thumbnail, ())) />
      </View>
    }
  };
};

module CardEffect = {
  let component = ReasonReact.statelessComponent("CardEffect");

  module Styles = {
    open Style;
    let container = style([
      flex(1.),
      justifyContent(FlexEnd),
      flexDirection(Row),
      alignItems(Center),
      marginTop(Auto),
    ]);

    let normalIcon = style([
      maxWidth(Pt(15.)),
    ]);
    let weirdIcon = style([
      maxWidth(Pt(20.)),
    ]);

    let effectWithoutSymbol = style([
      flex(1.),
    ]);
    let effectWithSymbol = style([
      flex(1.),
      paddingLeft(Pt(4.)),
      marginLeft(Pt(4.)),
      borderLeftWidth(2.),
      borderLeftColor(String("#d3d3d3")),
      borderStyle(Solid),
    ]);
  };

  let make = (~symbol, ~effect, _children) => {
    let symbolImage = switch symbol {
    | `NONE => <View />
    | `ATTACK => <Image style={Styles.normalIcon} resizeMode=`contain source=(Required(Packager.require("./assets/attack.png"))) />
    | `DEFEND => <Image style={Styles.normalIcon} resizeMode=`contain source=(Required(Packager.require("./assets/defend.png"))) />
    | `CONSTANT => <Image style={Styles.weirdIcon} resizeMode=`contain source=(Required(Packager.require("./assets/constant.png"))) />
    | `PLAY => <Image style={Styles.normalIcon} resizeMode=`contain source=(Required(Packager.require("./assets/play.png"))) />
    | `PUSH => <Image style={Styles.normalIcon} resizeMode=`contain source=(Required(Packager.require("./assets/push.png"))) />
    };

    let effectStyle = switch symbol {
    | `NONE => Styles.effectWithoutSymbol
    | _ => Styles.effectWithSymbol
    };

    let c = {
      ...component,
      render: (_self) => {
        <View style={Styles.container}>
          (symbolImage)
          <View style={effectStyle}><Text>(ReasonReact.string(effect))</Text></View>
        </View>
      }
    };

    c;
  };
};

module CardDetails = {
  let component = ReasonReact.statelessComponent("CardDetails");

  module Styles = {
    open Style;
    let container = style([
      flex(1.),
      flexDirection(Column),
      paddingLeft(Pt(8.)),
    ]);

    let title = style([
      fontWeight(`Bold)
    ]);

    let subtitle = style([
      /* fontStyle(Italic) */
    ]);
  };

  let make = (~title, ~subtitle, ~effect, ~symbol, _children) => {
    ...component,
    render: (_self) => {
      <View style={Styles.container}>
        <Text style={Styles.title}>(ReasonReact.string(title))</Text>
        <Text style={Styles.subtitle}>(ReasonReact.string(subtitle))</Text>
        <CardEffect effect symbol />
      </View>
    }
  };
};

module CardListItem = {
  let component = ReasonReact.statelessComponent("CardListItem");

  module Styles = {
    open Style;

    let cardListItem = style([
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
      borderRadius(3.)
    ]);
  };

  let make = (
    ~title,
    ~subtitle,
    ~thumbnail,
    ~effect,
    ~symbol,
    _children) => {
    ...component,
    render: (_self) => {
      <View style={Styles.cardListItem}>
        <CardImage thumbnail />
        <CardDetails title subtitle effect symbol />
      </View>
    },
  }
};

module ListOfCards = {
  type image = {.
    "thumbnail": string,
  };
  type effect = {.
    "symbol":  [ `ATTACK | `CONSTANT | `DEFEND | `NONE | `PLAY | `PUSH ],
    "text": option(string),
  };
  type card = {.
    "uid": string,
    "title": string,
    "subtitle": option(string),
    "effect": option(effect),
    "image": option(image),
  };

  module CardQuery = [%graphql {|
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
    |}];

  type cardSections = {.
    "characters": array(card),
    "events": array(card),
    "battles": array(card),
  };

  type state = {
    characters: array(card),
    events: array(card),
    battles: array(card),
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

  let renderSectionHeader = SectionList.renderAccessoryView(({ section }) => {
    let title = switch (section.key) {
    | Some(key) => key
    | None => ""
    };
    <Text>(ReasonReact.string(title))</Text>
  });

  let renderItem = SectionList.renderItem(({ item }) => {
    let thumbnail = switch (item##image) {
    | Some(image) => image##thumbnail
    | None => ""
    };
    let title = item##title;
    let subtitle = switch (item##subtitle) {
    | Some(subtitle) => subtitle
    | None => ""
    };
    let effect = switch (item##effect) {
    | Some(effect) => switch(effect##text) {
      | Some(text) => text
      | None => ""
      }
    | None => ""
    };
    let symbol = switch(item##effect) {
    | Some(effect) => effect##symbol
    | None => `NONE
    };
    <CardListItem title subtitle thumbnail effect symbol />
  })

  let make = (_children) => {
    ...component,
    initialState: () => { characters: [||], events: [||], battles: [||] },
    didMount: (self) =>
      self.send(FetchCards),
    reducer: (action, state) =>
      switch (action) {
      | StoreCards(cards) => ReasonReact.Update({
          characters: cards##characters,
          events: cards##events,
          battles: cards##battles,
        })
      | FetchCards => ReasonReact.SideEffects((self) => {
          sendQuery(CardQuery.make())
            |> Js.Promise.then_(tapLog)
            |> Js.Promise.then_(cards => {
              self.send(StoreCards(cards));
              Js.Promise.resolve(cards);
            })
            |> ignore;
        })
      },
    render: (self) => {
      let sections = SectionList.sections([|
        SectionList.section(~key="Characters", ~data=self.state.characters, ()),
        SectionList.section(~key="Events", ~data=self.state.events, ()),
        SectionList.section(~key="Battle Cards", ~data=self.state.battles, ()),
      |]);

      <View style=Styles.container>
        <SectionList
          sections
          keyExtractor=((item, int) => item##uid)
          renderItem
          renderSectionHeader
        />
      </View>
    }
  }
}

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
        ...(() => <ListOfCards />)
      </TabNavigator.Screen>,
  };
};

module DeckList = {
  let component = ReasonReact.statelessComponent("DeckList");

  module Styles = {
    open Style;
    let container = style([
      flex(1.),
      /* justifyContent(Center), */
      /* alignItems(Center), */
      /* backgroundColor(String("tomato")), */
    ]);
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
        ...(
             () =>
               <NBContent>
                  <Text>(ReasonReact.string("Deck"))</Text>
               </NBContent>
           )
      </TabNavigator.Screen>,
  };
};

let app = () => {
  <NBContainer>
    <NBHeader searchBar=true rounded=true>
      <NBItem>
        <NBIcon name="search" />
        <NBInput placeholder="Search" />
      </NBItem>
      <NBButton transparent=true>
        <Text>(ReasonReact.string("Search"))</Text>
      </NBButton>
    </NBHeader>

    <TabNavigator
      initialRoute=Routes.CardList routes=[|Routes.CardList, Routes.DeckList|]>
      ...(
          (~navigation) =>
            switch (navigation.currentRoute) {
            | Routes.CardList => <CardList navigation />
            | Routes.DeckList => <DeckList navigation />
            }
        )
    </TabNavigator>
  </NBContainer>
};
