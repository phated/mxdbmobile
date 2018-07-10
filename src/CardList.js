'use strict';

var Belt_Array = require("bs-platform/lib/js/belt_Array.js");
var Card$Mxdbmobile = require("./card/Card.js");

function from(characters, events, battles) {
  return Belt_Array.concatMany(/* array */[
              Belt_Array.map(characters, Card$Mxdbmobile.character),
              Belt_Array.map(events, Card$Mxdbmobile.$$event),
              Belt_Array.map(battles, Card$Mxdbmobile.battle)
            ]);
}

exports.from = from;
/* No side effect */
