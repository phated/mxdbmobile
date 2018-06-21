[@bs.module "native-base"] external icon : ReasonReact.reactClass = "Icon";

[@bs.deriving abstract]
type jsProps = {name: Js.nullable(string)};

let make = (~name=?, _children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=icon,
    ~props=jsProps(~name=Js.Nullable.fromOption(name)),
    [||],
  );
