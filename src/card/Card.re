type t =
  | Character(Character.t)
  | Event(Event.t)
  | Battle(Battle.t);

let character = character => Character(character);
let event = event => Event(event);
let battle = battle => Battle(battle);

let sameType = (c1, c2) =>
  switch (c1, c2) {
  | (Character(_), Character(_))
  | (Event(_), Event(_))
  | (Battle(_), Battle(_)) => true
  | _ => false
  };

let getUid = card =>
  switch (card) {
  | Character({uid}) => uid
  | Event({uid}) => uid
  | Battle({uid}) => uid
  };

let rarityGet = card =>
  switch (card) {
  | Character({rarity}) => rarity
  | Event({rarity}) => rarity
  | Battle({rarity}) => rarity
  };

let numberGet = card =>
  switch (card) {
  | Character({number}) => number
  | Event({number}) => number
  | Battle({number}) => number
  };

let expansionGet = card =>
  switch (card) {
  | Character({expansion}) => expansion
  | Event({expansion}) => expansion
  | Battle({expansion}) => expansion
  };

let getTitle = card =>
  switch (card) {
  | Character({title}) => title
  | Event({title}) => title
  | Battle({title}) => title
  };

let getType = card =>
  switch (card) {
  | Character(_) => CardType.Character
  | Event(_) => CardType.Event
  | Battle(_) => CardType.Battle
  };

let getEffect = card =>
  switch (card) {
  | Character({effect}) => effect
  | Event({effect}) => effect
  | Battle({effect}) => effect
  };

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
  let increment = _ => onIncrement(card);
  let decrement = _ => onDecrement(card);
  let image = getImage(card);

  let details =
    switch (card) {
    | Character(card) => <Character card />
    | Event(card) => <Event card />
    | Battle(card) => <Battle card />
    };

  {
    ...component,
    retainedProps: {
      card,
      count,
    },
    shouldUpdate: ({oldSelf, newSelf}) =>
      oldSelf.retainedProps.card != newSelf.retainedProps.card
      || oldSelf.retainedProps.count != newSelf.retainedProps.count,
    render: _self =>
      BsReactNative.(
        <View style=Styles.container>
          <CardCounter
            onIncrement=increment onDecrement=decrement value=count>
            <CardImage image size=Thumbnail />
          </CardCounter>
          details
        </View>
      ),
  };
};
