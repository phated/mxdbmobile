type t =
  | Loading
  | Cards
  | IndividualCard(Card.UID.t)
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
module IndividualCard = Page_IndividualCard;

let fromPath = path =>
  switch (path) {
  | [] => Cards
  | ["card", uid] => IndividualCard(Card.UID.fromString(uid))
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
  | Cards => []
  | IndividualCard(uid) => ["card", Card.UID.toString(uid)]
  | Loading => ["loading"]
  | Deck => ["deck"]
  | SavedDecks => ["saved-decks"]
  | Settings => ["settings"]
  | Legal => ["legal"]
  | Patreon => ["patreon"]
  | Stats => ["stats"]
  };

module Path = {
  let cards = toPath(Cards);
  let individualCard = uid => toPath(IndividualCard(uid));
  let deck = toPath(Deck);
  let savedDecks = toPath(SavedDecks);
  let settings = toPath(Settings);
  let legal = toPath(Legal);
  let patreon = toPath(Patreon);
  let stats = toPath(Stats);
};
