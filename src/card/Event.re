type t = {
  uid: string,
  title: string,
  mp: MP.t,
  effect: Effect.t,
  image: CardImage.t,
};

let decoder: Js.Json.t => t =
  json => {
    uid: json |> Json.Decode.field("uid", Json.Decode.string),
    title: json |> Json.Decode.field("title", Json.Decode.string),
    mp: json |> Json.Decode.field("mp", MP.decoder),
    effect: json |> Json.Decode.field("effect", Effect.decoder),
    image: json |> Json.Decode.field("image", CardImage.decoder),
  };

module Styles = {
  open BsReactNative.Style;

  let container = style([flex(1.0)]);

  let details =
    style([
      flex(1.0),
      flexDirection(Column),
      paddingHorizontal(8.0 |. Pt),
    ]);

  let title = style([fontWeight(`Bold)]);

  let cardListItem =
    style([
      height(182.0 |. Pt),
      flexDirection(Row),
      padding(16.0 |. Pt),
    ]);

  let image = style([height(150.0 |. Pt), width(108.0 |. Pt)]);
};

let component = ReasonReact.statelessComponent("Event");
let make = (~card, _children) => {
  ...component,
  shouldUpdate: _ => false,
  render: _self => {
    open BsReactNative;

    let {title, effect, mp} = card;

    let cardDetails =
      <View style=Styles.details>
        <Text style=Styles.title> (ReasonReact.string(title)) </Text>
        <Effect effect />
      </View>;
    let cardStats = <View> <MP value=mp /> </View>;

    <View style=Styles.container> cardDetails cardStats </View>;
  },
};
