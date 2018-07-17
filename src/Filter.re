type t = Js.Json.t;

let listToObj = list => Js.Json.object_(Js.Dict.fromList(list));
let wrap = filter => listToObj([("query", filter)]);

let empty = wrap(listToObj([]));

let effectText = search =>
  listToObj([("text_contains", Js.Json.string(search))]);

let create = search =>
  switch (search) {
  | Some(searchString) =>
    wrap(listToObj([("effect", effectText(searchString))]))
  | None => empty
  };
