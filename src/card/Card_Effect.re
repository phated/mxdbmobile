type t = {
  symbol: Card_Symbol.t,
  text: option(string),
};

let decoder = json => {
  symbol: json |> Json.Decode.field("symbol", Card_Symbol.decoder),
  text:
    json
    |> Json.Decode.optional(Json.Decode.field("text", Json.Decode.string)),
};

let getText = effect =>
  switch (effect.text) {
  | Some(text) => text
  | None => ""
  };

module Styles = {
  open BsReactNative.Style;

  let container = style([flex(1.)]);
  let effectContainer =
    style([
      justifyContent(FlexEnd),
      flexDirection(Row),
      alignItems(Center),
      marginTop(Auto),
    ]);

  let effectWithoutSymbol = style([flex(1.)]);
  let effectWithSymbol =
    style([
      flex(1.),
      paddingLeft(4.0->Pt),
      marginLeft(4.0->Pt),
      borderLeftWidth(2.0),
      borderLeftColor(Colors.Css.gray),
      borderStyle(Solid),
    ]);

  let effectText = style([fontSize(11.0->Float)]);
};

let component = ReasonReact.statelessComponent("Card.Effect");

let make = (~value, _children) => {
  let effectStyle =
    Card_Symbol.hasSymbol(value.symbol) ?
      Styles.effectWithSymbol : Styles.effectWithoutSymbol;

  let effectText = Belt.Option.getWithDefault(value.text, "");

  {
    ...component,
    render: _self =>
      BsReactNative.(
        <View style=Styles.container>
          <View style=Styles.effectContainer>
            <Card_Symbol value={value.symbol} />
            <View style=effectStyle>
              <Text style=Styles.effectText> <S> effectText </S> </Text>
            </View>
          </View>
        </View>
      ),
  };
};
