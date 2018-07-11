'use strict';

var Belt_Array = require("bs-platform/lib/js/belt_Array.js");
var Json_decode = require("@glennsl/bs-json/src/Json_decode.bs.js");
var Card$Mxdbmobile = require("./card/Card.js");
var Event$Mxdbmobile = require("./card/Event.js");
var Battle$Mxdbmobile = require("./card/Battle.js");
var Character$Mxdbmobile = require("./card/Character.js");

var empty_000 = /* characters : array */[];

var empty_001 = /* events : array */[];

var empty_002 = /* battles : array */[];

var empty = /* record */[
  empty_000,
  empty_001,
  empty_002
];

function toArray(cardList) {
  return Belt_Array.concatMany(/* array */[
              Belt_Array.map(cardList[/* characters */0], Card$Mxdbmobile.character),
              Belt_Array.map(cardList[/* events */1], Card$Mxdbmobile.$$event),
              Belt_Array.map(cardList[/* battles */2], Card$Mxdbmobile.battle)
            ]);
}

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

exports.empty = empty;
exports.toArray = toArray;
exports.decode = decode;
/* Event-Mxdbmobile Not a pure module */
