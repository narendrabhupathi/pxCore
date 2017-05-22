/*

 pxCore Copyright 2005-2017 John Robinson

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

// rtUrlUtils.h

#include "rtUrlUtils.h"
#include <string.h>


#if !defined(WIN32) && !defined(ENABLE_DFB)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wall"
#endif

#include <curl/curl.h>

#if !defined(WIN32) && !defined(ENABLE_DFB)
#pragma GCC diagnostic pop
#endif

/*
 * rtUrlEncodeParameters: Takes an url in the form of
 *  "http://blahblah/index.js?some=some1&parm=value" and
 *  returns an rtString with the query parameters url-encoded.
 */
rtString rtUrlEncodeParameters(const char* url)
{
  rtString retVal;

/*
  char * pch;
  pch = strtok ((char *)url,"?");
  if (pch != NULL) {
    retVal = pch;
    // Get remainder of url after '?' and encode it
    pch = strtok (NULL, "?");
    if( pch != NULL) {
      retVal.append("?");
      CURL *curl = curl_easy_init();
      if(curl) {
        char *output = curl_easy_escape(curl, pch, 0);
        if(output) {
          retVal.append(output);
        }
        curl_free(output);
      }
    }
  }
*/
  rtString tempStr = url;
  int32_t pos = tempStr.find(0,"?");
  if( pos != -1) {
    retVal = tempStr.substring(0, pos+1);
    tempStr = tempStr.substring(pos+1,0);
    CURL *curl = curl_easy_init();
    if(curl && tempStr.length() > 0) {
      char *output = curl_easy_escape(curl, tempStr.cString(), 0);
      if(output) {
        retVal.append(output);
      }
      curl_free(output);
    }
  }
  else {
    retVal = url;
  }

  // printf("Returning %s\n",retVal.cString());
  return retVal;
}
