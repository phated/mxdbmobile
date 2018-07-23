module Styles = {
  open BsReactNative.Style;

  let stepperIcon = style([color(Colors.Css.ourBlue)]);

  let counter =
    style([
      position(Absolute),
      bottom(0.0 |. Pt),
      left(39.0 |. Pt),
      width(30.0 |. Pt),
      height(30.0 |. Pt),
      backgroundColor(Colors.Css.transparentWhite),
      borderTopLeftRadius(15.0),
      borderTopRightRadius(15.0),
      alignItems(Center),
      justifyContent(Center),
    ]);
  let counterText =
    style([
      color(Colors.Css.ourBlue),
      fontSize(18.0 |. Float),
      fontWeight(`_900),
    ]);
};

type state = {counter: int};

type action =
  | Increment
  | Decrement;

let component = ReasonReact.reducerComponent("CardCounter");

let make = children => {
  ...component,
  initialState: () => {counter: 0},
  reducer: (action, state) =>
    switch (action) {
    | Increment when state.counter < 3 =>
      ReasonReact.Update({counter: state.counter + 1})
    | Decrement when state.counter > 0 =>
      ReasonReact.Update({counter: state.counter - 1})
    | Increment
    | Decrement => ReasonReact.NoUpdate
    },
  render: self =>
    BsReactNative.(
      <View>
        children
        <StepperButton side="left" onPress=(() => self.send(Decrement))>
          <Icon style=Styles.stepperIcon name="remove" />
        </StepperButton>
        <StepperButton side="right" onPress=(() => self.send(Increment))>
          <Icon style=Styles.stepperIcon name="add" />
        </StepperButton>
        <View style=Styles.counter>
          <Text style=Styles.counterText>
            (ReasonReact.string(string_of_int(self.state.counter)))
          </Text>
        </View>
      </View>
    ),
};
