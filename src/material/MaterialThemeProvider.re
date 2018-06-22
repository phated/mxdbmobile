[@bs.module "react-native-material-ui"]
external themeProvider : ReasonReact.reactClass = "ThemeProvider";

let uiTheme = {
  "listItem": {
    "leftElementContainer": {
      "width": "auto",
    }
  },
  "subheader": {
    "container": {
      "backgroundColor": "#f7f7f7", /* Temporary - default style in reroute-native */
    },
  },
};

let make = children =>
  ReasonReact.wrapJsForReason(
    ~reactClass=themeProvider,
    ~props={"uiTheme": uiTheme},
    children,
  );
