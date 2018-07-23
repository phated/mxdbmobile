module Comparator =
  Belt.Id.MakeComparable({
    type t = Card.t;

    let getType = card =>
      switch (card) {
      | Card.Character(_) => CardType.Character
      | Card.Event(_) => CardType.Event
      | Card.Battle(_) => CardType.Battle
      };

    let getUid = card =>
      switch (card) {
      | Card.Character({uid}) => uid
      | Card.Event({uid}) => uid
      | Card.Battle({uid}) => uid
      };

    let cmp = (first, second) => {
      let cardType1 = getType(first);
      let cardType2 = getType(second);

      if (cardType1 == cardType2) {
        let uid1 = getUid(first);
        let uid2 = getUid(second);
        compare(uid1, uid2);
      } else {
        /* Compare works on Variants in ocaml so no need for toInt??? */
        compare(
          cardType1,
          cardType2,
        );
      };
    };
  });

type t = Belt.Map.Dict.t(Comparator.t, int, Comparator.identity);

let empty = Belt.Map.Dict.empty;

let maybeInc = maybeCount =>
  switch (maybeCount) {
  | Some(count) when count < 3 => Some(count + 1)
  | Some(count) => Some(count)
  | None => Some(1)
  };
let maybeDec = maybeCount =>
  switch (maybeCount) {
  | Some(count) when count > 0 => Some(count - 1)
  | Some(count) => Some(count)
  | None => None
  };

let find = (deck, card) =>
  Belt.Map.Dict.getWithDefault(deck, card, 0, ~cmp=Comparator.cmp);

let increment = (deck, card) =>
  Belt.Map.Dict.update(deck, card, maybeInc, ~cmp=Comparator.cmp);
let decrement = (deck, card) =>
  Belt.Map.Dict.update(deck, card, maybeDec, ~cmp=Comparator.cmp);
