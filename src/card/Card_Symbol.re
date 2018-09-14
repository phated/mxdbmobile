type t =
  | Play
  | Push
  | Constant
  | Attack
  | Defend
  | None;

let fromString = symbol =>
  switch (symbol) {
  | "PLAY" => Play
  | "PUSH" => Push
  | "CONSTANT" => Constant
  | "ATTACK" => Attack
  | "DEFEND" => Defend
  | "NONE" => None
  | _ => failwith("Invalid symbol.")
  };

let decoder = json => json |> Json.Decode.map(fromString, Json.Decode.string);
