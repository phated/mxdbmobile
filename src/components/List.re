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

  let loadingContainer =
    style([flex(1.), alignItems(Center), justifyContent(Center)]);

  let separator =
    style([
      flex(1.0),
      height(1.0 |. Pt),
      backgroundColor(Colors.Css.gray),
    ]);
};

type activeState =
  | Active
  | Inactive
  | Loading;

type state = {
  position: ref(float),
  listRef: ref(option(ReasonReact.reactRef)),
};
type action =
  | Noop;
type retainedProps = {activeState};

let component = ReasonReact.reducerComponentWithRetainedProps("List");

let keyExtractor = (item, _idx) =>
  switch (item) {
  | Header(title) => title
  | Item(card, _count) => Card.getUid(card)
  };
let noop = _ => ReasonReact.null;

let itemSeparatorComponent =
  BsReactNative.(
    FlatList.separatorComponent(_ => <View style=Styles.separator />)
  );

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
  Utils.setTimeout(
    _ =>
      BsReactNative.FlatList.scrollToOffset(
        ~offset=position,
        ~animated=false,
        listRef,
        (),
      ),
    0,
  );

let setRef = (listRef, {ReasonReact.state}) =>
  state.listRef := Js.Nullable.toOption(listRef);

let make = (~data, ~renderHeader=noop, ~renderItem, ~activeState, _children) => {
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
    retainedProps: {
      activeState: activeState,
    },
    initialState: () => {position: ref(0.0), listRef: ref(None)},
    reducer: (action, _state) =>
      switch (action) {
      | Noop => ReasonReact.NoUpdate
      },
    didUpdate: ({oldSelf, newSelf}) =>
      if (oldSelf.retainedProps.activeState == Inactive
          && newSelf.retainedProps.activeState == Active) {
        switch (newSelf.state.listRef^) {
        | Some(listRef) =>
          scrollToOffset(~position=newSelf.state.position^, listRef)
        | None => ()
        };
      },
    render: self => {
      let _ = ();

      switch (activeState) {
      | Inactive => ReasonReact.null
      | Loading =>
        <View style=Styles.loadingContainer>
          <ActivityIndicator size=`large color=Colors.ourBlue />
        </View>
      | Active =>
        <FlatList
          data
          getItemLayout
          initialNumToRender=4
          maxToRenderPerBatch=4
          keyExtractor
          renderItem
          removeClippedSubviews=true
          itemSeparatorComponent
          ref=(self.handle(setRef))
          onScroll=(self.handle(onScroll))
        />
      };
    },
  };
};
