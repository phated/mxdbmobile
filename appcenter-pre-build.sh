#!/usr/bin/env bash

npm run build
sed "s/APPCENTER_SECRET_PLACEHOLDER/$APPCENTER_SECRET/g" templates/appcenter-config.json > android/app/src/main/assets/appcenter-config.json
