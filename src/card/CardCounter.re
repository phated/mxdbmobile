module Styles = {
  open BsReactNative.Style;

  let container = style([height(150.0 |. Pt), width(108.0 |. Pt)]);

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

  let isZero = style([opacity(0.5 |. Float)]);
  let notZero = style([]);
};

let component = ReasonReact.statelessComponent("CardCounter");

let make = (~onIncrement, ~onDecrement, ~value, children) => {
  ...component,
  render: _self => {
    open BsReactNative;
    let [|image|] = children;

    let opac = value == 0 ? Styles.isZero : Styles.notZero;
    let counterStyle = StyleSheet.flatten([opac, Styles.counter]);

    <View style=Styles.container>
      image
      <StepperButton side="left" onPress=onDecrement disabled=(value == 0)>
        <Icon style=Styles.stepperIcon name="remove" />
      </StepperButton>
      <StepperButton side="right" onPress=onIncrement disabled=(value == 3)>
        <Icon style=Styles.stepperIcon name="add" />
      </StepperButton>
      <View style=counterStyle>
        <Text style=Styles.counterText>
          (ReasonReact.string(string_of_int(value)))
        </Text>
      </View>
    </View>;
  },
};
