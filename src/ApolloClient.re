type storage;

[@bs.deriving abstract]
type persistCacheOptions = {
  cache: Apollo.apolloCache,
  storage,
  trigger: string,
  maxSize: bool,
  debug: bool,
};

[@bs.module "apollo-cache-persist"]
external persistCache: persistCacheOptions => Js.Promise.t(unit) = "";

[@bs.module "react-native"] [@bs.val]
external asyncStorage: storage = "AsyncStorage";

let cache = Apollo.Cache.InMemory.make();

persistCache(
  persistCacheOptions(
    ~cache,
    ~storage=asyncStorage,
    ~trigger="write",
    ~maxSize=false,
    ~debug=true,
  ),
);

let httpLink = Apollo.Link.Http.make(~uri="https://graphql.metaxdb.com/", ());

let link = Apollo.Link.from([|httpLink|]);

let make = () =>
  Apollo.Client.make(
    ~link,
    ~cache,
    ~initializers=[PrivateDeck.initializers],
    ~resolvers=[PrivateDeck.resolvers],
    (),
  );
