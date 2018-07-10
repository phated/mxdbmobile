'use strict';

var Block = require("bs-platform/lib/js/block.js");
var Pervasives = require("bs-platform/lib/js/pervasives.js");
var Json_decode = require("@glennsl/bs-json/src/Json_decode.bs.js");
var ReasonReact = require("reason-react/src/ReasonReact.js");
var Text$BsReactNative = require("bs-react-native/src/components/text.js");
var Style$BsReactNative = require("bs-react-native/src/style.js");

function fromString(value) {
  return /* MP */[value];
}

function decoder(json) {
  return Json_decode.map(fromString, Json_decode.$$int, json);
}

var container = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.width(/* Pt */Block.__(0, [45.0])),
      /* :: */[
        Style$BsReactNative.fontSize(/* Float */Block.__(0, [14.0])),
        /* [] */0
      ]
    ]);

var sign = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.fontSize(/* Float */Block.__(0, [11.0])),
      /* [] */0
    ]);

var Styles = /* module */[
  /* container */container,
  /* sign */sign
];

var component = ReasonReact.statelessComponent("MP");

function make(value, _) {
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
              var intValue = value[0];
              var sign$1 = intValue >= 0 ? ReasonReact.element(/* None */0, /* None */0, Text$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[sign], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* array */["+"])) : ReasonReact.element(/* None */0, /* None */0, Text$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[sign], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* array */["-"]));
              return ReasonReact.element(/* None */0, /* None */0, Text$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[container], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* array */[
                              "MP: ",
                              sign$1,
                              String(Pervasives.abs(intValue))
                            ]));
            }),
          /* initialState */component[/* initialState */10],
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */component[/* reducer */12],
          /* subscriptions */component[/* subscriptions */13],
          /* jsElementWrapped */component[/* jsElementWrapped */14]
        ];
}

exports.fromString = fromString;
exports.decoder = decoder;
exports.Styles = Styles;
exports.component = component;
exports.make = make;
/* container Not a pure module */
