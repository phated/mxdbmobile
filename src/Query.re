exception Graphql_error(string);

let send = (q, v) =>
  Fetch.(
    fetchWithInit(
      "https://api.graph.cool/simple/v1/metaxdb",
      RequestInit.make(
        ~method_=Post,
        ~body=
          Js.Dict.fromList([
            ("query", Js.Json.string(q)),
            ("variables", Filter.encode(v)),
          ])
          |> Js.Json.object_
          |> Js.Json.stringify
          |> BodyInit.make,
        ~credentials=Include,
        ~headers=HeadersInit.make({"Content-Type": "application/json"}),
        (),
      ),
    )
    |> Js.Promise.then_(resp =>
         if (Response.ok(resp)) {
           Response.json(resp)
           |> Js.Promise.then_(data => {
                Js.log(data);
                switch (Js.Json.decodeObject(data)) {
                | Some(obj) =>
                  Js.Dict.unsafeGet(obj, "data")
                  |> CardList.decode
                  |> Js.Promise.resolve
                | None =>
                  Js.Promise.reject(
                    Graphql_error("Response is not an object"),
                  )
                };
              });
         } else {
           Js.Promise.reject(
             Graphql_error("Request failed: " ++ Response.statusText(resp)),
           );
         }
       )
  );
