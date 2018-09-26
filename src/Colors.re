let primary = "#303030";
let black = "#303030";
let white = "#fff";
let gray = "#d3d3d3";

let ourBlue = "#0064a7";
let ourBlueDark = "#004a7d";

let warning = "#F8A81E";

module MetaX = {
  let strength = "#d22130";
  let intelligence = "#0062A6";
  let special = "#008353";
  /* let multi = "#4B2F84"; */
  /* let multi = "#390099"; */
  let multi = "#9E0059";

  let attack = "#E75424";
  let defend = "#00ABBC";
  let push = "#A53796";
  let constant = "#F8A81E";
  let play = "#20B14A";

  let character = "#314084";
  /* let character = "#43518F"; */
  let event = "#697D92";
  /* let event = "#91A0AF"; */
  let battle = "#7E7467";
  /* let battle = "#A19990"; */
  let remain = "#071108";

  module Css = {
    open BsReactNative.Style;
    let strength: string_interpolated = String(strength);
    let intelligence: string_interpolated = String(intelligence);
    let special: string_interpolated = String(special);
    let multi: string_interpolated = String(multi);

    let attack: string_interpolated = String(attack);
    let defend: string_interpolated = String(defend);
    let push: string_interpolated = String(push);
    let constant: string_interpolated = String(constant);
    let play: string_interpolated = String(play);

    let character: string_interpolated = String(character);
    let event: string_interpolated = String(event);
    let battle: string_interpolated = String(battle);
    let remain: string_interpolated = String(remain);
  };
};

module Wat = {
  open BsReactNative.Style;
  let ourBlue = String(ourBlue);
};

module Css = {
  open BsReactNative.Style;
  let black: string_interpolated = String(primary);
  let primary: string_interpolated = String(primary);
  let white: string_interpolated = String(white);
  let gray: string_interpolated = String(gray);

  let ourBlue: string_interpolated = String(ourBlue);
  let ourBlueDark: string_interpolated = String(ourBlueDark);

  let transparentWhite: string_interpolated =
    String("rgba(255, 255, 255, 0.9)");

  let warning: string_interpolated = String(warning);
};
