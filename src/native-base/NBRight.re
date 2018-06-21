[@bs.module "native-base"] external right : ReasonReact.reactClass = "Right";

let make = children =>
  ReasonReact.wrapJsForReason(
    ~reactClass=right,
    ~props=Js.Obj.empty(),
    children,
  );
