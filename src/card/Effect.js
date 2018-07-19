'use strict';

var Block = require("bs-platform/lib/js/block.js");
var Belt_Option = require("bs-platform/lib/js/belt_Option.js");
var Json_decode = require("@glennsl/bs-json/src/Json_decode.bs.js");
var ReasonReact = require("reason-react/src/ReasonReact.js");
var Icon$Mxdbmobile = require("../icon/Icon.js");
var Colors$Mxdbmobile = require("../Colors.js");
var Symbol$Mxdbmobile = require("./Symbol.js");
var Text$BsReactNative = require("bs-react-native/src/components/text.js");
var View$BsReactNative = require("bs-react-native/src/components/view.js");
var Style$BsReactNative = require("bs-react-native/src/style.js");

function decoder(json) {
  return /* record */[
          /* symbol */Json_decode.field("symbol", Symbol$Mxdbmobile.decoder, json),
          /* text */Json_decode.optional((function (param) {
                  return Json_decode.field("text", Json_decode.string, param);
                }), json)
        ];
}

var container = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.flex(1),
      /* [] */0
    ]);

var effectContainer = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.justifyContent(/* FlexEnd */1),
      /* :: */[
        Style$BsReactNative.flexDirection(/* Row */0),
        /* :: */[
          Style$BsReactNative.alignItems(/* Center */2),
          /* :: */[
            Style$BsReactNative.marginTop(/* Auto */0),
            /* [] */0
          ]
        ]
      ]
    ]);

var effectWithoutSymbol = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.flex(1),
      /* [] */0
    ]);

var effectWithSymbol = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.flex(1),
      /* :: */[
        Style$BsReactNative.paddingLeft(/* Pt */Block.__(0, [4.0])),
        /* :: */[
          Style$BsReactNative.marginLeft(/* Pt */Block.__(0, [4.0])),
          /* :: */[
            Style$BsReactNative.borderLeftWidth(2.0),
            /* :: */[
              Style$BsReactNative.borderLeftColor(Colors$Mxdbmobile.Css[/* gray */2]),
              /* :: */[
                Style$BsReactNative.borderStyle(/* Solid */0),
                /* [] */0
              ]
            ]
          ]
        ]
      ]
    ]);

var effectText = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.fontSize(/* Float */Block.__(0, [12.0])),
      /* [] */0
    ]);

var attack = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.color(Colors$Mxdbmobile.Css[/* attack */6]),
      /* [] */0
    ]);

var defend = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.color(Colors$Mxdbmobile.Css[/* defend */7]),
      /* [] */0
    ]);

var constant = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.color(Colors$Mxdbmobile.Css[/* constant */9]),
      /* [] */0
    ]);

var play = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.color(Colors$Mxdbmobile.Css[/* play */10]),
      /* [] */0
    ]);

var push = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.color(Colors$Mxdbmobile.Css[/* push */8]),
      /* [] */0
    ]);

var Styles = /* module */[
  /* container */container,
  /* effectContainer */effectContainer,
  /* effectWithoutSymbol */effectWithoutSymbol,
  /* effectWithSymbol */effectWithSymbol,
  /* effectText */effectText,
  /* attack */attack,
  /* defend */defend,
  /* constant */constant,
  /* play */play,
  /* push */push
];

var component = ReasonReact.statelessComponent("Effect");

function make(effect, _) {
  var match = effect[/* symbol */0];
  var symbolImage;
  switch (match) {
    case 0 : 
        symbolImage = ReasonReact.element(/* None */0, /* None */0, Icon$Mxdbmobile.make("play", /* Some */[play], /* None */0, /* Some */[16], /* array */[]));
        break;
    case 1 : 
        symbolImage = ReasonReact.element(/* None */0, /* None */0, Icon$Mxdbmobile.make("push", /* Some */[push], /* None */0, /* Some */[16], /* array */[]));
        break;
    case 2 : 
        symbolImage = ReasonReact.element(/* None */0, /* None */0, Icon$Mxdbmobile.make("constant", /* Some */[constant], /* None */0, /* Some */[14], /* array */[]));
        break;
    case 3 : 
        symbolImage = ReasonReact.element(/* None */0, /* None */0, Icon$Mxdbmobile.make("attack", /* Some */[attack], /* None */0, /* Some */[16], /* array */[]));
        break;
    case 4 : 
        symbolImage = ReasonReact.element(/* None */0, /* None */0, Icon$Mxdbmobile.make("defend", /* Some */[defend], /* None */0, /* Some */[16], /* array */[]));
        break;
    case 5 : 
        symbolImage = null;
        break;
    
  }
  var match$1 = effect[/* symbol */0];
  var effectStyle = match$1 >= 5 ? effectWithoutSymbol : effectWithSymbol;
  var effectText$1 = Belt_Option.getWithDefault(effect[/* text */1], "");
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
              return ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[container], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[effectContainer], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[
                                        symbolImage,
                                        ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[effectStyle], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[ReasonReact.element(/* None */0, /* None */0, Text$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[effectText], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* array */[effectText$1]))]))
                                      ]))]));
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