type t = {
  characters: array(Character.t),
  events: array(Event.t),
  battles: array(Battle.t),
};

let empty = {characters: [||], events: [||], battles: [||]};

let toArray = cardList =>
  Belt.Array.concatMany([|
    Belt.Array.map(cardList.characters, Card.character),
    Belt.Array.map(cardList.events, Card.event),
    Belt.Array.map(cardList.battles, Card.battle),
  |]);

let decode = json => {
  characters:
    json
    |> Json.Decode.field("characters", Json.Decode.array(Character.decoder)),
  events:
    json |> Json.Decode.field("events", Json.Decode.array(Event.decoder)),
  battles:
    json |> Json.Decode.field("battles", Json.Decode.array(Battle.decoder)),
};
