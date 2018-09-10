type t = {
  /* TODO: This should have card type */
  uid: string,
  rarity: Rarity.t,
  number: int,
  expansion: Expansion.t,
  title: string,
  mp: MP.t,
  stat: BattleStat.t,
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
    mp: json |> Json.Decode.field("mp", MP.decoder),
    stat: json |> Json.Decode.field("stats", BattleStat.decoder),
    effect: json |> Json.Decode.field("effect", Effect.decoder),
    image: json |> Json.Decode.field("image", CardImage.decoder),
  };

module Styles = {
  open BsReactNative.Style;

  let container = style([flex(1.0), flexDirection(Row)]);

  let details =
    style([flex(1.0), flexDirection(Column), paddingHorizontal(8.0->Pt)]);

  let title = style([fontWeight(`Bold)]);

  let image = style([height(150.0->Pt), width(108.0->Pt)]);

  let stats = style([alignItems(FlexEnd)]);
};

let component = ReasonReact.statelessComponent("Battle");
let make = (~card, _children) => {
  ...component,
  shouldUpdate: _ => false,
  render: _self => {
    open BsReactNative;

    let {title, effect, mp, stat} = card;

    let rank = string_of_int(BattleStat.rankGet(stat));

    let cardDetails =
      <View style=Styles.details>
        <Text style=Styles.title> <S> title </S> </Text>
        <Text> <S> {"Rank " ++ rank} </S> </Text>
        <Effect effect />
      </View>;
    let cardStats =
      <View style=Styles.stats> <MP value=mp /> <BattleStat stat /> </View>;

    <View style=Styles.container> cardDetails cardStats </View>;
  },
};
