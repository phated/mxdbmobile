type t = {
  key: string,
  name: string,
  hash: string,
};

let decode = json => {
  key: json |> Json.Decode.field("key", Json.Decode.string),
  name: json |> Json.Decode.field("name", Json.Decode.string),
  hash: json |> Json.Decode.field("hash", Json.Decode.string),
};

let encode = deck =>
  Json.Encode.object_([
    ("key", Json.Encode.string(deck.key)),
    ("name", Json.Encode.string(deck.name)),
    ("hash", Json.Encode.string(deck.hash)),
  ]);

let query = {|
query {
  privateDecks @client
}
|};

let initializers =
  Apollo.Initializers.make([
    {field: "isWorking", init: _client => Js.Json.boolean(true)},
    {field: "privateDecks", init: _client => Js.Json.objectArray([||])},
  ]);

let resolvers =
  Apollo.Resolvers.mutations([
    {
      field: "saveDeck",
      resolver: (_root, args, context, _info) => {
        /* Js.log4("saveDeck", args, context, _info); */
        let cache = context->Apollo.Context.cacheGet;

        let key = Json.Decode.field("key", Json.Decode.string, args);
        let name = Json.Decode.field("name", Json.Decode.string, args);
        let hash = Json.Decode.field("hash", Json.Decode.string, args);

        let toAdd = [|{key, name, hash}|];

        let query = Apollo.gql(. query);
        let json = Apollo.Cache.readQuery(~query, cache);

        let previous =
          json
          |> Json.Decode.field(
               "privateDecks",
               Json.Decode.withDefault([||], Json.Decode.array(decode)),
             );

        let decks =
          Belt.Array.concat(toAdd, previous)->Belt.Array.map(encode);

        let data =
          Json.Encode.object_([
            ("privateDecks", Json.Encode.jsonArray(decks)),
          ]);

        Apollo.Cache.writeQuery(~query, ~data, cache);
        Js.Json.null;
      },
    },
  ]);

module Mutation = {
  type t = Js.Json.t;

  let query = {|
    mutation PersistDeck($key: ID!, $name: String!, $hash: String!) {
      saveDeck(key: $key, name: $name, hash: $hash) @client
    }
  |};

  let parse = _res => Js.Json.null;
};
