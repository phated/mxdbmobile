'use strict';

var Js_dict = require("bs-platform/lib/js/js_dict.js");

var listToObj = Js_dict.fromList;

function wrap(filter) {
  return Js_dict.fromList(/* :: */[
              /* tuple */[
                "query",
                filter
              ],
              /* [] */0
            ]);
}

var empty = wrap(Js_dict.fromList(/* [] */0));

function effectText(search) {
  return Js_dict.fromList(/* :: */[
              /* tuple */[
                "text_contains",
                search
              ],
              /* [] */0
            ]);
}

function create(search) {
  if (search) {
    return wrap(Js_dict.fromList(/* :: */[
                    /* tuple */[
                      "effect",
                      effectText(search[0])
                    ],
                    /* [] */0
                  ]));
  } else {
    return empty;
  }
}

exports.listToObj = listToObj;
exports.wrap = wrap;
exports.empty = empty;
exports.effectText = effectText;
exports.create = create;
/* empty Not a pure module */
