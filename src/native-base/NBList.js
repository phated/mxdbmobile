'use strict';

var ReasonReact = require("reason-react/src/ReasonReact.js");
var NativeBase = require("native-base");

function make(dataArray, children) {
  return ReasonReact.wrapJsForReason(NativeBase.List, {
              dataArray: dataArray,
              renderRow: children
            }, children);
}

exports.make = make;
/* ReasonReact Not a pure module */
