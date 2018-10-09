type t = string;

let fromString = value => value;
let toString = value => value;

let decoder = json => Json.Decode.string(json);

module Styles = {
  open BsReactNative.Style;
  let title = style([fontWeight(`Bold)]);
};

let component = ReasonReact.statelessComponent("Card.Title");

let make = (~value, _children) => {
  ...component,
  render: _self =>
    <Text style=Styles.title> <S> {toString(value)} </S> </Text>,
};
