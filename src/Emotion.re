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
  [@bs.optional]
  flexDirection: string,
  [@bs.optional]
  justifyContent: string,
  [@bs.optional]
  alignItems: string,
  [@bs.optional]
  height: float,
  [@bs.optional]
  paddingHorizontal: float,
};

module type Styled = {let style: style;};

module type TextComponent = {include BsReactNative.Text.TextComponent;};
module Text = (Styled: Styled) : TextComponent => {
  [@bs.module "@emotion/native"] [@bs.scope "default"]
  external component: style => ReasonReact.reactClass = "Text";

  include BsReactNative.Text.CreateComponent({
    let view = component(Styled.style);
  });
};

module type ViewComponent = {include BsReactNative.View.ViewComponent;};
module View = (Styled: Styled) : ViewComponent => {
  [@bs.module "@emotion/native"] [@bs.scope "default"]
  external component: style => ReasonReact.reactClass = "View";

  include BsReactNative.View.CreateComponent({
    let view = component(Styled.style);
  });
};

module type SafeAreaViewComponent = {include BsReactNative.View.ViewComponent;
};
module SafeAreaView = (Styled: Styled) : SafeAreaViewComponent => {
  [@bs.module "@emotion/native"] [@bs.scope "default"]
  external component: style => ReasonReact.reactClass = "SafeAreaView";

  include BsReactNative.View.CreateComponent({
    let view = component(Styled.style);
  });
};

module type ImageComponent = {include BsReactNative.Image.ImageComponent;};
module Image = (Styled: Styled) : ImageComponent => {
  [@bs.module "@emotion/native"] [@bs.scope "default"]
  external component: style => ReasonReact.reactClass = "Image";

  include BsReactNative.Image.CreateComponent({
    let view = component(Styled.style);
  });
};

module type ScrollViewComponent = {
  include BsReactNative.ScrollView.ScrollViewComponent;
};
module ScrollView = (Styled: Styled) : ScrollViewComponent => {
  [@bs.module "@emotion/native"] [@bs.scope "default"]
  external component: style => ReasonReact.reactClass = "ScrollView";

  include BsReactNative.ScrollView.CreateComponent({
    let view = component(Styled.style);
  });
};

module type FlatListComponent = {
  include BsReactNative.FlatList.FlatListComponent;
};
module FlatList = (Styled: Styled) : FlatListComponent => {
  [@bs.module "@emotion/native"] [@bs.scope "default"]
  external component: style => ReasonReact.reactClass = "FlatList";

  include BsReactNative.FlatList.CreateComponent({
    let view = component(Styled.style);
  });
};

module type ActivityIndicatorComponent = {
  include BsReactNative.ActivityIndicator.ActivityIndicatorComponent;
};
module ActivityIndicator = (Styled: Styled) : ActivityIndicatorComponent => {
  [@bs.module "@emotion/native"] [@bs.scope "default"]
  external component: style => ReasonReact.reactClass = "ActivityIndicator";

  include BsReactNative.ActivityIndicator.CreateComponent({
    let view = component(Styled.style);
  });
};

module type StatusBarComponent = {include BsReactNative.StatusBar.Component;};
module StatusBar = (Styled: Styled) : StatusBarComponent => {
  [@bs.module "@emotion/native"] [@bs.scope "default"]
  external component: style => ReasonReact.reactClass = "StatusBar";

  include BsReactNative.StatusBar.CreateComponent({
    let view = component(Styled.style);
  });
};

module type TouchableOpacityComponent = {
  include BsReactNative.TouchableOpacity.Component;
};
module TouchableOpacity = (Styled: Styled) : TouchableOpacityComponent => {
  [@bs.module "@emotion/native"] [@bs.scope "default"]
  external component: style => ReasonReact.reactClass = "TouchableOpacity";

  include BsReactNative.TouchableOpacity.CreateComponent({
    let view = component(Styled.style);
  });
};

module type TouchableWithoutFeedbackComponent = {
  include BsReactNative.TouchableWithoutFeedback.Component;
};
module TouchableWithoutFeedback =
       (Styled: Styled)
       : TouchableWithoutFeedbackComponent => {
  [@bs.module "@emotion/native"] [@bs.scope "default"]
  external component: style => ReasonReact.reactClass =
    "TouchableWithoutFeedback";

  include BsReactNative.TouchableWithoutFeedback.CreateComponent({
    let view = component(Styled.style);
  });
};

/* TODO: WebView doesn't follow the same pattern as the other components */
/* TODO: TextInput doesn't follow the same pattern as the other components */

/* InnerRef helper */
module WithRef = {
  let component = ReasonReact.statelessComponent("Emotion.WithRef");

  let make = (~innerRef, children) => {
    ...component,
    render: _self => {
      let child =
        switch (children) {
        | [|item|] => item
        | _ => failwith("Need exactly 1 child")
        };

      ReasonReact.cloneElement(child, ~props={"innerRef": innerRef}, [||]);
    },
  };
};
