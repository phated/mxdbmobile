module Styles = {
  open BsReactNative.Style;

  let container =
    style([
      position(Absolute),
      backgroundColor(Colors.Css.transparentWhite),
      alignItems(Center),
      justifyContent(Center),
      top(60.0 |. Pt),
      height(30.0 |. Pt),
      width(35.0 |. Pt),
    ]);

  let left =
    style([
      left(0.0 |. Pt),
      borderTopRightRadius(15.0),
      borderBottomRightRadius(15.0),
    ]);
  let right =
    style([
      right(0.0 |. Pt),
      borderTopLeftRadius(15.0),
      borderBottomLeftRadius(15.0),
    ]);
};

type state = {scale: float};
type action =
  | Grow
  | Shrink;

let component = ReasonReact.reducerComponent("StepperButton");

let make = (~side, ~onPress, children) => {
  let directional =
    switch (side) {
    | "left" => Styles.left
    | "right" => Styles.right
    };
  let grow = (_, self) => self.ReasonReact.send(Grow);
  let shrink = (_, self) => self.ReasonReact.send(Shrink);

  let makeScale = scale =>
    BsReactNative.Style.(
      style([Transform.make(~scaleX=scale, ~scaleY=scale, ())])
    );

  {
    ...component,
    initialState: () => {scale: 1.0},
    reducer: (action, _state) =>
      switch (action) {
      | Grow => ReasonReact.Update({scale: 1.33})
      | Shrink => ReasonReact.Update({scale: 1.0})
      },
    render: self => {
      open BsReactNative;

      let scale = makeScale(self.state.scale);

      let style =
        StyleSheet.flatten([scale, directional, Styles.container]);

      <TouchableWithoutFeedback
        onPress
        onPressIn=(self.handle(grow))
        onPressOut=(self.handle(shrink))>
        <View style> ...children </View>
      </TouchableWithoutFeedback>;
    },
  };
};
