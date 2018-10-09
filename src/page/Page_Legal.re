module Styles = {
  let container =
    Emotion.style(~flex=1.0, ~justifyContent="space-between", ());

  let blockContainer =
    Emotion.style(
      ~flex=1.0,
      ~alignItems="center",
      ~justifyContent="center",
      (),
    );
};

let component = ReasonReact.statelessComponent("Page.Legal");

/* TODO: retained props */
let make = _children => {
  ...component,
  render: _self => {
    let graphcoolLogo =
      BsReactNative.Packager.require("../assets/graphcool.png");

    <View style=Styles.container>
      <View style=Styles.blockContainer>
        <Text> <S> "Icons provided by The Noun Project:" </S> </Text>
        <LinkOut url="https://thenounproject.com/icon/219514/">
          <Text> <S> "Cards Icon by Daniel Solis" </S> </Text>
        </LinkOut>
        <LinkOut url="https://thenounproject.com/icon/1156459/">
          <Text> <S> "Deck Icon by Michael G Brown" </S> </Text>
        </LinkOut>
      </View>
      <View style=Styles.blockContainer>
        <LinkOut url="https://www.graph.cool/cloud/">
          <Image source={`Required(graphcoolLogo)} />
        </LinkOut>
      </View>
    </View>;
  },
};
