[@bs.module "native-base"] external header : ReasonReact.reactClass = "Header";

[@bs.deriving abstract]
type jsProps = {
  searchBar: Js.nullable(bool),
  rounded: Js.nullable(bool),
};

let make = (~searchBar=?, ~rounded=?, children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=header,
    ~props=
      jsProps(
        ~searchBar=Js.Nullable.fromOption(searchBar),
        ~rounded=Js.Nullable.fromOption(rounded),
      ),
    children,
  );
