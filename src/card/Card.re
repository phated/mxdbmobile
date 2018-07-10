type t =
  | Character(Character.t)
  | Event(Event.t)
  | Battle(Battle.t);

let character = character => Character(character);
let event = event => Event(event);
let battle = battle => Battle(battle);
