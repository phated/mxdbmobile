'use strict';

var ReasonReact = require("reason-react/src/ReasonReact.js");
var Js_null_undefined = require("bs-platform/lib/js/js_null_undefined.js");
var ReactNativeMaterialUi = require("react-native-material-ui");

function make(centerElement, search, _) {
  var searchableConfig = search ? /* Some */[{
        autoFocus: true,
        placeholder: "Search"
      }] : /* None */0;
  return ReasonReact.wrapJsForReason(ReactNativeMaterialUi.Toolbar, {
              centerElement: centerElement,
              searchable: Js_null_undefined.fromOption(searchableConfig)
            }, /* array */[]);
}

exports.make = make;
/* ReasonReact Not a pure module */
