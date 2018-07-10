module Directive = {
  type t;
};

module rec Selection: {
  type t =
    | Field(Field.t);

  let field: Field.t => t;
} = {
  type t =
    | Field(Field.t);

  let field = f => Field(f);
}
and Field: {
  type t;

  let make: string => t;

  let setAlias: (t, string) => t;
  let setSelections: (t, list(Selection.t)) => t;
} = {
  type t = {
    alias: option(string),
    name: string,
    arguments: list(string),
    directives: list(Directive.t),
    selections: list(Selection.t),
  };

  let make = name => {
    alias: None,
    name,
    arguments: [],
    directives: [],
    selections: [],
  };

  let setAlias = (field, alias) => {...field, alias: Some(alias)};

  let setSelections = (field, selections) => {...field, selections};
};

module Operation = {
  type operationType =
    | Query
    | Mutation
    | Subscription;

  type t = {
    operationType: option(operationType),
    name: option(string),
    variableDefinitions: list(string),
    directives: list(Directive.t),
    selectionSets: list(Selection.t),
  };

  let empty = {
    operationType: None,
    name: None,
    variableDefinitions: [],
    directives: [],
    selectionSets: [],
  };
};

let named = (id, selectionSets) => {
  ...Operation.empty,
  name: Some(id),
  selectionSets,
};

let field = name => Field.make(name) |. Selection.field;

let withAlias = (selection: Selection.t, alias) =>
  switch (selection) {
  | Field(field) => Field.setAlias(field, alias) |. Selection.field
  };

let withSelection = (selection: Selection.t, newSelection) =>
  switch (selection) {
  | Field(field) =>
    Field.setSelections(field, newSelection) |. Selection.field
  };
/* module Types = {
     let character = Gql.type_("Character");
     let titleAsc = Gql.type_("title_ASC");
   }; */

let query =
  named(
    "AllCards",
    [
      field("allCards")
      |. withAlias("characters")
      |. withSelection([
           field("uid"),
           field("title"),
           field("subtitle"),
           field("effect")
           |. withSelection([field("symbol"), field("text")]),
           field("image") |. withSelection([field("thumbnail")]),
         ]),
    ],
  );
/* |. withArgument("filter", queryArgs([("type", Types.character)])) */
/* |. withArgument("orderBy", Types.titleAsc); */
