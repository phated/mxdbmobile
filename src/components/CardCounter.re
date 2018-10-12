module Styles = {
  open BsReactNative.Style;

  let container =
    style([flex(1.0), flexDirection(Row), justifyContent(SpaceBetween)]);

  let stepperIcon = style([color(Colors.Css.primary)]);

  let counter =
    style([
      width(30.0->Pt),
      height(30.0->Pt),
      backgroundColor(Colors.Css.transparentWhite),
      borderTopLeftRadius(15.0),
      borderTopRightRadius(15.0),
      alignItems(Center),
      justifyContent(Center),
      alignSelf(FlexEnd),
    ]);
  let counterText =
    style([
      color(Colors.Css.primary),
      fontSize(18.0->Float),
      fontWeight(`_900),
    ]);

  let isZero = style([opacity(0.5->Float)]);
  let notZero = style([]);
};

let component = ReasonReact.statelessComponent("CardCounter");

let make = (~onIncrement, ~onDecrement, ~value, _children) => {
  ...component,
  render: _self => {
    open BsReactNative;

    let opac = value == 0 ? Styles.isZero : Styles.notZero;
    let counterStyle = StyleSheet.flatten([opac, Styles.counter]);

    <View style=Styles.container>
      <StepperButton direction=Left onPress=onDecrement disabled={value == 0}>
        <Icon style=Styles.stepperIcon name="remove" />
      </StepperButton>
      <View style=counterStyle>
        <Text style=Styles.counterText>
          <S> {string_of_int(value)} </S>
        </Text>
      </View>
      <StepperButton direction=Right onPress=onIncrement disabled={value == 3}>
        <Icon style=Styles.stepperIcon name="add" />
      </StepperButton>
    </View>;
  },
};
