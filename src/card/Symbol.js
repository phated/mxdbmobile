'use strict';

var Pervasives = require("bs-platform/lib/js/pervasives.js");
var Json_decode = require("@glennsl/bs-json/src/Json_decode.bs.js");

function fromString(symbol) {
  switch (symbol) {
    case "ATTACK" : 
        return /* Attack */3;
    case "CONSTANT" : 
        return /* Constant */2;
    case "DEFEND" : 
        return /* Defend */4;
    case "NONE" : 
        return /* None */5;
    case "PLAY" : 
        return /* Play */0;
    case "PUSH" : 
        return /* Push */1;
    default:
      return Pervasives.failwith("Invalid symbol.");
  }
}

function decoder(json) {
  return Json_decode.map(fromString, Json_decode.string, json);
}

exports.fromString = fromString;
exports.decoder = decoder;
/* No side effect */
