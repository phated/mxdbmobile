type t =
  | Strength(int)
  | Intelligence(int)
  | Special(int)
  | StrengthIntelligence(int)
  | IntelligenceSpecial(int)
  | StrengthSpecial(int)
  | StrengthIntelligenceSpecial(int);

let rankGet = stat =>
  switch (stat) {
  | Strength(rank) => rank
  | Intelligence(rank) => rank
  | Special(rank) => rank
  | StrengthIntelligence(rank) => rank
  | IntelligenceSpecial(rank) => rank
  | StrengthSpecial(rank) => rank
  | StrengthIntelligenceSpecial(rank) => rank
  };

let toInt = stat =>
  switch (stat) {
  | Strength(_rank) => 0
  | Intelligence(_rank) => 1
  | Special(_rank) => 2
  | StrengthIntelligence(_rank) => 3
  | IntelligenceSpecial(_rank) => 4
  | StrengthSpecial(_rank) => 5
  | StrengthIntelligenceSpecial(_rank) => 6
  };

let toGroupIdentifier = stat =>
  switch (stat) {
  | Strength(rank) => Printf.sprintf("strength_%d", rank)
  | Intelligence(rank) => Printf.sprintf("intelligence_%d", rank)
  | Special(rank) => Printf.sprintf("special_%d", rank)
  | StrengthIntelligence(rank) => Printf.sprintf("multi_%d", rank)
  | IntelligenceSpecial(rank) => Printf.sprintf("multi_%d", rank)
  | StrengthSpecial(rank) => Printf.sprintf("multi_%d", rank)
  | StrengthIntelligenceSpecial(rank) => Printf.sprintf("multi_%d", rank)
  };

let fromStatList = statList =>
  switch (statList) {
  | [|Card_Stat.Strength(rank)|] => Strength(rank)
  | [|Intelligence(rank)|] => Intelligence(rank)
  | [|Special(rank)|] => Special(rank)
  /* Alphabetized */
  | [|Intelligence(rank), Special(_)|] => IntelligenceSpecial(rank)
  | [|Intelligence(rank), Strength(_)|] => StrengthIntelligence(rank)
  | [|Special(rank), Strength(_)|] => StrengthSpecial(rank)
  | [|Intelligence(rank), Special(_), Strength(_)|] =>
    StrengthIntelligenceSpecial(rank)
  | _ => failwith("Invalid Battle Card stat list.")
  };

let decoder = json =>
  json |> Json.Decode.map(fromStatList, Json.Decode.array(Card_Stat.decoder));

module Styles = {
  open BsReactNative.Style;

  let container = style([marginTop(Auto)]);

  let singleIconContainer =
    style([
      flexDirection(Row),
      justifyContent(FlexEnd),
      alignItems(Center),
      width(45.0->Pt),
    ]);

  let doubleIconContainer =
    style([
      flexDirection(Row),
      justifyContent(FlexEnd),
      alignItems(Center),
      width(52.5->Pt),
    ]);

  let tripleIconContainer =
    style([
      flexDirection(Row),
      justifyContent(FlexEnd),
      alignItems(Center),
      width(68.0->Pt),
    ]);

  let doubleIcon =
    style([position(Relative), width(38.5->Pt), height(30.0->Pt)]);
  let firstDouble =
    style([
      position(Absolute),
      top(5.0->Pt),
      left(0.0->Pt),
      borderRadius(12.0),
      backgroundColor(Colors.Css.white),
    ]);
  let secondDouble = style([position(Absolute), right(0.0->Pt)]);

  let tripleIcon =
    style([position(Relative), width(54.0->Pt), height(30.0->Pt)]);
  let firstTriple =
    style([position(Absolute), top(5.0->Pt), left(0.0->Pt)]);
  let secondTriple =
    style([
      position(Absolute),
      left(15.0->Pt),
      borderRadius(12.0),
      backgroundColor(Colors.Css.white),
    ]);
  let thirdTriple =
    style([
      position(Absolute),
      top(5.0->Pt),
      right(0.0->Pt),
      borderRadius(12.0),
      backgroundColor(Colors.Css.white),
    ]);

  let rank =
    style([
      marginLeft(4.0->Pt),
      width(10.0->Pt),
      fontSize(14.0->Float),
      /* textAlignVertical(Center), */
    ]);

  let strength = style([color(Colors.Css.strength)]);
  let intelligence = style([color(Colors.Css.intelligence)]);
  let special = style([color(Colors.Css.special)]);
};

let component = ReasonReact.statelessComponent("BattleStat");

let make = (~stat, _children) => {
  ...component,
  render: _self => {
    open BsReactNative;
    /* Elements comprising Doubles are reveresed because zIndex doesn't work on Android */
    let child =
      switch (stat) {
      | Strength(rank) =>
        <View style=Styles.singleIconContainer>
          <Icon name="strength" style=Styles.strength />
          <Text style=Styles.rank> <S> {string_of_int(rank)} </S> </Text>
        </View>
      | Intelligence(rank) =>
        <View style=Styles.singleIconContainer>
          <Icon name="intelligence" style=Styles.intelligence />
          <Text style=Styles.rank> <S> {string_of_int(rank)} </S> </Text>
        </View>
      | Special(rank) =>
        <View style=Styles.singleIconContainer>
          <Icon name="special" style=Styles.special />
          <Text style=Styles.rank> <S> {string_of_int(rank)} </S> </Text>
        </View>
      | StrengthIntelligence(rank) =>
        <View style=Styles.doubleIconContainer>
          <View style=Styles.doubleIcon>
            <View style=Styles.secondDouble>
              <Icon name="intelligence" style=Styles.intelligence />
            </View>
            <View style=Styles.firstDouble>
              <Icon name="strength" style=Styles.strength />
            </View>
          </View>
          <Text style=Styles.rank> <S> {string_of_int(rank)} </S> </Text>
        </View>
      | IntelligenceSpecial(rank) =>
        <View style=Styles.doubleIconContainer>
          <View style=Styles.doubleIcon>
            <View style=Styles.secondDouble>
              <Icon name="special" style=Styles.special />
            </View>
            <View style=Styles.firstDouble>
              <Icon name="intelligence" style=Styles.intelligence />
            </View>
          </View>
          <Text style=Styles.rank> <S> {string_of_int(rank)} </S> </Text>
        </View>
      | StrengthSpecial(rank) =>
        <View style=Styles.doubleIconContainer>
          <View style=Styles.doubleIcon>
            <View style=Styles.secondDouble>
              <Icon name="special" style=Styles.special />
            </View>
            <View style=Styles.firstDouble>
              <Icon name="strength" style=Styles.strength />
            </View>
          </View>
          <Text style=Styles.rank> <S> {string_of_int(rank)} </S> </Text>
        </View>
      | StrengthIntelligenceSpecial(rank) =>
        <View style=Styles.tripleIconContainer>
          <View style=Styles.tripleIcon>
            <View style=Styles.firstTriple>
              <Icon name="strength" style=Styles.strength />
            </View>
            <View style=Styles.secondTriple>
              <Icon name="intelligence" style=Styles.intelligence />
            </View>
            <View style=Styles.thirdTriple>
              <Icon name="special" style=Styles.special />
            </View>
          </View>
          <Text style=Styles.rank> <S> {string_of_int(rank)} </S> </Text>
        </View>
      };

    <View style=Styles.container> child </View>;
  },
};
