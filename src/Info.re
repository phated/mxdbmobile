module Styles = {
  open BsReactNative.Style;

  let container = style([flex(1.0)]);
};

let component = ReasonReact.statelessComponent("InfoPage");

let make = _children => {
  ...component,
  shouldUpdate: _ => false,
  render: _self => {
    open BsReactNative;
    let _ = ();

    <View style=Styles.container>
      <Text> (ReasonReact.string("Hello info!!!")) </Text>
    </View>;
  },
};
