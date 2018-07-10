[@bs.module "react-native-vector-icons"]
external createIconSetFromFontello : Js.Json.t => ReasonReact.reactClass = "";

[@bs.module] external config : Js.Json.t = "./config.json";

[@bs.deriving abstract]
type jsProps = {
  name: string,
  size: int,
  style: Js.nullable(BsReactNative.Style.t),
  onPress: Js.nullable(unit => unit),
};

let icon = createIconSetFromFontello(config);

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
