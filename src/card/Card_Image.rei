type t;

type size =
  | Thumbnail
  | Small
  | Medium;

let decoder: Js.Json.t => t;

let make:
  (~image: t, ~size: size, array(ReasonReact.reactElement)) =>
  ReasonReact.component(
    ReasonReact.stateless,
    ReasonReact.noRetainedProps,
    ReasonReact.actionless,
  );
