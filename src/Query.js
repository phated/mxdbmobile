'use strict';

var Fetch = require("bs-fetch/src/Fetch.js");
var Js_dict = require("bs-platform/lib/js/js_dict.js");
var Js_json = require("bs-platform/lib/js/js_json.js");
var Json_decode = require("@glennsl/bs-json/src/Json_decode.bs.js");
var Caml_exceptions = require("bs-platform/lib/js/caml_exceptions.js");
var Event$Mxdbmobile = require("./card/Event.js");
var Battle$Mxdbmobile = require("./card/Battle.js");
var Character$Mxdbmobile = require("./card/Character.js");

var Graphql_error = Caml_exceptions.create("Query-Mxdbmobile.Graphql_error");

function decode(json) {
  return /* record */[
          /* characters */Json_decode.field("characters", (function (param) {
                  return Json_decode.array(Character$Mxdbmobile.decoder, param);
                }), json),
          /* events */Json_decode.field("events", (function (param) {
                  return Json_decode.array(Event$Mxdbmobile.decoder, param);
                }), json),
          /* battles */Json_decode.field("battles", (function (param) {
                  return Json_decode.array(Battle$Mxdbmobile.decoder, param);
                }), json)
        ];
}

function send(q) {
  return fetch("https://api.graph.cool/simple/v1/metaxdb", Fetch.RequestInit[/* make */0](/* Some */[/* Post */2], /* Some */[{
                        "Content-Type": "application/json"
                      }], /* Some */[JSON.stringify(Js_dict.fromList(/* :: */[
                                /* tuple */[
                                  "query",
                                  q.query
                                ],
                                /* :: */[
                                  /* tuple */[
                                    "variables",
                                    q.variables
                                  ],
                                  /* [] */0
                                ]
                              ]))], /* None */0, /* None */0, /* None */0, /* Some */[/* Include */2], /* None */0, /* None */0, /* None */0, /* None */0)(/* () */0)).then((function (resp) {
                if (resp.ok) {
                  return resp.json().then((function (data) {
                                var match = Js_json.decodeObject(data);
                                if (match) {
                                  return Promise.resolve(decode(match[0]["data"]));
                                } else {
                                  return Promise.reject([
                                              Graphql_error,
                                              "Response is not an object"
                                            ]);
                                }
                              }));
                } else {
                  return Promise.reject([
                              Graphql_error,
                              "Request failed: " + resp.statusText
                            ]);
                }
              }));
}

exports.Graphql_error = Graphql_error;
exports.decode = decode;
exports.send = send;
/* Js_dict Not a pure module */
