'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var Caml_module = require("bs-platform/lib/js/caml_module.js");

var Directive = /* module */[];

var Selection = Caml_module.init_mod([
      "/Users/phated/projects/mxdbmobile/src/GraphQl.re",
      10,
      4
    ], [[0]]);

var Field = Caml_module.init_mod([
      "/Users/phated/projects/mxdbmobile/src/GraphQl.re",
      23,
      4
    ], [[
        0,
        0,
        0
      ]]);

function field(f) {
  return /* Field */[f];
}

Caml_module.update_mod([[0]], Selection, /* module */[/* field */field]);

function make(name) {
  return /* record */[
          /* alias : None */0,
          /* name */name,
          /* arguments : [] */0,
          /* directives : [] */0,
          /* selections : [] */0
        ];
}

function setAlias(field, alias) {
  return /* record */[
          /* alias : Some */[alias],
          /* name */field[/* name */1],
          /* arguments */field[/* arguments */2],
          /* directives */field[/* directives */3],
          /* selections */field[/* selections */4]
        ];
}

function setSelections(field, selections) {
  return /* record */[
          /* alias */field[/* alias */0],
          /* name */field[/* name */1],
          /* arguments */field[/* arguments */2],
          /* directives */field[/* directives */3],
          /* selections */selections
        ];
}

Caml_module.update_mod([[
        0,
        0,
        0
      ]], Field, /* module */[
      /* make */make,
      /* setAlias */setAlias,
      /* setSelections */setSelections
    ]);

var Operation = /* module */[/* empty : record */[
    /* operationType : None */0,
    /* name : None */0,
    /* variableDefinitions : [] */0,
    /* directives : [] */0,
    /* selectionSets : [] */0
  ]];

function named(id, selectionSets) {
  return /* record */[
          /* operationType : None */0,
          /* name : Some */[id],
          /* variableDefinitions : [] */0,
          /* directives : [] */0,
          /* selectionSets */selectionSets
        ];
}

function field$1(name) {
  return Curry._1(Selection[/* field */0], Curry._1(Field[/* make */0], name));
}

function withAlias(selection, alias) {
  return Curry._1(Selection[/* field */0], Curry._2(Field[/* setAlias */1], selection[0], alias));
}

function withSelection(selection, newSelection) {
  return Curry._1(Selection[/* field */0], Curry._2(Field[/* setSelections */2], selection[0], newSelection));
}

var query = named("AllCards", /* :: */[
      withSelection(withAlias(field$1("allCards"), "characters"), /* :: */[
            field$1("uid"),
            /* :: */[
              field$1("title"),
              /* :: */[
                field$1("subtitle"),
                /* :: */[
                  withSelection(field$1("effect"), /* :: */[
                        field$1("symbol"),
                        /* :: */[
                          field$1("text"),
                          /* [] */0
                        ]
                      ]),
                  /* :: */[
                    withSelection(field$1("image"), /* :: */[
                          field$1("thumbnail"),
                          /* [] */0
                        ]),
                    /* [] */0
                  ]
                ]
              ]
            ]
          ]),
      /* [] */0
    ]);

exports.Directive = Directive;
exports.Selection = Selection;
exports.Field = Field;
exports.Operation = Operation;
exports.named = named;
exports.field = field$1;
exports.withAlias = withAlias;
exports.withSelection = withSelection;
exports.query = query;
/* Selection Not a pure module */
