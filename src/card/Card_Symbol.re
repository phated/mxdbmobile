type t =
  | Play
  | Push
  | Constant
  | Attack
  | Defend
  | None;

let fromString = symbol =>
  switch (symbol) {
  | "PLAY" => Play
  | "PUSH" => Push
  | "CONSTANT" => Constant
  | "ATTACK" => Attack
  | "DEFEND" => Defend
  | "NONE" => None
  | _ => failwith("Invalid symbol.")
  };

let decoder = json => json |> Json.Decode.map(fromString, Json.Decode.string);

let isSymbol = text =>
  /* TODO: Not sure if I like this */
  switch (fromString(text)) {
  | Play
  | Push
  | Constant
  | Attack
  | Defend
  | None => true
  | exception (Failure(_)) => false
  };

let hasSymbol =
  fun
  | None => false
  | _ => true;

module Styles = {
  open BsReactNative.Style;

  let attack = style([color(Colors.MetaX.Css.attack)]);
  let defend = style([color(Colors.MetaX.Css.defend)]);
  let constant = style([color(Colors.MetaX.Css.constant)]);
  let play = style([color(Colors.MetaX.Css.play)]);
  let push = style([color(Colors.MetaX.Css.push)]);
};

let component = ReasonReact.statelessComponent("Card.Symbol");

let make = (~value, _children) => {
  ...component,
  render: _self =>
    switch (value) {
    | Attack => <Icon name="attack" style=Styles.attack size=16 />
    | Defend => <Icon name="defend" style=Styles.defend size=16 />
    | Constant => <Icon name="constant" style=Styles.constant size=14 />
    | Play => <Icon name="play" style=Styles.play size=16 />
    | Push => <Icon name="push" style=Styles.push size=16 />
    | None => ReasonReact.null
    },
};
