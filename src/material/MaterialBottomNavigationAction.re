/* The module is terrible and doesn't export properly. Here is a nifty workaround */
[@bs.deriving abstract]
type namespace = {
  [@bs.as "Action"] action: ReasonReact.reactClass
};

[@bs.module "react-native-material-ui"]
external namespace : namespace = "BottomNavigation";

[@bs.deriving abstract]
type jsProps = {
  [@bs.as "key"] key_: string,
  icon: string,
  label: string,
};

let make = (~key_, ~icon, ~label, _children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=namespace |. action,
    ~props=jsProps(
      ~key_,
      ~icon,
      ~label,
    ),
    [||]
  );
