let tapLog = res => {
  Js.log(res);
  Js.Promise.resolve(res);
};

[@bs.val] external setTimeout : (unit => unit, int) => int = "setTimeout";
[@bs.val] external clearTimeout : int => unit = "clearTimeout";

let nextTick = cb => setTimeout(cb, 0);
let clearTick = id => clearTimeout(id);
