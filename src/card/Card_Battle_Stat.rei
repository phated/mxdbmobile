type t;

let rankGet: t => int;

let toInt: t => int;

let toGroupIdentifier: t => string;

let decoder: Js.Json.t => t;

let make:
  (~stat: t, array(unit)) =>
  ReasonReact.component(
    ReasonReact.stateless,
    ReasonReact.noRetainedProps,
    ReasonReact.actionless,
  );
