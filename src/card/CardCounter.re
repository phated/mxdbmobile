module Styles = {
  open BsReactNative.Style;

  let stepperIcon = style([color(Colors.Css.primary)]);

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
      color(Colors.Css.primary),
      fontSize(18.0 |. Float),
      fontWeight(`_900),
    ]);
};

let component = ReasonReact.statelessComponent("CardCounter");

let make = (~onIncrement, ~onDecrement, ~value, children) => {
  ...component,
  render: _self =>
    BsReactNative.(
      <View>
        children
        <StepperButton side="left" onPress=onDecrement>
          <Icon style=Styles.stepperIcon name="remove" />
        </StepperButton>
        <StepperButton side="right" onPress=onIncrement>
          <Icon style=Styles.stepperIcon name="add" />
        </StepperButton>
        <View style=Styles.counter>
          <Text style=Styles.counterText>
            (ReasonReact.string(string_of_int(value)))
          </Text>
        </View>
      </View>
    ),
};
