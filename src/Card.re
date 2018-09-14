module Title = Card_Title;
module Type = Card_Type;
module Effect = Card_Effect;
module MP = Card_MP;
module Expansion = Card_Expansion;
module Image = Card_Image;
module Rarity = Card_Rarity;
module Symbol = Card_Symbol;

module Character = {
  module Stats = Card_Character_Stats;

  [@bs.deriving abstract]
  type t = {
    /* TODO: This should have card type */
    uid: string,
    rarity: Rarity.t,
    number: int,
    expansion: Expansion.t,
    cardType: Type.t,
    title: Title.t,
    subtitle: string,
    trait: string,
    mp: MP.t,
    stats: Stats.t,
    effect: Effect.t,
    image: Image.t,
  };

  let decoder: Js.Json.t => t =
    json =>
      t(
        ~uid=json |> Json.Decode.field("uid", Json.Decode.string),
        ~rarity=json |> Json.Decode.field("rarity", Rarity.decoder),
        ~number=json |> Json.Decode.field("number", Json.Decode.int),
        ~expansion=json |> Json.Decode.field("set", Expansion.decoder),
        ~cardType=
          json |> Json.Decode.field("type", Type.decoderCharacterOnly),
        ~title=json |> Json.Decode.field("title", Title.decoder),
        ~subtitle=json |> Json.Decode.field("subtitle", Json.Decode.string),
        ~trait=
          json
          |> Json.Decode.field(
               "trait",
               Json.Decode.field("name", Json.Decode.string),
             ),
        ~mp=json |> Json.Decode.field("mp", MP.decoder),
        ~stats=json |> Json.Decode.field("stats", Stats.decoder),
        ~effect=json |> Json.Decode.field("effect", Effect.decoder),
        ~image=json |> Json.Decode.field("image", Image.decoder),
      );

  let toGroupIdentifier = card =>
    Printf.sprintf(
      "%s_%s",
      titleGet(card)->Title.toString,
      subtitleGet(card),
    );

  module Styles = {
    open BsReactNative.Style;

    let container = style([flex(1.0), flexDirection(Row)]);

    let details =
      style([
        flex(1.0),
        flexDirection(Column),
        paddingHorizontal(8.0->Pt),
      ]);

    let title = style([fontWeight(`Bold)]);

    let stats = style([width(45.0->Pt), alignItems(FlexEnd)]);
  };

  let component = ReasonReact.statelessComponent("Character");
  let make = (~card, _children) => {
    ...component,
    shouldUpdate: _ => false,
    render: _self => {
      open BsReactNative;

      let title = titleGet(card)->Title.toString;
      let subtitle = subtitleGet(card);
      let trait = traitGet(card);
      let mp = mpGet(card);
      let effect = effectGet(card);
      let stats = statsGet(card);

      let cardDetails =
        <View style=Styles.details>
          <Text style=Styles.title>
            <S> title </S>
            <S> " - " </S>
            <S> subtitle </S>
          </Text>
          <Text> <S> trait </S> </Text>
          <Effect value=effect />
        </View>;
      let cardStats =
        <View style=Styles.stats>
          <MP value=mp />
          <Stats value=stats />
        </View>;

      <View style=Styles.container> cardDetails cardStats </View>;
    },
  };
};

module Event = {
  [@bs.deriving abstract]
  type t = {
    /* TODO: This should have card type */
    uid: string,
    rarity: Rarity.t,
    number: int,
    expansion: Expansion.t,
    [@bs.as "type"]
    cardType: Type.t,
    title: Title.t,
    mp: MP.t,
    effect: Effect.t,
    image: Image.t,
  };

  let decoder: Js.Json.t => t =
    json =>
      t(
        ~uid=json |> Json.Decode.field("uid", Json.Decode.string),
        ~rarity=json |> Json.Decode.field("rarity", Rarity.decoder),
        ~number=json |> Json.Decode.field("number", Json.Decode.int),
        ~expansion=json |> Json.Decode.field("set", Expansion.decoder),
        ~cardType=json |> Json.Decode.field("type", Type.decoderEventOnly),
        ~title=json |> Json.Decode.field("title", Title.decoder),
        ~mp=json |> Json.Decode.field("mp", MP.decoder),
        ~effect=json |> Json.Decode.field("effect", Effect.decoder),
        ~image=json |> Json.Decode.field("image", Image.decoder),
      );

  let toGroupIdentifier = card => titleGet(card)->Title.toString;

  module Styles = {
    open BsReactNative.Style;

    let container = style([flex(1.0), flexDirection(Row)]);

    let details =
      style([
        flex(1.0),
        flexDirection(Column),
        paddingHorizontal(8.0->Pt),
      ]);

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

      let title = titleGet(card)->Title.toString;
      let effect = effectGet(card);
      let mp = mpGet(card);

      let cardDetails =
        <View style=Styles.details>
          <Text style=Styles.title> <S> title </S> </Text>
          <Effect value=effect />
        </View>;
      let cardStats = <View> <MP value=mp /> </View>;

      <View style=Styles.container> cardDetails cardStats </View>;
    },
  };
};

module Battle = {
  module Stat = Card_Battle_Stat;

  [@bs.deriving abstract]
  type t = {
    /* TODO: This should have card type */
    uid: string,
    rarity: Rarity.t,
    number: int,
    expansion: Expansion.t,
    [@bs.as "type"]
    cardType: Type.t,
    title: Title.t,
    mp: MP.t,
    stat: Stat.t,
    effect: Effect.t,
    image: Image.t,
  };

  let decoder: Js.Json.t => t =
    json =>
      t(
        ~uid=json |> Json.Decode.field("uid", Json.Decode.string),
        ~rarity=json |> Json.Decode.field("rarity", Rarity.decoder),
        ~number=json |> Json.Decode.field("number", Json.Decode.int),
        ~expansion=json |> Json.Decode.field("set", Expansion.decoder),
        ~cardType=json |> Json.Decode.field("type", Type.decoderBattleOnly),
        ~title=json |> Json.Decode.field("title", Title.decoder),
        ~mp=json |> Json.Decode.field("mp", MP.decoder),
        ~stat=json |> Json.Decode.field("stats", Stat.decoder),
        ~effect=json |> Json.Decode.field("effect", Effect.decoder),
        ~image=json |> Json.Decode.field("image", Image.decoder),
      );

  let toGroupIdentifier = card => statGet(card)->Stat.toGroupIdentifier;

  module Styles = {
    open BsReactNative.Style;

    let container = style([flex(1.0), flexDirection(Row)]);

    let details =
      style([
        flex(1.0),
        flexDirection(Column),
        paddingHorizontal(8.0->Pt),
      ]);

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

      let title = titleGet(card)->Title.toString;
      let effect = effectGet(card);
      let mp = mpGet(card);
      let stat = statGet(card);

      let rank = string_of_int(Stat.rankGet(stat));

      let cardDetails =
        <View style=Styles.details>
          <Text style=Styles.title> <S> title </S> </Text>
          <Text> <S> {"Rank " ++ rank} </S> </Text>
          <Effect value=effect />
        </View>;
      let cardStats =
        <View style=Styles.stats> <MP value=mp /> <Stat stat /> </View>;

      <View style=Styles.container> cardDetails cardStats </View>;
    },
  };
};

type t =
  | Character(Character.t)
  | Event(Event.t)
  | Battle(Battle.t);

let character = character => Character(character);
let event = event => Event(event);
let battle = battle => Battle(battle);

/* TODO: Character/Battle/Event need card type so we don't accidentally decode to the wrong type */
let decoder = json =>
  json
  |> Json.Decode.oneOf([
       Json.Decode.map(character, Character.decoder),
       Json.Decode.map(battle, Battle.decoder),
       Json.Decode.map(event, Event.decoder),
     ]);

let uidGet =
  fun
  | Character(character) => Character.uidGet(character)
  | Event(event) => Event.uidGet(event)
  | Battle(battle) => Battle.uidGet(battle);

let rarityGet =
  fun
  | Character(character) => Character.rarityGet(character)
  | Event(event) => Event.rarityGet(event)
  | Battle(battle) => Battle.rarityGet(battle);

let numberGet =
  fun
  | Character(character) => Character.numberGet(character)
  | Event(event) => Event.numberGet(event)
  | Battle(battle) => Battle.numberGet(battle);

let expansionGet =
  fun
  | Character(character) => Character.expansionGet(character)
  | Event(event) => Event.expansionGet(event)
  | Battle(battle) => Battle.expansionGet(battle);

let titleGet =
  fun
  | Character(character) => Character.titleGet(character)
  | Event(event) => Event.titleGet(event)
  | Battle(battle) => Battle.titleGet(battle);

let typeGet =
  fun
  | Character(character) => Character.cardTypeGet(character)
  | Event(event) => Event.cardTypeGet(event)
  | Battle(battle) => Battle.cardTypeGet(battle);

let effectGet =
  fun
  | Character(character) => Character.effectGet(character)
  | Event(event) => Event.effectGet(event)
  | Battle(battle) => Battle.effectGet(battle);

let imageGet =
  fun
  | Character(character) => Character.imageGet(character)
  | Event(event) => Event.imageGet(event)
  | Battle(battle) => Battle.imageGet(battle);

let toGroupIdentifier =
  fun
  | Character(character) => Character.toGroupIdentifier(character)
  | Event(event) => Event.toGroupIdentifier(event)
  | Battle(battle) => Battle.toGroupIdentifier(battle);

let isTypeEqual = (c1, c2) => typeGet(c1) === typeGet(c2);

module Styles = {
  open BsReactNative.Style;

  let container =
    style([height(182.0->Pt), flexDirection(Row), padding(16.0->Pt)]);
};

type retainedProps = {
  card: t,
  count: int,
};

let component = ReasonReact.statelessComponentWithRetainedProps("Card");

let make = (~card, ~count, ~onIncrement, ~onDecrement, _children) => {
  let increment = _ => onIncrement(card);
  let decrement = _ => onDecrement(card);
  let image = imageGet(card);

  let details =
    switch (card) {
    | Character(card) => <Character card />
    | Event(card) => <Event card />
    | Battle(card) => <Battle card />
    };

  {
    ...component,
    retainedProps: {
      card,
      count,
    },
    shouldUpdate: ({oldSelf, newSelf}) =>
      oldSelf.retainedProps.card != newSelf.retainedProps.card
      || oldSelf.retainedProps.count != newSelf.retainedProps.count,
    render: _self =>
      <BsReactNative.View style=Styles.container>
        <CardCounter onIncrement=increment onDecrement=decrement value=count>
          <Image image size=Thumbnail />
        </CardCounter>
        details
      </BsReactNative.View>,
  };
};

type card = t;
module Compare =
  Belt.Id.MakeComparable({
    type t = card;

    let cmp =
      Compare.concat([
        Compare.by(card => typeGet(card)->Type.toInt),
        Compare.by(card =>
          switch (card) {
          | Battle(card) => Battle.statGet(card)->Battle.Stat.rankGet
          | _ => 0
          }
        ),
        Compare.by(card =>
          switch (card) {
          | Battle(card) => Battle.statGet(card)->Battle.Stat.toInt
          | _ => 0
          }
        ),
        Compare.by(card => titleGet(card)),
        Compare.by(card => effectGet(card)->Effect.getText),
        Compare.by(card => uidGet(card)),
      ]);
  });
