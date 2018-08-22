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

type state = {
  position: ref(float),
  listRef: ref(option(ReasonReact.reactRef)),
};

let component = ReasonReact.reducerComponent("List");

let keyExtractor = (item, _idx) =>
  switch (item) {
  | Header(title) => title
  | Item(card, _count) => Card.uidGet(card)
  };
let noop = _ => ReasonReact.null;

let itemSeparatorComponent = {
  open BsReactNative;

  let _ = ();

  FlatList.separatorComponent(({leadingItem}) =>
      switch (leadingItem) {
      | Some(Item(_card, _count)) => <View style=Styles.separator />
      | _ => ReasonReact.null
      }
  );
};

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

let onScroll = (evt, {ReasonReact.state}) => {
  let pt = BsReactNative.RNEvent.NativeScrollEvent.contentOffset(evt);
  state.position := pt.y;
};

let scrollToOffset = (~position, listRef) =>
  Utils.nextTick(_ =>
    BsReactNative.FlatList.scrollToOffset(
      ~offset=position,
      ~animated=false,
      listRef,
      (),
    )
  );

let setRef = (listRef, {ReasonReact.state}) =>
  state.listRef := Js.Nullable.toOption(listRef);

let make =
    (
      ~data,
      ~renderHeader=noop,
      ~renderItem,
      ~position=0.0,
      ~onPersistPosition,
      _children,
    ) => {
  open BsReactNative;

  let renderItem =
    FlatList.renderItem(({item}) =>
      switch (item) {
      | Header(title) => renderHeader(title)
      | Item(card, count) => renderItem(card, count)
      }
    );

  {
    ...component,
    initialState: () => {position: ref(0.0), listRef: ref(None)},
    reducer: ((), _state) => ReasonReact.NoUpdate,
    didMount: ({state, onUnmount}) =>
      switch (state.listRef^) {
      | Some(listRef) =>
        let tickId = scrollToOffset(~position, listRef);
        onUnmount(() => Utils.clearTick(tickId));
      | None => ()
      },
    willUnmount: self => onPersistPosition(self.state.position^),
    render: self => {
      let _ = ();

      <FlatList
        data
        getItemLayout
        initialNumToRender=4
        maxToRenderPerBatch=1
        keyExtractor
        renderItem
        removeClippedSubviews=true
        itemSeparatorComponent
        ref=(self.handle(setRef))
        onScroll=(self.handle(onScroll))
      />;
    },
  };
};
