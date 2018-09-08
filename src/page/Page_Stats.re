module Styles = {
  open BsReactNative.Style;

  let container =
    style([flex(1.0), alignItems(Center), justifyContent(Center)]);
};

let component = ReasonReact.statelessComponent("Page.Stats");

/* TODO: retained props */
let make = _children => {
  ...component,
  render: _self => {
    open BsReactNative;
    let _ = ();

    <View style=Styles.container> <Text> <S> "Stats Pane" </S> </Text> </View>;
  },
};
