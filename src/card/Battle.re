type t = {
  uid: string,
  title: string,
  mp: MP.t,
  stat: BattleStat.t,
  effect: Effect.t,
  image: CardImage.t,
};

let decoder: Js.Json.t => t =
  json => {
    uid: json |> Json.Decode.field("uid", Json.Decode.string),
    title: json |> Json.Decode.field("title", Json.Decode.string),
    mp: json |> Json.Decode.field("mp", MP.decoder),
    stat: json |> Json.Decode.field("stats", BattleStat.decoder),
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
    style([
      height(182.0 |. Pt),
      flexDirection(Row),
      padding(16.0 |. Pt),
    ]);

  let image = style([height(150.0 |. Pt), width(108.0 |. Pt)]);

  let stats = style([alignItems(FlexEnd)]);
};

let component = ReasonReact.statelessComponent("Battle");
let make =
    (
      ~title,
      ~mp,
      ~stat,
      ~image,
      ~effect,
      ~count,
      ~onIncrement,
      ~onDecrement,
      _children,
    ) => {
  ...component,
  render: _self => {
    open BsReactNative;

    let cardImage = <CardImage image style=Styles.image />;
    let cardCounter =
      <CardCounter onIncrement onDecrement value=count>
        ...cardImage
      </CardCounter>;
    let cardDetails =
      <View style=Styles.details>
        <Text style=Styles.title> (ReasonReact.string(title)) </Text>
        <Effect effect />
      </View>;
    let cardStats =
      <View style=Styles.stats> <MP value=mp /> <BattleStat stat /> </View>;

    <View style=Styles.cardListItem>
      cardCounter
      cardDetails
      cardStats
    </View>;
  },
};
