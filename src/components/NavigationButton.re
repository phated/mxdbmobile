module Styles = {
  open BsReactNative.Style;

  let container = style([flex(1.0), alignItems(Center), padding(8.0->Pt)]);
  let active = style([backgroundColor(Colors.Css.ourBlueDark)]);
};

let component = ReasonReact.statelessComponent("NavigationButton");

/* TODO: I'm thinking that this shouldn't contain the link */
let make = (~active, ~path, renderChild) => {
  ...component,
  render: _self => {
    open BsReactNative;

    let _ = ();

    let containerStyle =
      if (active) {
        StyleSheet.flatten([Styles.container, Styles.active]);
      } else {
        Styles.container;
      };

    <Link style=containerStyle path> {renderChild()} </Link>;
  },
};
