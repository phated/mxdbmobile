module Styles = {
  open BsReactNative.Style;

  let container =
    style([
      flexDirection(Row),
      padding(8.0->Pt),
      height(60.0->Pt),
      backgroundColor(Colors.Css.ourBlue),
    ]);
};

type mode =
  | Enabled
  | Disabled;

type action =
  | ChangeMode(mode);

let component = ReasonReact.reducerComponent("Toolbar");

let make = renderChild => {
  let enable = ((), self) => self.ReasonReact.send(ChangeMode(Enabled));
  let disable = ((), self) => self.ReasonReact.send(ChangeMode(Disabled));

  {
    ...component,
    initialState: () => Disabled,
    reducer: (action, _state) =>
      switch (action) {
      | ChangeMode(mode) => ReasonReact.Update(mode)
      },
    render: self => {
      let child =
        renderChild(
          ~enable=self.handle(enable),
          ~disable=self.handle(disable),
          self.state,
        );
      BsReactNative.(<View style=Styles.container> child </View>);
    },
  };
};
