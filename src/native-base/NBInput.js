'use strict';

var ReasonReact = require("reason-react/src/ReasonReact.js");
var NativeBase = require("native-base");
var Js_null_undefined = require("bs-platform/lib/js/js_null_undefined.js");

function make(placeholder, _) {
  return ReasonReact.wrapJsForReason(NativeBase.Input, {
              placeholder: Js_null_undefined.fromOption(placeholder)
            }, /* array */[]);
}

exports.make = make;
/* ReasonReact Not a pure module */
