'use strict';

var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var Js_json = require("bs-platform/lib/js/js_json.js");
var Belt_Array = require("bs-platform/lib/js/belt_Array.js");
var ReasonReact = require("reason-react/src/ReasonReact.js");
var Caml_exceptions = require("bs-platform/lib/js/caml_exceptions.js");
var Query$Mxdbmobile = require("./Query.js");
var Utils$Mxdbmobile = require("./Utils.js");
var View$BsReactNative = require("bs-react-native/src/components/view.js");
var Style$BsReactNative = require("bs-react-native/src/style.js");
var FastImage$Mxdbmobile = require("./FastImage.js");
var FlatList$BsReactNative = require("bs-react-native/src/components/flatList.js");

var Graphql_error = Caml_exceptions.create("GridOfCards-Mxdbmobile.CardQuery.Graphql_error");

var ppx_printed_query = "query   {\ncharacters: allCards(filter: {type: Character}, orderBy: title_ASC)  {\nuid  \nimage  {\nsmall  \n}\n}\nevents: allCards(filter: {type: Event}, orderBy: title_ASC)  {\nuid  \nimage  {\nsmall  \n}\n}\nbattles: allCards(filter: {type: Battle}, orderBy: title_ASC)  {\nuid  \nimage  {\nsmall  \n}\n}\n}";

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
                  throw Graphql_error;
                }
                var value$3 = value$1["image"];
                var match$2 = Js_json.decodeNull(value$3);
                var tmp$1;
                if (match$2) {
                  tmp$1 = /* None */0;
                } else {
                  var match$3 = Js_json.decodeObject(value$3);
                  var tmp$2;
                  if (match$3) {
                    var value$4 = match$3[0]["small"];
                    var match$4 = Js_json.decodeString(value$4);
                    var tmp$3;
                    if (match$4) {
                      tmp$3 = match$4[0];
                    } else {
                      throw Graphql_error;
                    }
                    tmp$2 = {
                      small: tmp$3
                    };
                  } else {
                    throw Graphql_error;
                  }
                  tmp$1 = /* Some */[tmp$2];
                }
                return {
                        uid: tmp,
                        image: tmp$1
                      };
              } else {
                throw Graphql_error;
              }
            }));
    } else {
      throw Graphql_error;
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
                  throw Graphql_error;
                }
                var value$3 = value$1["image"];
                var match$2 = Js_json.decodeNull(value$3);
                var tmp$1;
                if (match$2) {
                  tmp$1 = /* None */0;
                } else {
                  var match$3 = Js_json.decodeObject(value$3);
                  var tmp$2;
                  if (match$3) {
                    var value$4 = match$3[0]["small"];
                    var match$4 = Js_json.decodeString(value$4);
                    var tmp$3;
                    if (match$4) {
                      tmp$3 = match$4[0];
                    } else {
                      throw Graphql_error;
                    }
                    tmp$2 = {
                      small: tmp$3
                    };
                  } else {
                    throw Graphql_error;
                  }
                  tmp$1 = /* Some */[tmp$2];
                }
                return {
                        uid: tmp,
                        image: tmp$1
                      };
              } else {
                throw Graphql_error;
              }
            }));
    } else {
      throw Graphql_error;
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
                  throw Graphql_error;
                }
                var value$3 = value$1["image"];
                var match$2 = Js_json.decodeNull(value$3);
                var tmp$1;
                if (match$2) {
                  tmp$1 = /* None */0;
                } else {
                  var match$3 = Js_json.decodeObject(value$3);
                  var tmp$2;
                  if (match$3) {
                    var value$4 = match$3[0]["small"];
                    var match$4 = Js_json.decodeString(value$4);
                    var tmp$3;
                    if (match$4) {
                      tmp$3 = match$4[0];
                    } else {
                      throw Graphql_error;
                    }
                    tmp$2 = {
                      small: tmp$3
                    };
                  } else {
                    throw Graphql_error;
                  }
                  tmp$1 = /* Some */[tmp$2];
                }
                return {
                        uid: tmp,
                        image: tmp$1
                      };
              } else {
                throw Graphql_error;
              }
            }));
    } else {
      throw Graphql_error;
    }
    return {
            characters: tmp,
            events: tmp$1,
            battles: tmp$2
          };
  } else {
    throw Graphql_error;
  }
}

function make() {
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
  /* Graphql_error */Graphql_error,
  /* ppx_printed_query */ppx_printed_query,
  /* query */ppx_printed_query,
  /* parse */parse,
  /* make */make,
  /* makeWithVariables */makeWithVariables,
  /* ret_type */ret_type,
  /* MT_Ret */MT_Ret
];

var component = ReasonReact.reducerComponent("GridOfCards");

var container = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.flex(1),
      /* :: */[
        Style$BsReactNative.alignItems(/* Stretch */3),
        /* [] */0
      ]
    ]);

var small = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.height(/* Pt */Block.__(0, [100])),
      /* :: */[
        Style$BsReactNative.width(/* Pt */Block.__(0, [72])),
        /* [] */0
      ]
    ]);

var Styles = /* module */[
  /* container */container,
  /* small */small
];

function getUri(card) {
  var match = card.image;
  if (match) {
    return match[0].small;
  } else {
    return "";
  }
}

function renderItem(param) {
  return FlatList$BsReactNative.renderItem((function (param) {
                var small = getUri(param[/* item */0]);
                return ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[container], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[ReasonReact.element(/* None */0, /* None */0, FastImage$Mxdbmobile.make(small, /* array */[]))]));
              }), param);
}

function make$1() {
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
              Belt_Array.map(Belt_Array.concatMany(/* array */[
                        self[/* state */1][/* characters */0],
                        self[/* state */1][/* events */1],
                        self[/* state */1][/* battles */2]
                      ]), getUri);
              var data = Belt_Array.concatMany(/* array */[
                    self[/* state */1][/* characters */0],
                    self[/* state */1][/* events */1],
                    self[/* state */1][/* battles */2]
                  ]);
              return ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[container], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[ReasonReact.element(/* None */0, /* None */0, FlatList$BsReactNative.make(data, renderItem, (function (item, _) {
                                            return item.uid;
                                          }), /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[3], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[container])(/* array */[]))]));
            }),
          /* initialState */(function () {
              return /* record */[
                      /* characters : array */[],
                      /* events : array */[],
                      /* battles : array */[]
                    ];
            }),
          /* retainedProps */component[/* retainedProps */11],
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
                              Query$Mxdbmobile.send(make(/* () */0)).then(Utils$Mxdbmobile.tapLog).then((function (cards) {
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

exports.CardQuery = CardQuery;
exports.component = component;
exports.Styles = Styles;
exports.getUri = getUri;
exports.renderItem = renderItem;
exports.make = make$1;
/* component Not a pure module */
