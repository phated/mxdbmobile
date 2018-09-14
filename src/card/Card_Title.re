type t = string;

let fromString = value => value;
let toString = value => value;

let decoder = json => Json.Decode.string(json);
