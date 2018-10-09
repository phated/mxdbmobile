module Styles = {
  open BsReactNative.Style;

  let container = style([flex(1.0), alignItems(Center), padding(8.0->Pt)]);
  let active = style([backgroundColor(Colors.Css.ourBlueDark)]);
};

let component = ReasonReact.statelessComponent("NavigationButton");

let make = (~active, ~onPress, renderChild) => {
  ...component,
  render: _self => {
    let containerStyle =
      if (active) {
        BsReactNative.StyleSheet.flatten([Styles.container, Styles.active]);
      } else {
        Styles.container;
      };

    <TouchableOpacity style=containerStyle onPress>
      {renderChild()}
    </TouchableOpacity>;
  },
};
