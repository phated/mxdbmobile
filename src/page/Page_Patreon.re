module Styles = {
  let container =
    Emotion.style(~flex=1.0, ~justifyContent="space-between", ());

  let blockContainer =
    Emotion.style(
      ~flex=1.0,
      ~justifyContent="center",
      ~alignItems="center",
      (),
    );

  let patreonButton = Emotion.style(~marginTop=32.0, ());

  let patreonName = Emotion.style(~marginTop=10.0, ~fontWeight="bold", ());

  let special = Emotion.style(~color=Colors.MetaX.special, ());
};

let component = ReasonReact.statelessComponent("Page.Patreon");

/* TODO: retained props */
let make = _children => {
  ...component,
  render: _self => {
    let patreonLogo = BsReactNative.Packager.require("../assets/patron.png");

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
          <S> "Matt Smith, Mark de la Fuente & Steve Paulson" </S>
        </Text>
      </View>
    </View>;
  },
};
