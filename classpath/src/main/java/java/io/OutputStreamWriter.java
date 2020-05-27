/*
 * Copyright (c) 2012, Codename One and/or its affiliates. All rights reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 only, as
 * published by the Free Software Foundation.  Codename One designates this
 * particular file as subject to the "Classpath" exception as provided
 * by Oracle in the LICENSE file that accompanied this code.
 *  
 * This code is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * version 2 for more details (a copy is included in the LICENSE file that
 * accompanied this code).
 * 
 * You should have received a copy of the GNU General Public License version
 * 2 along with this work; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 * 
 * Please contact Codename One through http://www.codenameone.com/ if you 
 * need additional information or have any questions.
 */

package java.io;
/**
 * An OutputStreamWriter is a bridge from character streams to byte streams: Characters written to it are translated into bytes. The encoding that it uses may be specified by name, or the platform's default encoding may be accepted.
 * Each invocation of a write() method causes the encoding converter to be invoked on the given character(s). The resulting bytes are accumulated in a buffer before being written to the underlying output stream. The size of this buffer may be specified, but by default it is large enough for most purposes. Note that the characters passed to the write() methods are not buffered.
 * Since: CLDC 1.0 See Also:Writer, UnsupportedEncodingException
 */
public class OutputStreamWriter extends java.io.Writer {
    private OutputStream os;
    private String enc;
    
    /**
     * Create an OutputStreamWriter that uses the default character encoding.
     * os - An OutputStream
     */
    public OutputStreamWriter(java.io.OutputStream os){
         this.os = os;
         enc = "UTF-8";
    }

    /**
     * Create an OutputStreamWriter that uses the named character encoding.
     * os - An OutputStreamenc - The name of a supported
     * - If the named encoding is not supported
     */
    public OutputStreamWriter(java.io.OutputStream os, java.lang.String enc) throws java.io.UnsupportedEncodingException{
         this.os = os;
         this.enc = enc;
    }

    /**
     * Close the stream.
     */
    public void close() throws java.io.IOException{
        os.close();
    }

    /**
     * Flush the stream.
     */
    public void flush() throws java.io.IOException{
        os.flush();
    }

    /**
     * Write a portion of an array of characters.
     */
    public void write(char[] cbuf, int off, int len) throws java.io.IOException{
        write(new String(cbuf, off, len));
    }

    /**
     * Write a single character.
     */
    public void write(int c) throws java.io.IOException{
        write(new String(new char[] {(char)c}));
    }

    /**
     * Write a portion of a string.
     */
    public void write(java.lang.String str, int off, int len) throws java.io.IOException{
        if(off > 0 || len != str.length()) {
            str = str.substring(off, len);
        }
        os.write(str.getBytes(enc));
    }
    
    public void write(CharSequence csq) throws IOException {
        write(csq.toString());
    }

   

}
