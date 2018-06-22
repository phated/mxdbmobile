'use strict';

var ReasonReact = require("reason-react/src/ReasonReact.js");
var MaterialCommunityIcons = require("react-native-vector-icons/dist/MaterialCommunityIcons");

function make(name, _) {
  return ReasonReact.wrapJsForReason(MaterialCommunityIcons.default, {
              name: name,
              size: 24
            }, /* array */[]);
}

exports.make = make;
/* ReasonReact Not a pure module */
