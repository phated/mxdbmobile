type t = {
  thumbnail: string,
  small: string,
};

let decoder = json => {
  thumbnail: json |> Json.Decode.field("thumbnail", Json.Decode.string),
  small: json |> Json.Decode.field("small", Json.Decode.string),
};

let component = ReasonReact.statelessComponent("CardImage");

module Styles = {
  open BsReactNative.Style;

  let default = style([height(150.0 |. Pt), width(108.0 |. Pt)]);
};

/* TODO: this should do "size" things */
let make = (~image, ~style=Styles.default, _children) => {
  ...component,
  shouldUpdate: _ => false,
  render: _self =>
    BsReactNative.(
      <View>
        <Image
          style
          defaultSource=(
            Image.Required(Packager.require("../assets/card-back.jpg"))
          )
          source=(Image.URI(Image.imageURISource(~uri=image.small, ())))
        />
      </View>
    ),
};
