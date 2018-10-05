open BsReactNative;

[@bs.deriving abstract]
type style = {
  [@bs.optional]
  color: string,
  [@bs.optional]
  fontSize: float,
  [@bs.optional]
  margin: float,
  [@bs.optional]
  fontWeight: string,
  [@bs.optional]
  flex: float,
};

module type TextComponent = {include Text.TextComponent;};

module type Styled = {let style: style;};

module Text = (Styled: Styled) : TextComponent => {
  [@bs.module "@emotion/native"] [@bs.scope "default"]
  external component: style => ReasonReact.reactClass = "Text";

  include Text.CreateComponent({
    let view = component(Styled.style);
  });
};
