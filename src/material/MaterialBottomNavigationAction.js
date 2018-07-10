'use strict';

var ReasonReact = require("reason-react/src/ReasonReact.js");
var ReactNativeMaterialUi = require("react-native-material-ui");

function make(key_, icon, label, _) {
  return ReasonReact.wrapJsForReason(ReactNativeMaterialUi.BottomNavigation.Action, {
              key: key_,
              icon: icon,
              label: label
            }, /* array */[]);
}

exports.make = make;
/* ReasonReact Not a pure module */
