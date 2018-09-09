type t = {
  key: string,
  name: string,
  hash: string,
};

let getAll = () => {
  let toPrivateDeck = record => {
    key: Database.Decks.keyGet(record),
    name: Database.Decks.nameGet(record),
    hash: Database.Decks.hashGet(record),
  };

  Database.Decks.getAll()
  |> Repromise.map(records => Belt.Array.map(records, toPrivateDeck))
  |> Repromise.map(decks => Belt.Result.Ok(decks));
};

let persist = deck => {
  let maybeKey = Deck.keyGet(deck);
  let maybeName = Deck.nameGet(deck);
  let maybeHash = Deck.hash(deck);

  /* TODO: What should happen if the hash is empty? This is basically when a user removes the last card from a deck */
  switch (maybeKey, maybeName, maybeHash) {
  | (_, _, None) => Repromise.resolved(Belt.Result.Error("Unable to Hash"))
  | (None, Some(name), Some(hash)) => Database.Decks.insert(~name, ~hash)
  | (Some(key), Some(name), Some(hash)) =>
    Database.Decks.update(~key, ~name, ~hash)
  | _ => Repromise.resolved(Belt.Result.Error("Invalid configuration"))
  };
};
