type t = {
  thumbnail: string,
  small: string,
};

type size =
  | Thumbnail
  | Small;

let decoder = json => {
  thumbnail: json |> Json.Decode.field("thumbnail", Json.Decode.string),
  small: json |> Json.Decode.field("small", Json.Decode.string),
};

module Styles = {
  open BsReactNative.Style;

  let thumbnail = style([height(150.0->Pt), width(108.0->Pt)]);
  let small = style([height(200.0->Pt), width(142.0->Pt)]);
};

type retainedProps = {
  image: t,
  size,
};

let component = ReasonReact.statelessComponentWithRetainedProps("Card.Image");

let make = (~image, ~size, _children) => {
  ...component,
  retainedProps: {
    image,
    size,
  },
  shouldUpdate: ({oldSelf, newSelf}) =>
    oldSelf.retainedProps.image != newSelf.retainedProps.image
    || oldSelf.retainedProps.size != newSelf.retainedProps.size,
  render: _self => {
    open BsReactNative;

    let _ = ();

    let defaultSource =
      `Required(Packager.require("../assets/card-back.jpg"));

    let image =
      switch (size) {
      | Thumbnail =>
        <Image
          style=Styles.thumbnail
          defaultSource
          source={`URI(Image.imageURISource(~uri=image.small, ()))}
        />
      | Small =>
        <Image
          style=Styles.small
          defaultSource
          source={`URI(Image.imageURISource(~uri=image.small, ()))}
        />
      };

    <View> image </View>;
  },
};
