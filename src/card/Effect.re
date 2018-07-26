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
      paddingLeft(4.0 |. Pt),
      marginLeft(4.0 |. Pt),
      borderLeftWidth(2.0),
      borderLeftColor(Colors.Css.gray),
      borderStyle(Solid),
    ]);

  let effectText = style([fontSize(11.0 |. Float)]);

  let attack = style([color(Colors.Css.attack)]);
  let defend = style([color(Colors.Css.defend)]);
  let constant = style([color(Colors.Css.constant)]);
  let play = style([color(Colors.Css.play)]);
  let push = style([color(Colors.Css.push)]);
};

let component = ReasonReact.statelessComponent("Effect");

let make = (~effect, _children) => {
  let symbolImage =
    switch (effect.symbol) {
    | Attack => <Icon name="attack" style=Styles.attack size=16 />
    | Defend => <Icon name="defend" style=Styles.defend size=16 />
    | Constant => <Icon name="constant" style=Styles.constant size=14 />
    | Play => <Icon name="play" style=Styles.play size=16 />
    | Push => <Icon name="push" style=Styles.push size=16 />
    | None => ReasonReact.null
    };

  let effectStyle =
    switch (effect.symbol) {
    | None => Styles.effectWithoutSymbol
    | _ => Styles.effectWithSymbol
    };

  let effectText = Belt.Option.getWithDefault(effect.text, "");

  {
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
};
