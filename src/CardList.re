type t = array(Card.t);

let from = (characters, events, battles) =>
  Belt.Array.concatMany([|
    Belt.Array.map(characters, Card.character),
    Belt.Array.map(events, Card.event),
    Belt.Array.map(battles, Card.battle),
  |]);
