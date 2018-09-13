type t =
  | Character
  | Event
  | Battle;

let fromString = value =>
  switch (value) {
  | "Character" => Character
  | "Event" => Event
  | "Battle" => Battle
  | _ => failwith("Invalid card type.")
  };

let toInt = cardType =>
  switch (cardType) {
  | Character => 0
  | Event => 1
  | Battle => 2
  };
