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
    //vec3 pos
    //vec2 uv
    //vec4(1) color
    
    //tl br uv1,uv2,yv3,uv4 p1,p2,p3,p4
    float[] buffer;
    int size;
    QuadMesh next;
    int version;
    
    final static int STRIDE = 24;
    
    static QuadMesh CACHE;
    public static QuadMesh get(int size) {
        QuadMesh q = CACHE;
        if(q != null) {
            CACHE = CACHE.next;
            if(q.buffer.length < size) q.buffer = new float[size];
            q.size = size;
            q.next = null;
        } else {
            q = new QuadMesh();
            q.buffer = new float[size];
            q.size = size;
        }
        
        return q;
    }
    
    public void set(int index, float x1, float y1, float x2, float y2,
            float u1,float v1, 
            float u2,float v2, 
            float u3,float v3, 
            float u4,float v4 
            ) {
        int o = index * STRIDE;
        buffer[o++] = x1;
        buffer[o++] = y1;
        buffer[o++] = x2;
        buffer[o++] = y2;
        buffer[o++] = u1;
        buffer[o++] = v1;
        buffer[o++] = u2;
        buffer[o++] = v2;
        buffer[o++] = u3;
        buffer[o++] = v3;
        buffer[o++] = u4;
        buffer[o++] = v4;
        
    }
}
