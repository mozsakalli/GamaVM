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

/**
 *
 * @author mustafa
 */
public class QuadMesh {
    long handle;
    
    public QuadMesh(int size) {
        handle = create(size);
    }
    
    native static long create(int size);
    
    public native void set(int index, float x1, float y1, float x2, float y2, float u1, float v1, float u2, float v2, float u3, float v3, float u4, float v4);
}
