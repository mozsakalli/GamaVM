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
public class Mesh {
    int type;
    int capacity;
    int size;
    int version;
    long vertices;
    long cache;
    long gpu;
    
    public final static int QUAD    = 0;
    public final static int POLYGON = 1;
    
    public Mesh(int type, int capacity) {
        this.type = type;
        resize(capacity);
    }
    
    @Override protected native void finalize();
    
    public final native void resize(int capacity);
    public final native void setQuad(int index, float x, float y, float width, float height, float u1,float v1, float u2, float v2,
            float u3, float v3, float u4, float v4);
    public final native void setPolygon(float[] verts, float[] uvs, int[] colors, short[] triangles, int count);
}
