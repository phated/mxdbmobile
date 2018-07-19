module Styles = {
  open BsReactNative.Style;

  let search =
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

let component = ReasonReact.reducerComponent("SearchInput");

let noop = _ => ();
let make = (~onSearch=noop, ~onBlur=noop, ~previous="", _children) => {
  ...component,
  initialState: () => previous,
  reducer: (action, state) =>
    switch (action) {
    | UpdateText(text) => ReasonReact.Update(text)
    | Submit => ReasonReact.SideEffects((self => onSearch(self.state)))
    },
  render: self =>
    BsReactNative.(
      <TextInput
        style=Styles.search
        autoFocus=true
        autoCorrect=false
        spellCheck=false
        autoCapitalize=`none
        underlineColorAndroid="transparent"
        placeholder="Search"
        placeholderTextColor=Colors.gray
        onBlur
        blurOnSubmit=true
        value=self.state
        onChangeText=(text => self.send(UpdateText(text)))
        onSubmitEditing=(_ => self.send(Submit))
      />
    ),
};
