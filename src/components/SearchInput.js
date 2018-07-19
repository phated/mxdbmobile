'use strict';

var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var ReasonReact = require("reason-react/src/ReasonReact.js");
var Colors$Mxdbmobile = require("../Colors.js");
var Style$BsReactNative = require("bs-react-native/src/style.js");
var TextInput$BsReactNative = require("bs-react-native/src/components/textInput.js");

var search = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.flex(1.0),
      /* :: */[
        Style$BsReactNative.color(Colors$Mxdbmobile.Css[/* white */1]),
        /* :: */[
          Style$BsReactNative.fontSize(/* Float */Block.__(0, [20.0])),
          /* :: */[
            Style$BsReactNative.paddingVertical(/* Pt */Block.__(0, [8.0])),
            /* [] */0
          ]
        ]
      ]
    ]);

var Styles = /* module */[/* search */search];

var component = ReasonReact.reducerComponent("SearchInput");

function noop() {
  return /* () */0;
}

function make($staropt$star, $staropt$star$1, $staropt$star$2, _) {
  var onSearch = $staropt$star ? $staropt$star[0] : noop;
  var onBlur = $staropt$star$1 ? $staropt$star$1[0] : noop;
  var previous = $staropt$star$2 ? $staropt$star$2[0] : "";
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
              return ReasonReact.element(/* None */0, /* None */0, TextInput$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[search], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[/* none */-922086728], /* Some */[false], /* Some */[true], /* Some */[true], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[onBlur], /* None */0, /* Some */[(function (text) {
                                    return Curry._1(self[/* send */3], /* UpdateText */[text]);
                                  })], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[(function () {
                                    return Curry._1(self[/* send */3], /* Submit */0);
                                  })], /* Some */["Search"], /* Some */[Colors$Mxdbmobile.gray], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[self[/* state */1]], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */["transparent"], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[false])(/* array */[]));
            }),
          /* initialState */(function () {
              return previous;
            }),
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */(function (action, _) {
              if (action) {
                return /* Update */Block.__(0, [action[0]]);
              } else {
                return /* SideEffects */Block.__(1, [(function (self) {
                              return Curry._1(onSearch, self[/* state */1]);
                            })]);
              }
            }),
          /* subscriptions */component[/* subscriptions */13],
          /* jsElementWrapped */component[/* jsElementWrapped */14]
        ];
}

exports.Styles = Styles;
exports.component = component;
exports.noop = noop;
exports.make = make;
/* search Not a pure module */
