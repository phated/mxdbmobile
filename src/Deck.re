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

type t = Belt.MutableMap.t(Comparator.t, int, Comparator.identity);

let empty: t = Belt.MutableMap.make(~id=(module Comparator));

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

let find = (deck, card) => Belt.MutableMap.getWithDefault(deck, card, 0);

let increment = (deck, card) =>
  Belt.MutableMap.update(deck, card, maybeInc);
let decrement = (deck, card) =>
  Belt.MutableMap.update(deck, card, maybeDec);
