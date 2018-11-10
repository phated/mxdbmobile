type t = {
  id: string,
  author: string,
  name: string,
  hash: string,
};

let decode = json => {
  id: json |> Json.Decode.field("id", Json.Decode.string),
  author: json |> Json.Decode.field("author", Json.Decode.string),
  name: json |> Json.Decode.field("name", Json.Decode.string),
  hash: json |> Json.Decode.field("hash", Json.Decode.string),
};

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
