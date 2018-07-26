type t =
  | Header(string)
  | Item(Card.t, int);

let toItem = ((card, count)) => Item(card, count);

let isHeader = value =>
  switch (value) {
  | Item(_, _) => false
  | Header(_) => true
  };

module Styles = {
  open BsReactNative.Style;

  let separator =
    style([
      flex(1.0),
      height(1.0 |. Pt),
      backgroundColor(Colors.Css.gray),
    ]);
};

let component = ReasonReact.statelessComponent("List");

let keyExtractor = (item, _idx) =>
  switch (item) {
  | Header(title) => title
  | Item(card, _count) => Card.getUid(card)
  };
let noop = _ => ReasonReact.null;

let getItemLayout = (maybeData, idx) =>
  switch (maybeData) {
  | Some(data) when isHeader(data[idx]) => {
      "length": 40,
      "offset": 40 * idx,
      "index": idx,
    }
  | Some(_data) => {"length": 183, "offset": 183 * idx, "index": idx}
  | None => {"length": 0, "offset": 0, "index": idx}
  };

let make = (~data, ~renderHeader=noop, ~renderItem, _children) => {
  open BsReactNative;
  let itemSeparatorComponent =
    FlatList.separatorComponent(_ => <View style=Styles.separator />);

  let renderItem =
    FlatList.renderItem(({item}) =>
      switch (item) {
      | Header(title) => renderHeader(title)
      | Item(card, count) => renderItem(card, count)
      }
    );

  {
    ...component,
    render: _self => {
      let _ = ();

      <FlatList
        data
        getItemLayout
        initialNumToRender=4
        keyExtractor
        renderItem
        itemSeparatorComponent
      />;
    },
  };
};
