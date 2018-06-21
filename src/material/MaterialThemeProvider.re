[@bs.module "react-native-material-ui"]
external themeProvider : ReasonReact.reactClass = "ThemeProvider";

let make = children =>
  ReasonReact.wrapJsForReason(
    ~reactClass=themeProvider,
    ~props=Js.Obj.empty(),
    children,
  );
