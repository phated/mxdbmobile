type t = Belt.Set.t(Card.Compare.t, Card.Compare.identity);

let empty = Belt.Set.make(~id=(module Card.Compare));

let fromArray = cards => Belt.Set.fromArray(~id=(module Card.Compare), cards);

let map = (cards, mapper) =>
  Belt.Set.toArray(cards)->Belt.Array.map(mapper);

let decode = json => {
  let toSet = cards => Belt.Array.concatMany(cards)->fromArray;

  json
  |> Json.Decode.map(toSet, json =>
       [|
         json
         |> Json.Decode.field("characters", Json.Decode.array(Card.decoder)),
         json |> Json.Decode.field("events", Json.Decode.array(Card.decoder)),
         json
         |> Json.Decode.field("battles", Json.Decode.array(Card.decoder)),
       |]
     );
};
let parse = decode;

let query = {|
query CardList($title: String, $subtitle: String, $trait: String, $mp: Int, $effect: String, $symbol: CardSymbol) {
  characters: allCards(filter: {
    AND: [
      { type: Character },
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
    }
  }
  events: allCards(filter: {
    AND: [
      { type: Event },
      { OR: [
          { title_contains: $title },
          { mp: $mp },
          { effect: { text_contains: $effect } }
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
    mp
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
  battles: allCards(filter: {
    AND: [
      { type: Battle },
      { OR: [
          { title_contains: $title },
          { mp: $mp },
          { effect: { text_contains: $effect } }
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
    title
    type
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
}
|};
