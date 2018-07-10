type t = array(Stat.t);

let decoder = json => json |> Json.Decode.array(Stat.decoder);

module Styles = {
  open BsReactNative.Style;

  let container = style([marginTop(Auto)]);
};

let component = ReasonReact.statelessComponent("StatList");

let make = (~stats, _children) => {
  ...component,
  render: _self => {
    open BsReactNative;

    let statElements = Belt.Array.map(stats, stat => <Stat value=stat />);

    <View style=Styles.container> ...statElements </View>;
  },
};
