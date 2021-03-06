module Styles = {
  open BsReactNative.Style;

  let container = style([flex(1.0), justifyContent(SpaceBetween)]);

  let blockContainer =
    style([flex(1.0), justifyContent(Center), alignItems(Center)]);

  let patreonButton = style([marginTop(32.0->Pt)]);

  let patreonName = style([marginTop(10.0->Pt), fontWeight(`Bold)]);

  let special = style([color(Colors.MetaX.Css.special)]);
};

let patreonLogo = BsReactNative.Packager.require("../assets/patron.png");

let component = ReasonReact.statelessComponent("Page.Patreon");

/* TODO: retained props */
let make = _children => {
  ...component,
  render: _self =>
    BsReactNative.(
      <View style=Styles.container>
        <View style=Styles.blockContainer>
          <Text>
            <S> "Our work is supported by our Patrons on Patreon." </S>
          </Text>
          <Text> <S> "For development updates and extra features," </S> </Text>
          <Text> <S> "subscribe to us on Patreon!" </S> </Text>
          <LinkOut
            style=Styles.patreonButton url="https://www.patreon.com/metaxdb">
            <Image source={`Required(patreonLogo)} />
          </LinkOut>
        </View>
        <View style=Styles.blockContainer>
          <Text>
            <S> "Extra " </S>
            <Icon name="special" style=Styles.special />
            <S> " thanks to our Rank 5+ subscribers:" </S>
          </Text>
          <Text style=Styles.patreonName>
            <S>
              "Matt Smith, Mason Knox, Mark de la Fuente & Steve Paulson"
            </S>
          </Text>
        </View>
      </View>
    ),
};
