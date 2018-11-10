module Styles = {
  open BsReactNative.Style;

  let container = style([flex(1.0)]);
};
/*
 type state =
   | Fetching
   | Completed(Card.t);

 type action =
   | FetchInfo
   | StoreInfo(Card.t); */

let component = ReasonReact.statelessComponent("Page.IndividualCard");

module CardQuery = Apollo.CreateQuery(Card);
let make = (~client, ~uid, renderChildren) => {
  /*
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
     |> ignore; */
  ...component,
  /* initialState: () => Fetching,
     reducer: (action, _state) =>
       switch (action) {
       | FetchInfo => ReasonReact.UpdateWithSideEffects(Fetching, fetchInfo)
       | StoreInfo(card) => ReasonReact.Update(Completed(card))
       },
     didMount: self => self.send(FetchInfo), */
  render: _self => {
    open BsReactNative;

    let _ = ();
    <CardQuery client variables={Filter.encode(UID(uid))}>
      ...{
           ({result}) =>
             switch (result) {
             | Loading => <Loading />
             | Error(error) =>
               <View>
                 <Text> {ReasonReact.string(error##message)} </Text>
               </View>
             | Data(card) =>
               <ScrollView style=Styles.container>
                 {renderChildren(card)}
               </ScrollView>
             }
         }
    </CardQuery>;
  },
};
