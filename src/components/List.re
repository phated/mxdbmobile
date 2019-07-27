module Styles = {
  open BsReactNative.Style;

  let separator =
    style([flex(1.0), height(1.0->Pt), backgroundColor(Colors.Css.gray)]);
};

let component = ReasonReact.statelessComponent("List");

let getItemLayout = (_data, idx) => {
  "length": 55,
  "offset": 55 * idx,
  "index": idx,
};

let keyExtractor = (_item, idx) => string_of_int(idx);

let make = (~data, ~renderItem, _children) => {
  open BsReactNative;

  let renderItem = FlatList.renderItem(({item}) => renderItem(item));

  let itemSeparatorComponent =
    FlatList.separatorComponent(_ => <View style=Styles.separator />);
  let listFooterComponent = <View style=Styles.separator />;

  {
    ...component,
    render: _self =>
      <FlatList
        data
        getItemLayout
        initialNumToRender=4
        maxToRenderPerBatch=1
        renderItem
        keyExtractor
        removeClippedSubviews=true
        itemSeparatorComponent
        listFooterComponent
      />,
  };
};
