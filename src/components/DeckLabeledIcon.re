module Styles = {
  open BsReactNative.Style;

  let icon = style([color(Colors.Css.white)]);
  let label = style([fontSize(12.0->Float), color(Colors.Css.white)]);

  let deckErrorWrapper = style([width(16.0->Pt), position(Absolute)]);
  let deckError =
    style([
      color(Colors.Css.warning),
      position(Absolute),
      top(4.0->Pt),
      right((-20.0)->Pt),
    ]);
};

let component = ReasonReact.statelessComponent("DeckLabeledIcon");

let make = (~deck, _children) => {
  ...component,
  render: _self => {
    open BsReactNative;
    let deckSize = Deck.total(deck);

    let errorIcon =
      if (Deck.isValid(deck)) {
        ReasonReact.null;
      } else {
        <View style=Styles.deckErrorWrapper>
          <Icon name="warning" size=16 style=Styles.deckError />
        </View>;
      };

    <>
      <Icon name="deck" style=Styles.icon />
      errorIcon
      <Text style=Styles.label>
        <S> {Printf.sprintf("Deck (%d)", deckSize)} </S>
      </Text>
    </>;
  },
};
