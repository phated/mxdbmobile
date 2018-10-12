type decklist = Belt.Map.t(Card.Compare.t, int, Card.Compare.identity);
let emptyDecklist = Belt.Map.make(~id=(module Card.Compare));

type saveKey = string;
type name = string;

type t =
  | Empty
  | Named(name, decklist)
  | Saved(saveKey, name, decklist);

let keyGet = deck =>
  switch (deck) {
  | Empty => None
  | Named(_) => None
  | Saved(saveKey, _name, _deck) => Some(saveKey)
  };

let keySet = (deck, saveKey) =>
  switch (deck) {
  | Empty => Empty
  | Named(name, deck) => Saved(saveKey, name, deck)
  | Saved(_saveKey, name, deck) => Saved(saveKey, name, deck)
  };

let nameGet = deck =>
  switch (deck) {
  | Empty => None
  | Named(name, _deck) => Some(name)
  | Saved(_saveKey, name, _deck) => Some(name)
  };

let nameSet = (deck, name) =>
  switch (deck) {
  | Saved(saveKey, _name, deck) => Saved(saveKey, name, deck)
  | Named(_name, deck) => Named(name, deck)
  | Empty => Named(name, emptyDecklist)
  };

let empty = Empty;

let unbox = deck =>
  switch (deck) {
  | Empty => emptyDecklist
  | Named(_name, deck) => deck
  | Saved(_saveKey, _name, deck) => deck
  };

let forEach = (deck, iter) => unbox(deck)->Belt.Map.forEach(iter);

let mergeMany = (deck, deckArray) =>
  unbox(deck)->Belt.Map.mergeMany(deckArray);

let make = (~key=?, ~name=?, decklist) => {
  let deckName =
    switch (name) {
    | Some(name) => name
    | None =>
      let now = Js.Date.make();
      let todayDate = Js.Date.toLocaleDateString(now);
      let todayTime = Js.Date.toLocaleTimeString(now);
      Printf.sprintf("Untitled - %s %s", todayDate, todayTime);
    };

  switch (key) {
  | None => Named(deckName, decklist)
  | Some(saveKey) => Saved(saveKey, deckName, decklist)
  };
};

let fromArray = (~key=?, ~name=?, deckArray) => {
  let deck = mergeMany(Empty, deckArray);
  make(~key?, ~name?, deck);
};

let isEmpty = deck =>
  switch (deck) {
  /* TODO: not sure if I should check this */
  /* | Some({deck}) => Belt.Map.isEmpty(deck) */
  | Empty => true
  | Named(_) => false
  | Saved(_) => false
  };

let toArray = deck => unbox(deck)->Belt.Map.toArray;

let reduce = (deck, init, fn) => unbox(deck)->Belt.Map.reduce(init, fn);

let flatMap2 = (deck, init, mapper) => {
  let fn = (wrapper, key, value) =>
    switch (wrapper) {
    | None =>
      let first = (key, value);
      let initResults = init(first);
      let flattened = Belt.Array.concat([||], initResults);
      Some((flattened, first));
    | Some((results, prev)) =>
      let next = (key, value);
      let nextResults = mapper(prev, next);
      let flattened = Belt.Array.concat(results, nextResults);
      Some((flattened, next));
    };

  let result = unbox(deck)->Belt.Map.reduce(None, fn);

  switch (result) {
  | Some((result, _last)) => result
  | None => [||]
  };
};

let maybeInc = maybeCount =>
  switch (maybeCount) {
  | Some(count) when count < 3 => Some(count + 1)
  | Some(count) => Some(count)
  | None => Some(1)
  };
let maybeDec = maybeCount =>
  switch (maybeCount) {
  | Some(count) when count == 1 => None
  | Some(count) => Some(count - 1)
  | None => None
  };

let count = (deck, card) => unbox(deck)->Belt.Map.getWithDefault(card, 0);
let countCharacters = deck =>
  reduce(deck, 0, (total, card, count) =>
    switch (card) {
    | Card.Character(_) => count + total
    | _ => total
    }
  );
let countEvents = deck =>
  reduce(deck, 0, (total, card, count) =>
    switch (card) {
    | Card.Event(_) => count + total
    | _ => total
    }
  );
let countBattles = deck =>
  reduce(deck, 0, (total, card, count) =>
    switch (card) {
    | Card.Battle(_) => count + total
    | _ => total
    }
  );
let countStrength = deck =>
  reduce(deck, 0, (total, card, count) =>
    switch (card) {
    | Card.Battle(battle) when Card.Battle.isStrength(battle) =>
      count + total
    | _ => total
    }
  );
let countIntelligence = deck =>
  reduce(deck, 0, (total, card, count) =>
    switch (card) {
    | Card.Battle(battle) when Card.Battle.isIntelligence(battle) =>
      count + total
    | _ => total
    }
  );
let countSpecial = deck =>
  reduce(deck, 0, (total, card, count) =>
    switch (card) {
    | Card.Battle(battle) when Card.Battle.isSpecial(battle) => count + total
    | _ => total
    }
  );
let countMulti = deck =>
  reduce(deck, 0, (total, card, count) =>
    switch (card) {
    | Card.Battle(battle) when Card.Battle.isMulti(battle) => count + total
    | _ => total
    }
  );

let countBattleCardRanks = deck => {
  let strength = Belt.MutableMap.Int.make();
  let intelligence = Belt.MutableMap.Int.make();
  let special = Belt.MutableMap.Int.make();
  let multi = Belt.MutableMap.Int.make();

  let updater = (count, maybeCount) =>
    switch (maybeCount) {
    | Some(prevCount) => Some(prevCount + count)
    | None => Some(count)
    };

  forEach(deck, (card, count) =>
    switch (card) {
    | Card.Battle(battle) when Card.Battle.isStrength(battle) =>
      let rank = Card.Battle.rankGet(battle);
      Belt.MutableMap.Int.update(strength, rank, updater(count));
    | Card.Battle(battle) when Card.Battle.isIntelligence(battle) =>
      let rank = Card.Battle.rankGet(battle);
      Belt.MutableMap.Int.update(intelligence, rank, updater(count));
    | Card.Battle(battle) when Card.Battle.isSpecial(battle) =>
      let rank = Card.Battle.rankGet(battle);
      Belt.MutableMap.Int.update(special, rank, updater(count));
    | Card.Battle(battle) when Card.Battle.isMulti(battle) =>
      let rank = Card.Battle.rankGet(battle);
      Belt.MutableMap.Int.update(multi, rank, updater(count));
    | _ => ()
    }
  );

  let toData = (result, rank, count) =>
    Belt.Array.concat(result, [|{"x": rank, "y": count}|]);

  {
    "strength": Belt.MutableMap.Int.reduce(strength, [||], toData),
    "intelligence": Belt.MutableMap.Int.reduce(intelligence, [||], toData),
    "special": Belt.MutableMap.Int.reduce(special, [||], toData),
    "multi": Belt.MutableMap.Int.reduce(multi, [||], toData),
  };
};

let total = deck => reduce(deck, 0, (total, _card, count) => count + total);

let update = (deck, key, fn) =>
  switch (deck) {
  | Empty =>
    let newDeck = Belt.Map.update(emptyDecklist, key, fn);
    if (Belt.Map.isEmpty(newDeck)) {
      Empty;
    } else {
      make(newDeck);
    };
  | Named(name, deck) =>
    /* TODO: What happens if you "empty" a named deck? */
    let newDeck = Belt.Map.update(deck, key, fn);
    Named(name, newDeck);
  | Saved(saveKey, name, deck) =>
    /* TODO: What happens if you "empty" a saved deck? */
    let newDeck = Belt.Map.update(deck, key, fn);
    Saved(saveKey, name, newDeck);
  };

let increment = (deck, card) => update(deck, card, maybeInc);

let decrement = (deck, card) => update(deck, card, maybeDec);

let makeGroupings = deck => {
  let groupings = Belt.MutableMap.String.make();

  let updater = (amount, maybeAmount) =>
    switch (maybeAmount) {
    | Some(prevAmount) => Some(prevAmount + amount)
    | None => Some(amount)
    };

  forEach(
    deck,
    (card, amount) => {
      let groupId = Card.toGroupIdentifier(card);
      Belt.MutableMap.String.update(groupings, groupId, updater(amount));
    },
  );

  Belt.MutableMap.String.toList(groupings);
};

let getDeckSizeWarnings = deck => {
  let size = total(deck);
  if (size < 40) {
    ["Less than 40 cards."];
  } else if (size > 40) {
    ["More than 40 cards."];
  } else {
    [];
  };
};

let getAmountWarnings = deck => {
  let groupings = makeGroupings(deck);

  Belt.List.reduceReverse(groupings, [], (result, (identifier, amount)) =>
    if (amount > 3) {
      let (name, color) =
        switch (Js.String.splitAtMost(~limit=2, ":", identifier)) {
        | [|"1CHARACTER", name|] => (name, Colors.MetaX.Css.character)
        | [|"2EVENT", name|] => (name, Colors.MetaX.Css.event)
        | [|"3BATTLE", name|] =>
          switch (name) {
          | _ when Js.String.indexOf("Strength", name) === 0 => (
              name,
              Colors.MetaX.Css.strength,
            )
          | _ when Js.String.indexOf("Intelligence", name) === 0 => (
              name,
              Colors.MetaX.Css.intelligence,
            )
          | _ when Js.String.indexOf("Special", name) === 0 => (
              name,
              Colors.MetaX.Css.special,
            )
          | _ when Js.String.indexOf("Multi", name) === 0 => (
              name,
              Colors.MetaX.Css.multi,
            )
          | _ => failwith(name)
          }
        | _ => failwith(identifier)
        };

      [
        {
          "name": name,
          "amount": string_of_int(amount),
          "max": string_of_int(3),
          "color": color,
        },
        ...result,
      ];
    } else {
      result;
    }
  );
};

let hasValidGroupings = deck => {
  let groupings = makeGroupings(deck);

  Belt.List.every(groupings, ((_identifier, amount)) => amount <= 3);
};

/* Technically only exactly 40 is valid but the indicator is annoying for <40 */
let hasValidDeckSize = deck => total(deck) <= 40;

let isValid = deck => hasValidDeckSize(deck) && hasValidGroupings(deck);

let hash = deck => {
  let version = 0;

  let encodedVersion = Hash.toBase64(version);

  let result = Hash.emptyResult(encodedVersion);

  let encodeResult = reduce(deck, result, Hash.encodeCard);

  let encodedDeck =
    encodedVersion ++ String.concat("", encodeResult.cardHashes);

  let base64Checksum = Hash.toBase64(encodeResult.checksum mod 64);

  let encoded = encodedDeck ++ base64Checksum;
  /* AiAASAhA */
  if (Belt.List.size(encodeResult.cardHashes) > 0) {
    Some(encoded);
  } else {
    None;
  };
};

let query = {|
query CardList($uids: [String!]!) {
  characters: allCards(filter: {
    AND: [
      { type: Character },
      { uid_in: $uids }
    ]
  }, orderBy: title_ASC) {
    uid
    rarity
    number
    set
    type
    title
    subtitle
    trait {
      name
    }
    mp
    stats {
      type
      rank
    }
    effect {
      symbol
      text
    }
    image {
      thumbnail
      small
    }
  }
  events: allCards(filter: {
    AND: [
      { type: Event },
      { uid_in: $uids }
    ]
  }, orderBy: title_ASC) {
    uid
    rarity
    number
    set
    type
    title
    mp
    effect {
      symbol
      text
    }
    image {
      thumbnail
      small
    }
  }
  battles: allCards(filter: {
    AND: [
      { type: Battle },
      { uid_in: $uids }
    ]
  }, orderBy: title_ASC) {
    uid
    rarity
    number
    set
    type
    title
    mp
    stats(orderBy: type_ASC) {
      type
      rank
    }
    effect {
      symbol
      text
    }
    image {
      thumbnail
      small
    }
  }
}
|};

let decode = json => json |> Json.Decode.dict(Json.Decode.int);

let loadFromHash = (~key=?, ~name=?, hash) => {
  let (result, resolve) = Repromise.make();

  MyFetch.fetch(
    "https://metax.toyboat.net/decodeDeck.php?output=metaxdb&hash=" ++ hash,
  )
  |> Repromise.map(result =>
       switch (result) {
       | Belt.Result.Ok(data) => decode(data)->Belt.Result.Ok
       | Belt.Result.Error(msg) => Belt.Result.Error(msg)
       }
     )
  |> Repromise.wait(result =>
       switch (result) {
       | Belt.Result.Ok(dict) =>
         let uids =
           Js.Dict.keys(dict) |> Json.Encode.array(Json.Encode.string);
         let vars = Json.Encode.object_([("uids", uids)]);
         Query.send(query, vars, CardList.decode)
         |> Js.Promise.then_(cards => {
              let deckArray =
                CardList.map(
                  cards,
                  card => {
                    let uid = Card.uidGet(card)->Card.UID.toString;
                    let count = Js.Dict.unsafeGet(dict, uid);
                    (card, count);
                  },
                );

              fromArray(~key?, ~name?, deckArray)->Belt.Result.Ok->resolve;
              Js.Promise.resolve(cards);
            })
         |> Js.Promise.catch(err => {
              Js.log(err);
              Js.Promise.reject(Failure("wat"));
            })
         |> ignore;
       | Belt.Result.Error(msg) => Belt.Result.Error(msg)->resolve
       }
     );

  result;
};
