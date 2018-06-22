[@bs.module "react-native-fast-image"]
external image : ReasonReact.reactClass = "default";

/* [@bs.deriving abstract]
   type searchableConfig = {
     autoFocus: bool,
     placeholder: string,
   };

   [@bs.deriving abstract]
   type jsProps = {
     centerElement: string,
     searchable: Js.nullable(searchableConfig),
     rightElement: string,
   }; */

let make = (~uri, _children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=image,
    ~props={
      "source": {
        "uri": uri,
      },
      "resizeMode": "contain",
      "style": {
        "height": Js.undefined,
        "width": Js.undefined,
        "flex": 1,
      },
    },
    [||],
  );
