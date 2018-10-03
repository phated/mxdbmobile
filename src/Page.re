type t =
  | Loading
  | Cards
  | Deck
  | SavedDecks
  | Settings
  | Legal
  | Patreon
  | Stats;

module Stats = Page_Stats;
module Settings = Page_Settings;
module Legal = Page_Legal;
module Patreon = Page_Patreon;
module CardList = Page_CardList;
module Deck = Page_Deck;
module SavedDecks = Page_SavedDecks;

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
