'use strict';

var ReasonReact = require("reason-react/src/ReasonReact.js");
var ConfigJson = require("./config.json");
var Js_null_undefined = require("bs-platform/lib/js/js_null_undefined.js");
var ReactNativeVectorIcons = require("react-native-vector-icons");
var MaterialIcons = require("react-native-vector-icons/dist/MaterialIcons");

var customIcon = ReactNativeVectorIcons.createIconSetFromFontello(ConfigJson);

function isCustom(name) {
  switch (name) {
    case "attack" : 
    case "cards" : 
    case "constant" : 
    case "deck" : 
    case "defend" : 
    case "info" : 
    case "intelligence" : 
    case "play" : 
    case "push" : 
    case "special" : 
    case "strength" : 
        return true;
    default:
      return false;
  }
}

function make(name, style, onPress, $staropt$star, _) {
  var size = $staropt$star ? $staropt$star[0] : 24;
  var match = isCustom(name);
  var reactClass = match ? customIcon : MaterialIcons.default;
  return ReasonReact.wrapJsForReason(reactClass, {
              name: name,
              size: size,
              style: Js_null_undefined.fromOption(style),
              onPress: Js_null_undefined.fromOption(onPress)
            }, /* array */[]);
}

exports.customIcon = customIcon;
exports.isCustom = isCustom;
exports.make = make;
/* customIcon Not a pure module */
