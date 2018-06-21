[@bs.module "native-base"]
external container : ReasonReact.reactClass = "Container";

let make = children =>
  ReasonReact.wrapJsForReason(
    ~reactClass=container,
    ~props=Js.Obj.empty(),
    children,
  );
