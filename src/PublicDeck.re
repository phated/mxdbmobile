type t = {
  author: string,
  name: string,
  /* date: string, */
  hash: string,
  /* source: string, */
};

let decode = json => {
  author: json |> Json.Decode.field("author", Json.Decode.string),
  name: json |> Json.Decode.field("name", Json.Decode.string),
  hash: json |> Json.Decode.field("hash", Json.Decode.string),
};

let getAll = _ => {
  let (result, resolve) = Promise.pending();

  MyFetch.fetch("https://metax.toyboat.net/netdecker.php?json=true")
  ->Promise.get(result =>
       switch (result) {
       | Belt.Result.Ok(data) =>
         switch (Js.Json.decodeArray(data)) {
         | Some(arr) => Belt.Array.map(arr, decode)->Belt.Result.Ok->resolve
         | None => Belt.Result.Error("Unable to parse json")->resolve
         }
       | Belt.Result.Error(msg) => Belt.Result.Error(msg)->resolve
       }
     );

  result;
};
