'use strict';

var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var Caml_int32 = require("bs-platform/lib/js/caml_int32.js");
var ReasonReact = require("reason-react/src/ReasonReact.js");
var Icon$Mxdbmobile = require("./icon/Icon.js");
var Event$Mxdbmobile = require("./card/Event.js");
var Query$Mxdbmobile = require("./Query.js");
var Utils$Mxdbmobile = require("./Utils.js");
var Battle$Mxdbmobile = require("./card/Battle.js");
var Colors$Mxdbmobile = require("./Colors.js");
var Filter$Mxdbmobile = require("./Filter.js");
var Text$BsReactNative = require("bs-react-native/src/components/text.js");
var View$BsReactNative = require("bs-react-native/src/components/view.js");
var CardList$Mxdbmobile = require("./CardList.js");
var Style$BsReactNative = require("bs-react-native/src/style.js");
var Character$Mxdbmobile = require("./card/Character.js");
var FlatList$BsReactNative = require("bs-react-native/src/components/flatList.js");
var TextInput$BsReactNative = require("bs-react-native/src/components/textInput.js");
var SafeAreaView$BsReactNative = require("bs-react-native/src/components/safeAreaView.js");

var cardQuery = "\n    {\n      characters: allCards(filter: { type: Character }, orderBy: title_ASC) {\n        uid\n        title\n        subtitle\n        mp\n        stats {\n          type\n          rank\n        }\n        effect {\n          symbol\n          text\n        }\n        image {\n          thumbnail\n        }\n      }\n      events: allCards(filter: { type: Event }, orderBy: title_ASC) {\n        uid\n        title\n        mp\n        effect {\n          symbol\n          text\n        }\n        image {\n          thumbnail\n        }\n      }\n      battles: allCards(filter: { type: Battle }, orderBy: title_ASC) {\n        uid\n        title\n        mp\n        stats(orderBy: type_ASC) {\n          type\n          rank\n        }\n        effect {\n          symbol\n          text\n        }\n        image {\n          thumbnail\n        }\n      }\n    }\n    ";

var component = ReasonReact.reducerComponent("ListOfCards");

var container = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.flex(1),
      /* [] */0
    ]);

var separator = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.flex(1.0),
      /* :: */[
        Style$BsReactNative.height(/* Pt */Block.__(0, [1.0])),
        /* :: */[
          Style$BsReactNative.backgroundColor(Colors$Mxdbmobile.Css[/* gray */2]),
          /* [] */0
        ]
      ]
    ]);

var Styles = /* module */[
  /* container */container,
  /* separator */separator
];

function itemSeparatorComponent(param) {
  return FlatList$BsReactNative.separatorComponent((function () {
                return ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[separator], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[]));
              }), param);
}

function renderItem(param) {
  return FlatList$BsReactNative.renderItem((function (bag) {
                var card = bag[/* item */0];
                switch (card.tag | 0) {
                  case 0 : 
                      var match = card[0];
                      return ReasonReact.element(/* None */0, /* None */0, Character$Mxdbmobile.make(match[/* title */1], match[/* subtitle */2], match[/* mp */3], match[/* stats */4], match[/* image */6], match[/* effect */5], /* array */[]));
                  case 1 : 
                      var match$1 = card[0];
                      return ReasonReact.element(/* None */0, /* None */0, Event$Mxdbmobile.make(match$1[/* title */1], match$1[/* mp */2], match$1[/* image */4], match$1[/* effect */3], /* array */[]));
                  case 2 : 
                      var match$2 = card[0];
                      return ReasonReact.element(/* None */0, /* None */0, Battle$Mxdbmobile.make(match$2[/* title */1], match$2[/* mp */2], match$2[/* stat */3], match$2[/* image */5], match$2[/* effect */4], /* array */[]));
                  
                }
              }), param);
}

function getItemLayout(_, idx) {
  return {
          length: 170,
          offset: Caml_int32.imul(170, idx),
          index: idx
        };
}

function getUid(card) {
  return card[0][/* uid */0];
}

function make() {
  return /* record */[
          /* debugName */component[/* debugName */0],
          /* reactClassInternal */component[/* reactClassInternal */1],
          /* handedOffState */component[/* handedOffState */2],
          /* willReceiveProps */component[/* willReceiveProps */3],
          /* didMount */(function (self) {
              return Curry._1(self[/* send */3], /* FetchCards */0);
            }),
          /* didUpdate */component[/* didUpdate */5],
          /* willUnmount */component[/* willUnmount */6],
          /* willUpdate */component[/* willUpdate */7],
          /* shouldUpdate */component[/* shouldUpdate */8],
          /* render */(function (self) {
              var sections = CardList$Mxdbmobile.toArray(self[/* state */1]);
              return ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[container], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[ReasonReact.element(/* None */0, /* None */0, FlatList$BsReactNative.make(sections, renderItem, (function (card, _) {
                                            return card[0][/* uid */0];
                                          }), /* Some */[itemSeparatorComponent], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[getItemLayout], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[]))]));
            }),
          /* initialState */(function () {
              return CardList$Mxdbmobile.empty;
            }),
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */(function (action, _) {
              if (action) {
                return /* Update */Block.__(0, [action[0]]);
              } else {
                return /* SideEffects */Block.__(1, [(function (self) {
                              Query$Mxdbmobile.send(cardQuery, Filter$Mxdbmobile.empty).then(Utils$Mxdbmobile.tapLog).then((function (cards) {
                                      Curry._1(self[/* send */3], /* StoreCards */[cards]);
                                      return Promise.resolve(cards);
                                    }));
                              return /* () */0;
                            })]);
              }
            }),
          /* subscriptions */component[/* subscriptions */13],
          /* jsElementWrapped */component[/* jsElementWrapped */14]
        ];
}

var ListOfCards = /* module */[
  /* cardQuery */cardQuery,
  /* component */component,
  /* Styles */Styles,
  /* itemSeparatorComponent */itemSeparatorComponent,
  /* renderItem */renderItem,
  /* getItemLayout */getItemLayout,
  /* getUid */getUid,
  /* make */make
];

var component$1 = ReasonReact.statelessComponent("AppContainer");

var container$1 = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.flex(1),
      /* [] */0
    ]);

var Styles$1 = /* module */[/* container */container$1];

function make$1(children) {
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
                              /* Some */[container$1],
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
          /* initialState */component$1[/* initialState */10],
          /* retainedProps */component$1[/* retainedProps */11],
          /* reducer */component$1[/* reducer */12],
          /* subscriptions */component$1[/* subscriptions */13],
          /* jsElementWrapped */component$1[/* jsElementWrapped */14]
        ];
}

var AppContainer = /* module */[
  /* component */component$1,
  /* Styles */Styles$1,
  /* make */make$1
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

var Styles$2 = /* module */[/* search */search];

var component$2 = ReasonReact.reducerComponent("SearchInput");

function noop() {
  return /* () */0;
}

function make$2($staropt$star, _) {
  var onSearch = $staropt$star ? $staropt$star[0] : noop;
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
              return ReasonReact.element(/* None */0, /* None */0, TextInput$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[search], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[/* none */-922086728], /* Some */[false], /* Some */[true], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[(function (text) {
                                    return Curry._1(self[/* send */3], /* UpdateText */[text]);
                                  })], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[(function () {
                                    return Curry._1(self[/* send */3], /* SubmitAndClear */0);
                                  })], /* Some */["Search"], /* Some */[Colors$Mxdbmobile.gray], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */["transparent"], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[false])(/* array */[]));
            }),
          /* initialState */(function () {
              return "";
            }),
          /* retainedProps */component$2[/* retainedProps */11],
          /* reducer */(function (action, state) {
              if (action) {
                return /* Update */Block.__(0, [action[0]]);
              } else {
                return /* UpdateWithSideEffects */Block.__(2, [
                          "",
                          (function () {
                              return Curry._1(onSearch, state);
                            })
                        ]);
              }
            }),
          /* subscriptions */component$2[/* subscriptions */13],
          /* jsElementWrapped */component$2[/* jsElementWrapped */14]
        ];
}

var SearchInput = /* module */[
  /* Styles */Styles$2,
  /* component */component$2,
  /* noop */noop,
  /* make */make$2
];

var container$2 = Style$BsReactNative.style(/* :: */[
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

var Styles$3 = /* module */[
  /* container */container$2,
  /* title */title,
  /* icon */icon
];

var component$3 = ReasonReact.reducerComponent("Toolbar");

function make$3() {
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
          /* render */(function (self) {
              var match = self[/* state */1][/* search */0];
              if (match) {
                var enableSearch = function () {
                  return Curry._1(self[/* send */3], /* SearchMode */[/* Enabled */0]);
                };
                return ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[container$2], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[
                                ReasonReact.element(/* None */0, /* None */0, Text$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[title], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* array */["MetaX Deck Builder"])),
                                ReasonReact.element(/* None */0, /* None */0, Icon$Mxdbmobile.make("search", /* Some */[icon], /* Some */[enableSearch], /* None */0, /* array */[]))
                              ]));
              } else {
                var disableSearch = function () {
                  return Curry._1(self[/* send */3], /* SearchMode */[/* Disabled */1]);
                };
                return ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[container$2], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[
                                ReasonReact.element(/* None */0, /* None */0, Icon$Mxdbmobile.make("arrow-back", /* Some */[icon], /* Some */[disableSearch], /* None */0, /* array */[])),
                                ReasonReact.element(/* None */0, /* None */0, make$2(/* None */0, /* array */[]))
                              ]));
              }
            }),
          /* initialState */(function () {
              return /* record */[/* search : Disabled */1];
            }),
          /* retainedProps */component$3[/* retainedProps */11],
          /* reducer */(function (action, _) {
              return /* Update */Block.__(0, [/* record */[/* search */action[0]]]);
            }),
          /* subscriptions */component$3[/* subscriptions */13],
          /* jsElementWrapped */component$3[/* jsElementWrapped */14]
        ];
}

var Toolbar = /* module */[
  /* Styles */Styles$3,
  /* component */component$3,
  /* make */make$3
];

var container$3 = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.flex(1.0),
      /* :: */[
        Style$BsReactNative.alignItems(/* Center */2),
        /* :: */[
          Style$BsReactNative.padding(/* Pt */Block.__(0, [8.0])),
          /* [] */0
        ]
      ]
    ]);

var icon$1 = Style$BsReactNative.style(/* :: */[
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

var Styles$4 = /* module */[
  /* container */container$3,
  /* icon */icon$1,
  /* label */label
];

var component$4 = ReasonReact.statelessComponent("NavigationButton");

function make$4(icon$2, label$1, _) {
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
              return ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[container$3], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[
                              ReasonReact.element(/* None */0, /* None */0, Icon$Mxdbmobile.make(icon$2, /* Some */[icon$1], /* None */0, /* None */0, /* array */[])),
                              ReasonReact.element(/* None */0, /* None */0, Text$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[label], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* array */[label$1]))
                            ]));
            }),
          /* initialState */component$4[/* initialState */10],
          /* retainedProps */component$4[/* retainedProps */11],
          /* reducer */component$4[/* reducer */12],
          /* subscriptions */component$4[/* subscriptions */13],
          /* jsElementWrapped */component$4[/* jsElementWrapped */14]
        ];
}

var NavigationButton = /* module */[
  /* Styles */Styles$4,
  /* component */component$4,
  /* make */make$4
];

var container$4 = Style$BsReactNative.style(/* :: */[
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

var Styles$5 = /* module */[/* container */container$4];

var component$5 = ReasonReact.statelessComponent("NavigationBar");

function make$5(children) {
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
              return ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[container$4], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(children));
            }),
          /* initialState */component$5[/* initialState */10],
          /* retainedProps */component$5[/* retainedProps */11],
          /* reducer */component$5[/* reducer */12],
          /* subscriptions */component$5[/* subscriptions */13],
          /* jsElementWrapped */component$5[/* jsElementWrapped */14]
        ];
}

var NavigationBar = /* module */[
  /* Styles */Styles$5,
  /* component */component$5,
  /* make */make$5
];

function app() {
  return ReasonReact.element(/* None */0, /* None */0, make$1(/* array */[
                  ReasonReact.element(/* None */0, /* None */0, make$3(/* array */[])),
                  ReasonReact.element(/* None */0, /* None */0, make(/* array */[])),
                  ReasonReact.element(/* None */0, /* None */0, make$5(/* array */[
                            ReasonReact.element(/* None */0, /* None */0, make$4("cards", "Cards", /* array */[])),
                            ReasonReact.element(/* None */0, /* None */0, make$4("deck", "Deck", /* array */[])),
                            ReasonReact.element(/* None */0, /* None */0, make$4("info", "Info", /* array */[]))
                          ]))
                ]));
}

exports.ListOfCards = ListOfCards;
exports.AppContainer = AppContainer;
exports.SearchInput = SearchInput;
exports.Toolbar = Toolbar;
exports.NavigationButton = NavigationButton;
exports.NavigationBar = NavigationBar;
exports.app = app;
/* component Not a pure module */
