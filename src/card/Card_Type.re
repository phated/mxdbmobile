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
let decoderCharacterOnly = json =>
  json
  |> Json.Decode.map(
       cardType =>
         cardType === Character ?
           cardType : raise(Json.Decode.DecodeError("Incorrect card type.")),
       decoder,
     );
let decoderEventOnly = json =>
  json
  |> Json.Decode.map(
       cardType =>
         cardType === Event ?
           cardType : raise(Json.Decode.DecodeError("Incorrect card type.")),
       decoder,
     );
let decoderBattleOnly = json =>
  json
  |> Json.Decode.map(
       cardType =>
         cardType === Battle ?
           cardType : raise(Json.Decode.DecodeError("Incorrect card type.")),
       decoder,
     );

let toInt = cardType =>
  switch (cardType) {
  | Character => 0
  | Event => 1
  | Battle => 2
  };
