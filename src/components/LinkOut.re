let component = ReasonReact.statelessComponent("LinkOut");

let noopStyle = BsReactNative.Style.style([]);

let make = (~style=noopStyle, ~url, children) => {
  ...component,
  render: _self =>
    <TouchableOpacity
      style onPress={_ => BsReactNative.Linking.openURL(url) |> ignore}>
      ...children
    </TouchableOpacity>,
};
