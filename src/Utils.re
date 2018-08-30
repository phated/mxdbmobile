let tapLog = res => {
  Js.log(res);
  Js.Promise.resolve(res);
};

let nextTick = cb => Js.Global.setTimeout(cb, 0);
let clearTick = id => Js.Global.clearTimeout(id);
