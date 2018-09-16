type state('a) =
  | Fetching
  | Stored('a);

type action('a) =
  | FetchCards
  | StoreCards('a);

type retainedProps = {filter: Filter.t};

let component =
  ReasonReact.reducerComponentWithRetainedProps("Page.CardList");

let fetchCards = (filter, self) =>
  Query.send(CardList.query, Filter.encode(filter))
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
    initialState: () => Fetching,
    reducer: (action, _state) =>
      switch (action) {
      | FetchCards =>
        ReasonReact.UpdateWithSideEffects(Fetching, fetchCards(filter))
      | StoreCards(cards) => ReasonReact.Update(Stored(cards))
      },
    didUpdate: ({oldSelf, newSelf}) => {
      let _ = ();
      if (oldSelf.retainedProps.filter !== newSelf.retainedProps.filter) {
        newSelf.send(FetchCards);
      };
    },
    didMount: self => self.send(FetchCards),
    render: self =>
      switch (self.state) {
      | Fetching => <Loading />
      | Stored(data) =>
        <PositionedList
          data
          renderItem
          position
          onPersistPosition
          keyExtractor
        />
      },
  };
};
