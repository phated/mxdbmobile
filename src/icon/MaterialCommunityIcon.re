[@bs.module "react-native-vector-icons/dist/MaterialCommunityIcons"]
external icon : ReasonReact.reactClass = "default";

[@bs.deriving abstract]
type jsProps = {
  name: string,
  size: int,
};

let make = (~name, _children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=icon,
    ~props=jsProps(
      ~name,
      ~size=24,
    ),
    [||],
  );
