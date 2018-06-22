[@bs.module "react-native-material-ui"]
external subheader : ReasonReact.reactClass = "Subheader";

[@bs.deriving abstract]
type jsProps = {text: string};

let make = (~text, _children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=subheader,
    ~props=jsProps(~text),
    [||],
  );
