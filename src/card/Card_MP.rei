type t;

let fromInt: int => t;

let decoder: Js.Json.t => t;

let make:
  (~value: t, array(unit)) =>
  ReasonReact.component(
    ReasonReact.stateless,
    ReasonReact.noRetainedProps,
    ReasonReact.actionless,
  );
