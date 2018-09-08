var asynstorageDown = require('asyncstorage-down');
var packager = require('level-packager');
var subleveldown = require('subleveldown');

module.exports = {
  make: (location, options) => packager(asynstorageDown)(location, options),
  namespace: (db, namespace, options) => subleveldown(db, namespace, options),
};
