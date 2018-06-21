'use strict';

var ReasonReact = require("reason-react/src/ReasonReact.js");
var NativeBase = require("native-base");

function make(uri, _) {
  return ReasonReact.wrapJsForReason(NativeBase.Thumbnail, {
              source: {
                uri: uri
              },
              square: true,
              style: {
                height: 100,
                width: 72
              }
            }, /* array */[]);
}

exports.make = make;
/* ReasonReact Not a pure module */
