type t = int;

let fromInt = value => value;

let decoder = json => Json.Decode.int(json);

module Styles = {
  open BsReactNative.Style;

  let container = style([width(45.0->Pt), fontSize(14.0->Float)]);

  let sign = style([fontSize(11.0->Float)]);
};

let component = ReasonReact.statelessComponent("MP");

let make = (~value, _children) => {
  ...component,
  render: _self => {
    let sign =
      if (value >= 0) {
        <Text style=Styles.sign> <S> "+" </S> </Text>;
      } else {
        <Text style=Styles.sign> <S> "-" </S> </Text>;
      };

    <Text style=Styles.container>
      <S> "MP: " </S>
      sign
      <S> {string_of_int(abs(value))} </S>
    </Text>;
  },
};
