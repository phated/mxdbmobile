type t = Js.Json.t;

let listToObj = list => Js.Json.object_(Js.Dict.fromList(list));
let wrap = filter => listToObj([("filter", filter)]);

let empty = wrap(listToObj([]));

let create = search =>
  switch (search) {
  | Some(searchString) =>
    wrap(listToObj([("type", Js.Json.string(searchString))]))
  | None => empty
  };
