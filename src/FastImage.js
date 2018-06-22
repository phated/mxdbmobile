'use strict';

var ReasonReact = require("reason-react/src/ReasonReact.js");
var ReactNativeFastImage = require("react-native-fast-image");

function make(uri, _) {
  return ReasonReact.wrapJsForReason(ReactNativeFastImage.default, {
              source: {
                uri: uri
              },
              resizeMode: "contain",
              style: {
                height: undefined,
                width: undefined,
                flex: 1
              }
            }, /* array */[]);
}

exports.make = make;
/* ReasonReact Not a pure module */
