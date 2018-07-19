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
var Filter$Mxdbmobile = require("./Filter.js");
var Program$ReasonTea = require("reason-tea/src/Program.bs.js");
var Text$BsReactNative = require("bs-react-native/src/components/text.js");
var Toolbar$Mxdbmobile = require("./components/Toolbar.js");
var CardList$Mxdbmobile = require("./CardList.js");
var Style$BsReactNative = require("bs-react-native/src/style.js");
var SearchInput$Mxdbmobile = require("./components/SearchInput.js");
var NavigationBar$Mxdbmobile = require("./components/NavigationBar.js");
var SafeAreaView$BsReactNative = require("bs-react-native/src/components/safeAreaView.js");
var NavigationButton$Mxdbmobile = require("./components/NavigationButton.js");

var container = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.flex(1),
      /* [] */0
    ]);

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

var icon = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.color(Colors$Mxdbmobile.Css[/* white */1]),
      /* :: */[
        Style$BsReactNative.margin(/* Pt */Block.__(0, [8.0])),
        /* :: */[
          Style$BsReactNative.textAlignVertical(/* Center */3),
          /* [] */0
        ]
      ]
    ]);

var Styles = /* module */[
  /* container */container,
  /* title */title,
  /* icon */icon
];

function create() {
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
                              Query$Mxdbmobile.send(CardList$Mxdbmobile.query, self[/* state */0][/* filter */0]).then(Utils$Mxdbmobile.tapLog).then((function (cards) {
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
                var search = Filter$Mxdbmobile.toString(next[/* filter */0]);
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
                              Query$Mxdbmobile.send(CardList$Mxdbmobile.query, self[/* state */0][/* filter */0]).then(Utils$Mxdbmobile.tapLog).then((function (cards) {
                                      Curry._1(self[/* send */1], /* StoreCards */Block.__(1, [cards]));
                                      return Promise.resolve(cards);
                                    }));
                              return /* () */0;
                            })
                        ]);
              }
            }),
          /* view */(function (self) {
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
                              /* array */[
                                ReasonReact.element(/* None */0, /* None */0, Toolbar$Mxdbmobile.make((function (enable, disable, mode) {
                                            var onSearch = function (text) {
                                              return Curry._1(self[/* send */1], /* Search */Block.__(0, [text]));
                                            };
                                            if (mode) {
                                              return /* array */[
                                                      ReasonReact.element(/* None */0, /* None */0, Text$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[title], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* array */["MetaX Deck Builder"])),
                                                      ReasonReact.element(/* None */0, /* None */0, Icon$Mxdbmobile.make("search", /* Some */[icon], /* Some */[enable], /* None */0, /* array */[]))
                                                    ];
                                            } else {
                                              return /* array */[
                                                      ReasonReact.element(/* None */0, /* None */0, Icon$Mxdbmobile.make("arrow-back", /* Some */[icon], /* Some */[disable], /* None */0, /* array */[])),
                                                      ReasonReact.element(/* None */0, /* None */0, SearchInput$Mxdbmobile.make(/* Some */[onSearch], /* Some */[disable], /* Some */[Filter$Mxdbmobile.toString(self[/* state */0][/* filter */0])], /* array */[]))
                                                    ];
                                            }
                                          }))),
                                ReasonReact.element(/* None */0, /* None */0, CardList$Mxdbmobile.make(self[/* state */0][/* cards */1], /* array */[])),
                                ReasonReact.element(/* None */0, /* None */0, NavigationBar$Mxdbmobile.make(/* array */[
                                          ReasonReact.element(/* None */0, /* None */0, NavigationButton$Mxdbmobile.make("cards", "Cards", /* array */[])),
                                          ReasonReact.element(/* None */0, /* None */0, NavigationButton$Mxdbmobile.make("deck", "Deck", /* array */[])),
                                          ReasonReact.element(/* None */0, /* None */0, NavigationButton$Mxdbmobile.make("info", "Info", /* array */[]))
                                        ]))
                              ]
                            ]));
            })
        ];
}

exports.Styles = Styles;
exports.create = create;
/* container Not a pure module */
