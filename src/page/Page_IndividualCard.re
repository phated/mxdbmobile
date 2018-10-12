module Styles = {
  open BsReactNative.Style;

  let container = style([flex(1.0)]);
};

type state =
  | Fetching
  | Completed(Card.t);

type action =
  | FetchInfo
  | StoreInfo(Card.t);

let component = ReasonReact.reducerComponent("Page.IndividualCard");

let make = (~uid, renderChildren) => {
  let fetchInfo = self =>
    Query.send(
      Card.query,
      Filter.encode(UID(uid)),
      Json.Decode.field("Card", Card.decoder),
    )
    /* |> Js.Promise.then_(Utils.tapLog) */
    |> Js.Promise.then_(card => {
         self.ReasonReact.send(StoreInfo(card));
         Js.Promise.resolve(card);
       })
    |> ignore;

  {
    ...component,
    initialState: () => Fetching,
    reducer: (action, _state) =>
      switch (action) {
      | FetchInfo => ReasonReact.UpdateWithSideEffects(Fetching, fetchInfo)
      | StoreInfo(card) => ReasonReact.Update(Completed(card))
      },
    didMount: self => self.send(FetchInfo),
    render: self => {
      open BsReactNative;

      let _ = ();

      switch (self.state) {
      | Fetching => <Loading />
      | Completed(card) =>
        <ScrollView style=Styles.container>
          {renderChildren(card)}
        </ScrollView>
      };
    },
  };
};
