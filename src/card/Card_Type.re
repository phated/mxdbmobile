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

let decoder = json => json |> Json.Decode.map(fromString, Json.Decode.string);
let decoderOnly = (cardType, json) =>
  json
  |> Json.Decode.map(
       match =>
         cardType === match ?
           match : raise(Json.Decode.DecodeError("Incorrect card type.")),
       decoder,
     );

let toInt = cardType =>
  switch (cardType) {
  | Character => 0
  | Event => 1
  | Battle => 2
  };
