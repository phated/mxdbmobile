type t =
  | Common
  | Uncommon
  | Rare
  | XRare
  | URare
  | Promo
  | Starter;

let fromString = value =>
  switch (value) {
  | "C" => Common
  | "U" => Uncommon
  | "R" => Rare
  | "XR" => XRare
  | "UR" => URare
  | "P" => Promo
  | "S" => Starter
  | _ => failwith("Invalid rarity.")
  };

let toInt = rarity =>
  switch (rarity) {
  | Starter => 0
  | Common => 1
  | Uncommon => 2
  | Rare => 3
  | Promo => 4
  | XRare => 5
  | URare => 6
  };

let decoder = json => json |> Json.Decode.map(fromString, Json.Decode.string);
