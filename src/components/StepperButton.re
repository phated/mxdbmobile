module Styles = {
  open BsReactNative.Style;

  let container =
    style([
      position(Absolute),
      backgroundColor(Colors.Css.transparentWhite),
      alignItems(Center),
      justifyContent(Center),
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

type state = {
  top: float,
  width: float,
  height: float,
  borderRadius: float,
};
type action =
  | Grow
  | Shrink;

let component = ReasonReact.reducerComponent("StepperButton");

let make = (~side, ~onPress, children) => {
  ...component,
  initialState: () => {
    top: 60.0,
    width: 35.0,
    height: 30.0,
    borderRadius: 15.0,
  },
  reducer: (action, state) =>
    switch (action) {
    | Grow =>
      ReasonReact.Update({
        top: 55.0,
        width: 40.0,
        height: 40.0,
        borderRadius: 20.0,
      })
    | Shrink =>
      ReasonReact.Update({
        top: 60.0,
        width: 35.0,
        height: 30.0,
        borderRadius: 15.0,
      })
    },
  render: self => {
    open BsReactNative;
    open BsReactNative.Style;

    let positional =
      style([
        top(self.state.top |. Pt),
        width(self.state.width |. Pt),
        height(self.state.height |. Pt),
      ]);
    let directional =
      switch (side) {
      | "left" =>
        style([
          left(0.0 |. Pt),
          borderTopRightRadius(self.state.borderRadius),
          borderBottomRightRadius(self.state.borderRadius),
        ])
      | "right" =>
        style([
          right(0.0 |. Pt),
          borderTopLeftRadius(self.state.borderRadius),
          borderBottomLeftRadius(self.state.borderRadius),
        ])
      };
    let style =
      StyleSheet.flatten([positional, directional, Styles.container]);

    <TouchableWithoutFeedback
      onPress
      onPressIn=(() => self.send(Grow))
      onPressOut=(() => self.send(Shrink))>
      <View style> ...children </View>
    </TouchableWithoutFeedback>;
  },
};
