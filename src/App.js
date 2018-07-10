'use strict';

var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var Js_json = require("bs-platform/lib/js/js_json.js");
var Caml_int32 = require("bs-platform/lib/js/caml_int32.js");
var ReasonReact = require("reason-react/src/ReasonReact.js");
var Caml_exceptions = require("bs-platform/lib/js/caml_exceptions.js");
var Icon$Mxdbmobile = require("./icon/Icon.js");
var Event$Mxdbmobile = require("./card/Event.js");
var Query$Mxdbmobile = require("./Query.js");
var Utils$Mxdbmobile = require("./Utils.js");
var Battle$Mxdbmobile = require("./card/Battle.js");
var Colors$Mxdbmobile = require("./Colors.js");
var Text$BsReactNative = require("bs-react-native/src/components/text.js");
var View$BsReactNative = require("bs-react-native/src/components/view.js");
var CardList$Mxdbmobile = require("./CardList.js");
var Style$BsReactNative = require("bs-react-native/src/style.js");
var Character$Mxdbmobile = require("./card/Character.js");
var FlatList$BsReactNative = require("bs-react-native/src/components/flatList.js");
var MaterialIcon$Mxdbmobile = require("./icon/MaterialIcon.js");
var TextInput$BsReactNative = require("bs-react-native/src/components/textInput.js");
var SafeAreaView$BsReactNative = require("bs-react-native/src/components/safeAreaView.js");

var Graphql_error = Caml_exceptions.create("App-Mxdbmobile.ListOfCards.CardQuery.Graphql_error");

var ppx_printed_query = "query   {\ncharacters: allCards(filter: {type: Character}, orderBy: title_ASC)  {\nuid  \ntitle  \nsubtitle  \nmp  \nstats  {\ntype  \nrank  \n}\neffect  {\nsymbol  \ntext  \n}\nimage  {\nthumbnail  \n}\n}\nevents: allCards(filter: {type: Event}, orderBy: title_ASC)  {\nuid  \ntitle  \nmp  \neffect  {\nsymbol  \ntext  \n}\nimage  {\nthumbnail  \n}\n}\nbattles: allCards(filter: {type: Battle}, orderBy: title_ASC)  {\nuid  \ntitle  \nmp  \nstats(orderBy: type_ASC)  {\ntype  \nrank  \n}\neffect  {\nsymbol  \ntext  \n}\nimage  {\nthumbnail  \n}\n}\n}";

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
                var value$3 = value$1["title"];
                var match$2 = Js_json.decodeString(value$3);
                var tmp$1;
                if (match$2) {
                  tmp$1 = match$2[0];
                } else {
                  throw Graphql_error;
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
                    throw Graphql_error;
                  }
                  tmp$2 = /* Some */[tmp$3];
                }
                var value$5 = value$1["mp"];
                var match$5 = Js_json.decodeNumber(value$5);
                var tmp$4;
                if (match$5) {
                  tmp$4 = match$5[0] | 0;
                } else {
                  throw Graphql_error;
                }
                var value$6 = value$1["stats"];
                var match$6 = Js_json.decodeNull(value$6);
                var tmp$5;
                if (match$6) {
                  tmp$5 = /* None */0;
                } else {
                  var match$7 = Js_json.decodeArray(value$6);
                  var tmp$6;
                  if (match$7) {
                    tmp$6 = match$7[0].map((function (value) {
                            var match = Js_json.decodeObject(value);
                            if (match) {
                              var value$1 = match[0];
                              var value$2 = value$1["type"];
                              var match$1 = Js_json.decodeString(value$2);
                              var tmp;
                              if (match$1) {
                                switch (match$1[0]) {
                                  case "Intelligence" : 
                                      tmp = /* Intelligence */860902239;
                                      break;
                                  case "Special" : 
                                      tmp = /* Special */749117977;
                                      break;
                                  case "Strength" : 
                                      tmp = /* Strength */-398422367;
                                      break;
                                  default:
                                    throw Graphql_error;
                                }
                              } else {
                                throw Graphql_error;
                              }
                              var value$3 = value$1["rank"];
                              var match$2 = Js_json.decodeNumber(value$3);
                              var tmp$1;
                              if (match$2) {
                                tmp$1 = match$2[0] | 0;
                              } else {
                                throw Graphql_error;
                              }
                              return {
                                      type: tmp,
                                      rank: tmp$1
                                    };
                            } else {
                              throw Graphql_error;
                            }
                          }));
                  } else {
                    throw Graphql_error;
                  }
                  tmp$5 = /* Some */[tmp$6];
                }
                var value$7 = value$1["effect"];
                var match$8 = Js_json.decodeNull(value$7);
                var tmp$7;
                if (match$8) {
                  tmp$7 = /* None */0;
                } else {
                  var match$9 = Js_json.decodeObject(value$7);
                  var tmp$8;
                  if (match$9) {
                    var value$8 = match$9[0];
                    var value$9 = value$8["symbol"];
                    var match$10 = Js_json.decodeString(value$9);
                    var tmp$9;
                    if (match$10) {
                      switch (match$10[0]) {
                        case "ATTACK" : 
                            tmp$9 = /* ATTACK */311601096;
                            break;
                        case "CONSTANT" : 
                            tmp$9 = /* CONSTANT */-14462620;
                            break;
                        case "DEFEND" : 
                            tmp$9 = /* DEFEND */425991990;
                            break;
                        case "NONE" : 
                            tmp$9 = /* NONE */868932280;
                            break;
                        case "PLAY" : 
                            tmp$9 = /* PLAY */890959348;
                            break;
                        case "PUSH" : 
                            tmp$9 = /* PUSH */891410906;
                            break;
                        default:
                          throw Graphql_error;
                      }
                    } else {
                      throw Graphql_error;
                    }
                    var value$10 = value$8["text"];
                    var match$11 = Js_json.decodeNull(value$10);
                    var tmp$10;
                    if (match$11) {
                      tmp$10 = /* None */0;
                    } else {
                      var match$12 = Js_json.decodeString(value$10);
                      var tmp$11;
                      if (match$12) {
                        tmp$11 = match$12[0];
                      } else {
                        throw Graphql_error;
                      }
                      tmp$10 = /* Some */[tmp$11];
                    }
                    tmp$8 = {
                      symbol: tmp$9,
                      text: tmp$10
                    };
                  } else {
                    throw Graphql_error;
                  }
                  tmp$7 = /* Some */[tmp$8];
                }
                var value$11 = value$1["image"];
                var match$13 = Js_json.decodeNull(value$11);
                var tmp$12;
                if (match$13) {
                  tmp$12 = /* None */0;
                } else {
                  var match$14 = Js_json.decodeObject(value$11);
                  var tmp$13;
                  if (match$14) {
                    var value$12 = match$14[0]["thumbnail"];
                    var match$15 = Js_json.decodeString(value$12);
                    var tmp$14;
                    if (match$15) {
                      tmp$14 = match$15[0];
                    } else {
                      throw Graphql_error;
                    }
                    tmp$13 = {
                      thumbnail: tmp$14
                    };
                  } else {
                    throw Graphql_error;
                  }
                  tmp$12 = /* Some */[tmp$13];
                }
                return {
                        uid: tmp,
                        title: tmp$1,
                        subtitle: tmp$2,
                        mp: tmp$4,
                        stats: tmp$5,
                        effect: tmp$7,
                        image: tmp$12
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
                var value$3 = value$1["title"];
                var match$2 = Js_json.decodeString(value$3);
                var tmp$1;
                if (match$2) {
                  tmp$1 = match$2[0];
                } else {
                  throw Graphql_error;
                }
                var value$4 = value$1["mp"];
                var match$3 = Js_json.decodeNumber(value$4);
                var tmp$2;
                if (match$3) {
                  tmp$2 = match$3[0] | 0;
                } else {
                  throw Graphql_error;
                }
                var value$5 = value$1["effect"];
                var match$4 = Js_json.decodeNull(value$5);
                var tmp$3;
                if (match$4) {
                  tmp$3 = /* None */0;
                } else {
                  var match$5 = Js_json.decodeObject(value$5);
                  var tmp$4;
                  if (match$5) {
                    var value$6 = match$5[0];
                    var value$7 = value$6["symbol"];
                    var match$6 = Js_json.decodeString(value$7);
                    var tmp$5;
                    if (match$6) {
                      switch (match$6[0]) {
                        case "ATTACK" : 
                            tmp$5 = /* ATTACK */311601096;
                            break;
                        case "CONSTANT" : 
                            tmp$5 = /* CONSTANT */-14462620;
                            break;
                        case "DEFEND" : 
                            tmp$5 = /* DEFEND */425991990;
                            break;
                        case "NONE" : 
                            tmp$5 = /* NONE */868932280;
                            break;
                        case "PLAY" : 
                            tmp$5 = /* PLAY */890959348;
                            break;
                        case "PUSH" : 
                            tmp$5 = /* PUSH */891410906;
                            break;
                        default:
                          throw Graphql_error;
                      }
                    } else {
                      throw Graphql_error;
                    }
                    var value$8 = value$6["text"];
                    var match$7 = Js_json.decodeNull(value$8);
                    var tmp$6;
                    if (match$7) {
                      tmp$6 = /* None */0;
                    } else {
                      var match$8 = Js_json.decodeString(value$8);
                      var tmp$7;
                      if (match$8) {
                        tmp$7 = match$8[0];
                      } else {
                        throw Graphql_error;
                      }
                      tmp$6 = /* Some */[tmp$7];
                    }
                    tmp$4 = {
                      symbol: tmp$5,
                      text: tmp$6
                    };
                  } else {
                    throw Graphql_error;
                  }
                  tmp$3 = /* Some */[tmp$4];
                }
                var value$9 = value$1["image"];
                var match$9 = Js_json.decodeNull(value$9);
                var tmp$8;
                if (match$9) {
                  tmp$8 = /* None */0;
                } else {
                  var match$10 = Js_json.decodeObject(value$9);
                  var tmp$9;
                  if (match$10) {
                    var value$10 = match$10[0]["thumbnail"];
                    var match$11 = Js_json.decodeString(value$10);
                    var tmp$10;
                    if (match$11) {
                      tmp$10 = match$11[0];
                    } else {
                      throw Graphql_error;
                    }
                    tmp$9 = {
                      thumbnail: tmp$10
                    };
                  } else {
                    throw Graphql_error;
                  }
                  tmp$8 = /* Some */[tmp$9];
                }
                return {
                        uid: tmp,
                        title: tmp$1,
                        mp: tmp$2,
                        effect: tmp$3,
                        image: tmp$8
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
                var value$3 = value$1["title"];
                var match$2 = Js_json.decodeString(value$3);
                var tmp$1;
                if (match$2) {
                  tmp$1 = match$2[0];
                } else {
                  throw Graphql_error;
                }
                var value$4 = value$1["mp"];
                var match$3 = Js_json.decodeNumber(value$4);
                var tmp$2;
                if (match$3) {
                  tmp$2 = match$3[0] | 0;
                } else {
                  throw Graphql_error;
                }
                var value$5 = value$1["stats"];
                var match$4 = Js_json.decodeNull(value$5);
                var tmp$3;
                if (match$4) {
                  tmp$3 = /* None */0;
                } else {
                  var match$5 = Js_json.decodeArray(value$5);
                  var tmp$4;
                  if (match$5) {
                    tmp$4 = match$5[0].map((function (value) {
                            var match = Js_json.decodeObject(value);
                            if (match) {
                              var value$1 = match[0];
                              var value$2 = value$1["type"];
                              var match$1 = Js_json.decodeString(value$2);
                              var tmp;
                              if (match$1) {
                                switch (match$1[0]) {
                                  case "Intelligence" : 
                                      tmp = /* Intelligence */860902239;
                                      break;
                                  case "Special" : 
                                      tmp = /* Special */749117977;
                                      break;
                                  case "Strength" : 
                                      tmp = /* Strength */-398422367;
                                      break;
                                  default:
                                    throw Graphql_error;
                                }
                              } else {
                                throw Graphql_error;
                              }
                              var value$3 = value$1["rank"];
                              var match$2 = Js_json.decodeNumber(value$3);
                              var tmp$1;
                              if (match$2) {
                                tmp$1 = match$2[0] | 0;
                              } else {
                                throw Graphql_error;
                              }
                              return {
                                      type: tmp,
                                      rank: tmp$1
                                    };
                            } else {
                              throw Graphql_error;
                            }
                          }));
                  } else {
                    throw Graphql_error;
                  }
                  tmp$3 = /* Some */[tmp$4];
                }
                var value$6 = value$1["effect"];
                var match$6 = Js_json.decodeNull(value$6);
                var tmp$5;
                if (match$6) {
                  tmp$5 = /* None */0;
                } else {
                  var match$7 = Js_json.decodeObject(value$6);
                  var tmp$6;
                  if (match$7) {
                    var value$7 = match$7[0];
                    var value$8 = value$7["symbol"];
                    var match$8 = Js_json.decodeString(value$8);
                    var tmp$7;
                    if (match$8) {
                      switch (match$8[0]) {
                        case "ATTACK" : 
                            tmp$7 = /* ATTACK */311601096;
                            break;
                        case "CONSTANT" : 
                            tmp$7 = /* CONSTANT */-14462620;
                            break;
                        case "DEFEND" : 
                            tmp$7 = /* DEFEND */425991990;
                            break;
                        case "NONE" : 
                            tmp$7 = /* NONE */868932280;
                            break;
                        case "PLAY" : 
                            tmp$7 = /* PLAY */890959348;
                            break;
                        case "PUSH" : 
                            tmp$7 = /* PUSH */891410906;
                            break;
                        default:
                          throw Graphql_error;
                      }
                    } else {
                      throw Graphql_error;
                    }
                    var value$9 = value$7["text"];
                    var match$9 = Js_json.decodeNull(value$9);
                    var tmp$8;
                    if (match$9) {
                      tmp$8 = /* None */0;
                    } else {
                      var match$10 = Js_json.decodeString(value$9);
                      var tmp$9;
                      if (match$10) {
                        tmp$9 = match$10[0];
                      } else {
                        throw Graphql_error;
                      }
                      tmp$8 = /* Some */[tmp$9];
                    }
                    tmp$6 = {
                      symbol: tmp$7,
                      text: tmp$8
                    };
                  } else {
                    throw Graphql_error;
                  }
                  tmp$5 = /* Some */[tmp$6];
                }
                var value$10 = value$1["image"];
                var match$11 = Js_json.decodeNull(value$10);
                var tmp$10;
                if (match$11) {
                  tmp$10 = /* None */0;
                } else {
                  var match$12 = Js_json.decodeObject(value$10);
                  var tmp$11;
                  if (match$12) {
                    var value$11 = match$12[0]["thumbnail"];
                    var match$13 = Js_json.decodeString(value$11);
                    var tmp$12;
                    if (match$13) {
                      tmp$12 = match$13[0];
                    } else {
                      throw Graphql_error;
                    }
                    tmp$11 = {
                      thumbnail: tmp$12
                    };
                  } else {
                    throw Graphql_error;
                  }
                  tmp$10 = /* Some */[tmp$11];
                }
                return {
                        uid: tmp,
                        title: tmp$1,
                        mp: tmp$2,
                        stats: tmp$3,
                        effect: tmp$5,
                        image: tmp$10
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
              var sections = CardList$Mxdbmobile.from(self[/* state */1][/* characters */0], self[/* state */1][/* events */1], self[/* state */1][/* battles */2]);
              return ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[container], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[ReasonReact.element(/* None */0, /* None */0, FlatList$BsReactNative.make(sections, renderItem, (function (card, _) {
                                            return card[0][/* uid */0];
                                          }), /* Some */[itemSeparatorComponent], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[getItemLayout], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[]))]));
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
                            /* characters */cards[/* characters */0],
                            /* events */cards[/* events */1],
                            /* battles */cards[/* battles */2]
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

var ListOfCards = /* module */[
  /* CardQuery */CardQuery,
  /* component */component,
  /* Styles */Styles,
  /* itemSeparatorComponent */itemSeparatorComponent,
  /* renderItem */renderItem,
  /* getItemLayout */getItemLayout,
  /* getUid */getUid,
  /* make */make$1
];

var component$1 = ReasonReact.statelessComponent("AppContainer");

var container$1 = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.flex(1),
      /* [] */0
    ]);

var Styles$1 = /* module */[/* container */container$1];

function make$2(children) {
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
  /* make */make$2
];

var container$2 = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.flexDirection(/* Row */0),
      /* :: */[
        Style$BsReactNative.padding(/* Pt */Block.__(0, [16.0])),
        /* :: */[
          Style$BsReactNative.backgroundColor(Colors$Mxdbmobile.Css[/* primary */0]),
          /* [] */0
        ]
      ]
    ]);

var title = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.color(Colors$Mxdbmobile.Css[/* white */1]),
      /* :: */[
        Style$BsReactNative.fontSize(/* Float */Block.__(0, [20.0])),
        /* :: */[
          Style$BsReactNative.fontWeight(/* Bold */737455525),
          /* :: */[
            Style$BsReactNative.flex(1.0),
            /* [] */0
          ]
        ]
      ]
    ]);

var search = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.flex(1.0),
      /* :: */[
        Style$BsReactNative.marginLeft(/* Pt */Block.__(0, [8.0])),
        /* :: */[
          Style$BsReactNative.color(Colors$Mxdbmobile.Css[/* white */1]),
          /* :: */[
            Style$BsReactNative.fontSize(/* Float */Block.__(0, [20.0])),
            /* [] */0
          ]
        ]
      ]
    ]);

var icon = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.color(Colors$Mxdbmobile.Css[/* white */1]),
      /* [] */0
    ]);

var Styles$2 = /* module */[
  /* container */container$2,
  /* title */title,
  /* search */search,
  /* icon */icon
];

var component$2 = ReasonReact.reducerComponent("Toolbar");

function make$3() {
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
              var match = self[/* state */1][/* search */0];
              if (match) {
                var onSearch = function () {
                  return Curry._1(self[/* send */3], /* SearchMode */[/* Enabled */0]);
                };
                return ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[container$2], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[
                                ReasonReact.element(/* None */0, /* None */0, Text$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[title], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* array */["MetaX Deck Builder"])),
                                ReasonReact.element(/* None */0, /* None */0, MaterialIcon$Mxdbmobile.make("search", /* Some */[icon], /* Some */[onSearch], /* array */[]))
                              ]));
              } else {
                var onBack = function () {
                  return Curry._1(self[/* send */3], /* SearchMode */[/* Disabled */1]);
                };
                return ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[container$2], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[
                                ReasonReact.element(/* None */0, /* None */0, MaterialIcon$Mxdbmobile.make("arrow-back", /* Some */[icon], /* Some */[onBack], /* array */[])),
                                ReasonReact.element(/* None */0, /* None */0, TextInput$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[search], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[true], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */["Search"], /* Some */[Colors$Mxdbmobile.gray], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[]))
                              ]));
              }
            }),
          /* initialState */(function () {
              return /* record */[/* search : Disabled */1];
            }),
          /* retainedProps */component$2[/* retainedProps */11],
          /* reducer */(function (action, _) {
              return /* Update */Block.__(0, [/* record */[/* search */action[0]]]);
            }),
          /* subscriptions */component$2[/* subscriptions */13],
          /* jsElementWrapped */component$2[/* jsElementWrapped */14]
        ];
}

var Toolbar = /* module */[
  /* Styles */Styles$2,
  /* component */component$2,
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

var Styles$3 = /* module */[
  /* container */container$3,
  /* icon */icon$1,
  /* label */label
];

var component$3 = ReasonReact.statelessComponent("NavigationButton");

function make$4(icon$2, label$1, _) {
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
              return ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[container$3], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[
                              ReasonReact.element(/* None */0, /* None */0, Icon$Mxdbmobile.make(icon$2, /* Some */[icon$1], /* None */0, /* array */[])),
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

var Styles$4 = /* module */[/* container */container$4];

var component$4 = ReasonReact.statelessComponent("NavigationBar");

function make$5(children) {
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
              return ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[container$4], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(children));
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
  /* make */make$5
];

function app() {
  return ReasonReact.element(/* None */0, /* None */0, make$2(/* array */[
                  ReasonReact.element(/* None */0, /* None */0, make$3(/* array */[])),
                  ReasonReact.element(/* None */0, /* None */0, make$1(/* array */[])),
                  ReasonReact.element(/* None */0, /* None */0, make$5(/* array */[
                            ReasonReact.element(/* None */0, /* None */0, make$4("cards", "Cards", /* array */[])),
                            ReasonReact.element(/* None */0, /* None */0, make$4("deck", "Deck", /* array */[])),
                            ReasonReact.element(/* None */0, /* None */0, make$4("info", "Info", /* array */[]))
                          ]))
                ]));
}

exports.ListOfCards = ListOfCards;
exports.AppContainer = AppContainer;
exports.Toolbar = Toolbar;
exports.NavigationButton = NavigationButton;
exports.NavigationBar = NavigationBar;
exports.app = app;
/* component Not a pure module */
