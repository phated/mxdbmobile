import { AppRegistry } from 'react-native';
import codePush from "react-native-code-push";

import { root as RootComponent } from './src/Main.bs.js';

AppRegistry.registerComponent('mxdbmobile', () => codePush(RootComponent));
