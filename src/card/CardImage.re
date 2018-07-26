type t = {
  thumbnail: string,
  small: string,
};

let decoder = json => {
  thumbnail: json |> Json.Decode.field("thumbnail", Json.Decode.string),
  small: json |> Json.Decode.field("small", Json.Decode.string),
};

module Styles = {
  open BsReactNative.Style;

  let default = style([height(150.0 |. Pt), width(108.0 |. Pt)]);
};

type retainedProps = {
  image: t,
  style: BsReactNative.Style.t,
};

let component =
  ReasonReact.statelessComponentWithRetainedProps("CardImage");

/* TODO: this should do "size" things */
let make = (~image, ~style=Styles.default, _children) => {
  ...component,
  retainedProps: {
    image,
    style,
  },
  shouldUpdate: ({oldSelf, newSelf}) =>
    oldSelf.retainedProps.image != newSelf.retainedProps.image
    || oldSelf.retainedProps.style != newSelf.retainedProps.style,
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
