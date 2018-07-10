'use strict';

var Block = require("bs-platform/lib/js/block.js");
var Json_decode = require("@glennsl/bs-json/src/Json_decode.bs.js");
var ReasonReact = require("reason-react/src/ReasonReact.js");
var MP$Mxdbmobile = require("./MP.js");
var Image$Mxdbmobile = require("./Image.js");
var Effect$Mxdbmobile = require("./Effect.js");
var Text$BsReactNative = require("bs-react-native/src/components/text.js");
var View$BsReactNative = require("bs-react-native/src/components/view.js");
var Style$BsReactNative = require("bs-react-native/src/style.js");
var CardImage$Mxdbmobile = require("../CardImage.js");
var BattleStat$Mxdbmobile = require("./BattleStat.js");

function decoder(json) {
  return /* record */[
          /* uid */Json_decode.field("uid", Json_decode.string, json),
          /* title */Json_decode.field("title", Json_decode.string, json),
          /* mp */Json_decode.field("mp", MP$Mxdbmobile.decoder, json),
          /* stat */Json_decode.field("stats", BattleStat$Mxdbmobile.decoder, json),
          /* effect */Json_decode.field("effect", Effect$Mxdbmobile.decoder, json),
          /* image */Json_decode.field("image", Image$Mxdbmobile.decoder, json)
        ];
}

var details = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.flex(1.0),
      /* :: */[
        Style$BsReactNative.flexDirection(/* Column */2),
        /* :: */[
          Style$BsReactNative.paddingLeft(/* Pt */Block.__(0, [8.0])),
          /* [] */0
        ]
      ]
    ]);

var title = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.fontWeight(/* Bold */737455525),
      /* [] */0
    ]);

var cardListItem = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.height(/* Pt */Block.__(0, [170.0])),
      /* :: */[
        Style$BsReactNative.flexDirection(/* Row */0),
        /* :: */[
          Style$BsReactNative.padding(/* Pt */Block.__(0, [16.0])),
          /* [] */0
        ]
      ]
    ]);

var thumbnail = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.height(/* Pt */Block.__(0, [100.0])),
      /* :: */[
        Style$BsReactNative.width(/* Pt */Block.__(0, [72.0])),
        /* [] */0
      ]
    ]);

var stats = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.alignItems(/* FlexEnd */1),
      /* [] */0
    ]);

var Styles = /* module */[
  /* details */details,
  /* title */title,
  /* cardListItem */cardListItem,
  /* thumbnail */thumbnail,
  /* stats */stats
];

var component = ReasonReact.statelessComponent("Battle");

function make(title$1, mp, stat, image, effect, _) {
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
              var cardImage = ReasonReact.element(/* None */0, /* None */0, CardImage$Mxdbmobile.make(image[/* thumbnail */0], thumbnail, /* array */[]));
              var cardDetails = ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[details], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[
                        ReasonReact.element(/* None */0, /* None */0, Text$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[title], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* array */[title$1])),
                        ReasonReact.element(/* None */0, /* None */0, Effect$Mxdbmobile.make(effect, /* array */[]))
                      ]));
              var cardStats = ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[stats], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[
                        ReasonReact.element(/* None */0, /* None */0, MP$Mxdbmobile.make(mp, /* array */[])),
                        ReasonReact.element(/* None */0, /* None */0, BattleStat$Mxdbmobile.make(stat, /* array */[]))
                      ]));
              return ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[cardListItem], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[
                              cardImage,
                              cardDetails,
                              cardStats
                            ]));
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
/* details Not a pure module */
