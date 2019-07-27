let iconHitSlop = {"top": 10, "bottom": 10, "left": 10, "right": 10};

let noop = _ => ();

module Styles = {
  open BsReactNative.Style;

  let iconWrapper = style([height(40.0->Pt), width(40.0->Pt)]);

  let icon =
    style([
      color(Colors.Css.white),
      margin(8.0->Pt),
      textAlignVertical(Center),
    ]);
};

let component = ReasonReact.statelessComponent("IconButton");

let make = (~icon, ~onPress=noop, _children) => {
  ...component,
  render: _self => {
    open BsReactNative;

    let _ = ();

    <TouchableOpacity hitSlop=iconHitSlop onPress>
      <View style=Styles.iconWrapper>
        <Icon name=icon style=Styles.icon />
      </View>
    </TouchableOpacity>;
  },
};
