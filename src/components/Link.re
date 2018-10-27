module Styles = {
  open BsReactNative.Style;

  let default = style([]);
};

let component = ReasonReact.statelessComponent("NavigationButton");

let make = (~style=Styles.default, ~path, children) => {
  ...component,
  render: _self => {
    open BsReactNative;

    let url = Oolong.Url.make(path, "", "");

    <TouchableOpacity style onPress={_evt => Router.push(url)}>
      ...children
    </TouchableOpacity>;
  },
};
