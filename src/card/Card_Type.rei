type t;

let fromString: string => t;

let isCharacter: t => bool;
let isEvent: t => bool;
let isBattle: t => bool;

let decoder: Js.Json.t => t;

let toInt: t => int;
