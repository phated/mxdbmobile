'use strict';

var ReasonReact = require("reason-react/src/ReasonReact.js");
var NativeBase = require("native-base");
var Js_null_undefined = require("bs-platform/lib/js/js_null_undefined.js");

function make(name, _) {
  return ReasonReact.wrapJsForReason(NativeBase.Icon, {
              name: Js_null_undefined.fromOption(name)
            }, /* array */[]);
}

exports.make = make;
/* ReasonReact Not a pure module */
