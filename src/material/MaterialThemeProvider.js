'use strict';

var ReasonReact = require("reason-react/src/ReasonReact.js");
var ReactNativeMaterialUi = require("react-native-material-ui");

var uiTheme = {
  listItem: {
    leftElementContainer: {
      width: "auto"
    }
  },
  subheader: {
    container: {
      backgroundColor: "#f7f7f7"
    }
  }
};

function make(children) {
  return ReasonReact.wrapJsForReason(ReactNativeMaterialUi.ThemeProvider, {
              uiTheme: uiTheme
            }, children);
}

exports.uiTheme = uiTheme;
exports.make = make;
/* ReasonReact Not a pure module */
