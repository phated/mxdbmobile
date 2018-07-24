type t =
  | Empty
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

let isSymbol = text =>
  switch (Symbol.fromString(text)) {
  | Play
  | Push
  | Constant
  | Attack
  | Defend
  | None => true
  | exception (Failure(_)) => false
  /* | exception => false */
  };

let toString = filter =>
  switch (filter) {
  | FreeText(searchString) => searchString
  | Empty => ""
  };

let encode = filter => {
  let query =
    switch (filter) {
    | Empty => Json.Encode.null
    | FreeText(text) when isSymbol(text) =>
      /* Js.log("is symbol"); */
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
  /* Js.log(query); */
  query;
};
