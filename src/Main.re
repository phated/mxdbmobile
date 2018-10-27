let root =
  ReasonReact.wrapReasonForJs(
    ~component=Oolong.ReactProgram.component, _jsProps =>
    Oolong.ReactProgram.make(
      ~program=Application.create,
      ~router=Router.router,
      (),
    )
  );
