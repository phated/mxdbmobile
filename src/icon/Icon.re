[@bs.module "react-native-vector-icons"]
external createIconSetFromFontello : Js.Json.t => ReasonReact.reactClass = "";

[@bs.module "react-native-vector-icons/dist/MaterialIcons"]
external materialIcon : ReasonReact.reactClass = "default";

[@bs.module "react-native-vector-icons/dist/MaterialCommunityIcons"]
external communityIcon : ReasonReact.reactClass = "default";

[@bs.module] external config : Js.Json.t = "./config.json";

[@bs.deriving abstract]
type jsProps = {
  name: string,
  size: int,
  style: Js.nullable(BsReactNative.Style.t),
  onPress: Js.nullable(unit => unit),
};

let customIcon = createIconSetFromFontello(config);

let isCustom = name =>
  switch (name) {
  | "strength"
  | "intelligence"
  | "special" => true
  | "constant"
  | "play"
  | "push" => true
  | "attack"
  | "defend" => true
  | "cards"
  | "deck"
  | "info" => true
  | _ => false
  };

let isCommunity = name =>
  switch (name) {
  | "plus-circle-outline" => true
  | _ => false
  };

let make = (~name, ~style=?, ~onPress=?, ~size=24, _children) => {
  let reactClass =
    switch (name) {
    | name when isCustom(name) => customIcon
    | name when isCommunity(name) => communityIcon
    | name => materialIcon
    };
  ReasonReact.wrapJsForReason(
    ~reactClass,
    ~props=
      jsProps(
        ~name,
        ~size,
        ~style=Js.Nullable.fromOption(style),
        ~onPress=Js.Nullable.fromOption(onPress),
      ),
    [||],
  );
};
