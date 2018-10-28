module Styles = {
  open BsReactNative.Style;

  let icon = style([color(Colors.Css.white)]);
  let label = style([fontSize(12.0->Float), color(Colors.Css.white)]);
};

let component = ReasonReact.statelessComponent("LabeledIcon");

let make = (~label, ~icon, _children) => {
  ...component,
  render: _self =>
    <>
      <Icon name=icon style=Styles.icon />
      <BsReactNative.Text style=Styles.label>
        <S> label </S>
      </BsReactNative.Text>
    </>,
};
