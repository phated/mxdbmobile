type t;

let fromString: string => t;
let toString: t => string;

let decoder: Js.Json.t => t;

let make:
  (~value: t, array(unit)) =>
  ReasonReact.component(
    ReasonReact.stateless,
    ReasonReact.noRetainedProps,
    ReasonReact.actionless,
  );
