module Styles = {
  open BsReactNative.Style;

  let loadingContainer =
    style([flex(1.0), alignItems(Center), justifyContent(Center)]);
};

let component = ReasonReact.statelessComponent("Loading");

let make = _children => {
  ...component,
  render: _self =>
    <View style=Styles.loadingContainer>
      <ActivityIndicator size=`large color=Colors.Wat.ourBlue />
    </View>,
};
