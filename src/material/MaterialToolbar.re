[@bs.module "react-native-material-ui"]
external toolbar : ReasonReact.reactClass = "Toolbar";

[@bs.deriving abstract]
type searchableConfig = {
  autoFocus: bool,
  placeholder: string,
};

[@bs.deriving abstract]
type jsProps = {
  centerElement: string,
  searchable: Js.nullable(searchableConfig),
  rightElement: string,
};

let make = (~centerElement, ~search, ~rightElement, _children) => {
  let searchableConfig =
    search ?
      Some(searchableConfig(~autoFocus=true, ~placeholder="Search")) : None;

  ReasonReact.wrapJsForReason(
    ~reactClass=toolbar,
    ~props=
      jsProps(
        ~centerElement,
        ~rightElement,
        ~searchable=Js.Nullable.fromOption(searchableConfig),
      ),
    [||],
  );
};
