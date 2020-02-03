type response;
[@bs.val] external fetch_: string => Promise.t(response) = "fetch";

[@bs.get] external ok: response => bool = "";
[@bs.send] external json: response => Promise.t(Js.Json.t) = "";

let fetch = url =>
  fetch_(url)
  ->Promise.flatMap(resp =>
       if (ok(resp)) {
         json(resp)->Promise.map(json => Belt.Result.Ok(json));
       } else {
         Promise.resolved(Belt.Result.Error("Response not okay"));
       }
     );
