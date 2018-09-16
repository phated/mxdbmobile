type t = string;

let fromString = value => value;
let toString = value => value;

let decoder = json => Json.Decode.string(json);

module Styles = {
  open BsReactNative.Style;
  let subtitle = style([fontWeight(`Bold)]);
};

let component = ReasonReact.statelessComponent("Card.Subtitle");

let make = (~value, _children) => {
  ...component,
  render: _self =>
    BsReactNative.(
      <Text style=Styles.subtitle> <S> "-" {toString(value)} </S> </Text>
    ),
};
