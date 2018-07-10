'use strict';

var ReasonReact = require("reason-react/src/ReasonReact.js");
var ReactNativeMaterialUi = require("react-native-material-ui");

function make(active, children) {
  return ReasonReact.wrapJsForReason(ReactNativeMaterialUi.BottomNavigation, {
              active: active
            }, children);
}

exports.make = make;
/* ReasonReact Not a pure module */
