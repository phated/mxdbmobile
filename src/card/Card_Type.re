type t =
  | Character
  | Event
  | Battle;

/* TODO: Should this raise the DecodeError? or maybe decoder needs to convert? */
let fromString = value =>
  switch (value) {
  | "Character" => Character
  | "Event" => Event
  | "Battle" => Battle
  | _ => failwith("Invalid card type.")
  };

let isCharacter =
  fun
  | Character => true
  | Event => false
  | Battle => false;

let isEvent =
  fun
  | Character => false
  | Event => true
  | Battle => false;

let isBattle =
  fun
  | Character => false
  | Event => false
  | Battle => true;

let decoder = json => json |> Json.Decode.map(fromString, Json.Decode.string);

let toInt = cardType =>
  switch (cardType) {
  | Character => 0
  | Event => 1
  | Battle => 2
  };
