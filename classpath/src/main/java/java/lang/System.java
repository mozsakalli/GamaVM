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

package java.lang;

import java.io.IOException;
import java.io.OutputStream;
import java.io.PrintStream;

public final class System {

    static class SystemOutStream extends PrintStream {

        final static OutputStream EMPTYSTREAM = new OutputStream() {
            @Override
            public void write(int b) throws IOException {
            }
        };

        StringBuilder buffer = new StringBuilder();
        
        public SystemOutStream() {
            super(EMPTYSTREAM);
        }

        @Override
        public void print(String str) {
            synchronized (this) {
                buffer.append(str);
            }
        }

        @Override
        public void println(String str) {
            synchronized (this) {
                buffer.append(str);
                printImpl(buffer.toString());
                buffer.setLength(0);
            }
        }

        @Override
        public void flush() {
            synchronized (this) {
                if (buffer.length() > 0) {
                    printImpl(buffer.toString());
                }
                buffer.setLength(0);
            }
        }

        private native static void printImpl(String str);
    }
    
    public static final java.io.PrintStream err = new SystemOutStream();
    public static final java.io.PrintStream out = new SystemOutStream();

    public native static void arraycopy(java.lang.Object src, int srcOffset, java.lang.Object dst, int dstOffset, int length);

    /**
     * Returns the current time in milliseconds.
     */
    public native static long currentTimeMillis();
    public native static long nanoTime();
    
    public static native void exit(int status);

    public native static void gc();
    
    public static java.lang.String getProperty(java.lang.String key){
        return null; 
    }

    /**
     * Returns the same hashcode for the given object as would be returned by the default method hashCode(), whether or not the given object's class overrides hashCode(). The hashcode for the null reference is zero.
     */
    public static int identityHashCode(java.lang.Object x){
        if(x == null) {
            return 0;
        }
        return x.hashCode(); 
    }

    public static String getenv(String name) {
        throw new UnsupportedOperationException();
    }
    
    public static void setOut(PrintStream out) {
        //System.class.getDeclaredField("out").set(null, out);
    }
}
