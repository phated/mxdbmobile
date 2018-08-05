module Styles = {
  open BsReactNative.Style;

  let container = style([flex(1.0)]);
};

let component = ReasonReact.statelessComponent("InfoPage");

/* TODO: retained props */
let make = _children => {
  ...component,
  render: _self => {
    open BsReactNative;
    let _ = ();

    <View style=Styles.container>
      <Text> (ReasonReact.string("Hello info!!!")) </Text>
    </View>;
  },
};
