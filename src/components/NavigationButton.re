module Styles = {
  open BsReactNative.Style;

  let container = style([flex(1.0), alignItems(Center), padding(8.0->Pt)]);
  let active = style([backgroundColor(Colors.Css.ourBlueDark)]);

  let icon = style([color(Colors.Css.white)]);
  let label = style([fontSize(12.0->Float), color(Colors.Css.white)]);
};

let component = ReasonReact.statelessComponent("NavigationButton");

let make = (~icon, ~label, ~active, ~onPress, _children) => {
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

    <TouchableOpacity style=containerStyle onPress>
      <Icon name=icon style=Styles.icon />
      <Text style=Styles.label> <S> label </S> </Text>
    </TouchableOpacity>;
  },
};
