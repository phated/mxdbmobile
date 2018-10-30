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

/* [@bs.module "apollo-cache-hermes"]
   external createHermesCache: unit => ReasonApolloTypes.apolloCache = "Hermes"; */

let inMemoryCache =
  ApolloInMemoryCache.createInMemoryCache();
                                         /* ~dataIdFromObject=data => data##id->Debug.tap,
                                            (), */
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
  ApolloLinks.createHttpLink(
    ~uri="https://api.graph.cool/simple/v1/metaxdb",
    (),
  );

/* [@bs.module "apollo-link-retry"] [@bs.new]
   external createRetryLink: unit => ReasonApolloTypes.apolloLink = "RetryLink";

   let retryLink = createRetryLink(); */

/* [@bs.module "apollo-link-queue"] [@bs.new]
   external createQueueLink: unit => ReasonApolloTypes.apolloLink = "default";

   [@bs.send] external openLink: ReasonApolloTypes.apolloLink => unit = "open";
   [@bs.send] external closeLink: ReasonApolloTypes.apolloLink => unit = "close";

   let offlineLink = createQueueLink(); */

let link =
  ApolloLinks.from([|
    /* retryLink, */
    /* offlineLink, */
    httpLink,
  |]);

/* let handleOffline = isConnected =>
     if (isConnected) {
       openLink(offlineLink);
     } else {
       closeLink(offlineLink);
     };

   BsReactNative.NetInfo.IsConnected.fetch()
   |> Js.Promise.then_(isConnected => {
        handleOffline(isConnected);
        Js.Promise.resolve(isConnected);
      });

   BsReactNative.NetInfo.IsConnected.addEventListener(handleOffline); */

let client = ReasonApollo.createApolloClient(~link, ~cache=inMemoryCache, ());
