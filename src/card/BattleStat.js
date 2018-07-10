'use strict';

var Block = require("bs-platform/lib/js/block.js");
var Pervasives = require("bs-platform/lib/js/pervasives.js");
var Json_decode = require("@glennsl/bs-json/src/Json_decode.bs.js");
var ReasonReact = require("reason-react/src/ReasonReact.js");
var Icon$Mxdbmobile = require("../icon/Icon.js");
var Colors$Mxdbmobile = require("../Colors.js");
var Text$BsReactNative = require("bs-react-native/src/components/text.js");
var View$BsReactNative = require("bs-react-native/src/components/view.js");
var StatList$Mxdbmobile = require("./StatList.js");
var Style$BsReactNative = require("bs-react-native/src/style.js");

function fromStatList(statList) {
  var len = statList.length;
  if (len >= 4) {
    return Pervasives.failwith("Invalid Battle Card stat list.");
  } else {
    switch (len) {
      case 0 : 
          return Pervasives.failwith("Invalid Battle Card stat list.");
      case 1 : 
          var match = statList[0];
          switch (match.tag | 0) {
            case 0 : 
                return /* Strength */Block.__(0, [match[0]]);
            case 1 : 
                return /* Intelligence */Block.__(1, [match[0]]);
            case 2 : 
                return /* Special */Block.__(2, [match[0]]);
            
          }
      case 2 : 
          var match$1 = statList[0];
          switch (match$1.tag | 0) {
            case 0 : 
                return Pervasives.failwith("Invalid Battle Card stat list.");
            case 1 : 
                var rank = match$1[0];
                var match$2 = statList[1];
                switch (match$2.tag | 0) {
                  case 0 : 
                      return /* StrengthIntelligence */Block.__(3, [rank]);
                  case 1 : 
                      return Pervasives.failwith("Invalid Battle Card stat list.");
                  case 2 : 
                      return /* IntelligenceSpecial */Block.__(4, [rank]);
                  
                }
            case 2 : 
                var match$3 = statList[1];
                switch (match$3.tag | 0) {
                  case 0 : 
                      return /* StrengthSpecial */Block.__(5, [match$1[0]]);
                  case 1 : 
                  case 2 : 
                      return Pervasives.failwith("Invalid Battle Card stat list.");
                  
                }
            
          }
      case 3 : 
          var match$4 = statList[0];
          switch (match$4.tag | 0) {
            case 1 : 
                var match$5 = statList[1];
                switch (match$5.tag | 0) {
                  case 0 : 
                  case 1 : 
                      return Pervasives.failwith("Invalid Battle Card stat list.");
                  case 2 : 
                      var match$6 = statList[2];
                      switch (match$6.tag | 0) {
                        case 0 : 
                            return /* StrengthIntelligenceSpecial */Block.__(6, [match$4[0]]);
                        case 1 : 
                        case 2 : 
                            return Pervasives.failwith("Invalid Battle Card stat list.");
                        
                      }
                  
                }
            case 0 : 
            case 2 : 
                return Pervasives.failwith("Invalid Battle Card stat list.");
            
          }
      
    }
  }
}

function decoder(json) {
  return Json_decode.map(fromStatList, StatList$Mxdbmobile.decoder, json);
}

var container = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.marginTop(/* Auto */0),
      /* [] */0
    ]);

var singleIconContainer = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.flexDirection(/* Row */0),
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
    ]);

var doubleIconContainer = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.flexDirection(/* Row */0),
      /* :: */[
        Style$BsReactNative.justifyContent(/* FlexEnd */1),
        /* :: */[
          Style$BsReactNative.alignItems(/* Center */2),
          /* :: */[
            Style$BsReactNative.width(/* Pt */Block.__(0, [52.5])),
            /* [] */0
          ]
        ]
      ]
    ]);

var tripleIconContainer = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.flexDirection(/* Row */0),
      /* :: */[
        Style$BsReactNative.justifyContent(/* FlexEnd */1),
        /* :: */[
          Style$BsReactNative.alignItems(/* Center */2),
          /* :: */[
            Style$BsReactNative.width(/* Pt */Block.__(0, [68.0])),
            /* [] */0
          ]
        ]
      ]
    ]);

var doubleIcon = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.position(/* Relative */1),
      /* :: */[
        Style$BsReactNative.width(/* Pt */Block.__(0, [38.5])),
        /* :: */[
          Style$BsReactNative.height(/* Pt */Block.__(0, [30.0])),
          /* [] */0
        ]
      ]
    ]);

var firstDouble = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.position(/* Absolute */0),
      /* :: */[
        Style$BsReactNative.top(/* Pt */Block.__(0, [5.0])),
        /* :: */[
          Style$BsReactNative.left(/* Pt */Block.__(0, [0.0])),
          /* :: */[
            Style$BsReactNative.zIndex(2),
            /* :: */[
              Style$BsReactNative.borderRadius(12.0),
              /* :: */[
                Style$BsReactNative.backgroundColor(Colors$Mxdbmobile.Css[/* white */1]),
                /* [] */0
              ]
            ]
          ]
        ]
      ]
    ]);

var secondDouble = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.position(/* Absolute */0),
      /* :: */[
        Style$BsReactNative.right(/* Pt */Block.__(0, [0.0])),
        /* :: */[
          Style$BsReactNative.zIndex(1),
          /* [] */0
        ]
      ]
    ]);

var tripleIcon = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.position(/* Relative */1),
      /* :: */[
        Style$BsReactNative.width(/* Pt */Block.__(0, [54.0])),
        /* :: */[
          Style$BsReactNative.height(/* Pt */Block.__(0, [30.0])),
          /* [] */0
        ]
      ]
    ]);

var firstTriple = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.position(/* Absolute */0),
      /* :: */[
        Style$BsReactNative.top(/* Pt */Block.__(0, [5.0])),
        /* :: */[
          Style$BsReactNative.left(/* Pt */Block.__(0, [0.0])),
          /* :: */[
            Style$BsReactNative.zIndex(1),
            /* [] */0
          ]
        ]
      ]
    ]);

var secondTriple = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.position(/* Absolute */0),
      /* :: */[
        Style$BsReactNative.left(/* Pt */Block.__(0, [15.0])),
        /* :: */[
          Style$BsReactNative.zIndex(2),
          /* :: */[
            Style$BsReactNative.borderRadius(12.0),
            /* :: */[
              Style$BsReactNative.backgroundColor(Colors$Mxdbmobile.Css[/* white */1]),
              /* [] */0
            ]
          ]
        ]
      ]
    ]);

var thirdTriple = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.position(/* Absolute */0),
      /* :: */[
        Style$BsReactNative.top(/* Pt */Block.__(0, [5.0])),
        /* :: */[
          Style$BsReactNative.right(/* Pt */Block.__(0, [0.0])),
          /* :: */[
            Style$BsReactNative.zIndex(3),
            /* :: */[
              Style$BsReactNative.borderRadius(12.0),
              /* :: */[
                Style$BsReactNative.backgroundColor(Colors$Mxdbmobile.Css[/* white */1]),
                /* [] */0
              ]
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
  /* singleIconContainer */singleIconContainer,
  /* doubleIconContainer */doubleIconContainer,
  /* tripleIconContainer */tripleIconContainer,
  /* doubleIcon */doubleIcon,
  /* firstDouble */firstDouble,
  /* secondDouble */secondDouble,
  /* tripleIcon */tripleIcon,
  /* firstTriple */firstTriple,
  /* secondTriple */secondTriple,
  /* thirdTriple */thirdTriple,
  /* rank */rank,
  /* strength */strength,
  /* intelligence */intelligence,
  /* special */special
];

var component = ReasonReact.statelessComponent("BattleStat");

function make(stat, _) {
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
              var child;
              switch (stat.tag | 0) {
                case 0 : 
                    child = ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[singleIconContainer], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[
                              ReasonReact.element(/* None */0, /* None */0, Icon$Mxdbmobile.make("strength", /* Some */[strength], /* None */0, /* array */[])),
                              ReasonReact.element(/* None */0, /* None */0, Text$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[rank], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* array */[String(stat[0])]))
                            ]));
                    break;
                case 1 : 
                    child = ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[singleIconContainer], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[
                              ReasonReact.element(/* None */0, /* None */0, Icon$Mxdbmobile.make("intelligence", /* Some */[intelligence], /* None */0, /* array */[])),
                              ReasonReact.element(/* None */0, /* None */0, Text$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[rank], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* array */[String(stat[0])]))
                            ]));
                    break;
                case 2 : 
                    child = ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[singleIconContainer], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[
                              ReasonReact.element(/* None */0, /* None */0, Icon$Mxdbmobile.make("special", /* Some */[special], /* None */0, /* array */[])),
                              ReasonReact.element(/* None */0, /* None */0, Text$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[rank], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* array */[String(stat[0])]))
                            ]));
                    break;
                case 3 : 
                    child = ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[doubleIconContainer], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[
                              ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[doubleIcon], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[
                                        ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[firstDouble], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[ReasonReact.element(/* None */0, /* None */0, Icon$Mxdbmobile.make("strength", /* Some */[strength], /* None */0, /* array */[]))])),
                                        ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[secondDouble], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[ReasonReact.element(/* None */0, /* None */0, Icon$Mxdbmobile.make("intelligence", /* Some */[intelligence], /* None */0, /* array */[]))]))
                                      ])),
                              ReasonReact.element(/* None */0, /* None */0, Text$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[rank], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* array */[String(stat[0])]))
                            ]));
                    break;
                case 4 : 
                    child = ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[doubleIconContainer], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[
                              ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[doubleIcon], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[
                                        ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[firstDouble], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[ReasonReact.element(/* None */0, /* None */0, Icon$Mxdbmobile.make("intelligence", /* Some */[intelligence], /* None */0, /* array */[]))])),
                                        ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[secondDouble], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[ReasonReact.element(/* None */0, /* None */0, Icon$Mxdbmobile.make("special", /* Some */[special], /* None */0, /* array */[]))]))
                                      ])),
                              ReasonReact.element(/* None */0, /* None */0, Text$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[rank], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* array */[String(stat[0])]))
                            ]));
                    break;
                case 5 : 
                    child = ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[doubleIconContainer], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[
                              ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[doubleIcon], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[
                                        ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[firstDouble], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[ReasonReact.element(/* None */0, /* None */0, Icon$Mxdbmobile.make("strength", /* Some */[strength], /* None */0, /* array */[]))])),
                                        ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[secondDouble], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[ReasonReact.element(/* None */0, /* None */0, Icon$Mxdbmobile.make("special", /* Some */[special], /* None */0, /* array */[]))]))
                                      ])),
                              ReasonReact.element(/* None */0, /* None */0, Text$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[rank], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* array */[String(stat[0])]))
                            ]));
                    break;
                case 6 : 
                    child = ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[tripleIconContainer], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[
                              ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[tripleIcon], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[
                                        ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[firstTriple], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[ReasonReact.element(/* None */0, /* None */0, Icon$Mxdbmobile.make("strength", /* Some */[strength], /* None */0, /* array */[]))])),
                                        ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[secondTriple], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[ReasonReact.element(/* None */0, /* None */0, Icon$Mxdbmobile.make("intelligence", /* Some */[intelligence], /* None */0, /* array */[]))])),
                                        ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[thirdTriple], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[ReasonReact.element(/* None */0, /* None */0, Icon$Mxdbmobile.make("special", /* Some */[special], /* None */0, /* array */[]))]))
                                      ])),
                              ReasonReact.element(/* None */0, /* None */0, Text$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[rank], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* array */[String(stat[0])]))
                            ]));
                    break;
                
              }
              return ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[container], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[child]));
            }),
          /* initialState */component[/* initialState */10],
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */component[/* reducer */12],
          /* subscriptions */component[/* subscriptions */13],
          /* jsElementWrapped */component[/* jsElementWrapped */14]
        ];
}

exports.fromStatList = fromStatList;
exports.decoder = decoder;
exports.Styles = Styles;
exports.component = component;
exports.make = make;
/* container Not a pure module */
