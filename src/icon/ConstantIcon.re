open BsReactNative;

module Styles = {
  open Style;

  let weirdIcon = style([maxWidth(Pt(20.))]);
};

let component = ReasonReact.statelessComponent("ConstantIcon");

let make = _children => {
  ...component,
  render: _self =>
    <Image
      style=Styles.weirdIcon
      resizeMode=`contain
      source=(Required(Packager.require("../assets/constant.png")))
    />,
};
