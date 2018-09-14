type t =
  | Strength(int)
  | Intelligence(int)
  | Special(int);

type stat = {
  type_: string,
  rank: int,
};

let fromRecord = ({type_, rank}) =>
  switch (type_) {
  | "Strength" => Strength(rank)
  | "Intelligence" => Intelligence(rank)
  | "Special" => Special(rank)
  | _ => failwith("Invalid stat type.")
  };

let decoder = json =>
  json
  |> Json.Decode.map(fromRecord, json =>
       {
         type_: json |> Json.Decode.field("type", Json.Decode.string),
         rank: json |> Json.Decode.field("rank", Json.Decode.int),
       }
     );

module Styles = {
  open BsReactNative.Style;

  let container =
    style([
      flexDirection(Row),
      marginTop(8.0->Pt),
      justifyContent(FlexEnd),
      alignItems(Center),
      width(45.0->Pt),
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

let component = ReasonReact.statelessComponent("Stat");

let make = (~value, _children) => {
  ...component,
  render: _self =>
    BsReactNative.(
      switch (value) {
      | Strength(rank) =>
        <View style=Styles.container>
          <Icon name="strength" style=Styles.strength />
          <Text style=Styles.rank> <S> {string_of_int(rank)} </S> </Text>
        </View>
      | Intelligence(rank) =>
        <View style=Styles.container>
          <Icon name="intelligence" style=Styles.intelligence />
          <Text style=Styles.rank> <S> {string_of_int(rank)} </S> </Text>
        </View>
      | Special(rank) =>
        <View style=Styles.container>
          <Icon name="special" style=Styles.special />
          <Text style=Styles.rank> <S> {string_of_int(rank)} </S> </Text>
        </View>
      }
    ),
};
