import { AppRegistry } from 'react-native';
import { name as appName } from './app.json';

import { root as RootComponent } from './src/Main.bs.js';

AppRegistry.registerComponent(appName, () => RootComponent);
