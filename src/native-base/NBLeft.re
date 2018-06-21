[@bs.module "native-base"] external left : ReasonReact.reactClass = "Left";

let make = children =>
  ReasonReact.wrapJsForReason(
    ~reactClass=left,
    ~props=Js.Obj.empty(),
    children,
  );
