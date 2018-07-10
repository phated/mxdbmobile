type t = {
  symbol: Symbol.t,
  text: option(string),
};

let decoder = json => {
  symbol: json |> Json.Decode.field("symbol", Symbol.decoder),
  text:
    json
    |> Json.Decode.optional(Json.Decode.field("text", Json.Decode.string)),
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
      paddingLeft(4.0 |. Pt),
      marginLeft(4.0 |. Pt),
      borderLeftWidth(2.0),
      borderLeftColor(Colors.Css.gray),
      borderStyle(Solid),
    ]);

  let effectText = style([fontSize(12.0 |. Float)]);
};

let component = ReasonReact.statelessComponent("Effect");

let make = (~effect, _children) => {
  let symbolImage =
    switch (effect.symbol) {
    | Attack => <AttackIcon />
    | Defend => <DefendIcon />
    | Constant => <ConstantIcon />
    | Play => <PlayIcon />
    | Push => <PushIcon />
    | None => ReasonReact.null
    };

  let effectStyle =
    switch (effect.symbol) {
    | None => Styles.effectWithoutSymbol
    | _ => Styles.effectWithSymbol
    };

  let effectText = Belt.Option.getWithDefault(effect.text, "");

  let c = {
    ...component,
    render: _self =>
      BsReactNative.(
        <View style=Styles.container>
          <View style=Styles.effectContainer>
            symbolImage
            <View style=effectStyle>
              <Text style=Styles.effectText>
                (ReasonReact.string(effectText))
              </Text>
            </View>
          </View>
        </View>
      ),
  };

  c;
};
