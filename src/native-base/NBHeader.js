'use strict';

var ReasonReact = require("reason-react/src/ReasonReact.js");
var NativeBase = require("native-base");
var Js_null_undefined = require("bs-platform/lib/js/js_null_undefined.js");

function make(searchBar, rounded, children) {
  return ReasonReact.wrapJsForReason(NativeBase.Header, {
              searchBar: Js_null_undefined.fromOption(searchBar),
              rounded: Js_null_undefined.fromOption(rounded)
            }, children);
}

exports.make = make;
/* ReasonReact Not a pure module */
