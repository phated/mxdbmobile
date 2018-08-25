type t =
  | Cards
  | Deck
  | Settings
  | Stats;

let fromPath = path =>
  switch (path) {
  | [""] => Cards
  | ["deck"] => Deck
  | ["settings"] => Settings
  | ["stats"] => Stats
  | _ => failwith("Invalid route")
  };

let toPath = page =>
  switch (page) {
  | Cards => [""]
  | Deck => ["deck"]
  | Settings => ["stats"]
  | Stats => ["settings"]
  };
