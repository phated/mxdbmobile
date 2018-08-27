type t =
  | Cards
  | Deck
  | Settings
  | Legal
  | Patreon
  | Stats;

let fromPath = path =>
  switch (path) {
  | [""] => Cards
  | ["deck"] => Deck
  | ["settings"] => Settings
  | ["legal"] => Legal
  | ["patreon"] => Patreon
  | ["stats"] => Stats
  | _ => failwith("Invalid route")
  };

let toPath = page =>
  switch (page) {
  | Cards => [""]
  | Deck => ["deck"]
  | Settings => ["stats"]
  | Legal => ["legal"]
  | Patreon => ["patreon"]
  | Stats => ["settings"]
  };
