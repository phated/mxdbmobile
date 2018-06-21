'use strict';

var ReasonReact = require("reason-react/src/ReasonReact.js");
var NativeBase = require("native-base");

function make(children) {
  return ReasonReact.wrapJsForReason(NativeBase.Container, { }, children);
}

exports.make = make;
/* ReasonReact Not a pure module */
