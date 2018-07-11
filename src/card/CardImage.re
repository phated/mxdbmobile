type t = {thumbnail: string};

let decoder = json => {
  thumbnail: json |> Json.Decode.field("thumbnail", Json.Decode.string),
};

let component = ReasonReact.statelessComponent("CardImage");

module Styles = {
  open BsReactNative.Style;
  /* let container = style([flex(1.)]); */
};

/* TODO: this should do "size" things */
let make = (~image, ~style, _children) => {
  ...component,
  render: _self =>
    BsReactNative.(
      <View>
        <Image
          style
          source=(Image.URI(Image.imageURISource(~uri=image.thumbnail, ())))
        />
      </View>
    ),
};
