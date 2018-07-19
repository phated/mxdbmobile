type t =
  | Strength(int)
  | Intelligence(int)
  | Special(int)
  | StrengthIntelligence(int)
  | IntelligenceSpecial(int)
  | StrengthSpecial(int)
  | StrengthIntelligenceSpecial(int);

let fromStatList: array(Stat.t) => t =
  statList =>
    switch (statList) {
    | [|Strength(rank)|] => Strength(rank)
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

let decoder = json => json |> Json.Decode.map(fromStatList, StatList.decoder);

module Styles = {
  open BsReactNative.Style;

  let container = style([marginTop(Auto)]);

  let singleIconContainer =
    style([
      flexDirection(Row),
      justifyContent(FlexEnd),
      alignItems(Center),
      width(45.0 |. Pt),
    ]);

  let doubleIconContainer =
    style([
      flexDirection(Row),
      justifyContent(FlexEnd),
      alignItems(Center),
      width(52.5 |. Pt),
    ]);

  let tripleIconContainer =
    style([
      flexDirection(Row),
      justifyContent(FlexEnd),
      alignItems(Center),
      width(68.0 |. Pt),
    ]);

  let doubleIcon =
    style([position(Relative), width(38.5 |. Pt), height(30.0 |. Pt)]);
  let firstDouble =
    style([
      position(Absolute),
      top(5.0 |. Pt),
      left(0.0 |. Pt),
      zIndex(2),
      borderRadius(12.0),
      backgroundColor(Colors.Css.white),
    ]);
  let secondDouble =
    style([position(Absolute), right(0.0 |. Pt), zIndex(1)]);

  let tripleIcon =
    style([position(Relative), width(54.0 |. Pt), height(30.0 |. Pt)]);
  let firstTriple =
    style([
      position(Absolute),
      top(5.0 |. Pt),
      left(0.0 |. Pt),
      zIndex(1),
    ]);
  let secondTriple =
    style([
      position(Absolute),
      left(15.0 |. Pt),
      zIndex(2),
      borderRadius(12.0),
      backgroundColor(Colors.Css.white),
    ]);
  let thirdTriple =
    style([
      position(Absolute),
      top(5.0 |. Pt),
      right(0.0 |. Pt),
      zIndex(3),
      borderRadius(12.0),
      backgroundColor(Colors.Css.white),
    ]);

  let rank =
    style([
      marginLeft(4.0 |. Pt),
      width(10.0 |. Pt),
      fontSize(14.0 |. Float),
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
    let child =
      switch (stat) {
      | Strength(rank) =>
        <View style=Styles.singleIconContainer>
          <Icon name="strength" style=Styles.strength />
          <Text style=Styles.rank>
            (ReasonReact.string(string_of_int(rank)))
          </Text>
        </View>
      | Intelligence(rank) =>
        <View style=Styles.singleIconContainer>
          <Icon name="intelligence" style=Styles.intelligence />
          <Text style=Styles.rank>
            (ReasonReact.string(string_of_int(rank)))
          </Text>
        </View>
      | Special(rank) =>
        <View style=Styles.singleIconContainer>
          <Icon name="special" style=Styles.special />
          <Text style=Styles.rank>
            (ReasonReact.string(string_of_int(rank)))
          </Text>
        </View>
      | StrengthIntelligence(rank) =>
        <View style=Styles.doubleIconContainer>
          <View style=Styles.doubleIcon>
            <View style=Styles.firstDouble>
              <Icon name="strength" style=Styles.strength />
            </View>
            <View style=Styles.secondDouble>
              <Icon name="intelligence" style=Styles.intelligence />
            </View>
          </View>
          <Text style=Styles.rank>
            (ReasonReact.string(string_of_int(rank)))
          </Text>
        </View>
      | IntelligenceSpecial(rank) =>
        <View style=Styles.doubleIconContainer>
          <View style=Styles.doubleIcon>
            <View style=Styles.firstDouble>
              <Icon name="intelligence" style=Styles.intelligence />
            </View>
            <View style=Styles.secondDouble>
              <Icon name="special" style=Styles.special />
            </View>
          </View>
          <Text style=Styles.rank>
            (ReasonReact.string(string_of_int(rank)))
          </Text>
        </View>
      | StrengthSpecial(rank) =>
        <View style=Styles.doubleIconContainer>
          <View style=Styles.doubleIcon>
            <View style=Styles.firstDouble>
              <Icon name="strength" style=Styles.strength />
            </View>
            <View style=Styles.secondDouble>
              <Icon name="special" style=Styles.special />
            </View>
          </View>
          <Text style=Styles.rank>
            (ReasonReact.string(string_of_int(rank)))
          </Text>
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
          <Text style=Styles.rank>
            (ReasonReact.string(string_of_int(rank)))
          </Text>
        </View>
      };

    <View style=Styles.container> child </View>;
  },
};