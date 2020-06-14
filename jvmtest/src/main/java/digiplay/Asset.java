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

import gamavm.VM;

/**
 *
 * @author mustafa
 */
public class Asset {
    public byte[] data;
    
    public void load(String path) {
        loadBytes(path);
    }
    
    public void completed() {}
    private final void loaded(long mem, int length) {
        if(length > 0) {
            data = VM.wrapBytes(mem, length);
        }
        completed();
    }
    private native long loadBytes(String path);
}
