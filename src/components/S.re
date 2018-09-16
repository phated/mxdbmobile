let component = ReasonReact.statelessComponent("String");

let make = children => {
  ...component,
  render: _self => {
    let text = Js.Array.joinWith(" ", children);
    ReasonReact.string(text);
  },
};
