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

package digiplay.net;

import java.io.IOException;
import java.io.InputStream;

/**
 *
 * @author mustafa
 */
public class Socket extends InputStream {
    long handle;
    int read, write, size;
    byte[] buffer;
    
    public native void connect(String host, int port);
    public native void disconnect();
    public native void write(byte[] data, int offset, int length);
    public void write(byte[] data) {
        write(data, 0, data.length);
    }

    private void append(byte[] bytes, int offset, int length) {
        if(buffer == null || buffer.length - size < length) {
            byte[] tmp = new byte[buffer == null ? 1024*32 : buffer.length + length];
            if(buffer != null)
                System.arraycopy(buffer, 0, tmp, 0, buffer.length);
            buffer = tmp;
        }
        int len = buffer.length - write;
        if(len > length) len = length;
        if(len > 0) {
            System.arraycopy(bytes, offset, buffer, write, len);
            offset += len;
            length -= len;
            write += len;
            if(write >= buffer.length) write = 0;
            size += len;
        }
        
        if(length > 0) {
            System.arraycopy(bytes, offset, buffer, write, length);
            write += length;
            if(write >= buffer.length) write = 0;
            size += length;
        }
    }
    
    @Override
    public void close() throws IOException {
        disconnect();
        read = write = size = 0;
    }

    @Override
    public int available() throws IOException {
        return size;
    }

    @Override
    public int read() throws IOException {
        if(size > 0) {
            int ret = buffer[read];
            read = (read+1) % buffer.length;
            size--;
            if(size == 0) read = write = 0;
            return ret;
        }
        return -1;
    }
}
