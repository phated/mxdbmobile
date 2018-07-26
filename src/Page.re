type t =
  | Cards
  | Deck
  | Info;

let fromPath = path =>
  switch (path) {
  | [""] => Cards
  | ["deck"] => Deck
  | ["info"] => Info
  | _ => failwith("Invalid route")
  };

let toPath = page =>
  switch (page) {
  | Cards => [""]
  | Deck => ["deck"]
  | Info => ["info"]
  };
