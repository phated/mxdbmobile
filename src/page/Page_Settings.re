module Styles = {
  let listItem =
    Emotion.style(
      ~flex=1.0,
      ~flexDirection="row",
      ~justifyContent="space-between",
      ~alignItems="center",
      ~height=54.0,
      ~paddingHorizontal=16.0,
      (),
    );
};

type t = {
  title: string,
  onPress: unit => unit,
};

let component = ReasonReact.statelessComponent("Page.Settings");

let renderItem = ({title, onPress}) =>
  <TouchableOpacity onPress>
    <View style=Styles.listItem>
      <Text> <S> title </S> </Text>
      <Icon name="chevron-right" />
    </View>
  </TouchableOpacity>;

/* TODO: retained props */
let make = (~data, _children) => {
  ...component,
  render: _self => <List data renderItem />,
};
