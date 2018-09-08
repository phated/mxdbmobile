module Styles = {
  open BsReactNative.Style;

  let listItem =
    style([
      flex(1.0),
      flexDirection(Row),
      justifyContent(SpaceBetween),
      alignItems(Center),
      height(54.0->Pt),
      paddingHorizontal(16.0->Pt),
    ]);
};

type t = {
  title: string,
  onPress: unit => unit,
};

let component = ReasonReact.statelessComponent("Page.Settings");

let renderItem = ({title, onPress}) =>
  BsReactNative.(
    <TouchableOpacity onPress>
      <View style=Styles.listItem>
        <Text> <S> title </S> </Text>
        <Icon name="chevron-right" />
      </View>
    </TouchableOpacity>
  );

/* TODO: retained props */
let make = (~data, _children) => {
  ...component,
  render: _self => <List data renderItem />,
};
