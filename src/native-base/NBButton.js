'use strict';

var ReasonReact = require("reason-react/src/ReasonReact.js");
var NativeBase = require("native-base");
var Js_null_undefined = require("bs-platform/lib/js/js_null_undefined.js");

function make(transparent, children) {
  return ReasonReact.wrapJsForReason(NativeBase.Button, {
              transparent: Js_null_undefined.fromOption(transparent)
            }, children);
}

exports.make = make;
/* ReasonReact Not a pure module */
