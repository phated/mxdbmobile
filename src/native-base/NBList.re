[@bs.module "native-base"] external list : ReasonReact.reactClass = "List";

type image = {. "thumbnail": string};
type effect = {
  .
  "symbol": [ | `ATTACK | `CONSTANT | `DEFEND | `NONE | `PLAY | `PUSH],
  "text": option(string),
};
type card = {
  .
  "uid": string,
  "title": string,
  "subtitle": option(string),
  "effect": option(effect),
  "image": option(image),
};

[@bs.deriving abstract]
type jsProps = {
  dataArray: array(card),
  renderRow: card => ReasonReact.reactElement,
};

let make = (~dataArray, children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=list,
    ~props=jsProps(~dataArray, ~renderRow=children),
    children,
  );
