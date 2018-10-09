module Styles = {
  open BsReactNative.Style;

  let scroller = style([flex(1.0)]);
  let container =
    style([paddingTop(4.0->Pt), justifyContent(SpaceBetween)]);

  let warningContainer =
    style([
      flexDirection(Row),
      alignItems(Center),
      paddingHorizontal(10.0->Pt),
      paddingVertical(4.0->Pt),
    ]);

  let warningMessageWrapper =
    style([flex(1.0), paddingHorizontal(4.0->Pt)]);

  let warningIcon = style([color(Colors.Css.warning)]);
  let warningMessage = style([color(Colors.Css.black)]);
  let warningCounts = style([color(Colors.Css.black), textAlign(Right)]);

  let testCharacter =
    style([color(Colors.MetaX.Css.character), fontWeight(`Bold)]);
  let testStrength =
    style([color(Colors.MetaX.Css.strength), fontWeight(`Bold)]);

  let chartContainer =
    style([height(460.0->Pt), padding(10.0->Pt), paddingTop(20.0->Pt)]);
};

let toAmountWarningMessage = warning => {
  open BsReactNative.Style;

  let titleStyle = style([color(warning##color), fontWeight(`Bold)]);
  <View style=Styles.warningContainer>
    <Icon name="warning" style=Styles.warningIcon />
    <View style=Styles.warningMessageWrapper>
      <Text style=Styles.warningMessage>
        <S> "Too many " </S>
        <Text style=titleStyle> <S> {warning##name} </S> </Text>
        <S> "." </S>
      </Text>
    </View>
    <View>
      <Text style=Styles.warningCounts>
        <S> "Have:" {warning##amount} </S>
        <S> "\nMax:" {warning##max} </S>
      </Text>
    </View>
  </View>;
};

let toDeckSizeWarningMessage = warning =>
  <View style=Styles.warningContainer>
    <Icon name="warning" style=Styles.warningIcon />
    <View style=Styles.warningMessageWrapper>
      <Text style=Styles.warningMessage> <S> warning </S> </Text>
    </View>
  </View>;

let component = ReasonReact.statelessComponent("Page.Stats");

/* TODO: retained props */
let make = (~deck, _children) => {
  ...component,
  render: _self => {
    let characterCount = Deck.countCharacters(deck);
    let eventCount = Deck.countEvents(deck);
    let battleCount = Deck.countBattles(deck);
    let missingCount = max(40 - characterCount - eventCount - battleCount, 0);

    let cardTypeData = [|
      Pie.Data.row(
        ~x="Characters",
        ~y=characterCount,
        ~fill=Colors.MetaX.character,
      ),
      Pie.Data.row(~x="Events", ~y=eventCount, ~fill=Colors.MetaX.event),
      Pie.Data.row(
        ~x="Battle Cards",
        ~y=battleCount,
        ~fill=Colors.MetaX.battle,
      ),
      Pie.Data.row(~x="Remain", ~y=missingCount, ~fill=Colors.MetaX.remain),
    |];

    let toStrengthRow = item =>
      Bar.Data.row(~x=item##x, ~y=item##y, ~fill=Colors.MetaX.strength);
    let toIntelligenceRow = item =>
      Bar.Data.row(~x=item##x, ~y=item##y, ~fill=Colors.MetaX.intelligence);
    let toSpecialRow = item =>
      Bar.Data.row(~x=item##x, ~y=item##y, ~fill=Colors.MetaX.special);
    let toMultiRow = item =>
      Bar.Data.row(~x=item##x, ~y=item##y, ~fill=Colors.MetaX.multi);

    let battleCards = Deck.countBattleCardRanks(deck);
    let rankData = [|
      Belt.Array.map(battleCards##strength, toStrengthRow),
      Belt.Array.map(battleCards##intelligence, toIntelligenceRow),
      Belt.Array.map(battleCards##special, toSpecialRow),
      Belt.Array.map(battleCards##multi, toMultiRow),
    |];

    let strengthCount = Deck.countStrength(deck);
    let intelligenceCount = Deck.countIntelligence(deck);
    let specialCount = Deck.countSpecial(deck);
    let multiCount = Deck.countMulti(deck);

    let battleCardData = [|
      Pie.Data.row(
        ~x="Strength",
        ~y=strengthCount,
        ~fill=Colors.MetaX.strength,
      ),
      Pie.Data.row(
        ~x="Intelligence",
        ~y=intelligenceCount,
        ~fill=Colors.MetaX.intelligence,
      ),
      Pie.Data.row(~x="Special", ~y=specialCount, ~fill=Colors.MetaX.special),
      Pie.Data.row(~x="Multi", ~y=multiCount, ~fill=Colors.MetaX.multi),
    |];

    let amountWarnings =
      Deck.getAmountWarnings(deck)
      ->Belt.List.map(toAmountWarningMessage)
      ->Belt.List.toArray;

    let deckSizeWarning =
      Deck.getDeckSizeWarnings(deck)
      ->Belt.List.map(toDeckSizeWarningMessage)
      ->Belt.List.toArray;

    <ScrollView contentContainerStyle=Styles.container style=Styles.scroller>
      <View> ...deckSizeWarning </View>
      <View> ...amountWarnings </View>
      <StaticSvg style=Styles.chartContainer>
        <Pie data=cardTypeData />
        <Pie data=battleCardData />
        <Bar data=rankData />
      </StaticSvg>
    </ScrollView>;
  },
};
