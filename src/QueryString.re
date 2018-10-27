let parse = str =>
  Js.String.split("&", str)
  ->Belt.Array.keepMap(pair =>
      switch (Js.String.split("=", pair)) {
      | [|key, value|] => Some((key, value))
      | _ => None
      }
    )
  ->Belt.Map.String.fromArray;

let get = (params, key) => params->Belt.Map.String.get(key);

let getInt = (~default, params, key) =>
  params
  ->Belt.Map.String.get(key)
  ->Belt.Option.map(int_of_string)
  ->Belt.Option.getWithDefault(default);

let getFloat = (~default, params, key) =>
  params
  ->Belt.Map.String.get(key)
  ->Belt.Option.map(float_of_string)
  ->Belt.Option.getWithDefault(default);

let getString = (~default, params, key) =>
  params->Belt.Map.String.get(key)->Belt.Option.getWithDefault(default);
