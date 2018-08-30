type response;
[@bs.val] external fetch_: string => Repromise.t(response) = "fetch";

[@bs.get] external ok: response => bool = "";
[@bs.send] external json: response => Repromise.t(Js.Json.t) = "";

let fetch = url =>
  fetch_(url)
  |> Repromise.andThen(resp =>
       if (ok(resp)) {
         json(resp) |> Repromise.map(json => Belt.Result.Ok(json));
       } else {
         Repromise.resolved(Belt.Result.Error("Response not okay"));
       }
     );
