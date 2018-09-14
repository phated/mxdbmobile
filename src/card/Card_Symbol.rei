type t;

let fromString: string => t;

let decoder: Js.Json.t => t;

let isSymbol: string => bool;
let hasSymbol: t => bool;

let make:
  (~value: t, array(unit)) =>
  ReasonReact.component(
    ReasonReact.stateless,
    ReasonReact.noRetainedProps,
    ReasonReact.actionless,
  );
