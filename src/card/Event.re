[@bs.deriving abstract]
type t = {
  /* TODO: This should have card type */
  uid: string,
  rarity: Rarity.t,
  number: int,
  expansion: Expansion.t,
  title: Card_Title.t,
  mp: MP.t,
  effect: Effect.t,
  image: CardImage.t,
};

let decoder: Js.Json.t => t =
  json =>
    t(
      ~uid=json |> Json.Decode.field("uid", Json.Decode.string),
      ~rarity=json |> Json.Decode.field("rarity", Rarity.decoder),
      ~number=json |> Json.Decode.field("number", Json.Decode.int),
      ~expansion=json |> Json.Decode.field("set", Expansion.decoder),
      ~title=json |> Json.Decode.field("title", Card_Title.decoder),
      ~mp=json |> Json.Decode.field("mp", MP.decoder),
      ~effect=json |> Json.Decode.field("effect", Effect.decoder),
      ~image=json |> Json.Decode.field("image", CardImage.decoder),
    );

let toGroupIdentifier = card => titleGet(card)->Card_Title.toString;

module Styles = {
  open BsReactNative.Style;

  let container = style([flex(1.0), flexDirection(Row)]);

  let details =
    style([flex(1.0), flexDirection(Column), paddingHorizontal(8.0->Pt)]);

  let title = style([fontWeight(`Bold)]);

  let cardListItem =
    style([height(182.0->Pt), flexDirection(Row), padding(16.0->Pt)]);

  let image = style([height(150.0->Pt), width(108.0->Pt)]);
};

let component = ReasonReact.statelessComponent("Event");
let make = (~card, _children) => {
  ...component,
  shouldUpdate: _ => false,
  render: _self => {
    open BsReactNative;

    let title = titleGet(card)->Card_Title.toString;
    let effect = effectGet(card);
    let mp = mpGet(card);

    let cardDetails =
      <View style=Styles.details>
        <Text style=Styles.title> <S> title </S> </Text>
        <Effect effect />
      </View>;
    let cardStats = <View> <MP value=mp /> </View>;

    <View style=Styles.container> cardDetails cardStats </View>;
  },
};
