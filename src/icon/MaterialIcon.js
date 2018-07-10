'use strict';

var ReasonReact = require("reason-react/src/ReasonReact.js");
var Js_null_undefined = require("bs-platform/lib/js/js_null_undefined.js");
var MaterialIcons = require("react-native-vector-icons/dist/MaterialIcons");

function make(name, style, onPress, _) {
  return ReasonReact.wrapJsForReason(MaterialIcons.default, {
              name: name,
              size: 24,
              style: Js_null_undefined.fromOption(style),
              onPress: Js_null_undefined.fromOption(onPress)
            }, /* array */[]);
}

exports.make = make;
/* ReasonReact Not a pure module */
