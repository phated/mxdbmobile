type t =
  | Strength(int)
  | Intelligence(int)
  | Special(int);

let decoder: Js.Json.t => t;

let make:
  (~value: t, array(unit)) =>
  ReasonReact.component(
    ReasonReact.stateless,
    ReasonReact.noRetainedProps,
    ReasonReact.actionless,
  );
