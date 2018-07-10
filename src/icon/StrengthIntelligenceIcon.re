open BsReactNative;

module Styles = {
  open Style;

  let normalIcon = style([maxWidth(38.5 |. Pt), maxHeight(27.5 |. Pt)]);
};

let component = ReasonReact.statelessComponent("StrengthIntelligenceIcon");

let make = _children => {
  ...component,
  render: _self =>
    <Image
      style=Styles.normalIcon
      resizeMode=`contain
      source=(
        Required(Packager.require("../assets/strength-intelligence-big.png"))
      )
    />,
};
