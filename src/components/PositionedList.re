module Item = {
  type t('a, 'b) = {
    key: 'a,
    value: 'b,
    size: int,
  };
};

type t('key, 'value) =
  | Header(string)
  | Item(Item.t('key, 'value));

module Styles = {
  open BsReactNative.Style;

  let separator =
    style([flex(1.0), height(1.0->Pt), backgroundColor(Colors.Css.gray)]);
};

type state = {
  position: ref(float),
  listRef: ref(option(ReasonReact.reactRef)),
};

let component = ReasonReact.reducerComponent("PositionedList");

let noop = _ => failwith("No renderHeader method provided");

let getItemLayout = (maybeData, idx) => {
  let maybeItem =
    switch (maybeData) {
    | Some(data) => Some(data[idx])
    | None => None
    };
  switch (maybeItem) {
  | Some(Header(_)) => {"length": 40, "offset": 40 * idx, "index": idx}
  | Some(Item({size})) => {
      "length": size,
      "offset": size * idx,
      "index": idx,
    }
  | None => {"length": 0, "offset": 0, "index": idx}
  };
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
      ~keyExtractor,
      ~initialNumToRender=4,
      _children,
    ) => {
  open BsReactNative;

  let renderItem =
    FlatList.renderItem(({item}) =>
      switch (item) {
      | Header(title) => renderHeader(title)
      | Item({key, value}) => renderItem(key, value)
      }
    );
  /* TODO: List Footer Component for 1 item list? */
  let itemSeparatorComponent =
    FlatList.separatorComponent(({leadingItem}) =>
      switch (leadingItem) {
      | Some(Item(_)) => <View style=Styles.separator />
      | _ => ReasonReact.null
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
    render: self =>
      <FlatList
        data
        getItemLayout
        initialNumToRender
        maxToRenderPerBatch=1
        keyExtractor
        renderItem
        removeClippedSubviews=true
        itemSeparatorComponent
        ref={self.handle(setRef)}
        onScroll={self.handle(onScroll)}
      />,
  };
};
