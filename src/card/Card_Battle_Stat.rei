type t;

let rankGet: t => int;

let toInt: t => int;

let toGroupIdentifier: t => string;

let decoder: Js.Json.t => t;

let isStrength: t => bool;
let isIntelligence: t => bool;
let isSpecial: t => bool;
let isMulti: t => bool;

let make:
  (~stat: t, array(unit)) =>
  ReasonReact.component(
    ReasonReact.stateless,
    ReasonReact.noRetainedProps,
    ReasonReact.actionless,
  );
