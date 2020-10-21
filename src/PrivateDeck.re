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
  ->Promise.map(records => Belt.Array.map(records, toPrivateDeck))
  ->Promise.map(decks => Belt.Result.Ok(decks));
};

let persist = deck => {
  let maybeKey = Deck.keyGet(deck);
  let maybeName = Deck.nameGet(deck);
  let maybeHash = Deck.hash(deck);

  switch (maybeKey, maybeName, maybeHash) {
  | (Some(key), _, None) =>
    Database.Decks.delete(~key)
    ->Promise.map(
         fun
         | Belt.Result.Ok(_key) => Belt.Result.Ok(Deck.empty)
         | Belt.Result.Error(msg) => Belt.Result.Error(msg),
       )
  | (None, Some(name), Some(hash)) =>
    Database.Decks.insert(~name, ~hash)
    ->Promise.map(
         fun
         | Belt.Result.Ok(key) => Belt.Result.Ok(Deck.keySet(deck, key))
         | Belt.Result.Error(msg) => Belt.Result.Error(msg),
       )
  | (Some(key), Some(name), Some(hash)) =>
    Database.Decks.update(~key, ~name, ~hash)
    ->Promise.map(
         fun
         | Belt.Result.Ok(_key) => Belt.Result.Ok(deck)
         | Belt.Result.Error(msg) => Belt.Result.Error(msg),
       )
  | _ => Promise.resolved(Belt.Result.Error("Invalid configuration"))
  };
};
