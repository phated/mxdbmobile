type t = {
  thumbnail: string,
  small: string,
  medium: string,
};

type size =
  | Thumbnail
  | Small
  | Medium;

let decoder = json => {
  thumbnail: json |> Json.Decode.field("thumbnail", Json.Decode.string),
  small: json |> Json.Decode.field("small", Json.Decode.string),
  medium: json |> Json.Decode.field("medium", Json.Decode.string),
};

module Styles = {
  open BsReactNative.Style;
  let thumbnail = style([height(150.0->Pt), width(108.0->Pt)]);
  let small = style([height(200.0->Pt), width(142.0->Pt)]);
  let medium = style([height(400.0->Pt), width(285.0->Pt)]);
};

let component = ReasonReact.statelessComponent("Card.Image");

let make = (~image, ~size, children) => {
  ...component,
  render: _self => {
    open BsReactNative;

    let _ = ();

    let defaultSource =
      `Required(Packager.require("../assets/card-back.jpg"));

    let image =
      switch (size) {
      | Thumbnail =>
        <ImageBackground
          style=Styles.thumbnail
          defaultSource
          source={`URI(Image.imageURISource(~uri=image.small, ()))}>
          ...children
        </ImageBackground>
      | Small =>
        <ImageBackground
          style=Styles.small
          defaultSource
          source={`URI(Image.imageURISource(~uri=image.small, ()))}>
          ...children
        </ImageBackground>
      | Medium =>
        <ImageBackground
          style=Styles.medium
          defaultSource
          source={`URI(Image.imageURISource(~uri=image.medium, ()))}>
          ...children
        </ImageBackground>
      };

    <View> image </View>;
  },
};
