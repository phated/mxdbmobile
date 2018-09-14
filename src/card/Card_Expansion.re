type t =
  | JL
  | GL
  | AT
  | BM
  | TT;

let fromString = value =>
  switch (value) {
  | "JL" => JL
  | "GL" => GL
  | "AT" => AT
  | "BM" => BM
  | "TT" => TT
  | _ => failwith("Invalid expansion.")
  };

let toInt = set =>
  switch (set) {
  | JL => 0
  | GL => 1
  | AT => 2
  | BM => 3
  | TT => 4
  };

let decoder = json => json |> Json.Decode.map(fromString, Json.Decode.string);