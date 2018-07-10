open BsReactNative;

module Styles = {
  open Style;

  let normalIcon = style([maxWidth(54.0 |. Pt), maxHeight(27.5 |. Pt)]);
};

let component =
  ReasonReact.statelessComponent("StrengthIntelligenceSpecialIcon");

let make = _children => {
  ...component,
  render: _self =>
    <Image
      style=Styles.normalIcon
      resizeMode=`contain
      source=(
        Required(
          Packager.require("../assets/strength-intelligence-special-big.png"),
        )
      )
    />,
};
