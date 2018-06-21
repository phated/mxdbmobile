[@bs.module "native-base"] external body : ReasonReact.reactClass = "Body";

let make = children =>
  ReasonReact.wrapJsForReason(
    ~reactClass=body,
    ~props=Js.Obj.empty(),
    children,
  );
