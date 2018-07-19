'use strict';

var Block = require("bs-platform/lib/js/block.js");
var Belt_Array = require("bs-platform/lib/js/belt_Array.js");
var Caml_int32 = require("bs-platform/lib/js/caml_int32.js");
var Json_decode = require("@glennsl/bs-json/src/Json_decode.bs.js");
var ReasonReact = require("reason-react/src/ReasonReact.js");
var Card$Mxdbmobile = require("./card/Card.js");
var Event$Mxdbmobile = require("./card/Event.js");
var Battle$Mxdbmobile = require("./card/Battle.js");
var Colors$Mxdbmobile = require("./Colors.js");
var View$BsReactNative = require("bs-react-native/src/components/view.js");
var Style$BsReactNative = require("bs-react-native/src/style.js");
var Character$Mxdbmobile = require("./card/Character.js");
var FlatList$BsReactNative = require("bs-react-native/src/components/flatList.js");

var empty_000 = /* characters : array */[];

var empty_001 = /* events : array */[];

var empty_002 = /* battles : array */[];

var empty = /* record */[
  empty_000,
  empty_001,
  empty_002
];

function toArray(cardList) {
  return Belt_Array.concatMany(/* array */[
              Belt_Array.map(cardList[/* characters */0], Card$Mxdbmobile.character),
              Belt_Array.map(cardList[/* events */1], Card$Mxdbmobile.$$event),
              Belt_Array.map(cardList[/* battles */2], Card$Mxdbmobile.battle)
            ]);
}

function decode(json) {
  return /* record */[
          /* characters */Json_decode.field("characters", (function (param) {
                  return Json_decode.array(Character$Mxdbmobile.decoder, param);
                }), json),
          /* events */Json_decode.field("events", (function (param) {
                  return Json_decode.array(Event$Mxdbmobile.decoder, param);
                }), json),
          /* battles */Json_decode.field("battles", (function (param) {
                  return Json_decode.array(Battle$Mxdbmobile.decoder, param);
                }), json)
        ];
}

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
                      return ReasonReact.element(/* None */0, /* None */0, Character$Mxdbmobile.make(match[/* title */1], match[/* subtitle */2], match[/* trait */3], match[/* mp */4], match[/* stats */5], match[/* image */7], match[/* effect */6], /* array */[]));
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

var component = ReasonReact.statelessComponent("CardList");

function make(cards, _) {
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
              var sections = toArray(cards);
              return ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[container], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[ReasonReact.element(/* None */0, /* None */0, FlatList$BsReactNative.make(sections, renderItem, (function (card, _) {
                                            return card[0][/* uid */0];
                                          }), /* Some */[itemSeparatorComponent], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[getItemLayout], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[]))]));
            }),
          /* initialState */component[/* initialState */10],
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */component[/* reducer */12],
          /* subscriptions */component[/* subscriptions */13],
          /* jsElementWrapped */component[/* jsElementWrapped */14]
        ];
}

var query = "\nquery CardList($title: String, $subtitle: String, $trait: String, $mp: Int, $effect: String, $symbol: CardSymbol) {\n  characters: allCards(filter: {\n    AND: [\n      { type: Character },\n      { OR: [\n          { title_contains: $title },\n          { subtitle_contains: $subtitle },\n          { trait: { name_contains: $trait } },\n          { mp: $mp },\n          { effect: { text_contains: $effect } },\n        ]\n      },\n      { effect: { symbol: $symbol } }\n    ]\n  }, orderBy: title_ASC) {\n    uid\n    title\n    subtitle\n    trait {\n      name\n    }\n    mp\n    stats {\n      type\n      rank\n    }\n    effect {\n      symbol\n      text\n    }\n    image {\n      thumbnail\n    }\n  }\n  events: allCards(filter: {\n    AND: [\n      { type: Event },\n      { OR: [\n          { title_contains: $title },\n          { mp: $mp },\n          { effect: { text_contains: $effect } }\n        ]\n      },\n      { effect: { symbol: $symbol } }\n    ]\n  }, orderBy: title_ASC) {\n    uid\n    title\n    mp\n    effect {\n      symbol\n      text\n    }\n    image {\n      thumbnail\n    }\n  }\n  battles: allCards(filter: {\n    AND: [\n      { type: Battle },\n      { OR: [\n          { title_contains: $title },\n          { mp: $mp },\n          { effect: { text_contains: $effect } }\n        ]\n      },\n      { effect: { symbol: $symbol } }\n    ]\n  }, orderBy: title_ASC) {\n    uid\n    title\n    mp\n    stats(orderBy: type_ASC) {\n      type\n      rank\n    }\n    effect {\n      symbol\n      text\n    }\n    image {\n      thumbnail\n    }\n  }\n}\n";

exports.empty = empty;
exports.toArray = toArray;
exports.decode = decode;
exports.Styles = Styles;
exports.itemSeparatorComponent = itemSeparatorComponent;
exports.renderItem = renderItem;
exports.getItemLayout = getItemLayout;
exports.getUid = getUid;
exports.component = component;
exports.make = make;
exports.query = query;
/* container Not a pure module */
