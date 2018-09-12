type t = {
  /* TODO: This should have card type */
  uid: string,
  rarity: Rarity.t,
  number: int,
  expansion: Expansion.t,
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
    rarity: json |> Json.Decode.field("rarity", Rarity.decoder),
    number: json |> Json.Decode.field("number", Json.Decode.int),
    expansion: json |> Json.Decode.field("set", Expansion.decoder),
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

let toGroupIdentifier = ({title, subtitle}) =>
  Printf.sprintf("%s_%s", title, subtitle);

module Styles = {
  open BsReactNative.Style;

  let container = style([flex(1.0), flexDirection(Row)]);

  let details =
    style([flex(1.0), flexDirection(Column), paddingHorizontal(8.0->Pt)]);

  let title = style([fontWeight(`Bold)]);

  let stats = style([width(45.0->Pt), alignItems(FlexEnd)]);
};

let component = ReasonReact.statelessComponent("Character");
let make = (~card, _children) => {
  ...component,
  shouldUpdate: _ => false,
  render: _self => {
    open BsReactNative;

    let {title, subtitle, trait, mp, effect, stats} = card;

    let cardDetails =
      <View style=Styles.details>
        <Text style=Styles.title>
          <S> title </S>
          <S> " - " </S>
          <S> subtitle </S>
        </Text>
        <Text> <S> trait </S> </Text>
        <Effect effect />
      </View>;
    let cardStats =
      <View style=Styles.stats> <MP value=mp /> <StatList stats /> </View>;

    <View style=Styles.container> cardDetails cardStats </View>;
  },
};
