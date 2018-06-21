'use strict';

var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var Fetch = require("bs-fetch/src/Fetch.js");
var Js_dict = require("bs-platform/lib/js/js_dict.js");
var Js_json = require("bs-platform/lib/js/js_json.js");
var ReasonReact = require("reason-react/src/ReasonReact.js");
var Caml_exceptions = require("bs-platform/lib/js/caml_exceptions.js");
var NBIcon$Mxdbmobile = require("./native-base/NBIcon.js");
var NBItem$Mxdbmobile = require("./native-base/NBItem.js");
var NBInput$Mxdbmobile = require("./native-base/NBInput.js");
var Text$BsReactNative = require("bs-react-native/src/components/text.js");
var View$BsReactNative = require("bs-react-native/src/components/view.js");
var Image$BsReactNative = require("bs-react-native/src/components/image.js");
var NBButton$Mxdbmobile = require("./native-base/NBButton.js");
var NBHeader$Mxdbmobile = require("./native-base/NBHeader.js");
var Style$BsReactNative = require("bs-react-native/src/style.js");
var NBContent$Mxdbmobile = require("./native-base/NBContent.js");
var ReRoute$RerouteNative = require("reroute-native/src/ReRoute.js");
var NBContainer$Mxdbmobile = require("./native-base/NBContainer.js");
var SectionList$BsReactNative = require("bs-react-native/src/components/sectionList.js");

var Routes = /* module */[];

var include = ReRoute$RerouteNative.CreateNavigation(Routes);

var TabNavigator = include[1];

var Graphql_error = Caml_exceptions.create("App-Mxdbmobile.Graphql_error");

function sendQuery(q) {
  return fetch("https://api.graph.cool/simple/v1/metaxdb", Fetch.RequestInit[/* make */0](/* Some */[/* Post */2], /* Some */[{
                        "Content-Type": "application/json"
                      }], /* Some */[JSON.stringify(Js_dict.fromList(/* :: */[
                                /* tuple */[
                                  "query",
                                  q.query
                                ],
                                /* :: */[
                                  /* tuple */[
                                    "variables",
                                    q.variables
                                  ],
                                  /* [] */0
                                ]
                              ]))], /* None */0, /* None */0, /* None */0, /* Some */[/* Include */2], /* None */0, /* None */0, /* None */0, /* None */0)(/* () */0)).then((function (resp) {
                if (resp.ok) {
                  return resp.json().then((function (data) {
                                var match = Js_json.decodeObject(data);
                                if (match) {
                                  return Promise.resolve(Curry._1(q.parse, match[0]["data"]));
                                } else {
                                  return Promise.reject([
                                              Graphql_error,
                                              "Response is not an object"
                                            ]);
                                }
                              }));
                } else {
                  return Promise.reject([
                              Graphql_error,
                              "Request failed: " + resp.statusText
                            ]);
                }
              }));
}

function tapLog(res) {
  console.log(res);
  return Promise.resolve(res);
}

var component = ReasonReact.statelessComponent("CardImage");

var container = Style$BsReactNative.style(/* [] */0);

var thumbnail = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.height(/* Pt */Block.__(0, [100])),
      /* :: */[
        Style$BsReactNative.width(/* Pt */Block.__(0, [72])),
        /* [] */0
      ]
    ]);

var Styles = /* module */[
  /* container */container,
  /* thumbnail */thumbnail
];

function make(thumbnail$1, _) {
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
              return ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[container], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[ReasonReact.element(/* None */0, /* None */0, Image$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[/* URI */Block.__(0, [Image$BsReactNative.imageURISource(thumbnail$1, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* () */0)])], /* Some */[thumbnail], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[]))]));
            }),
          /* initialState */component[/* initialState */10],
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */component[/* reducer */12],
          /* subscriptions */component[/* subscriptions */13],
          /* jsElementWrapped */component[/* jsElementWrapped */14]
        ];
}

var CardImage = /* module */[
  /* component */component,
  /* Styles */Styles,
  /* make */make
];

var component$1 = ReasonReact.statelessComponent("CardEffect");

var container$1 = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.flex(1),
      /* :: */[
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
      ]
    ]);

var normalIcon = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.maxWidth(/* Pt */Block.__(0, [15])),
      /* [] */0
    ]);

var weirdIcon = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.maxWidth(/* Pt */Block.__(0, [20])),
      /* [] */0
    ]);

var effectWithoutSymbol = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.flex(1),
      /* [] */0
    ]);

var effectWithSymbol = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.flex(1),
      /* :: */[
        Style$BsReactNative.paddingLeft(/* Pt */Block.__(0, [4])),
        /* :: */[
          Style$BsReactNative.marginLeft(/* Pt */Block.__(0, [4])),
          /* :: */[
            Style$BsReactNative.borderLeftWidth(2),
            /* :: */[
              Style$BsReactNative.borderLeftColor(/* String */Block.__(0, ["#d3d3d3"])),
              /* :: */[
                Style$BsReactNative.borderStyle(/* Solid */0),
                /* [] */0
              ]
            ]
          ]
        ]
      ]
    ]);

var Styles$1 = /* module */[
  /* container */container$1,
  /* normalIcon */normalIcon,
  /* weirdIcon */weirdIcon,
  /* effectWithoutSymbol */effectWithoutSymbol,
  /* effectWithSymbol */effectWithSymbol
];

function make$1(symbol, effect, _) {
  var symbolImage = symbol >= 425991990 ? (
      symbol >= 890959348 ? (
          symbol >= 891410906 ? ReasonReact.element(/* None */0, /* None */0, Image$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[/* contain */427065300], /* Some */[/* Required */Block.__(1, [require("./assets/push.png")])], /* Some */[normalIcon], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[])) : ReasonReact.element(/* None */0, /* None */0, Image$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[/* contain */427065300], /* Some */[/* Required */Block.__(1, [require("./assets/play.png")])], /* Some */[normalIcon], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[]))
        ) : (
          symbol >= 868932280 ? ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[])) : ReasonReact.element(/* None */0, /* None */0, Image$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[/* contain */427065300], /* Some */[/* Required */Block.__(1, [require("./assets/defend.png")])], /* Some */[normalIcon], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[]))
        )
    ) : (
      symbol >= 311601096 ? ReasonReact.element(/* None */0, /* None */0, Image$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[/* contain */427065300], /* Some */[/* Required */Block.__(1, [require("./assets/attack.png")])], /* Some */[normalIcon], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[])) : ReasonReact.element(/* None */0, /* None */0, Image$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[/* contain */427065300], /* Some */[/* Required */Block.__(1, [require("./assets/constant.png")])], /* Some */[weirdIcon], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[]))
    );
  var effectStyle = symbol !== 868932280 ? effectWithSymbol : effectWithoutSymbol;
  return /* record */[
          /* debugName */component$1[/* debugName */0],
          /* reactClassInternal */component$1[/* reactClassInternal */1],
          /* handedOffState */component$1[/* handedOffState */2],
          /* willReceiveProps */component$1[/* willReceiveProps */3],
          /* didMount */component$1[/* didMount */4],
          /* didUpdate */component$1[/* didUpdate */5],
          /* willUnmount */component$1[/* willUnmount */6],
          /* willUpdate */component$1[/* willUpdate */7],
          /* shouldUpdate */component$1[/* shouldUpdate */8],
          /* render */(function () {
              return ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[container$1], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[
                              symbolImage,
                              ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[effectStyle], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[ReasonReact.element(/* None */0, /* None */0, Text$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* array */[effect]))]))
                            ]));
            }),
          /* initialState */component$1[/* initialState */10],
          /* retainedProps */component$1[/* retainedProps */11],
          /* reducer */component$1[/* reducer */12],
          /* subscriptions */component$1[/* subscriptions */13],
          /* jsElementWrapped */component$1[/* jsElementWrapped */14]
        ];
}

var CardEffect = /* module */[
  /* component */component$1,
  /* Styles */Styles$1,
  /* make */make$1
];

var component$2 = ReasonReact.statelessComponent("CardDetails");

var container$2 = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.flex(1),
      /* :: */[
        Style$BsReactNative.flexDirection(/* Column */2),
        /* :: */[
          Style$BsReactNative.paddingLeft(/* Pt */Block.__(0, [8])),
          /* [] */0
        ]
      ]
    ]);

var title = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.fontWeight(/* Bold */737455525),
      /* [] */0
    ]);

var subtitle = Style$BsReactNative.style(/* [] */0);

var Styles$2 = /* module */[
  /* container */container$2,
  /* title */title,
  /* subtitle */subtitle
];

function make$2(title$1, subtitle$1, effect, symbol, _) {
  return /* record */[
          /* debugName */component$2[/* debugName */0],
          /* reactClassInternal */component$2[/* reactClassInternal */1],
          /* handedOffState */component$2[/* handedOffState */2],
          /* willReceiveProps */component$2[/* willReceiveProps */3],
          /* didMount */component$2[/* didMount */4],
          /* didUpdate */component$2[/* didUpdate */5],
          /* willUnmount */component$2[/* willUnmount */6],
          /* willUpdate */component$2[/* willUpdate */7],
          /* shouldUpdate */component$2[/* shouldUpdate */8],
          /* render */(function () {
              return ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[container$2], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[
                              ReasonReact.element(/* None */0, /* None */0, Text$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[title], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* array */[title$1])),
                              ReasonReact.element(/* None */0, /* None */0, Text$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[subtitle], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* array */[subtitle$1])),
                              ReasonReact.element(/* None */0, /* None */0, make$1(symbol, effect, /* array */[]))
                            ]));
            }),
          /* initialState */component$2[/* initialState */10],
          /* retainedProps */component$2[/* retainedProps */11],
          /* reducer */component$2[/* reducer */12],
          /* subscriptions */component$2[/* subscriptions */13],
          /* jsElementWrapped */component$2[/* jsElementWrapped */14]
        ];
}

var CardDetails = /* module */[
  /* component */component$2,
  /* Styles */Styles$2,
  /* make */make$2
];

var component$3 = ReasonReact.statelessComponent("CardListItem");

var cardListItem = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.flex(1),
      /* :: */[
        Style$BsReactNative.flexDirection(/* Row */0),
        /* :: */[
          Style$BsReactNative.marginLeft(/* Pt */Block.__(0, [8])),
          /* :: */[
            Style$BsReactNative.marginRight(/* Pt */Block.__(0, [8])),
            /* :: */[
              Style$BsReactNative.marginTop(/* Pt */Block.__(0, [4])),
              /* :: */[
                Style$BsReactNative.marginBottom(/* Pt */Block.__(0, [4])),
                /* :: */[
                  Style$BsReactNative.padding(/* Pt */Block.__(0, [4])),
                  /* :: */[
                    Style$BsReactNative.borderStyle(/* Solid */0),
                    /* :: */[
                      Style$BsReactNative.borderWidth(1),
                      /* :: */[
                        Style$BsReactNative.borderColor(/* String */Block.__(0, ["#d3d3d3"])),
                        /* :: */[
                          Style$BsReactNative.borderRadius(3),
                          /* [] */0
                        ]
                      ]
                    ]
                  ]
                ]
              ]
            ]
          ]
        ]
      ]
    ]);

var Styles$3 = /* module */[/* cardListItem */cardListItem];

function make$3(title, subtitle, thumbnail, effect, symbol, _) {
  return /* record */[
          /* debugName */component$3[/* debugName */0],
          /* reactClassInternal */component$3[/* reactClassInternal */1],
          /* handedOffState */component$3[/* handedOffState */2],
          /* willReceiveProps */component$3[/* willReceiveProps */3],
          /* didMount */component$3[/* didMount */4],
          /* didUpdate */component$3[/* didUpdate */5],
          /* willUnmount */component$3[/* willUnmount */6],
          /* willUpdate */component$3[/* willUpdate */7],
          /* shouldUpdate */component$3[/* shouldUpdate */8],
          /* render */(function () {
              return ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[cardListItem], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[
                              ReasonReact.element(/* None */0, /* None */0, make(thumbnail, /* array */[])),
                              ReasonReact.element(/* None */0, /* None */0, make$2(title, subtitle, effect, symbol, /* array */[]))
                            ]));
            }),
          /* initialState */component$3[/* initialState */10],
          /* retainedProps */component$3[/* retainedProps */11],
          /* reducer */component$3[/* reducer */12],
          /* subscriptions */component$3[/* subscriptions */13],
          /* jsElementWrapped */component$3[/* jsElementWrapped */14]
        ];
}

var CardListItem = /* module */[
  /* component */component$3,
  /* Styles */Styles$3,
  /* make */make$3
];

var Graphql_error$1 = Caml_exceptions.create("App-Mxdbmobile.ListOfCards.CardQuery.Graphql_error");

var ppx_printed_query = "query   {\ncharacters: allCards(filter: {type: Character}, orderBy: title_ASC)  {\nuid  \ntitle  \nsubtitle  \neffect  {\nsymbol  \ntext  \n}\nimage  {\nthumbnail  \n}\n}\nevents: allCards(filter: {type: Event}, orderBy: title_ASC)  {\nuid  \ntitle  \nsubtitle  \neffect  {\nsymbol  \ntext  \n}\nimage  {\nthumbnail  \n}\n}\nbattles: allCards(filter: {type: Battle}, orderBy: title_ASC)  {\nuid  \ntitle  \nsubtitle  \neffect  {\nsymbol  \ntext  \n}\nimage  {\nthumbnail  \n}\n}\n}";

function parse(value) {
  var match = Js_json.decodeObject(value);
  if (match) {
    var value$1 = match[0];
    var value$2 = value$1["characters"];
    var match$1 = Js_json.decodeArray(value$2);
    var tmp;
    if (match$1) {
      tmp = match$1[0].map((function (value) {
              var match = Js_json.decodeObject(value);
              if (match) {
                var value$1 = match[0];
                var value$2 = value$1["uid"];
                var match$1 = Js_json.decodeString(value$2);
                var tmp;
                if (match$1) {
                  tmp = match$1[0];
                } else {
                  throw Graphql_error$1;
                }
                var value$3 = value$1["title"];
                var match$2 = Js_json.decodeString(value$3);
                var tmp$1;
                if (match$2) {
                  tmp$1 = match$2[0];
                } else {
                  throw Graphql_error$1;
                }
                var value$4 = value$1["subtitle"];
                var match$3 = Js_json.decodeNull(value$4);
                var tmp$2;
                if (match$3) {
                  tmp$2 = /* None */0;
                } else {
                  var match$4 = Js_json.decodeString(value$4);
                  var tmp$3;
                  if (match$4) {
                    tmp$3 = match$4[0];
                  } else {
                    throw Graphql_error$1;
                  }
                  tmp$2 = /* Some */[tmp$3];
                }
                var value$5 = value$1["effect"];
                var match$5 = Js_json.decodeNull(value$5);
                var tmp$4;
                if (match$5) {
                  tmp$4 = /* None */0;
                } else {
                  var match$6 = Js_json.decodeObject(value$5);
                  var tmp$5;
                  if (match$6) {
                    var value$6 = match$6[0];
                    var value$7 = value$6["symbol"];
                    var match$7 = Js_json.decodeString(value$7);
                    var tmp$6;
                    if (match$7) {
                      switch (match$7[0]) {
                        case "ATTACK" : 
                            tmp$6 = /* ATTACK */311601096;
                            break;
                        case "CONSTANT" : 
                            tmp$6 = /* CONSTANT */-14462620;
                            break;
                        case "DEFEND" : 
                            tmp$6 = /* DEFEND */425991990;
                            break;
                        case "NONE" : 
                            tmp$6 = /* NONE */868932280;
                            break;
                        case "PLAY" : 
                            tmp$6 = /* PLAY */890959348;
                            break;
                        case "PUSH" : 
                            tmp$6 = /* PUSH */891410906;
                            break;
                        default:
                          throw Graphql_error$1;
                      }
                    } else {
                      throw Graphql_error$1;
                    }
                    var value$8 = value$6["text"];
                    var match$8 = Js_json.decodeNull(value$8);
                    var tmp$7;
                    if (match$8) {
                      tmp$7 = /* None */0;
                    } else {
                      var match$9 = Js_json.decodeString(value$8);
                      var tmp$8;
                      if (match$9) {
                        tmp$8 = match$9[0];
                      } else {
                        throw Graphql_error$1;
                      }
                      tmp$7 = /* Some */[tmp$8];
                    }
                    tmp$5 = {
                      symbol: tmp$6,
                      text: tmp$7
                    };
                  } else {
                    throw Graphql_error$1;
                  }
                  tmp$4 = /* Some */[tmp$5];
                }
                var value$9 = value$1["image"];
                var match$10 = Js_json.decodeNull(value$9);
                var tmp$9;
                if (match$10) {
                  tmp$9 = /* None */0;
                } else {
                  var match$11 = Js_json.decodeObject(value$9);
                  var tmp$10;
                  if (match$11) {
                    var value$10 = match$11[0]["thumbnail"];
                    var match$12 = Js_json.decodeString(value$10);
                    var tmp$11;
                    if (match$12) {
                      tmp$11 = match$12[0];
                    } else {
                      throw Graphql_error$1;
                    }
                    tmp$10 = {
                      thumbnail: tmp$11
                    };
                  } else {
                    throw Graphql_error$1;
                  }
                  tmp$9 = /* Some */[tmp$10];
                }
                return {
                        uid: tmp,
                        title: tmp$1,
                        subtitle: tmp$2,
                        effect: tmp$4,
                        image: tmp$9
                      };
              } else {
                throw Graphql_error$1;
              }
            }));
    } else {
      throw Graphql_error$1;
    }
    var value$3 = value$1["events"];
    var match$2 = Js_json.decodeArray(value$3);
    var tmp$1;
    if (match$2) {
      tmp$1 = match$2[0].map((function (value) {
              var match = Js_json.decodeObject(value);
              if (match) {
                var value$1 = match[0];
                var value$2 = value$1["uid"];
                var match$1 = Js_json.decodeString(value$2);
                var tmp;
                if (match$1) {
                  tmp = match$1[0];
                } else {
                  throw Graphql_error$1;
                }
                var value$3 = value$1["title"];
                var match$2 = Js_json.decodeString(value$3);
                var tmp$1;
                if (match$2) {
                  tmp$1 = match$2[0];
                } else {
                  throw Graphql_error$1;
                }
                var value$4 = value$1["subtitle"];
                var match$3 = Js_json.decodeNull(value$4);
                var tmp$2;
                if (match$3) {
                  tmp$2 = /* None */0;
                } else {
                  var match$4 = Js_json.decodeString(value$4);
                  var tmp$3;
                  if (match$4) {
                    tmp$3 = match$4[0];
                  } else {
                    throw Graphql_error$1;
                  }
                  tmp$2 = /* Some */[tmp$3];
                }
                var value$5 = value$1["effect"];
                var match$5 = Js_json.decodeNull(value$5);
                var tmp$4;
                if (match$5) {
                  tmp$4 = /* None */0;
                } else {
                  var match$6 = Js_json.decodeObject(value$5);
                  var tmp$5;
                  if (match$6) {
                    var value$6 = match$6[0];
                    var value$7 = value$6["symbol"];
                    var match$7 = Js_json.decodeString(value$7);
                    var tmp$6;
                    if (match$7) {
                      switch (match$7[0]) {
                        case "ATTACK" : 
                            tmp$6 = /* ATTACK */311601096;
                            break;
                        case "CONSTANT" : 
                            tmp$6 = /* CONSTANT */-14462620;
                            break;
                        case "DEFEND" : 
                            tmp$6 = /* DEFEND */425991990;
                            break;
                        case "NONE" : 
                            tmp$6 = /* NONE */868932280;
                            break;
                        case "PLAY" : 
                            tmp$6 = /* PLAY */890959348;
                            break;
                        case "PUSH" : 
                            tmp$6 = /* PUSH */891410906;
                            break;
                        default:
                          throw Graphql_error$1;
                      }
                    } else {
                      throw Graphql_error$1;
                    }
                    var value$8 = value$6["text"];
                    var match$8 = Js_json.decodeNull(value$8);
                    var tmp$7;
                    if (match$8) {
                      tmp$7 = /* None */0;
                    } else {
                      var match$9 = Js_json.decodeString(value$8);
                      var tmp$8;
                      if (match$9) {
                        tmp$8 = match$9[0];
                      } else {
                        throw Graphql_error$1;
                      }
                      tmp$7 = /* Some */[tmp$8];
                    }
                    tmp$5 = {
                      symbol: tmp$6,
                      text: tmp$7
                    };
                  } else {
                    throw Graphql_error$1;
                  }
                  tmp$4 = /* Some */[tmp$5];
                }
                var value$9 = value$1["image"];
                var match$10 = Js_json.decodeNull(value$9);
                var tmp$9;
                if (match$10) {
                  tmp$9 = /* None */0;
                } else {
                  var match$11 = Js_json.decodeObject(value$9);
                  var tmp$10;
                  if (match$11) {
                    var value$10 = match$11[0]["thumbnail"];
                    var match$12 = Js_json.decodeString(value$10);
                    var tmp$11;
                    if (match$12) {
                      tmp$11 = match$12[0];
                    } else {
                      throw Graphql_error$1;
                    }
                    tmp$10 = {
                      thumbnail: tmp$11
                    };
                  } else {
                    throw Graphql_error$1;
                  }
                  tmp$9 = /* Some */[tmp$10];
                }
                return {
                        uid: tmp,
                        title: tmp$1,
                        subtitle: tmp$2,
                        effect: tmp$4,
                        image: tmp$9
                      };
              } else {
                throw Graphql_error$1;
              }
            }));
    } else {
      throw Graphql_error$1;
    }
    var value$4 = value$1["battles"];
    var match$3 = Js_json.decodeArray(value$4);
    var tmp$2;
    if (match$3) {
      tmp$2 = match$3[0].map((function (value) {
              var match = Js_json.decodeObject(value);
              if (match) {
                var value$1 = match[0];
                var value$2 = value$1["uid"];
                var match$1 = Js_json.decodeString(value$2);
                var tmp;
                if (match$1) {
                  tmp = match$1[0];
                } else {
                  throw Graphql_error$1;
                }
                var value$3 = value$1["title"];
                var match$2 = Js_json.decodeString(value$3);
                var tmp$1;
                if (match$2) {
                  tmp$1 = match$2[0];
                } else {
                  throw Graphql_error$1;
                }
                var value$4 = value$1["subtitle"];
                var match$3 = Js_json.decodeNull(value$4);
                var tmp$2;
                if (match$3) {
                  tmp$2 = /* None */0;
                } else {
                  var match$4 = Js_json.decodeString(value$4);
                  var tmp$3;
                  if (match$4) {
                    tmp$3 = match$4[0];
                  } else {
                    throw Graphql_error$1;
                  }
                  tmp$2 = /* Some */[tmp$3];
                }
                var value$5 = value$1["effect"];
                var match$5 = Js_json.decodeNull(value$5);
                var tmp$4;
                if (match$5) {
                  tmp$4 = /* None */0;
                } else {
                  var match$6 = Js_json.decodeObject(value$5);
                  var tmp$5;
                  if (match$6) {
                    var value$6 = match$6[0];
                    var value$7 = value$6["symbol"];
                    var match$7 = Js_json.decodeString(value$7);
                    var tmp$6;
                    if (match$7) {
                      switch (match$7[0]) {
                        case "ATTACK" : 
                            tmp$6 = /* ATTACK */311601096;
                            break;
                        case "CONSTANT" : 
                            tmp$6 = /* CONSTANT */-14462620;
                            break;
                        case "DEFEND" : 
                            tmp$6 = /* DEFEND */425991990;
                            break;
                        case "NONE" : 
                            tmp$6 = /* NONE */868932280;
                            break;
                        case "PLAY" : 
                            tmp$6 = /* PLAY */890959348;
                            break;
                        case "PUSH" : 
                            tmp$6 = /* PUSH */891410906;
                            break;
                        default:
                          throw Graphql_error$1;
                      }
                    } else {
                      throw Graphql_error$1;
                    }
                    var value$8 = value$6["text"];
                    var match$8 = Js_json.decodeNull(value$8);
                    var tmp$7;
                    if (match$8) {
                      tmp$7 = /* None */0;
                    } else {
                      var match$9 = Js_json.decodeString(value$8);
                      var tmp$8;
                      if (match$9) {
                        tmp$8 = match$9[0];
                      } else {
                        throw Graphql_error$1;
                      }
                      tmp$7 = /* Some */[tmp$8];
                    }
                    tmp$5 = {
                      symbol: tmp$6,
                      text: tmp$7
                    };
                  } else {
                    throw Graphql_error$1;
                  }
                  tmp$4 = /* Some */[tmp$5];
                }
                var value$9 = value$1["image"];
                var match$10 = Js_json.decodeNull(value$9);
                var tmp$9;
                if (match$10) {
                  tmp$9 = /* None */0;
                } else {
                  var match$11 = Js_json.decodeObject(value$9);
                  var tmp$10;
                  if (match$11) {
                    var value$10 = match$11[0]["thumbnail"];
                    var match$12 = Js_json.decodeString(value$10);
                    var tmp$11;
                    if (match$12) {
                      tmp$11 = match$12[0];
                    } else {
                      throw Graphql_error$1;
                    }
                    tmp$10 = {
                      thumbnail: tmp$11
                    };
                  } else {
                    throw Graphql_error$1;
                  }
                  tmp$9 = /* Some */[tmp$10];
                }
                return {
                        uid: tmp,
                        title: tmp$1,
                        subtitle: tmp$2,
                        effect: tmp$4,
                        image: tmp$9
                      };
              } else {
                throw Graphql_error$1;
              }
            }));
    } else {
      throw Graphql_error$1;
    }
    return {
            characters: tmp,
            events: tmp$1,
            battles: tmp$2
          };
  } else {
    throw Graphql_error$1;
  }
}

function make$4() {
  return {
          query: ppx_printed_query,
          variables: null,
          parse: parse
        };
}

function makeWithVariables() {
  return {
          query: ppx_printed_query,
          variables: null,
          parse: parse
        };
}

function ret_type() {
  return /* module */[];
}

var MT_Ret = /* module */[];

var CardQuery = /* module */[
  /* Graphql_error */Graphql_error$1,
  /* ppx_printed_query */ppx_printed_query,
  /* query */ppx_printed_query,
  /* parse */parse,
  /* make */make$4,
  /* makeWithVariables */makeWithVariables,
  /* ret_type */ret_type,
  /* MT_Ret */MT_Ret
];

var component$4 = ReasonReact.reducerComponent("ListOfCards");

var container$3 = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.flex(1),
      /* [] */0
    ]);

var Styles$4 = /* module */[/* container */container$3];

function renderSectionHeader(param) {
  return SectionList$BsReactNative.renderAccessoryView((function (param) {
                var match = param[/* section */0][/* key */1];
                var title = match ? match[0] : "";
                return ReasonReact.element(/* None */0, /* None */0, Text$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* array */[title]));
              }), param);
}

function renderItem(param) {
  return SectionList$BsReactNative.renderItem((function (param) {
                var item = param[/* item */0];
                var match = item.image;
                var thumbnail = match ? match[0].thumbnail : "";
                var title = item.title;
                var match$1 = item.subtitle;
                var subtitle = match$1 ? match$1[0] : "";
                var match$2 = item.effect;
                var effect;
                if (match$2) {
                  var match$3 = match$2[0].text;
                  effect = match$3 ? match$3[0] : "";
                } else {
                  effect = "";
                }
                var match$4 = item.effect;
                var symbol = match$4 ? match$4[0].symbol : /* NONE */868932280;
                return ReasonReact.element(/* None */0, /* None */0, make$3(title, subtitle, thumbnail, effect, symbol, /* array */[]));
              }), param);
}

function make$5() {
  return /* record */[
          /* debugName */component$4[/* debugName */0],
          /* reactClassInternal */component$4[/* reactClassInternal */1],
          /* handedOffState */component$4[/* handedOffState */2],
          /* willReceiveProps */component$4[/* willReceiveProps */3],
          /* didMount */(function (self) {
              return Curry._1(self[/* send */3], /* FetchCards */0);
            }),
          /* didUpdate */component$4[/* didUpdate */5],
          /* willUnmount */component$4[/* willUnmount */6],
          /* willUpdate */component$4[/* willUpdate */7],
          /* shouldUpdate */component$4[/* shouldUpdate */8],
          /* render */(function (self) {
              var sections = SectionList$BsReactNative.sections(/* array */[
                    SectionList$BsReactNative.section(self[/* state */1][/* characters */0], /* Some */["Characters"], /* None */0, /* () */0),
                    SectionList$BsReactNative.section(self[/* state */1][/* events */1], /* Some */["Events"], /* None */0, /* () */0),
                    SectionList$BsReactNative.section(self[/* state */1][/* battles */2], /* Some */["Battle Cards"], /* None */0, /* () */0)
                  ]);
              return ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[container$3], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[ReasonReact.element(/* None */0, /* None */0, SectionList$BsReactNative.make(sections, renderItem, (function (item, _) {
                                          return item.uid;
                                        }), /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[renderSectionHeader], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* array */[]))]));
            }),
          /* initialState */(function () {
              return /* record */[
                      /* characters : array */[],
                      /* events : array */[],
                      /* battles : array */[]
                    ];
            }),
          /* retainedProps */component$4[/* retainedProps */11],
          /* reducer */(function (action, _) {
              if (action) {
                var cards = action[0];
                return /* Update */Block.__(0, [/* record */[
                            /* characters */cards.characters,
                            /* events */cards.events,
                            /* battles */cards.battles
                          ]]);
              } else {
                return /* SideEffects */Block.__(1, [(function (self) {
                              sendQuery(make$4(/* () */0)).then(tapLog).then((function (cards) {
                                      Curry._1(self[/* send */3], /* StoreCards */[cards]);
                                      return Promise.resolve(cards);
                                    }));
                              return /* () */0;
                            })]);
              }
            }),
          /* subscriptions */component$4[/* subscriptions */13],
          /* jsElementWrapped */component$4[/* jsElementWrapped */14]
        ];
}

var ListOfCards = /* module */[
  /* CardQuery */CardQuery,
  /* component */component$4,
  /* Styles */Styles$4,
  /* renderSectionHeader */renderSectionHeader,
  /* renderItem */renderItem,
  /* make */make$5
];

var component$5 = ReasonReact.statelessComponent("CardList");

function tabItem(param) {
  return ReasonReact.element(/* None */0, /* None */0, Curry._4(TabNavigator[/* TabBar */2][/* Item */0][/* make */0], "Cards", /* None */0, /* Some */[Style$BsReactNative.style(/* :: */[
                        Style$BsReactNative.color(/* String */Block.__(0, [param[/* isActive */0] ? "blue" : "gray"])),
                        /* [] */0
                      ])], /* array */[]));
}

function make$6(navigation, _) {
  return /* record */[
          /* debugName */component$5[/* debugName */0],
          /* reactClassInternal */component$5[/* reactClassInternal */1],
          /* handedOffState */component$5[/* handedOffState */2],
          /* willReceiveProps */component$5[/* willReceiveProps */3],
          /* didMount */component$5[/* didMount */4],
          /* didUpdate */component$5[/* didUpdate */5],
          /* willUnmount */component$5[/* willUnmount */6],
          /* willUpdate */component$5[/* willUpdate */7],
          /* shouldUpdate */component$5[/* shouldUpdate */8],
          /* render */(function () {
              return ReasonReact.element(/* None */0, /* None */0, Curry._3(TabNavigator[/* Screen */1][/* make */0], navigation, tabItem, (function () {
                                return ReasonReact.element(/* None */0, /* None */0, make$5(/* array */[]));
                              })));
            }),
          /* initialState */component$5[/* initialState */10],
          /* retainedProps */component$5[/* retainedProps */11],
          /* reducer */component$5[/* reducer */12],
          /* subscriptions */component$5[/* subscriptions */13],
          /* jsElementWrapped */component$5[/* jsElementWrapped */14]
        ];
}

var CardList = /* module */[
  /* component */component$5,
  /* tabItem */tabItem,
  /* make */make$6
];

var component$6 = ReasonReact.statelessComponent("DeckList");

var container$4 = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.flex(1),
      /* [] */0
    ]);

var Styles$5 = /* module */[/* container */container$4];

function tabItem$1(param) {
  return ReasonReact.element(/* None */0, /* None */0, Curry._4(TabNavigator[/* TabBar */2][/* Item */0][/* make */0], "Deck (0)", /* None */0, /* Some */[Style$BsReactNative.style(/* :: */[
                        Style$BsReactNative.color(/* String */Block.__(0, [param[/* isActive */0] ? "blue" : "gray"])),
                        /* [] */0
                      ])], /* array */[]));
}

function make$7(navigation, _) {
  return /* record */[
          /* debugName */component$6[/* debugName */0],
          /* reactClassInternal */component$6[/* reactClassInternal */1],
          /* handedOffState */component$6[/* handedOffState */2],
          /* willReceiveProps */component$6[/* willReceiveProps */3],
          /* didMount */component$6[/* didMount */4],
          /* didUpdate */component$6[/* didUpdate */5],
          /* willUnmount */component$6[/* willUnmount */6],
          /* willUpdate */component$6[/* willUpdate */7],
          /* shouldUpdate */component$6[/* shouldUpdate */8],
          /* render */(function () {
              return ReasonReact.element(/* None */0, /* None */0, Curry._3(TabNavigator[/* Screen */1][/* make */0], navigation, tabItem$1, (function () {
                                return ReasonReact.element(/* None */0, /* None */0, NBContent$Mxdbmobile.make(/* array */[ReasonReact.element(/* None */0, /* None */0, Text$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* array */["Deck"]))]));
                              })));
            }),
          /* initialState */component$6[/* initialState */10],
          /* retainedProps */component$6[/* retainedProps */11],
          /* reducer */component$6[/* reducer */12],
          /* subscriptions */component$6[/* subscriptions */13],
          /* jsElementWrapped */component$6[/* jsElementWrapped */14]
        ];
}

var DeckList = /* module */[
  /* component */component$6,
  /* Styles */Styles$5,
  /* tabItem */tabItem$1,
  /* make */make$7
];

function app() {
  return ReasonReact.element(/* None */0, /* None */0, NBContainer$Mxdbmobile.make(/* array */[
                  ReasonReact.element(/* None */0, /* None */0, NBHeader$Mxdbmobile.make(/* Some */[true], /* Some */[true], /* array */[
                            ReasonReact.element(/* None */0, /* None */0, NBItem$Mxdbmobile.make(/* array */[
                                      ReasonReact.element(/* None */0, /* None */0, NBIcon$Mxdbmobile.make(/* Some */["search"], /* array */[])),
                                      ReasonReact.element(/* None */0, /* None */0, NBInput$Mxdbmobile.make(/* Some */["Search"], /* array */[]))
                                    ])),
                            ReasonReact.element(/* None */0, /* None */0, NBButton$Mxdbmobile.make(/* Some */[true], /* array */[ReasonReact.element(/* None */0, /* None */0, Text$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* array */["Search"]))]))
                          ])),
                  ReasonReact.element(/* None */0, /* None */0, Curry._6(TabNavigator[/* make */0], /* CardList */0, /* array */[
                            /* CardList */0,
                            /* DeckList */1
                          ], /* None */0, /* None */0, /* None */0, (function (navigation) {
                              var match = navigation[/* currentRoute */1];
                              if (match) {
                                return ReasonReact.element(/* None */0, /* None */0, make$7(navigation, /* array */[]));
                              } else {
                                return ReasonReact.element(/* None */0, /* None */0, make$6(navigation, /* array */[]));
                              }
                            })))
                ]));
}

var StackNavigator = include[0];

exports.Routes = Routes;
exports.StackNavigator = StackNavigator;
exports.TabNavigator = TabNavigator;
exports.Graphql_error = Graphql_error;
exports.sendQuery = sendQuery;
exports.tapLog = tapLog;
exports.CardImage = CardImage;
exports.CardEffect = CardEffect;
exports.CardDetails = CardDetails;
exports.CardListItem = CardListItem;
exports.ListOfCards = ListOfCards;
exports.CardList = CardList;
exports.DeckList = DeckList;
exports.app = app;
/* include Not a pure module */
