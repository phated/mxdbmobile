'use strict';

var ReasonReact = require("reason-react/src/ReasonReact.js");
var ReactNativeMaterialUi = require("react-native-material-ui");

function make(text, _) {
  return ReasonReact.wrapJsForReason(ReactNativeMaterialUi.Subheader, {
              text: text
            }, /* array */[]);
}

exports.make = make;
/* ReasonReact Not a pure module */
