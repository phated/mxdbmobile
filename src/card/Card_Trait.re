type t = string;

let fromString = value => value;
let toString = value => value;

let decoder = json => Json.Decode.field("name", Json.Decode.string, json);

let component = ReasonReact.statelessComponent("Card.Trait");

let make = (~value, _children) => {
  ...component,
  render: _self => BsReactNative.(<Text> <S> {toString(value)} </S> </Text>),
};
