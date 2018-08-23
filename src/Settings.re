module Styles = {
  open BsReactNative.Style;

  let listItem =
    style([
      flex(1.0),
      flexDirection(Row),
      justifyContent(SpaceBetween),
      alignItems(Center),
      height(54.0 |. Pt),
      paddingHorizontal(16.0 |. Pt),
    ]);
};

let component = ReasonReact.statelessComponent("SettingsPage");

/* TODO: retained props */
let make = _children => {
  ...component,
  render: _self => {
    open BsReactNative;
    let _ = ();

    let data = [|"Patreon Supporters", "Software"|];

    let renderItem = item => {
      let _ = ();
      <TouchableOpacity>
        <View style=Styles.listItem>
          <Text> (ReasonReact.string(item)) </Text>
          <Icon name="chevron-right" />
        </View>
      </TouchableOpacity>;
    };

    <List data renderItem />;
  },
};
