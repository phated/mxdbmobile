type publicDeck = {
  author: string,
  name: string,
  hash: string,
};

type t = array(publicDeck);

let decode = json =>
  json
  |> Json.Decode.field(
       "publicDecks",
       Json.Decode.array(json =>
         {
           author: json |> Json.Decode.field("author", Json.Decode.string),
           name: json |> Json.Decode.field("name", Json.Decode.string),
           hash: json |> Json.Decode.field("hash", Json.Decode.string),
         }
       ),
     );
let parse = decode;

let query = {|
query {
  publicDecks {
    id
    name
    author
    hash
  }
}
|};
