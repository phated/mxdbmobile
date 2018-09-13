type t =
  | Title(string);

let fromString = value => Title(value);
let toString = (Title(value)) => value;

let decoder = json => json |> Json.Decode.map(fromString, Json.Decode.string);
