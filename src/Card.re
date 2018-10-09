module UID = Card_UID;
module Rarity = Card_Rarity;
module Number = Card_Number;
module Expansion = Card_Expansion;
module Title = Card_Title;
module Subtitle = Card_Subtitle;
module Type = Card_Type;
module Effect = Card_Effect;
module MP = Card_MP;
module Image = Card_Image;
module Symbol = Card_Symbol;
module Trait = Card_Trait;

module Character = {
  module Stats = Card_Character_Stats;

  [@bs.deriving abstract]
  type t = {
    uid: UID.t,
    rarity: Rarity.t,
    number: Number.t,
    expansion: Expansion.t,
    cardType: Type.t,
    title: Title.t,
    subtitle: Subtitle.t,
    trait: Trait.t,
    mp: MP.t,
    stats: Stats.t,
    effect: Effect.t,
    image: Image.t,
  };

  let decoder = json => {
    let typeDecoder = Type.decoder |> Decode.onlyIf(Type.isCharacter);

    t(
      ~uid=json |> Json.Decode.field("uid", UID.decoder),
      ~rarity=json |> Json.Decode.field("rarity", Rarity.decoder),
      ~number=json |> Json.Decode.field("number", Number.decoder),
      ~expansion=json |> Json.Decode.field("set", Expansion.decoder),
      ~cardType=json |> Json.Decode.field("type", typeDecoder),
      ~title=json |> Json.Decode.field("title", Title.decoder),
      ~subtitle=json |> Json.Decode.field("subtitle", Subtitle.decoder),
      ~trait=json |> Json.Decode.field("trait", Trait.decoder),
      ~mp=json |> Json.Decode.field("mp", MP.decoder),
      ~stats=json |> Json.Decode.field("stats", Stats.decoder),
      ~effect=json |> Json.Decode.field("effect", Effect.decoder),
      ~image=json |> Json.Decode.field("image", Image.decoder),
    );
  };

  let toGroupIdentifier = card =>
    Printf.sprintf(
      "1CHARACTER:%s - %s",
      titleGet(card)->Title.toString,
      subtitleGet(card)->Subtitle.toString,
    );

  module Styles = {
    open BsReactNative.Style;

    let details = style([paddingHorizontal(8.0->Pt)]);

    let stats = style([flex(0.0), width(45.0->Pt), alignItems(FlexEnd)]);
  };

  let component = ReasonReact.statelessComponent("Card.Character");
  let make = (~card, _children) => {
    ...component,
    shouldUpdate: _ => false,
    render: _self =>
      <Container.Row>
        <Container.Column style=Styles.details>
          <Text>
            <Title value={titleGet(card)} />
            <Subtitle value={subtitleGet(card)} />
          </Text>
          <Trait value={traitGet(card)} />
          <Effect value={effectGet(card)} />
        </Container.Column>
        <Container.Column style=Styles.stats>
          <MP value={mpGet(card)} />
          <Stats value={statsGet(card)} />
        </Container.Column>
      </Container.Row>,
  };
};

module Event = {
  [@bs.deriving abstract]
  type t = {
    uid: UID.t,
    rarity: Rarity.t,
    number: Number.t,
    expansion: Expansion.t,
    cardType: Type.t,
    title: Title.t,
    mp: MP.t,
    effect: Effect.t,
    image: Image.t,
  };

  let decoder = json => {
    let typeDecoder = Type.decoder |> Decode.onlyIf(Type.isEvent);

    t(
      ~uid=json |> Json.Decode.field("uid", UID.decoder),
      ~rarity=json |> Json.Decode.field("rarity", Rarity.decoder),
      ~number=json |> Json.Decode.field("number", Number.decoder),
      ~expansion=json |> Json.Decode.field("set", Expansion.decoder),
      ~cardType=json |> Json.Decode.field("type", typeDecoder),
      ~title=json |> Json.Decode.field("title", Title.decoder),
      ~mp=json |> Json.Decode.field("mp", MP.decoder),
      ~effect=json |> Json.Decode.field("effect", Effect.decoder),
      ~image=json |> Json.Decode.field("image", Image.decoder),
    );
  };

  let toGroupIdentifier = card =>
    Printf.sprintf("2EVENT:%s", titleGet(card)->Title.toString);

  module Styles = {
    open BsReactNative.Style;

    let details = style([paddingHorizontal(8.0->Pt)]);

    let stats = style([flex(0.0)]);
  };

  let component = ReasonReact.statelessComponent("Card.Event");
  let make = (~card, _children) => {
    ...component,
    shouldUpdate: _ => false,
    render: _self =>
      <Container.Row>
        <Container.Column style=Styles.details>
          <Title value={titleGet(card)} />
          <Effect value={effectGet(card)} />
        </Container.Column>
        <Container.Column style=Styles.stats>
          <MP value={mpGet(card)} />
        </Container.Column>
      </Container.Row>,
  };
};

module Battle = {
  module Stat = Card_Battle_Stat;

  [@bs.deriving abstract]
  type t = {
    uid: UID.t,
    rarity: Rarity.t,
    number: Number.t,
    expansion: Expansion.t,
    cardType: Type.t,
    title: Title.t,
    mp: MP.t,
    stat: Stat.t,
    effect: Effect.t,
    image: Image.t,
  };

  let decoder = json => {
    let typeDecoder = Type.decoder |> Decode.onlyIf(Type.isBattle);

    t(
      ~uid=json |> Json.Decode.field("uid", UID.decoder),
      ~rarity=json |> Json.Decode.field("rarity", Rarity.decoder),
      ~number=json |> Json.Decode.field("number", Number.decoder),
      ~expansion=json |> Json.Decode.field("set", Expansion.decoder),
      ~cardType=json |> Json.Decode.field("type", typeDecoder),
      ~title=json |> Json.Decode.field("title", Title.decoder),
      ~mp=json |> Json.Decode.field("mp", MP.decoder),
      ~stat=json |> Json.Decode.field("stats", Stat.decoder),
      ~effect=json |> Json.Decode.field("effect", Effect.decoder),
      ~image=json |> Json.Decode.field("image", Image.decoder),
    );
  };

  let rankGet = card => statGet(card)->Stat.rankGet;

  let toGroupIdentifier = card =>
    Printf.sprintf("3BATTLE:%s", statGet(card)->Stat.toGroupIdentifier);

  let isStrength = card => statGet(card)->Stat.isStrength;
  let isIntelligence = card => statGet(card)->Stat.isIntelligence;
  let isSpecial = card => statGet(card)->Stat.isSpecial;
  let isMulti = card => statGet(card)->Stat.isMulti;

  module Styles = {
    open BsReactNative.Style;

    let details = style([paddingHorizontal(8.0->Pt)]);

    let stats = style([flex(0.0), alignItems(FlexEnd)]);
  };

  let component = ReasonReact.statelessComponent("Battle");
  let make = (~card, _children) => {
    ...component,
    shouldUpdate: _ => false,
    render: _self => {
      let stat = statGet(card);

      let rank = string_of_int(Stat.rankGet(stat));

      <Container.Row>
        <Container.Column style=Styles.details>
          <Title value={titleGet(card)} />
          <Text> <S> {"Rank " ++ rank} </S> </Text>
          <Effect value={effectGet(card)} />
        </Container.Column>
        <Container.Column style=Styles.stats>
          <MP value={mpGet(card)} />
          <Stat stat />
        </Container.Column>
      </Container.Row>;
    },
  };
};

type t =
  | Character(Character.t)
  | Event(Event.t)
  | Battle(Battle.t);

let ofCharacter = character => Character(character);
let ofEvent = event => Event(event);
let ofBattle = battle => Battle(battle);

let decoder = json =>
  json
  |> Json.Decode.oneOf([
       Json.Decode.map(ofCharacter, Character.decoder),
       Json.Decode.map(ofEvent, Event.decoder),
       Json.Decode.map(ofBattle, Battle.decoder),
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

  let container = style([height(182.0->Pt), padding(16.0->Pt)]);
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
      <Container.Row style=Styles.container>
        <CardCounter onIncrement=increment onDecrement=decrement value=count>
          <Image image size=Thumbnail />
        </CardCounter>
        details
      </Container.Row>,
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
