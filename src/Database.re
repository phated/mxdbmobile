module Levelup = {
  type t('a);
  type stream;

  [@bs.deriving abstract]
  type options = {valueEncoding: string};

  [@bs.module "../level.dist.js"]
  external make: (string, ~options: options=?, unit) => t(unit) = "";
  [@bs.module "../level.dist.js"]
  external namespace: (t('a), string, ~options: options=?, unit) => t('b) =
    "";
  [@bs.send] external put: (t('a), string, 'a) => Promise.t(unit) = "";
  [@bs.send] external get: (t('a), string) => Promise.t('a) = "";
  [@bs.send] external del: (t('a), string) => Promise.t('a) = "";
  [@bs.send] external createReadStream: (t('a), unit) => stream = "";
  [@bs.send] external createValueStream: (t('a), unit) => stream = "";

  [@bs.send]
  external onData: (stream, [@bs.as "data"] _, 'a => unit) => stream = "on";
  [@bs.send]
  external onEnd: (stream, [@bs.as "end"] _, 'a => unit) => stream = "on";
};

module Base = {
  let db = Levelup.make("mxdbmobile", ());
};

module Decks = {
  [@bs.deriving abstract]
  type toJS = {
    key: string,
    name: string,
    hash: string,
    createdAt: Js.Date.t,
    updatedAt: Js.Date.t,
  };

  let options = Levelup.options(~valueEncoding="json");
  let db = Levelup.namespace(Base.db, "decks", ~options, ());

  let insert = (~name, ~hash) => {
    let now = Js.Date.make();
    let key = Js.Date.toISOString(now);
    let record = toJS(~key, ~name, ~hash, ~createdAt=now, ~updatedAt=now);
    Levelup.put(db, key, record)->Promise.map(_ => Belt.Result.Ok(key));
  };

  let update = (~key, ~name, ~hash) => {
    /* TODO: Fix created at */
    let now = Js.Date.make();
    let record = toJS(~key, ~name, ~hash, ~createdAt=now, ~updatedAt=now);
    Levelup.put(db, key, record)->Promise.map(_ => Belt.Result.Ok(key));
  };

  let delete = (~key) =>
    Levelup.del(db, key)->Promise.map(_ => Belt.Result.Ok(key));

  let getAll = () => {
    let records = Belt.MutableQueue.make();
    let (promise, resolve) = Promise.pending();

    let onData = record => Belt.MutableQueue.add(records, record);
    let onEnd = _ => {
      Js.log("end");
      Belt.MutableQueue.toArray(records)->resolve;
    };

    let _ =
      db
      ->Levelup.createValueStream()
      ->Levelup.onData(onData)
      ->Levelup.onEnd(onEnd);

    promise;
  };
};
