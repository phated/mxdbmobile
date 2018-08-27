let component = ReasonReact.statelessComponent("String");

let make = children => {
  ...component,
  render: _self => {
    let [|text|] = children;
    ReasonReact.string(text);
  },
};
