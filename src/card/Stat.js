'use strict';

var Block = require("bs-platform/lib/js/block.js");
var Pervasives = require("bs-platform/lib/js/pervasives.js");
var Json_decode = require("@glennsl/bs-json/src/Json_decode.bs.js");
var ReasonReact = require("reason-react/src/ReasonReact.js");
var Icon$Mxdbmobile = require("../icon/Icon.js");
var Colors$Mxdbmobile = require("../Colors.js");
var Text$BsReactNative = require("bs-react-native/src/components/text.js");
var View$BsReactNative = require("bs-react-native/src/components/view.js");
var Style$BsReactNative = require("bs-react-native/src/style.js");

function fromRecord(param) {
  var rank = param[/* rank */1];
  switch (param[/* type_ */0]) {
    case "Intelligence" : 
        return /* Intelligence */Block.__(1, [rank]);
    case "Special" : 
        return /* Special */Block.__(2, [rank]);
    case "Strength" : 
        return /* Strength */Block.__(0, [rank]);
    default:
      return Pervasives.failwith("Invalid stat type.");
  }
}

function decoder(json) {
  return Json_decode.map(fromRecord, (function (json) {
                return /* record */[
                        /* type_ */Json_decode.field("type", Json_decode.string, json),
                        /* rank */Json_decode.field("rank", Json_decode.$$int, json)
                      ];
              }), json);
}

var container = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.flexDirection(/* Row */0),
      /* :: */[
        Style$BsReactNative.marginTop(/* Pt */Block.__(0, [8.0])),
        /* :: */[
          Style$BsReactNative.justifyContent(/* FlexEnd */1),
          /* :: */[
            Style$BsReactNative.alignItems(/* Center */2),
            /* :: */[
              Style$BsReactNative.width(/* Pt */Block.__(0, [45.0])),
              /* [] */0
            ]
          ]
        ]
      ]
    ]);

var rank = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.marginLeft(/* Pt */Block.__(0, [4.0])),
      /* :: */[
        Style$BsReactNative.width(/* Pt */Block.__(0, [10.0])),
        /* :: */[
          Style$BsReactNative.fontSize(/* Float */Block.__(0, [14.0])),
          /* [] */0
        ]
      ]
    ]);

var strength = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.color(Colors$Mxdbmobile.Css[/* strength */3]),
      /* [] */0
    ]);

var intelligence = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.color(Colors$Mxdbmobile.Css[/* intelligence */4]),
      /* [] */0
    ]);

var special = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.color(Colors$Mxdbmobile.Css[/* special */5]),
      /* [] */0
    ]);

var Styles = /* module */[
  /* container */container,
  /* rank */rank,
  /* strength */strength,
  /* intelligence */intelligence,
  /* special */special
];

var component = ReasonReact.statelessComponent("Stat");

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
              switch (value.tag | 0) {
                case 0 : 
                    return ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[container], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[
                                    ReasonReact.element(/* None */0, /* None */0, Icon$Mxdbmobile.make("strength", /* Some */[strength], /* None */0, /* array */[])),
                                    ReasonReact.element(/* None */0, /* None */0, Text$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[rank], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* array */[String(value[0])]))
                                  ]));
                case 1 : 
                    return ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[container], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[
                                    ReasonReact.element(/* None */0, /* None */0, Icon$Mxdbmobile.make("intelligence", /* Some */[intelligence], /* None */0, /* array */[])),
                                    ReasonReact.element(/* None */0, /* None */0, Text$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[rank], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* array */[String(value[0])]))
                                  ]));
                case 2 : 
                    return ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[container], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[
                                    ReasonReact.element(/* None */0, /* None */0, Icon$Mxdbmobile.make("special", /* Some */[special], /* None */0, /* array */[])),
                                    ReasonReact.element(/* None */0, /* None */0, Text$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[rank], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* array */[String(value[0])]))
                                  ]));
                
              }
            }),
          /* initialState */component[/* initialState */10],
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */component[/* reducer */12],
          /* subscriptions */component[/* subscriptions */13],
          /* jsElementWrapped */component[/* jsElementWrapped */14]
        ];
}

exports.fromRecord = fromRecord;
exports.decoder = decoder;
exports.Styles = Styles;
exports.component = component;
exports.make = make;
/* container Not a pure module */
