[@bs.module "react-native-material-ui"]
external listItem : ReasonReact.reactClass = "ListItem";

[@bs.deriving abstract]
type jsProps = {
  leftElement: ReasonReact.reactElement,
  centerElement: ReasonReact.reactElement,
  divider: bool,
  numberOfLines: string,
};

let make = (~centerElement, ~leftElement, ~divider, _children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=listItem,
    ~props=jsProps(
      ~centerElement,
      ~leftElement,
      ~divider,
      ~numberOfLines="dynamic",
    ),
    [||],
  );
