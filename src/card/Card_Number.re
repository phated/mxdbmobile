type t = int;

let toInt = value => value;
let decoder = json => Json.Decode.int(json);
