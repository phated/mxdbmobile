'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var Fetch = require("bs-fetch/src/Fetch.js");
var Js_dict = require("bs-platform/lib/js/js_dict.js");
var Js_json = require("bs-platform/lib/js/js_json.js");
var Caml_exceptions = require("bs-platform/lib/js/caml_exceptions.js");

var Graphql_error = Caml_exceptions.create("Query-Mxdbmobile.Graphql_error");

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
                                  return Promise.resolve(Curry._1(q.parse, match[0]["data"]));
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
exports.send = send;
/* Js_dict Not a pure module */
