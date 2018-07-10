'use strict';

var Block = require("bs-platform/lib/js/block.js");

function character(character$1) {
  return /* Character */Block.__(0, [character$1]);
}

function $$event($$event$1) {
  return /* Event */Block.__(1, [$$event$1]);
}

function battle(battle$1) {
  return /* Battle */Block.__(2, [battle$1]);
}

exports.character = character;
exports.$$event = $$event;
exports.battle = battle;
/* No side effect */
