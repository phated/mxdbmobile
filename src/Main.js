'use strict';

var ReasonReact = require("reason-react/src/ReasonReact.js");
var Application$Mxdbmobile = require("./Application.js");
var ReactProgram$ReasonTea = require("reason-tea/src/ReactProgram.bs.js");

function run() {
  return ReasonReact.element(/* None */0, /* None */0, ReactProgram$ReasonTea.make(Application$Mxdbmobile.create, /* array */[]));
}

exports.run = run;
/* ReasonReact Not a pure module */
