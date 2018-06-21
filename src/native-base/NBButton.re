[@bs.module "native-base"] external button : ReasonReact.reactClass = "Button";

[@bs.deriving abstract]
type jsProps = {transparent: Js.nullable(bool)};

let make = (~transparent=?, children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=button,
    ~props=jsProps(~transparent=Js.Nullable.fromOption(transparent)),
    children,
  );
