'use strict';

var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var ReasonReact = require("reason-react/src/ReasonReact.js");
var Colors$Mxdbmobile = require("../Colors.js");
var View$BsReactNative = require("bs-react-native/src/components/view.js");
var Style$BsReactNative = require("bs-react-native/src/style.js");

var container = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.flexDirection(/* Row */0),
      /* :: */[
        Style$BsReactNative.padding(/* Pt */Block.__(0, [8.0])),
        /* :: */[
          Style$BsReactNative.height(/* Pt */Block.__(0, [60.0])),
          /* :: */[
            Style$BsReactNative.backgroundColor(Colors$Mxdbmobile.Css[/* primary */0]),
            /* [] */0
          ]
        ]
      ]
    ]);

var Styles = /* module */[/* container */container];

var component = ReasonReact.reducerComponent("Toolbar");

function make(renderChildren) {
  var enable = function (_, self) {
    return Curry._1(self[/* send */3], /* ChangeMode */[/* Enabled */0]);
  };
  var disable = function (_, self) {
    return Curry._1(self[/* send */3], /* ChangeMode */[/* Disabled */1]);
  };
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
          /* render */(function (self) {
              var children = Curry._3(renderChildren, Curry._1(self[/* handle */0], enable), Curry._1(self[/* handle */0], disable), self[/* state */1]);
              return ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[container], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(children));
            }),
          /* initialState */(function () {
              return /* Disabled */1;
            }),
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */(function (action, _) {
              return /* Update */Block.__(0, [action[0]]);
            }),
          /* subscriptions */component[/* subscriptions */13],
          /* jsElementWrapped */component[/* jsElementWrapped */14]
        ];
}

exports.Styles = Styles;
exports.component = component;
exports.make = make;
/* container Not a pure module */
