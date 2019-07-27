let component = ReasonReact.statelessComponent("LinkOut");

let noopStyle = BsReactNative.Style.style([]);

let make = (~style=noopStyle, ~url, children) => {
  ...component,
  render: _self =>
    BsReactNative.(
      <TouchableOpacity style onPress={_ => Linking.openURL(url) |> ignore}>
        ...children
      </TouchableOpacity>
    ),
};
