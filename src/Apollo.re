type storage;

[@bs.deriving abstract]
type persistCacheOptions = {
  cache: ReasonApolloTypes.apolloCache,
  storage,
  trigger: string,
  maxSize: bool,
  debug: bool,
};

[@bs.module "apollo-cache-persist"]
external persistCache: persistCacheOptions => Js.Promise.t(unit) = "";

[@bs.module "react-native"] [@bs.val]
external asyncStorage: storage = "AsyncStorage";

let inMemoryCache = ApolloInMemoryCache.createInMemoryCache();

/*
 persistCache(
   persistCacheOptions(
     ~cache=inMemoryCache,
     ~storage=asyncStorage,
     ~trigger="background",
     ~maxSize=false,
     ~debug=true,
   ),
 ); */

let httpLink =
  ApolloLinks.createHttpLink(~uri="https://graphql.metaxdb.com/", ());

let link = ApolloLinks.from([|httpLink|]);

let client = ReasonApollo.createApolloClient(~link, ~cache=inMemoryCache, ());
