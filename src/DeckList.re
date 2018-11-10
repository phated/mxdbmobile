type t = {
  public: array(PublicDeck.t),
  private: array(PrivateDeck.t),
};

let decode = json => {
  public:
    json
    |> Json.Decode.field(
         "publicDecks",
         Json.Decode.withDefault([||], Json.Decode.array(PublicDeck.decode)),
       ),
  private:
    json
    |> Json.Decode.field(
         "privateDecks",
         Json.Decode.withDefault(
           [||],
           Json.Decode.array(PrivateDeck.decode),
         ),
       ),
};

let parse = json => {
  Js.log(json);
  decode(json);
};

let query = {|
query {
  privateDecks @client
  publicDecks {
    id
    name
    author
    hash
  }
}
|};
