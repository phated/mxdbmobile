open BsReactNative;

let component = ReasonReact.statelessComponent("CardImage");

module Styles = {
  open Style;

  let container = style([flex(1.)]);
};

let make = (~src, ~style, _children) => {
  ...component,
  render: _self =>
    <View style=Styles.container>
      <Image style source=(Image.URI(Image.imageURISource(~uri=src, ()))) />
    </View>,
};
