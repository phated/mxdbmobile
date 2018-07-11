'use strict';

var ReasonReact = require("reason-react/src/ReasonReact.js");
var ConfigJson = require("./config.json");
var Js_null_undefined = require("bs-platform/lib/js/js_null_undefined.js");
var ReactNativeVectorIcons = require("react-native-vector-icons");

var icon = ReactNativeVectorIcons.createIconSetFromFontello(ConfigJson);

function make(name, style, onPress, $staropt$star, _) {
  var size = $staropt$star ? $staropt$star[0] : 24;
  return ReasonReact.wrapJsForReason(icon, {
              name: name,
              size: size,
              style: Js_null_undefined.fromOption(style),
              onPress: Js_null_undefined.fromOption(onPress)
            }, /* array */[]);
}

exports.icon = icon;
exports.make = make;
/* icon Not a pure module */
