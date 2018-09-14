type t;

let decoder: Js.Json.t => t;

let getText: t => string;

let make:
  (~value: t, array(unit)) =>
  ReasonReact.component(
    ReasonReact.stateless,
    ReasonReact.noRetainedProps,
    ReasonReact.actionless,
  );
