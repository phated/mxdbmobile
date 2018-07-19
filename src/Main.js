'use strict';

var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var Caml_obj = require("bs-platform/lib/js/caml_obj.js");
var ReasonReact = require("reason-react/src/ReasonReact.js");
var Icon$Mxdbmobile = require("./icon/Icon.js");
var Route$ReasonTea = require("reason-tea/src/Route.bs.js");
var Query$Mxdbmobile = require("./Query.js");
var Utils$Mxdbmobile = require("./Utils.js");
var Colors$Mxdbmobile = require("./Colors.js");
var Program$ReasonTea = require("reason-tea/src/Program.bs.js");
var Text$BsReactNative = require("bs-react-native/src/components/text.js");
var View$BsReactNative = require("bs-react-native/src/components/view.js");
var CardList$Mxdbmobile = require("./CardList.js");
var Style$BsReactNative = require("bs-react-native/src/style.js");
var TextInput$BsReactNative = require("bs-react-native/src/components/textInput.js");
var SafeAreaView$BsReactNative = require("bs-react-native/src/components/safeAreaView.js");

var cardQuery = "\n    query CardList($title: String, $subtitle: String, $trait: String, $mp: Int, $effect: String, $symbol: CardSymbol) {\n      characters: allCards(filter: {\n        AND: [\n          { type: Character },\n          { OR: [\n              { title_contains: $title },\n              { subtitle_contains: $subtitle },\n              { trait: { name_contains: $trait } },\n              { mp: $mp },\n              { effect: { text_contains: $effect } },\n            ]\n          },\n          { effect: { symbol: $symbol } }\n        ]\n      }, orderBy: title_ASC) {\n        uid\n        title\n        subtitle\n        trait {\n          name\n        }\n        mp\n        stats {\n          type\n          rank\n        }\n        effect {\n          symbol\n          text\n        }\n        image {\n          thumbnail\n        }\n      }\n      events: allCards(filter: {\n        AND: [\n          { type: Event },\n          { OR: [\n              { title_contains: $title },\n              { mp: $mp },\n              { effect: { text_contains: $effect } }\n            ]\n          },\n          { effect: { symbol: $symbol } }\n        ]\n      }, orderBy: title_ASC) {\n        uid\n        title\n        mp\n        effect {\n          symbol\n          text\n        }\n        image {\n          thumbnail\n        }\n      }\n      battles: allCards(filter: {\n        AND: [\n          { type: Battle },\n          { OR: [\n              { title_contains: $title },\n              { mp: $mp },\n              { effect: { text_contains: $effect } }\n            ]\n          },\n          { effect: { symbol: $symbol } }\n        ]\n      }, orderBy: title_ASC) {\n        uid\n        title\n        mp\n        stats(orderBy: type_ASC) {\n          type\n          rank\n        }\n        effect {\n          symbol\n          text\n        }\n        image {\n          thumbnail\n        }\n      }\n    }\n    ";

var component = ReasonReact.statelessComponent("AppContainer");

var container = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.flex(1),
      /* [] */0
    ]);

var Styles = /* module */[/* container */container];

function make(children) {
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
              return ReasonReact.element(/* None */0, /* None */0, Curry.app(SafeAreaView$BsReactNative.make, [
                              /* None */0,
                              /* None */0,
                              /* None */0,
                              /* None */0,
                              /* None */0,
                              /* None */0,
                              /* None */0,
                              /* None */0,
                              /* None */0,
                              /* Some */[container],
                              /* None */0,
                              /* None */0,
                              /* None */0,
                              /* None */0,
                              /* None */0,
                              /* None */0,
                              /* None */0,
                              /* None */0,
                              /* None */0,
                              /* None */0,
                              children
                            ]));
            }),
          /* initialState */component[/* initialState */10],
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */component[/* reducer */12],
          /* subscriptions */component[/* subscriptions */13],
          /* jsElementWrapped */component[/* jsElementWrapped */14]
        ];
}

var AppContainer = /* module */[
  /* component */component,
  /* Styles */Styles,
  /* make */make
];

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

var Styles$1 = /* module */[/* search */search];

var component$1 = ReasonReact.reducerComponent("SearchInput");

function noop() {
  return /* () */0;
}

function make$1($staropt$star, $staropt$star$1, _) {
  var onSearch = $staropt$star ? $staropt$star[0] : noop;
  var onBlur = $staropt$star$1 ? $staropt$star$1[0] : noop;
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
          /* render */(function (self) {
              return ReasonReact.element(/* None */0, /* None */0, TextInput$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[search], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[/* none */-922086728], /* Some */[false], /* Some */[true], /* Some */[true], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[onBlur], /* None */0, /* Some */[(function (text) {
                                    return Curry._1(self[/* send */3], /* UpdateText */[text]);
                                  })], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[(function () {
                                    return Curry._1(self[/* send */3], /* Submit */0);
                                  })], /* Some */["Search"], /* Some */[Colors$Mxdbmobile.gray], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[self[/* state */1]], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */["transparent"], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[false])(/* array */[]));
            }),
          /* initialState */(function () {
              return "";
            }),
          /* retainedProps */component$1[/* retainedProps */11],
          /* reducer */(function (action, state) {
              if (typeof action === "number") {
                if (action !== 0) {
                  return /* UpdateWithSideEffects */Block.__(2, [
                            "",
                            (function () {
                                return Curry._1(onSearch, state);
                              })
                          ]);
                } else {
                  return /* SideEffects */Block.__(1, [(function (self) {
                                return Curry._1(onSearch, self[/* state */1]);
                              })]);
                }
              } else {
                return /* Update */Block.__(0, [action[0]]);
              }
            }),
          /* subscriptions */component$1[/* subscriptions */13],
          /* jsElementWrapped */component$1[/* jsElementWrapped */14]
        ];
}

var SearchInput = /* module */[
  /* Styles */Styles$1,
  /* component */component$1,
  /* noop */noop,
  /* make */make$1
];

var container$1 = Style$BsReactNative.style(/* :: */[
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

var Styles$2 = /* module */[/* container */container$1];

var component$2 = ReasonReact.reducerComponent("Toolbar");

function make$2(renderChildren) {
  var enable = function (_, self) {
    return Curry._1(self[/* send */3], /* ChangeMode */[/* Enabled */0]);
  };
  var disable = function (_, self) {
    return Curry._1(self[/* send */3], /* ChangeMode */[/* Disabled */1]);
  };
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
          /* render */(function (self) {
              var children = Curry._3(renderChildren, Curry._1(self[/* handle */0], enable), Curry._1(self[/* handle */0], disable), self[/* state */1]);
              return ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[container$1], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(children));
            }),
          /* initialState */(function () {
              return /* Disabled */1;
            }),
          /* retainedProps */component$2[/* retainedProps */11],
          /* reducer */(function (action, _) {
              return /* Update */Block.__(0, [action[0]]);
            }),
          /* subscriptions */component$2[/* subscriptions */13],
          /* jsElementWrapped */component$2[/* jsElementWrapped */14]
        ];
}

var Toolbar = /* module */[
  /* Styles */Styles$2,
  /* component */component$2,
  /* make */make$2
];

var container$2 = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.flex(1.0),
      /* :: */[
        Style$BsReactNative.alignItems(/* Center */2),
        /* :: */[
          Style$BsReactNative.padding(/* Pt */Block.__(0, [8.0])),
          /* [] */0
        ]
      ]
    ]);

var icon = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.color(Colors$Mxdbmobile.Css[/* white */1]),
      /* [] */0
    ]);

var label = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.fontSize(/* Float */Block.__(0, [12.0])),
      /* :: */[
        Style$BsReactNative.color(Colors$Mxdbmobile.Css[/* white */1]),
        /* [] */0
      ]
    ]);

var Styles$3 = /* module */[
  /* container */container$2,
  /* icon */icon,
  /* label */label
];

var component$3 = ReasonReact.statelessComponent("NavigationButton");

function make$3(icon$1, label$1, _) {
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
              return ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[container$2], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[
                              ReasonReact.element(/* None */0, /* None */0, Icon$Mxdbmobile.make(icon$1, /* Some */[icon], /* None */0, /* None */0, /* array */[])),
                              ReasonReact.element(/* None */0, /* None */0, Text$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[label], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* array */[label$1]))
                            ]));
            }),
          /* initialState */component$3[/* initialState */10],
          /* retainedProps */component$3[/* retainedProps */11],
          /* reducer */component$3[/* reducer */12],
          /* subscriptions */component$3[/* subscriptions */13],
          /* jsElementWrapped */component$3[/* jsElementWrapped */14]
        ];
}

var NavigationButton = /* module */[
  /* Styles */Styles$3,
  /* component */component$3,
  /* make */make$3
];

var container$3 = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.justifyContent(/* Center */2),
      /* :: */[
        Style$BsReactNative.alignContent(/* Center */2),
        /* :: */[
          Style$BsReactNative.flexDirection(/* Row */0),
          /* :: */[
            Style$BsReactNative.backgroundColor(Colors$Mxdbmobile.Css[/* primary */0]),
            /* [] */0
          ]
        ]
      ]
    ]);

var Styles$4 = /* module */[/* container */container$3];

var component$4 = ReasonReact.statelessComponent("NavigationBar");

function make$4(children) {
  return /* record */[
          /* debugName */component$4[/* debugName */0],
          /* reactClassInternal */component$4[/* reactClassInternal */1],
          /* handedOffState */component$4[/* handedOffState */2],
          /* willReceiveProps */component$4[/* willReceiveProps */3],
          /* didMount */component$4[/* didMount */4],
          /* didUpdate */component$4[/* didUpdate */5],
          /* willUnmount */component$4[/* willUnmount */6],
          /* willUpdate */component$4[/* willUpdate */7],
          /* shouldUpdate */component$4[/* shouldUpdate */8],
          /* render */(function () {
              return ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[container$3], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(children));
            }),
          /* initialState */component$4[/* initialState */10],
          /* retainedProps */component$4[/* retainedProps */11],
          /* reducer */component$4[/* reducer */12],
          /* subscriptions */component$4[/* subscriptions */13],
          /* jsElementWrapped */component$4[/* jsElementWrapped */14]
        ];
}

var NavigationBar = /* module */[
  /* Styles */Styles$4,
  /* component */component$4,
  /* make */make$4
];

var title = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.color(Colors$Mxdbmobile.Css[/* white */1]),
      /* :: */[
        Style$BsReactNative.fontSize(/* Float */Block.__(0, [20.0])),
        /* :: */[
          Style$BsReactNative.margin(/* Pt */Block.__(0, [8.0])),
          /* :: */[
            Style$BsReactNative.fontWeight(/* Bold */737455525),
            /* :: */[
              Style$BsReactNative.flex(1.0),
              /* [] */0
            ]
          ]
        ]
      ]
    ]);

var icon$1 = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.color(Colors$Mxdbmobile.Css[/* white */1]),
      /* :: */[
        Style$BsReactNative.margin(/* Pt */Block.__(0, [8.0])),
        /* :: */[
          Style$BsReactNative.textAlignVertical(/* Center */3),
          /* [] */0
        ]
      ]
    ]);

var Styles$5 = /* module */[
  /* title */title,
  /* icon */icon$1
];

function application() {
  var program = Program$ReasonTea.routerProgram("Main App");
  return /* record */[
          /* debug */program[/* debug */0],
          /* fromRoute */(function (action, route) {
              var match = route[/* path */0];
              if (action !== 1 && !(action !== 0 || !(match && match[0] === "" && !match[1]))) {
                return /* UpdateWithSideEffects */Block.__(1, [
                          /* record */[
                            /* filter : Empty */0,
                            /* cards */CardList$Mxdbmobile.empty
                          ],
                          (function (self) {
                              Query$Mxdbmobile.send(cardQuery, self[/* state */0][/* filter */0]).then(Utils$Mxdbmobile.tapLog).then((function (cards) {
                                      Curry._1(self[/* send */1], /* StoreCards */Block.__(1, [cards]));
                                      return Promise.resolve(cards);
                                    }));
                              return /* () */0;
                            })
                        ]);
              } else {
                return /* NoUpdate */0;
              }
            }),
          /* toRoute */(function (param) {
              var next = param[/* next */1];
              if (Caml_obj.caml_equal(param[/* previous */0], next)) {
                return /* NoTransition */1;
              } else {
                var match = next[/* filter */0];
                var search = match ? match[0] : "";
                return /* Push */Block.__(0, [Route$ReasonTea.make(/* :: */[
                                "",
                                /* [] */0
                              ], "", search)]);
              }
            }),
          /* update */(function (action, state) {
              if (action.tag) {
                return /* Update */Block.__(0, [/* record */[
                            /* filter */state[/* filter */0],
                            /* cards */action[0]
                          ]]);
              } else {
                return /* UpdateWithSideEffects */Block.__(1, [
                          /* record */[
                            /* filter : FreeText */[action[0]],
                            /* cards */state[/* cards */1]
                          ],
                          (function (self) {
                              Query$Mxdbmobile.send(cardQuery, self[/* state */0][/* filter */0]).then(Utils$Mxdbmobile.tapLog).then((function (cards) {
                                      Curry._1(self[/* send */1], /* StoreCards */Block.__(1, [cards]));
                                      return Promise.resolve(cards);
                                    }));
                              return /* () */0;
                            })
                        ]);
              }
            }),
          /* view */(function (self) {
              return ReasonReact.element(/* None */0, /* None */0, make(/* array */[
                              ReasonReact.element(/* None */0, /* None */0, make$2((function (enable, disable, mode) {
                                          var onSearch = function (text) {
                                            return Curry._1(self[/* send */1], /* Search */Block.__(0, [text]));
                                          };
                                          if (mode) {
                                            return /* array */[
                                                    ReasonReact.element(/* None */0, /* None */0, Text$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[title], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* array */["MetaX Deck Builder"])),
                                                    ReasonReact.element(/* None */0, /* None */0, Icon$Mxdbmobile.make("search", /* Some */[icon$1], /* Some */[enable], /* None */0, /* array */[]))
                                                  ];
                                          } else {
                                            return /* array */[
                                                    ReasonReact.element(/* None */0, /* None */0, Icon$Mxdbmobile.make("arrow-back", /* Some */[icon$1], /* Some */[disable], /* None */0, /* array */[])),
                                                    ReasonReact.element(/* None */0, /* None */0, make$1(/* Some */[onSearch], /* Some */[disable], /* array */[]))
                                                  ];
                                          }
                                        }))),
                              ReasonReact.element(/* None */0, /* None */0, CardList$Mxdbmobile.make(self[/* state */0][/* cards */1], /* array */[])),
                              ReasonReact.element(/* None */0, /* None */0, make$4(/* array */[
                                        ReasonReact.element(/* None */0, /* None */0, make$3("cards", "Cards", /* array */[])),
                                        ReasonReact.element(/* None */0, /* None */0, make$3("deck", "Deck", /* array */[])),
                                        ReasonReact.element(/* None */0, /* None */0, make$3("info", "Info", /* array */[]))
                                      ]))
                            ]));
            })
        ];
}

var component$5 = ReasonReact.reducerComponent("ApplicationContainer");

function make$5(application, _) {
  return /* record */[
          /* debugName */component$5[/* debugName */0],
          /* reactClassInternal */component$5[/* reactClassInternal */1],
          /* handedOffState */component$5[/* handedOffState */2],
          /* willReceiveProps */component$5[/* willReceiveProps */3],
          /* didMount */(function (self) {
              return Program$ReasonTea.startup(/* None */0, Curry._1(application, /* () */0), (function (view) {
                            return Curry._1(self[/* send */3], /* Render */[view]);
                          }));
            }),
          /* didUpdate */component$5[/* didUpdate */5],
          /* willUnmount */component$5[/* willUnmount */6],
          /* willUpdate */component$5[/* willUpdate */7],
          /* shouldUpdate */component$5[/* shouldUpdate */8],
          /* render */(function (self) {
              return self[/* state */1];
            }),
          /* initialState */(function () {
              return null;
            }),
          /* retainedProps */component$5[/* retainedProps */11],
          /* reducer */(function (action, _) {
              return /* Update */Block.__(0, [action[0]]);
            }),
          /* subscriptions */component$5[/* subscriptions */13],
          /* jsElementWrapped */component$5[/* jsElementWrapped */14]
        ];
}

var ApplicationContainer = /* module */[
  /* component */component$5,
  /* make */make$5
];

function app() {
  return ReasonReact.element(/* None */0, /* None */0, make$5(application, /* array */[]));
}

exports.cardQuery = cardQuery;
exports.AppContainer = AppContainer;
exports.SearchInput = SearchInput;
exports.Toolbar = Toolbar;
exports.NavigationButton = NavigationButton;
exports.NavigationBar = NavigationBar;
exports.Styles = Styles$5;
exports.application = application;
exports.ApplicationContainer = ApplicationContainer;
exports.app = app;
/* component Not a pure module */
