module Hash = Deck_Hash;

type decklist = Belt.Map.t(Card.Compare.t, int, Card.Compare.identity);
let emptyDecklist = Belt.Map.make(~id=(module Card.Compare));

type name = string;
type uid = string;

/* TODO: move out? */
[@bs.module] external cuid: unit => uid = "cuid";

type t =
  | Remote(uid, name, string)
  | Local(uid, name, decklist);

let keyGet = deck =>
  switch (deck) {
  | Remote(uid, _, _) => uid
  | Local(uid, _, _) => uid
  };

let nameGet = deck =>
  switch (deck) {
  | Remote(_, name, _) => name
  | Local(_, name, _) => name
  };

let nameSet = (deck, name) =>
  switch (deck) {
  /* TODO: wat */
  | Remote(uid, _name, hash) => Remote(uid, name, hash)
  | Local(uid, _name, deck) => Local(uid, name, deck)
  };

let hashGet = deck =>
  switch (deck) {
  | Remote(_, _, hash) => hash
  | Local(_, _, deck) => Belt.Option.getWithDefault(Hash.encode(deck), "")
  };

let untitled = () => {
  let now = Js.Date.make();
  let todayDate = Js.Date.toLocaleDateString(now);
  let todayTime = Js.Date.toLocaleTimeString(now);
  Printf.sprintf("Untitled - %s %s", todayDate, todayTime);
};

let empty = () => {
  let uid = cuid();
  let name = untitled();
  Local(uid, name, emptyDecklist);
};

let unbox = deck =>
  switch (deck) {
  | Remote(_, _, _) => emptyDecklist
  | Local(_saveKey, _name, deck) => deck
  };

let forEach = (deck, iter) => unbox(deck)->Belt.Map.forEach(iter);

/* let mergeMany = (deck, deckArray) =>
   unbox(deck)->Belt.Map.mergeMany(deckArray); */

let make = (~key=?, ~name=?, decklist) => {
  let deckName = Belt.Option.getWithDefault(name, untitled());
  let uid = Belt.Option.getWithDefault(name, cuid());

  Local(uid, deckName, decklist);
};

let fromArray = (~key=?, ~name=?, deckArray) => {
  let deck = Belt.Map.mergeMany(emptyDecklist, deckArray);
  make(~key?, ~name?, deck);
};

let isEmpty = deck =>
  switch (deck) {
  | Remote(_, _, hash) => String.length(hash) !== 0
  | Local(_, _, deck) => Belt.Map.isEmpty(deck)
  };

let asMap = deck => unbox(deck);
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
  | Remote(uid, name, hash) => Remote(uid, name, hash)
  | Local(uid, name, deck) =>
    Local(uid, name, Belt.Map.update(deck, key, fn))
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

let query = {|
query Deck($hash: String!) {
  deck(hash: $hash) {
    card {
      id
      uid
      rarity
      number
      set
      type
      title
      subtitle
      trait {
        id
        name
      }
      mp
      stats(orderBy: type_ASC) {
        id
        type
        rank
      }
      effect {
        id
        symbol
        text
      }
      image {
        id
        thumbnail
        small
        medium
      }
    }
    quantity
  }
}
|};

let decode = json =>
  json
  |> Json.Decode.field(
       "deck",
       Json.Decode.array(json =>
         (
           json |> Json.Decode.field("card", Card.decoder),
           json |> Json.Decode.field("quantity", Json.Decode.int),
         )
       ),
     )
  |> fromArray;

let encode = deck =>
  Json.Encode.object_([
    ("key", Json.Encode.string(keyGet(deck))),
    ("name", Json.Encode.string(nameGet(deck))),
    ("hash", Json.Encode.string(hashGet(deck))),
  ]);

let parse = decode;
