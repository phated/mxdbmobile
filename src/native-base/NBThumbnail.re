[@bs.module "native-base"]
external thumbnail : ReasonReact.reactClass = "Thumbnail";

[@bs.deriving abstract]
type absUri = { uri: string };

[@bs.deriving abstract]
type styl = {
  height: int,
  width: int,
};

[@bs.deriving abstract]
type jsProps = {
  source: absUri,
  square: bool,
  style: styl,
};

let make = (~uri: string, _children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=thumbnail,
    ~props=jsProps(
      ~source=absUri(
        ~uri=uri
      ),
      ~square=true,
      ~style=styl(
        ~height=100,
        ~width=72,
      )
    ),
    [||],
  );
