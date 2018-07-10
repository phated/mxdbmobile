[@bs.module "react-native-vector-icons/dist/MaterialIcons"]
external icon : ReasonReact.reactClass = "default";

[@bs.deriving abstract]
type jsProps = {
  name: string,
  size: int,
  style: Js.nullable(BsReactNative.Style.t),
  onPress: Js.nullable(unit => unit),
};

let make = (~name, ~style=?, ~onPress=?, _children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=icon,
    ~props=
      jsProps(
        ~name,
        ~size=24,
        ~style=Js.Nullable.fromOption(style),
        ~onPress=Js.Nullable.fromOption(onPress),
      ),
    [||],
  );
