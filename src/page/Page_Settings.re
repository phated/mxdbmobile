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
  path: list(string),
};

let component = ReasonReact.statelessComponent("Page.Settings");

let renderItem = ({title, path}) =>
  BsReactNative.(
    <Link path>
      <View style=Styles.listItem>
        <Text> <S> title </S> </Text>
        <Icon name="chevron-right" />
      </View>
    </Link>
  );

/* TODO: retained props */
let make = (~data, _children) => {
  ...component,
  render: _self => <List data renderItem />,
};
