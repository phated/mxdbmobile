module Styles = {
  open BsReactNative.Style;

  let container =
    style([flex(1.0), alignItems(Center), padding(8.0 |. Pt)]);

  let icon = style([color(Colors.Css.white)]);
  let label = style([fontSize(12.0 |. Float), color(Colors.Css.white)]);
};

let component = ReasonReact.statelessComponent("NavigationButton");

let make = (~icon, ~label, ~onPress, _children) => {
  ...component,
  render: _self =>
    BsReactNative.(
      <TouchableOpacity style=Styles.container onPress>
        <Icon name=icon style=Styles.icon />
        <Text style=Styles.label> (ReasonReact.string(label)) </Text>
      </TouchableOpacity>
    ),
};
