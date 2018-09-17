let primary = "#303030";
let white = "#fff";
let gray = "#d3d3d3";

let ourBlue = "#0064a7";
let ourBlueDark = "#004a7d";

let strength = "#d22130";
let intelligence = "#0062A6";
let special = "#008353";
let attack = "#E75424";
let defend = "#00ABBC";
let push = "#A53796";
let constant = "#F8A81E";
let play = "#20B14A";

module Wat = {
  open BsReactNative.Style;
  let ourBlue = String(ourBlue);
};

module Css = {
  open BsReactNative.Style;
  let primary: string_interpolated = String(primary);
  let white: string_interpolated = String(white);
  let gray: string_interpolated = String(gray);

  let ourBlue: string_interpolated = String(ourBlue);
  let ourBlueDark: string_interpolated = String(ourBlueDark);

  let transparentWhite: string_interpolated =
    String("rgba(255, 255, 255, 0.9)");

  let strength: string_interpolated = String(strength);
  let intelligence: string_interpolated = String(intelligence);
  let special: string_interpolated = String(special);
  let attack: string_interpolated = String(attack);
  let defend: string_interpolated = String(defend);
  let push: string_interpolated = String(push);
  let constant: string_interpolated = String(constant);
  let play: string_interpolated = String(play);
};
