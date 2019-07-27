module Styles = {
  open BsReactNative.Style;

  let header =
    style([
      height(40.0->Pt),
      backgroundColor(Colors.Css.ourBlueDark),
      alignItems(Center),
      justifyContent(Center),
    ]);
  let headerText =
    style([
      color(Colors.Css.white),
      fontSize(20.0->Float),
      fontWeight(`_800),
    ]);
};

let component = ReasonReact.statelessComponent("Page.Deck");

let make = (~deck, ~position, ~onPersistPosition, renderChild) => {
  let toHeader = card =>
    switch (card) {
    | Card.Character(_) =>
      let characterCount = Deck.countCharacters(deck);
      let title = Printf.sprintf("Characters (%d)", characterCount);
      PositionedList.Header(title);
    | Card.Event(_) =>
      let eventCount = Deck.countEvents(deck);
      let title = Printf.sprintf("Events (%d)", eventCount);
      PositionedList.Header(title);
    | Card.Battle(_) =>
      let battleCount = Deck.countBattles(deck);
      let title = Printf.sprintf("Battle Cards (%d)", battleCount);
      PositionedList.Header(title);
    };

  let keyExtractor = (item, _idx) =>
    switch (item) {
    | PositionedList.Header(title) => title
    | PositionedList.Item({key}) => Card.uidGet(key)->Card.UID.toString
    };

  let init = ((card, count)) => [|
    toHeader(card),
    PositionedList.Item({key: card, value: count, size: 183}),
  |];

  let mapper = ((prevCard, _), (nextCard, count)) =>
    Card.isTypeEqual(prevCard, nextCard)
      ? [|PositionedList.Item({key: nextCard, value: count, size: 183})|]
      : [|
        toHeader(nextCard),
        PositionedList.Item({key: nextCard, value: count, size: 183}),
      |];

  let cards = Deck.flatMap2(deck, init, mapper);
  /*
   I'm not too sure why my Header items cause the list to jump when restoring position
   but if I render all elements up front, it doesn't jump.
   This shouldn't be an issue because decks aren't super long.

   TODO: Maybe add the `initialScrollIndex` to positioned list
    */
  let initialNumToRender = Belt.Array.length(cards);

  let renderHeader = title =>
    BsReactNative.(
      <View style=Styles.header>
        <Text style=Styles.headerText> <S> title </S> </Text>
      </View>
    );
  let renderItem = (card, count) => renderChild(card, count);

  {
    ...component,
    render: _self =>
      <PositionedList
        data=cards
        initialNumToRender
        renderItem
        renderHeader
        position
        onPersistPosition
        keyExtractor
      />,
  };
};
