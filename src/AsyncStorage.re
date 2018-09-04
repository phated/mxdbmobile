type error;

let toOption = x => Repromise.resolved(Js.toOption(x));

let map_cb = (cb, err, value) =>
  cb(Js.Null.toOption(err), Js.toOption(value));

let map_cb_err_only = (cb, err) => cb(Js.Null.toOption(err));

[@bs.scope "AsyncStorage"] [@bs.module "react-native"]
external _getItem: string => Repromise.t(Js.nullable(string)) = "getItem";

let getItem = key => _getItem(key) |> Repromise.andThen(toOption);

[@bs.scope "AsyncStorage"] [@bs.module "react-native"]
external _setItem: (string, string) => Repromise.t('a) = "setItem";

let setItem = (key, value) => _setItem(key, value);

[@bs.scope "AsyncStorage"] [@bs.module "react-native"]
external _removeItem: string => Repromise.t(unit) = "removeItem";

let removeItem = key => _removeItem(key);

[@bs.scope "AsyncStorage"] [@bs.module "react-native"]
external _mergeItem: (string, string) => Repromise.t(unit) = "mergeItem";

let mergeItem = (key, value) => _mergeItem(key, value);
/*
 [@bs.scope "AsyncStorage"] [@bs.module "react-native"]
 external _clear:
   Js.Undefined.t(Js.Null.t(error) => unit) => Repromise.t(unit) =
   "clear";

 let clear = (~callback=?, ()) =>
   switch (callback) {
   | None => _clear(Js.undefined)
   | Some(cb) => _clear(Js.Undefined.return(map_cb_err_only(cb)))
   }; */

[@bs.scope "AsyncStorage"] [@bs.module "react-native"]
external _getAllKeys: unit => Repromise.t(Js.nullable(array(string))) =
  "getAllKeys";

let getAllKeys = () => _getAllKeys() |> Repromise.andThen(toOption);
/*
 [@bs.scope "AsyncStorage"] [@bs.module "react-native"]
 external flushGetRequests: unit => unit = "";

 [@bs.scope "AsyncStorage"] [@bs.module "react-native"]
 external _multiGet:
   (
     array(string),
     Js.Undefined.t(
       (
         Js.Null.t(array(error)),
         Js.Null_undefined.t(array(array(string)))
       ) =>
       unit,
     )
   ) =>
   Repromise.t(Js.Null_undefined.t(array(array(string)))) =
   "multiGet";

 let multiGet = (keys, ~callback=?, ()) =>
   switch (callback) {
   | None => Repromise.then_(toOption, _multiGet(keys, Js.undefined))
   | Some(cb) =>
     Repromise.then_(
       toOption,
       _multiGet(keys, Js.Undefined.return(map_cb(cb))),
     )
   };

 [@bs.scope "AsyncStorage"] [@bs.module "react-native"]
 external _multiSet:
   (
     array(array(string)),
     Js.Undefined.t(Js.Null.t(array(error)) => unit)
   ) =>
   Repromise.t(unit) =
   "multiSet";

 let multiSet = (keyValues, ~callback=?, ()) => {
   let combine = ((key, value)) => [|key, value|];
   switch (callback) {
   | None => _multiSet(Array.map(combine, keyValues), Js.undefined)
   | Some(cb) =>
     _multiSet(
       Array.map(combine, keyValues),
       Js.Undefined.return(map_cb_err_only(cb)),
     )
   };
 };

 [@bs.scope "AsyncStorage"] [@bs.module "react-native"]
 external _multiRemove:
   (array(string), Js.Undefined.t(Js.Null.t(array(error)) => unit)) =>
   Repromise.t(unit) =
   "multiRemove";

 let multiRemove = (keys, ~callback=?, ()) =>
   switch (callback) {
   | None => _multiRemove(keys, Js.undefined)
   | Some(cb) => _multiRemove(keys, Js.Undefined.return(map_cb_err_only(cb)))
   };

 [@bs.scope "AsyncStorage"] [@bs.module "react-native"]
 external _multiMerge:
   (
     array(array(string)),
     Js.Undefined.t(Js.Null.t(array(error)) => unit)
   ) =>
   Repromise.t(unit) =
   "multiMerge";

 let multiMerge = (keyValues, ~callback=?, ()) => {
   let combine = ((key, value)) => [|key, value|];
   switch (callback) {
   | None => _multiMerge(Array.map(combine, keyValues), Js.undefined)
   | Some(cb) =>
     _multiMerge(
       Array.map(combine, keyValues),
       Js.Undefined.return(map_cb_err_only(cb)),
     )
   };
 }; */
