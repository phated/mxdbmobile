module Styles = {
  open BsReactNative.Style;

  let container =
    style([
      position(Absolute),
      backgroundColor(Colors.Css.transparentWhite),
      alignItems(Center),
      justifyContent(Center),
      top(60.0->Pt),
      height(30.0->Pt),
      width(35.0->Pt),
    ]);

  let disabled = style([opacity(0.5->Float)]);
  let enabled = style([]);

  let left =
    style([
      left(0.0->Pt),
      borderTopRightRadius(15.0),
      borderBottomRightRadius(15.0),
    ]);
  let right =
    style([
      right(0.0->Pt),
      borderTopLeftRadius(15.0),
      borderBottomLeftRadius(15.0),
    ]);
};

let hitSlop = {"top": 15, "bottom": 15, "left": 15, "right": 15};

type state = {scale: float};
type action =
  | Grow
  | Shrink;

type direction =
  | Left
  | Right;

let vibrationPattern = [|10, 10|];

let component = ReasonReact.reducerComponent("StepperButton");

let make = (~direction, ~onPress, ~disabled, children) => {
  let directional =
    switch (direction) {
    | Left => Styles.left
    | Right => Styles.right
    };
  let grow = (_, self) =>
    if (disabled === false) {
      self.ReasonReact.send(Grow);
    };
  let shrink = (_, self) =>
    if (disabled === false) {
      self.ReasonReact.send(Shrink);
    };
  let press = _ =>
    if (disabled === false) {
      BsReactNative.Vibration.vibrate(
        ~pattern=vibrationPattern,
        ~repeat=false,
      );
      onPress();
    };

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
      let onOff = disabled ? Styles.disabled : Styles.enabled;

      let style =
        StyleSheet.flatten([scale, onOff, directional, Styles.container]);

      <TouchableWithoutFeedback
        hitSlop
        onPress=press
        onPressIn={self.handle(grow)}
        onPressOut={self.handle(shrink)}>
        <View style> ...children </View>
      </TouchableWithoutFeedback>;
    },
  };
};
