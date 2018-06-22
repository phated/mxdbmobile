'use strict';


function tapLog(res) {
  console.log(res);
  return Promise.resolve(res);
}

exports.tapLog = tapLog;
/* No side effect */
