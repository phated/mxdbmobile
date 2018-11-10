type t = Belt.Set.t(Card.Compare.t, Card.Compare.identity);

let empty = Belt.Set.make(~id=(module Card.Compare));

let fromArray = cards => Belt.Set.fromArray(~id=(module Card.Compare), cards);

let map = (cards, mapper) =>
  Belt.Set.toArray(cards)->Belt.Array.map(mapper);

let decode = json =>
  fromArray(
    Json.Decode.field("cards", Json.Decode.array(Card.decoder), json),
  );

let parse = decode;

let query = {|
query CardList($title: String, $subtitle: String, $trait: String, $mp: Int, $effect: String, $symbol: CardSymbol) {
  cards: allCards(filter: {
    AND: [
      { OR: [
          { title_contains: $title },
          { subtitle_contains: $subtitle },
          { trait: { name_contains: $trait } },
          { mp: $mp },
          { effect: { text_contains: $effect } },
        ]
      },
      { effect: { symbol: $symbol } }
    ]
  }, orderBy: title_ASC) {
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
    stats {
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
      large
    }
  }
}
|};
