'use strict';

var ReasonReact = require("reason-react/src/ReasonReact.js");
var ReactNativeMaterialUi = require("react-native-material-ui");

function make(centerElement, leftElement, divider, _) {
  return ReasonReact.wrapJsForReason(ReactNativeMaterialUi.ListItem, {
              leftElement: leftElement,
              centerElement: centerElement,
              divider: divider,
              numberOfLines: "dynamic"
            }, /* array */[]);
}

exports.make = make;
/* ReasonReact Not a pure module */
