'use strict';

var Json_decode = require("@glennsl/bs-json/src/Json_decode.bs.js");

function decoder(json) {
  return /* record */[/* thumbnail */Json_decode.field("thumbnail", Json_decode.string, json)];
}

exports.decoder = decoder;
/* No side effect */
