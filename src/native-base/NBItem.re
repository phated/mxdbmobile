[@bs.module "native-base"] external item : ReasonReact.reactClass = "Item";

let make = children =>
  ReasonReact.wrapJsForReason(
    ~reactClass=item,
    ~props=Js.Obj.empty(),
    children,
  );
