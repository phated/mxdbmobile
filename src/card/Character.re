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
      paddingLeft(8.0 |. Pt),
      paddingRight(8.0 |. Pt),
    ]);

  let title = style([fontWeight(`Bold)]);

  let cardListItem =
    style([
      /* flex(1.), */
      height(170.0 |. Pt),
      flexDirection(Row),
      /* marginLeft(8.0 |. Pt), */
      /* marginRight(8.0 |. Pt), */
      /* marginTop(4.0 |. Pt), */
      /* marginBottom(4.0 |. Pt), */
      padding(16.0 |. Pt),
      /* borderStyle(Solid), */
      /* borderBottomWidth(2.0), */
      /* borderColor(Colors.Css.gray), */
      /* borderRadius(3.), */
    ]);

  let thumbnail = style([height(100.0 |. Pt), width(72.0 |. Pt)]);

  let stats = style([width(45.0 |. Pt), alignItems(FlexEnd)]);
};

let component = ReasonReact.statelessComponent("Character");
let make =
    (~title, ~subtitle, ~trait, ~mp, ~stats, ~image, ~effect, _children) => {
  ...component,
  render: _self => {
    open BsReactNative;

    let cardImage = <CardImage image style=Styles.thumbnail />;
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

    <View style=Styles.cardListItem> cardImage cardDetails cardStats </View>;
  },
};
