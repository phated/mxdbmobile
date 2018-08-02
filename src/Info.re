module Styles = {
  open BsReactNative.Style;

  let container = style([flex(1.0)]);
};

let component = ReasonReact.statelessComponent("InfoPage");

/* TODO: retained props */
let make = (~shown, _children) => {
  ...component,
  render: _self => {
    open BsReactNative;
    let _ = ();

    shown ?
      <View style=Styles.container>
        <Text> (ReasonReact.string("Hello info!!!")) </Text>
      </View> :
      ReasonReact.null;
  },
};
