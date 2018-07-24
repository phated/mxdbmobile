type t =
  | Character(Character.t)
  | Event(Event.t)
  | Battle(Battle.t);

let character = character => Character(character);
let event = event => Event(event);
let battle = battle => Battle(battle);

let getImage = card =>
  switch (card) {
  | Character({image}) => image
  | Event({image}) => image
  | Battle({image}) => image
  };

module Styles = {
  open BsReactNative.Style;

  let container =
    style([
      height(182.0 |. Pt),
      flexDirection(Row),
      padding(16.0 |. Pt),
    ]);
};

type retainedProps = {
  card: t,
  count: int,
};

let component = ReasonReact.statelessComponentWithRetainedProps("Card");

let make = (~card, ~count, ~onIncrement, ~onDecrement, _children) => {
  ...component,
  retainedProps: {
    card,
    count,
  },
  shouldUpdate: ({oldSelf, newSelf}) =>
    oldSelf.retainedProps.card != newSelf.retainedProps.card
    || oldSelf.retainedProps.count != newSelf.retainedProps.count,
  render: _self => {
    /* Js.log2("rendering this child", card); */

    open BsReactNative;
    let increment = _ => onIncrement(card);
    let decrement = _ => onDecrement(card);

    let image = getImage(card);
    let details =
      switch (card) {
      | Character(card) => <Character card />
      | Event(card) => <Event card />
      | Battle(card) => <Battle card />
      };
    <View style=Styles.container>
      <CardCounter onIncrement=increment onDecrement=decrement value=count>
        <CardImage image />
      </CardCounter>
      details
    </View>;
  },
};
