module Row =
  Emotion.View({
    let style = Emotion.style(~flex=1.0, ~flexDirection="row", ());
  });

module Column =
  Emotion.View({
    let style = Emotion.style(~flex=1.0, ~flexDirection="column", ());
  });
