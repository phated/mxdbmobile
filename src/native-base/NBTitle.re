[@bs.module "native-base"] external title : ReasonReact.reactClass = "Title";

let make = children =>
  ReasonReact.wrapJsForReason(
    ~reactClass=title,
    ~props=Js.Obj.empty(),
    children,
  );
