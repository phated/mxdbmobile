let tapLog = res => {
  Js.log(res);
  Js.Promise.resolve(res);
};

[@bs.val] external setTimeout : (unit => unit, int) => unit = "setTimeout";
