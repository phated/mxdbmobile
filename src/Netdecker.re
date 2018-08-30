let fetch = _ => {
  let (result, resolve) = Repromise.make();

  MyFetch.fetch("https://metax.toyboat.net/netdecker.php?json=true")
  |> Repromise.wait(result =>
       switch (result) {
       | Belt.Result.Ok(data) =>
         switch (Js.Json.decodeArray(data)) {
         | Some(arr) =>
           Belt.Array.map(arr, SavedDecks.decode)->Belt.Result.Ok->resolve
         | None => Belt.Result.Error("Unable to parse json")->resolve
         }
       | Belt.Result.Error(msg) => Belt.Result.Error(msg)->resolve
       }
     );

  result;
};
