open BsReactNative;

module Styles = {
  open Style;

  let normalIcon = style([maxWidth(22.0 |. Pt), maxHeight(22.0 |. Pt)]);
};

let component = ReasonReact.statelessComponent("SpecialIcon");

let make = _children => {
  ...component,
  render: _self =>
    <Image
      style=Styles.normalIcon
      resizeMode=`contain
      source=(Required(Packager.require("../assets/special-big.png")))
    />,
};
