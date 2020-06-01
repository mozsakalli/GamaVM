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

package gamavm.jdwp;

import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author mustafa
 */
public class JdwpClient {
    
    byte[] inBuffer = new byte[1024];
    int inLength;
    int socket;
    boolean handsShaken;
    int payload;
    List<JdwpPacket> outPackets = new ArrayList();
    JdwpPacket inPacket = new JdwpPacket();
    boolean pending4;
    
    public JdwpClient(int socket) {
        this.socket = socket;
        payload = 14;
    }
    
    public boolean isConnected() {
        return socket>0;
    }
    
    boolean readSome(int length) {
        int readed = Jdwp.socketRead(socket, inBuffer, inLength, length);
        if(readed < 0) {
            socket = 0;
            return false;
        }
        inLength += readed;
        return true;
    }
    
    public JdwpPacket readPacket() {
        if(!readSome(payload - inLength)) return null;
        if(inLength != payload) return null;
        if(!handsShaken) {
            JdwpPacket hp = new JdwpPacket();
            hp.setBytes(inBuffer, 0, 14);
            outPackets.add(hp);
            handsShaken = true;
            
            //send vm start
            Jdwp.onVMStart();
            
            inLength = 0;
            payload = 4;
            pending4 = true;
            if(!readSome(4)) return null;
            if(inLength != payload) return null;
        }
        
        if(pending4) {
            payload = ((inBuffer[0]&0xff)<<24)|((inBuffer[1]&0xff)<<16)|((inBuffer[2]&0xff)<<8)|((inBuffer[3]&0xff));  
            inLength = 0;
            pending4 = false;
            if(!readSome(payload - inLength)) return null;
        }
        
        if(payload == inLength) {
            inPacket.start(inBuffer, 0);
            pending4 = true;
            payload = 4;
            return inPacket;
        }
        
        return null;
    }
    
    public void flush() {
        while(!outPackets.isEmpty()) {
            JdwpPacket p = outPackets.get(0);
            if(p.sentPtr >= p.ptr) {
                outPackets.remove(0);
                continue;
            }
            int written = Jdwp.socketWrite(socket, p.buffer, p.sentPtr, p.ptr - p.sentPtr);
            if(written < 0) {
                socket = 0;
                return;
            }
            p.sentPtr += written;
            if(p.sentPtr >= p.ptr) outPackets.remove(0);
        }
    }
}
