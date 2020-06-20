/*
 * Copyright (C) 2019 Digitoy Games.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package digiplay;

import gamavm.External;
import gamavm.VM;

/**
 *
 * @author mustafa
 */
public class Net {
    /*
    public interface HttpListener {
        public void onHttpSuccess(byte[] bytes);
        public void onHttpFail();
    }
    public native static void http(String url, String params, HttpListener callback);
    */
    
    @External
    public static class Http extends ByteArrayCompletable {
        public String url;
        public String postData;

        public Http(String url) {
            this.url = url;
        }
        
        public Http param(String name, Object value) {
            if(value != null) {
                if(postData == null)
                    postData = name;
                else postData += "&" + name;
                postData += "=" + value;
            }
            return this;
        }
        
        public void start() {
            start(VM.getAddress(this), url, postData);
        }
        
        @External private static native void start(long handle, String url, String postData);
    }
}
