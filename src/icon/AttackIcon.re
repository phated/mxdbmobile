open BsReactNative;

module Styles = {
  open Style;

  let normalIcon = style([maxWidth(Pt(15.))]);
};

let component = ReasonReact.statelessComponent("AttackIcon");

let make = _children => {
  ...component,
  render: _self =>
    <Image
      style=Styles.normalIcon
      resizeMode=`contain
      source=(Required(Packager.require("../assets/attack.png")))
    />,
};
