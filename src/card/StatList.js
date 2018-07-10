'use strict';

var Belt_Array = require("bs-platform/lib/js/belt_Array.js");
var Json_decode = require("@glennsl/bs-json/src/Json_decode.bs.js");
var ReasonReact = require("reason-react/src/ReasonReact.js");
var Stat$Mxdbmobile = require("./Stat.js");
var View$BsReactNative = require("bs-react-native/src/components/view.js");
var Style$BsReactNative = require("bs-react-native/src/style.js");

function decoder(json) {
  return Json_decode.array(Stat$Mxdbmobile.decoder, json);
}

var container = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.marginTop(/* Auto */0),
      /* [] */0
    ]);

var Styles = /* module */[/* container */container];

var component = ReasonReact.statelessComponent("StatList");

function make(stats, _) {
  return /* record */[
          /* debugName */component[/* debugName */0],
          /* reactClassInternal */component[/* reactClassInternal */1],
          /* handedOffState */component[/* handedOffState */2],
          /* willReceiveProps */component[/* willReceiveProps */3],
          /* didMount */component[/* didMount */4],
          /* didUpdate */component[/* didUpdate */5],
          /* willUnmount */component[/* willUnmount */6],
          /* willUpdate */component[/* willUpdate */7],
          /* shouldUpdate */component[/* shouldUpdate */8],
          /* render */(function () {
              var statElements = Belt_Array.map(stats, (function (stat) {
                      return ReasonReact.element(/* None */0, /* None */0, Stat$Mxdbmobile.make(stat, /* array */[]));
                    }));
              return ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[container], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(statElements));
            }),
          /* initialState */component[/* initialState */10],
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */component[/* reducer */12],
          /* subscriptions */component[/* subscriptions */13],
          /* jsElementWrapped */component[/* jsElementWrapped */14]
        ];
}

exports.decoder = decoder;
exports.Styles = Styles;
exports.component = component;
exports.make = make;
/* container Not a pure module */
