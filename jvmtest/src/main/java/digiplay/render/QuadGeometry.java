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

package digiplay.render;

/**
 *
 * @author mustafa
 */
public class QuadGeometry {

    //x,y,z x4 = 12
    //uv x4    = 8
    //
    float[] buffer;
    int size;
    int version;
    QuadGeometry next;
    
    static QuadGeometry CACHE;
    
    public static QuadGeometry alloc(int size) {
        QuadGeometry r = CACHE;
        if(r != null) {
            CACHE = CACHE.next;
            r.next = null;
            if(r.size < size) {
                r.buffer = new float[size];
            }
            r.size = size;
        } else r = new QuadGeometry(size);
        return r;
    }
    
    public QuadGeometry(int size) {
        buffer = new float[size];
        this.size = size;
    }
    
    public void set(int index, 
            float x1, float y1, float z1, 
            float x2, float y2, float z2, 
            float x3, float y3, float z3, 
            float x4, float y4, float z4, 
            float u1, float v1, float u2, float v2, 
            float u3, float v3, float u4, float v4) {
    }
    
    /*
    int version;
    
    public QuadGeometry(int capacity) {
        handle = alloc(capacity);
    }
    
    final native long alloc(int capacity);
    final native void dealloc(long handle);
    
    public native void set(int index, 
            float x1, float y1, float z1, 
            float x2, float y2, float z2, 
            float x3, float y3, float z3, 
            float x4, float y4, float z4, 
            float u1, float v1, float u2, float v2, 
            float u3, float v3, float u4, float v4);
    
    public native void applyMatrix(Matrix2D matrix);
    */
}
