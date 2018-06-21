[@bs.module "native-base"] external input : ReasonReact.reactClass = "Input";

[@bs.deriving abstract]
type jsProps = {placeholder: Js.nullable(string)};

let make = (~placeholder=?, _children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=input,
    ~props=jsProps(~placeholder=Js.Nullable.fromOption(placeholder)),
    [||],
  );
