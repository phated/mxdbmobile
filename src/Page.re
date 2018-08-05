type t =
  | Cards
  | Deck
  | Info;

let fromPath = path =>
  switch (path) {
  | [""] => Cards
  | ["deck"] => Deck
  | ["info"] => Info
  | _ => failwith("Invalid route")
  };

let toPath = page =>
  switch (page) {
  | Cards => [""]
  | Deck => ["deck"]
  | Info => ["info"]
  };

type state = {
  cardListPosition: float,
  deckPosition: float,
};
type action =
  | PersistCardListPosition(float)
  | PersistDeckPosition(float);

let noop = _ => ();

let component = ReasonReact.reducerComponent("Page");

let make = (~current, renderPage) => {
  let persistCardListPosition = (position, self) =>
    self.ReasonReact.send(PersistCardListPosition(position));
  let persistDeckPosition = (position, self) =>
    self.ReasonReact.send(PersistDeckPosition(position));

  {
    ...component,
    initialState: () => {cardListPosition: 0.0, deckPosition: 0.0},
    reducer: (action, state) =>
      switch (action) {
      | PersistCardListPosition(position) =>
        ReasonReact.Update({...state, cardListPosition: position})
      | PersistDeckPosition(position) =>
        ReasonReact.Update({...state, deckPosition: position})
      },
    render: self =>
      switch (current) {
      | Cards =>
        renderPage(
          ~position=self.state.cardListPosition,
          ~onPersistPosition=self.handle(persistCardListPosition),
          current,
        )
      | Deck =>
        renderPage(
          ~position=self.state.deckPosition,
          ~onPersistPosition=self.handle(persistDeckPosition),
          current,
        )
      | Info => renderPage(~position=0.0, ~onPersistPosition=noop, current)
      },
  };
};
