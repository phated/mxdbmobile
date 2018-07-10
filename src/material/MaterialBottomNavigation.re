[@bs.module "react-native-material-ui"]
external bottomNavigation : ReasonReact.reactClass = "BottomNavigation";

[@bs.deriving abstract]
type jsProps = {active: string};

let make = (~active, children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=bottomNavigation,
    ~props=jsProps(~active),
    children,
  );
