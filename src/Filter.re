type t =
  | Empty
  | UID(Card.UID.t)
  | FreeText(string);

let maybeEncodeMP = maybeInt => {
  let trimmedInt =
    Js.String.startsWith("+", maybeInt) ?
      Js.String.sliceToEnd(~from=1, maybeInt) : maybeInt;
  switch (int_of_string(trimmedInt)) {
  | num => Json.Encode.int(num)
  | exception (Failure(_)) => Json.Encode.null
  };
};

let toString = filter =>
  switch (filter) {
  | FreeText(searchString) => searchString
  | UID(uid) => Card.UID.toString(uid)
  | Empty => ""
  };

/* TODO: This needs to handle UID and other types */
let fromString = str =>
  switch (str) {
  | "" => Empty
  | searchString => FreeText(searchString)
  };

let encode = filter => {
  let query =
    switch (filter) {
    | Empty => Json.Encode.null
    | UID(uid) =>
      Json.Encode.object_([
        ("uid", Json.Encode.string(Card.UID.toString(uid))),
      ])
    | FreeText(text) when Card.Symbol.isSymbol(text) =>
      Json.Encode.object_([("symbol", Json.Encode.string(text))])
    | FreeText(text) =>
      Json.Encode.object_([
        ("title", Json.Encode.string(text)),
        ("subtitle", Json.Encode.string(text)),
        ("trait", Json.Encode.string(text)),
        ("mp", maybeEncodeMP(text)),
        ("effect", Json.Encode.string(text)),
      ])
    };
  query;
};
