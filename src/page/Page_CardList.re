type activeState('a) =
  | Fetching
  | Stored('a);

type action('a) =
  | FetchCards
  | StoreCards('a);

type state('a) = {
  activeState: activeState('a),
  position: float,
};

type retainedProps = {filter: Filter.t};

let component =
  ReasonReact.reducerComponentWithRetainedProps("Page.CardList");

let fetchCards = (filter, self) =>
  Query.send(CardList.query, Filter.encode(filter), CardList.decode)
  /* |> Js.Promise.then_(Utils.tapLog) */
  |> Js.Promise.then_(cards => {
       let data =
         CardList.map(cards, card =>
           PositionedList.Item({key: card, value: (), size: 183})
         );
       self.ReasonReact.send(StoreCards(data));
       Js.Promise.resolve(data);
     })
  |> ignore;

let make = (~filter, ~position, ~onPersistPosition, renderChild) => {
  let renderItem = (card, _) => renderChild(card);
  /* TODO: move this back into PositionedList? */
  let keyExtractor = (item, _idx) =>
    switch (item) {
    | PositionedList.Header(title) => title
    | PositionedList.Item({key}) => Card.uidGet(key)->Card.UID.toString
    };

  {
    ...component,
    retainedProps: {
      filter: filter,
    },
    initialState: () => {activeState: Fetching, position},
    reducer: (action, state) =>
      switch (action) {
      | FetchCards =>
        ReasonReact.UpdateWithSideEffects(
          {...state, activeState: Fetching},
          fetchCards(filter),
        )
      | StoreCards(cards) =>
        ReasonReact.Update({...state, activeState: Stored(cards)})
      },
    didUpdate: ({oldSelf, newSelf}) => {
      let _ = ();
      if (oldSelf.retainedProps.filter !== newSelf.retainedProps.filter) {
        newSelf.send(FetchCards);
      };
    },
    didMount: self => self.send(FetchCards),
    render: self =>
      switch (self.state.activeState) {
      | Fetching => <Loading />
      | Stored(data) =>
        <PositionedList
          data
          renderItem
          position={self.state.position}
          onPersistPosition
          keyExtractor
        />
      },
  };
};
