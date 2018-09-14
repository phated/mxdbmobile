type t;

type size =
  | Thumbnail
  | Small;

let decoder: Js.Json.t => t;

type retainedProps;

let make:
  (~image: t, ~size: size, array(unit)) =>
  ReasonReact.component(
    ReasonReact.stateless,
    retainedProps,
    ReasonReact.actionless,
  );
