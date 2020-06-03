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
public class IndexBuffer {

    long deviceHandle;
    short[] buffer;
    int size;
    public boolean dirty;
    
    public IndexBuffer(int size) {
        buffer = new short[size];
    }
    
    public void set(int index, int val) {
        buffer[index] = (short)val;
    }
    
    public void set(int index, int val0, int val1, int val2) {
        buffer[index++] = (short)val0;
        buffer[index++] = (short)val1;
        buffer[index] = (short)val2;
    }
    
    @Override
    protected native void finalize() throws Throwable;
    
    public native void bind();
    
}
