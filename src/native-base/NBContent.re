[@bs.module "native-base"]
external content : ReasonReact.reactClass = "Content";

let make = children =>
  ReasonReact.wrapJsForReason(
    ~reactClass=content,
    ~props=Js.Obj.empty(),
    children,
  );
