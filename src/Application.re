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
  | Search(string)
  | StoreCards(CardList.t);
type state = {
  filter: Filter.t,
  cards: CardList.t,
};

let create = () => {
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
              Query.send(CardList.query, self.state.filter)
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
        let search = Filter.toString(next.filter);
        ReasonTea.Program.Push(
          ReasonTea.Route.make(~path=[""], ~search, ~hash=""),
        );
      },
    update: (action, state) =>
      switch (action) {
      | StoreCards(cards) => ReasonTea.Program.Update({...state, cards})
      | Search(filter) =>
        ReasonTea.Program.UpdateWithSideEffects(
          {cards: CardList.empty, filter: FreeText(filter)},
          (
            self =>
              Query.send(CardList.query, self.state.filter)
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
        <SafeAreaView style=Styles.container>
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
                       <SearchInput
                         previous=(Filter.toString(self.state.filter))
                         onBlur=disable
                         onSearch
                       />,
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
        </SafeAreaView>
      ),
  };
};
