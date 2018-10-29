module GetCardsQuery = ReasonApollo.CreateQuery(CardList);

let component = ReasonReact.statelessComponent("Page.CardList");

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
    render: _self =>
      <GetCardsQuery client=Apollo.client variables={Filter.encode(filter)}>
        ...{
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
           }
      </GetCardsQuery>,
  };
};
