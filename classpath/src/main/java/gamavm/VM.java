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

package gamavm;

import java.lang.reflect.Method;

/**
 *
 * @author mustafa
 */
@External
public class VM {
    
    public static native Class getClass(Object o);
    public static native Object getObject(long address);
    public static native ClassLoader getSystemClassLoader();
    
    public static native long getAddress(Object o);
    public static native Object allocObject(Class cls);
    public static native Object allocArray(Class cls, int length);
    public static native byte[] wrapBytes(long addr, int length);
    public static native int[] wrapInts(long addr, int length);
    
    public static native long allocMem(int size);
    public static native void freeMem(long ptr);
    public static native void setShort(long ptr, int value);
    public static native void setFloat(long ptr, float value);
    
    public static native int getArrayLength(Object array);
    
    public static native void gcProtect(Object o);
    public static native void gcUnProtect(Object o);
    
    @External public static native byte[] readFile(String path);
    public static native byte[] extractZip(String name, byte[] zip, int offset);
    
    public static native Method getCaller();
}
