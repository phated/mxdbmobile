let inMemoryCache = ApolloInMemoryCache.createInMemoryCache();

let httpLink =
  ApolloLinks.createHttpLink(
    ~uri="https://api.graph.cool/simple/v1/metaxdb",
    (),
  );

let client =
  ReasonApollo.createApolloClient(~link=httpLink, ~cache=inMemoryCache, ());
