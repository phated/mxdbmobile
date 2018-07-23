type t = {
  uid: string,
  title: string,
  subtitle: string,
  trait: string,
  mp: MP.t,
  stats: StatList.t,
  effect: Effect.t,
  image: CardImage.t,
};

let decoder: Js.Json.t => t =
  json => {
    uid: json |> Json.Decode.field("uid", Json.Decode.string),
    title: json |> Json.Decode.field("title", Json.Decode.string),
    subtitle: json |> Json.Decode.field("subtitle", Json.Decode.string),
    trait:
      json
      |> Json.Decode.field(
           "trait",
           Json.Decode.field("name", Json.Decode.string),
         ),
    mp: json |> Json.Decode.field("mp", MP.decoder),
    stats: json |> Json.Decode.field("stats", StatList.decoder),
    effect: json |> Json.Decode.field("effect", Effect.decoder),
    image: json |> Json.Decode.field("image", CardImage.decoder),
  };

module Styles = {
  open BsReactNative.Style;

  let details =
    style([
      flex(1.0),
      flexDirection(Column),
      paddingHorizontal(8.0 |. Pt),
    ]);

  let title = style([fontWeight(`Bold)]);

  let cardListItem =
    style([height(182.0 |. Pt), flexDirection(Row), padding(16.0 |. Pt)]);

  let image = style([height(150.0 |. Pt), width(108.0 |. Pt)]);

  let stats = style([width(45.0 |. Pt), alignItems(FlexEnd)]);
};

let component = ReasonReact.statelessComponent("Character");
let make =
    (~title, ~subtitle, ~trait, ~mp, ~stats, ~image, ~effect, _children) => {
  ...component,
  render: _self => {
    open BsReactNative;

    let cardImage = <CardImage image style=Styles.image />;
    let cardCounter = <CardCounter> ...cardImage </CardCounter>;
    let cardDetails =
      <View style=Styles.details>
        <Text style=Styles.title>
          (ReasonReact.string(title))
          (ReasonReact.string(" - "))
          (ReasonReact.string(subtitle))
        </Text>
        <Text> (ReasonReact.string(trait)) </Text>
        <Effect effect />
      </View>;
    let cardStats =
      <View style=Styles.stats> <MP value=mp /> <StatList stats /> </View>;

    <View style=Styles.cardListItem> cardCounter cardDetails cardStats </View>;
  },
};
