'use strict';

var Js_exn = require("bs-platform/lib/js/js_exn.js");
var Caml_format = require("bs-platform/lib/js/caml_format.js");
var Json_encode = require("@glennsl/bs-json/src/Json_encode.bs.js");
var Symbol$Mxdbmobile = require("./card/Symbol.js");
var Caml_builtin_exceptions = require("bs-platform/lib/js/caml_builtin_exceptions.js");

function maybeEncodeMP(maybeInt) {
  var match = maybeInt.startsWith("+");
  var trimmedInt = match ? maybeInt.slice(1) : maybeInt;
  try {
    return Caml_format.caml_int_of_string(trimmedInt);
  }
  catch (raw_exn){
    var exn = Js_exn.internalToOCamlException(raw_exn);
    if (exn[0] === Caml_builtin_exceptions.failure) {
      return null;
    } else {
      throw exn;
    }
  }
}

function isSymbol(text) {
  try {
    Symbol$Mxdbmobile.fromString(text);
    return true;
  }
  catch (raw_exn){
    var exn = Js_exn.internalToOCamlException(raw_exn);
    if (exn[0] === Caml_builtin_exceptions.failure) {
      return false;
    } else {
      throw exn;
    }
  }
}

function encode(filter) {
  var query;
  if (filter) {
    var text = filter[0];
    if (isSymbol(text)) {
      console.log("is symbol");
      query = Json_encode.object_(/* :: */[
            /* tuple */[
              "symbol",
              text
            ],
            /* [] */0
          ]);
    } else {
      query = Json_encode.object_(/* :: */[
            /* tuple */[
              "title",
              text
            ],
            /* :: */[
              /* tuple */[
                "subtitle",
                text
              ],
              /* :: */[
                /* tuple */[
                  "trait",
                  text
                ],
                /* :: */[
                  /* tuple */[
                    "mp",
                    maybeEncodeMP(text)
                  ],
                  /* :: */[
                    /* tuple */[
                      "effect",
                      text
                    ],
                    /* [] */0
                  ]
                ]
              ]
            ]
          ]);
    }
  } else {
    query = null;
  }
  console.log(query);
  return query;
}

exports.maybeEncodeMP = maybeEncodeMP;
exports.isSymbol = isSymbol;
exports.encode = encode;
/* Json_encode Not a pure module */
