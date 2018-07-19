module Styles = {
  open BsReactNative.Style;

  let container =
    style([
      justifyContent(Center),
      alignContent(Center),
      flexDirection(Row),
      backgroundColor(Colors.Css.primary),
    ]);
};
let component = ReasonReact.statelessComponent("NavigationBar");

let make = children => {
  ...component,
  render: _self =>
    BsReactNative.(<View style=Styles.container> ...children </View>),
};
