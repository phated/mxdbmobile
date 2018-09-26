[@bs.module "react-dom/server.browser"]
external renderToStaticMarkup: ReasonReact.reactElement => string = "";

let wrapperStyles =
  ReactDOMRe.Style.make(
    ~display="flex",
    ~flex="1",
    ~flexDirection="row",
    ~flexWrap="wrap",
    ~justifyContent="space-between",
    (),
  );

let component = ReasonReact.statelessComponent("StaticSvg");

let make = (~style=?, children) => {
  ...component,
  render: _self => {
    open BsReactNative;

    /* Arbitrary number of children */
    /* TODO: Reason's child spread doesn't work when window.addEventListener doesn't exist */
    let [|child1, child2, child3|] = children;

    let html =
      renderToStaticMarkup(
        <div style=wrapperStyles> child1 child2 child3 </div>,
      );

    <WebView
      ?style
      scrollEnabled=false
      bounces=false
      source={WebView.sourceHtml(~html, ())}
    />;
  },
};
