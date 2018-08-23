module Styles = {
  open BsReactNative.Style;

  let input =
    style([
      flex(1.0),
      color(Colors.Css.white),
      fontSize(20.0 |. Float),
      paddingVertical(8.0 |. Pt),
    ]);
};

type state = string;
type action =
  | UpdateText(string)
  | Submit;

let component = ReasonReact.reducerComponent("ToolbarInput");

let noop = _ => ();
let make = (~onSubmit=noop, ~placeholder, ~onBlur=noop, ~previous="", _children) => {
  ...component,
  initialState: () => previous,
  reducer: (action, state) =>
    switch (action) {
    | UpdateText(text) => ReasonReact.Update(text)
    | Submit => ReasonReact.SideEffects((self => onSubmit(self.state)))
    },
  render: self =>
    BsReactNative.(
      <TextInput
        style=Styles.input
        autoFocus=true
        autoCorrect=false
        spellCheck=false
        autoCapitalize=`none
        underlineColorAndroid="transparent"
        placeholder
        placeholderTextColor=Colors.gray
        onBlur
        blurOnSubmit=true
        value=self.state
        onChangeText=(text => self.send(UpdateText(text)))
        onSubmitEditing=(_ => self.send(Submit))
      />
    ),
};
