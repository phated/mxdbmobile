let root =
  ReasonReact.wrapReasonForJs(
    ~component=ReasonReact.statelessComponent("Root"), _jsProps =>
    ReasonTea.ReactProgram.make(~program=Application.create, ())
  );
