module Styles = {
  open BsReactNative.Style;

  let normalIcon = style([width(22.0 |. Pt), height(22.0 |. Pt)]);
};

let component = ReasonReact.statelessComponent("IntelligenceIcon");

let make = _children => {
  ...component,
  render: _self =>
    BsReactNative.(
      <Image
        style=Styles.normalIcon
        resizeMode=`cover
        source=(Required(Packager.require("../assets/intelligence-big.png")))
      />
    ),
};
