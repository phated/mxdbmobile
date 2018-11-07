module GetCardsQuery = ReasonApollo.CreateQuery(CardList);

type action =
  | LoadData;
type state =
  | QuickRender
  | DataRender;

let component = ReasonReact.reducerComponent("Page.CardList");

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
    initialState: () => QuickRender,
    reducer: (action, _state) =>
      switch (action) {
      | LoadData => ReasonReact.Update(DataRender)
      },
    didMount: self => {
      let id = Utils.nextTick(() => self.send(LoadData));
      self.onUnmount(() => Utils.clearTick(id));
    },
    render: self =>
      switch (self.state) {
      | QuickRender => <Loading />
      | DataRender =>
        <GetCardsQuery client=Apollo.client variables={Filter.encode(filter)}>
          ...(
               ({result}) =>
                 switch (result) {
                 | Loading => <Loading />
                 | Error(error) =>
                   BsReactNative.(
                     <View>
                       <Text> {ReasonReact.string(error##message)} </Text>
                     </View>
                   )
                 | Data(cards) =>
                   let data =
                     CardList.map(cards, card =>
                       PositionedList.Item({key: card, value: (), size: 183})
                     );
                   <PositionedList
                     data
                     renderItem
                     position
                     onPersistPosition
                     keyExtractor
                   />;
                 }
             )
        </GetCardsQuery>
      },
  };
};
