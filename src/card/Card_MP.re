type t =
  | MP(int);

let fromInt = value => MP(value);

let decoder = json => json |> Json.Decode.map(fromInt, Json.Decode.int);

module Styles = {
  open BsReactNative.Style;

  let container = style([width(45.0->Pt), fontSize(14.0->Float)]);

  let sign = style([fontSize(11.0->Float)]);
};

let component = ReasonReact.statelessComponent("MP");

let make = (~value, _children) => {
  ...component,
  render: _self => {
    open BsReactNative;
    let MP(intValue) = value;

    let sign =
      if (intValue >= 0) {
        <Text style=Styles.sign> <S> "+" </S> </Text>;
      } else {
        <Text style=Styles.sign> <S> "-" </S> </Text>;
      };

    <Text style=Styles.container>
      <S> "MP: " </S>
      sign
      <S> {string_of_int(abs(intValue))} </S>
    </Text>;
  },
};
