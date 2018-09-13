type t =
  | Character(Character.t)
  | Event(Event.t)
  | Battle(Battle.t);

let character = character => Character(character);
let event = event => Event(event);
let battle = battle => Battle(battle);

/* TODO: Character/Battle/Event need card type so we don't accidentally decode to the wrong type */
let decoder = json =>
  json
  |> Json.Decode.oneOf([
       Json.Decode.map(character, Character.decoder),
       Json.Decode.map(battle, Battle.decoder),
       Json.Decode.map(event, Event.decoder),
     ]);

/* TODO: Once we have card type, this can likely be simplified */
let sameType = (c1, c2) =>
  switch (c1, c2) {
  | (Character(_), Character(_))
  | (Event(_), Event(_))
  | (Battle(_), Battle(_)) => true
  | _ => false
  };

let uidGet = card =>
  switch (card) {
  | Character(character) => Character.uidGet(character)
  | Event(event) => Event.uidGet(event)
  | Battle(battle) => Battle.uidGet(battle)
  };

let rarityGet = card =>
  switch (card) {
  | Character(character) => Character.rarityGet(character)
  | Event(event) => Event.rarityGet(event)
  | Battle(battle) => Battle.rarityGet(battle)
  };

let numberGet = card =>
  switch (card) {
  | Character(character) => Character.numberGet(character)
  | Event(event) => Event.numberGet(event)
  | Battle(battle) => Battle.numberGet(battle)
  };

let expansionGet = card =>
  switch (card) {
  | Character(character) => Character.expansionGet(character)
  | Event(event) => Event.expansionGet(event)
  | Battle(battle) => Battle.expansionGet(battle)
  };

let titleGet = card =>
  switch (card) {
  | Character(character) => Character.titleGet(character)
  | Event(event) => Event.titleGet(event)
  | Battle(battle) => Battle.titleGet(battle)
  };

/* TODO: this should be attached to the card records */
let typeGet = card =>
  switch (card) {
  | Character(_) => CardType.Character
  | Event(_) => CardType.Event
  | Battle(_) => CardType.Battle
  };

let effectGet = card =>
  switch (card) {
  | Character(character) => Character.effectGet(character)
  | Event(event) => Event.effectGet(event)
  | Battle(battle) => Battle.effectGet(battle)
  };

let imageGet = card =>
  switch (card) {
  | Character(character) => Character.imageGet(character)
  | Event(event) => Event.imageGet(event)
  | Battle(battle) => Battle.imageGet(battle)
  };

let toGroupIdentifier = card =>
  switch (card) {
  | Character(character) => Character.toGroupIdentifier(character)
  | Event(event) => Event.toGroupIdentifier(event)
  | Battle(battle) => Battle.toGroupIdentifier(battle)
  };

module Styles = {
  open BsReactNative.Style;

  let container =
    style([height(182.0->Pt), flexDirection(Row), padding(16.0->Pt)]);
};

type retainedProps = {
  card: t,
  count: int,
};

let component = ReasonReact.statelessComponentWithRetainedProps("Card");

let make = (~card, ~count, ~onIncrement, ~onDecrement, _children) => {
  let increment = _ => onIncrement(card);
  let decrement = _ => onDecrement(card);
  let image = imageGet(card);

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
          <CardCounter onIncrement=increment onDecrement=decrement value=count>
            <CardImage image size=Thumbnail />
          </CardCounter>
          details
        </View>
      ),
  };
};

type card = t;
module Compare =
  Belt.Id.MakeComparable({
    type t = card;

    let cmp =
      Compare.concat([
        Compare.by(card => typeGet(card)->CardType.toInt),
        Compare.by(card =>
          switch (card) {
          | Battle(card) => Battle.statGet(card)->BattleStat.rankGet
          | _ => 0
          }
        ),
        Compare.by(card =>
          switch (card) {
          | Battle(card) => Battle.statGet(card)->BattleStat.toInt
          | _ => 0
          }
        ),
        Compare.by(card => titleGet(card)),
        Compare.by(card => effectGet(card)->Effect.getText),
        Compare.by(card => uidGet(card)),
      ]);
  });
