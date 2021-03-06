/*

pxCore Copyright 2005-2018 John Robinson

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

*/

var https = require('https');
var url = require('url');
var ac = require('rcvrcore/utils/AccessControl');

function HttpsWrap(accessControl) {
  HttpsWrap.prototype.request = function (options, callback) {
    if (accessControl) {
      var optionsCopy = ac._extend({}, typeof options === 'string' ? url.parse(options) : options);
      optionsCopy._defaultAgent = https.globalAgent;
      return accessControl.createClientRequest(optionsCopy, callback, "https://");
    }
    return https.request.apply(null, arguments);
  };

  HttpsWrap.prototype.get = function (options, callback) {
    var req = this.request.apply(this, arguments);
    req.end();
    return req;
  };
}

// No not expose sockets.
//HttpsWrap.prototype.globalAgent = https.globalAgent;

// Server functionality needs to be disabled.
//HttpsWrap.prototype.Server = https.Server;
//HttpsWrap.prototype.createServer = https.createServer;

module.exports = HttpsWrap;
