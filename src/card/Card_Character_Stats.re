type t = array(Card_Stat.t);

let decoder = json => json |> Json.Decode.array(Card_Stat.decoder);

module Styles = {
  open BsReactNative.Style;

  let container = style([marginTop(Auto)]);
};

let component = ReasonReact.statelessComponent("StatList");

let make = (~value, _children) => {
  ...component,
  render: _self => {
    open BsReactNative;

    let statElements = Belt.Array.map(value, stat => <Card_Stat value=stat />);

    <View style=Styles.container> ...statElements </View>;
  },
};
