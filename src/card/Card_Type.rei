type t;

let fromString: string => t;

let decoder: Js.Json.t => t;
let decoderCharacterOnly: Js.Json.t => t;
let decoderEventOnly: Js.Json.t => t;
let decoderBattleOnly: Js.Json.t => t;

let toInt: t => int;
