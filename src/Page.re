type t =
  | Loading
  | Cards
  | Deck
  | SavedDecks
  | Settings
  | Legal
  | Patreon
  | Stats;

let fromPath = path =>
  switch (path) {
  | [""] => Cards
  | ["loading"] => Loading
  | ["deck"] => Deck
  | ["saved-decks"] => SavedDecks
  | ["settings"] => Settings
  | ["legal"] => Legal
  | ["patreon"] => Patreon
  | ["stats"] => Stats
  | _ => failwith("Invalid route")
  };

let toPath = page =>
  switch (page) {
  | Cards => [""]
  | Loading => ["loading"]
  | Deck => ["deck"]
  | SavedDecks => ["saved-decks"]
  | Settings => ["stats"]
  | Legal => ["legal"]
  | Patreon => ["patreon"]
  | Stats => ["settings"]
  };
