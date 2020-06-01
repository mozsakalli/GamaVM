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

package com.cava.debugger;

import com.cava.debugger.handler.eventrequest.events.EventData;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author mustafa
 */
public class Debugger {
    
    static int payload = -1;
    static byte[] buffer;
    static int writePtr;
    static int readPtr;
    static int length;
    static boolean handsShaken;
    static Packet packet = new Packet();
    static OutBuffer outBuffer = new OutBuffer();
    
    final static List<EventData> outputQueue = new ArrayList();
    
    public static void resetState() {
        readPtr = writePtr = 0;
        outBuffer.ptr = length = 0;
        payload = 0;
        handsShaken = false;
        outputQueue.clear();
        VM.activeStepEventId = -1;
    }
    
    public static void receive(byte[] bytes, int offset, int len) {
        ensure(len);
        for(int i=0; i<len; i++) {
            buffer[writePtr++] = bytes[offset + i];
        }
        length += len;
    }

    public static OutBuffer process() {
        if(!handsShaken) {
            if(length < 14) return null;
            outBuffer.setBytes(buffer, 0, 14);
            payload = 14;
            packetReaded();
            handsShaken = true;
            return outBuffer;
        }
        
        if(payload == -1) {
            if(length < 4) return null;
            payload = ((buffer[readPtr]&0xff)<<24)|((buffer[readPtr+1]&0xff)<<16)|((buffer[readPtr+2]&0xff)<<8)|((buffer[readPtr+3]&0xff));  
        }

        //packet not completly received yet!
        if(length < payload) return null;
        packet.start(buffer, readPtr);
        
        //System.out.println(packet);
        
        JdwpHandler handler = JdwpHandlers.get(packet);
        if(handler != null) {
            //System.out.println("handler: "+handler+" cmdset="+handler.getCommandSet()+" cmd="+handler.getCommand());
            outBuffer.reset();
            int errorCode = handler.handle(packet, outBuffer);
            outBuffer.complete(packet.id, errorCode);
            packetReaded();
            return outBuffer;
        } 
        System.err.println("Unknown handler "+Integer.toHexString(packet.getKey())+" cs="+packet.commandSet+" c="+packet.command);
        packetReaded();
        return null;
    }
    
    private static void packetReaded() {
        readPtr += payload;
        length -= payload;
        payload = -1;
        if(length == 0) {
            readPtr = writePtr = 0;
        }
    }
    static void ensure(int required) {
        if(buffer == null || writePtr+required > buffer.length) {
            byte[] tmp = new byte[buffer != null ? Math.max(buffer.length*2, writePtr+required) : required*2];
            for(int i=0; i<writePtr; i++) tmp[i] = buffer[i];
            buffer = tmp;
        }
    }
    
    public static void write(byte[] bytes, int offset, int len) throws Exception {
        if(socketOut!=null)
        synchronized(socketOut) {
            socketOut.write(bytes, offset, len);
        }
    }
    
    public static void sendEventData(EventData data) {
        synchronized(outputQueue) {
            outputQueue.add(data);
        }
    }
    static int clientSocket;
    static byte[] clientBuffer = new byte[1024*16];
    
    public static void start(final String host, final int port) throws Exception {
        if(host == null || host.isEmpty()) throw new Exception("Debugger host parameter missing");
        clientSocket = DebuggerSocket.connect(host, port);
        if(clientSocket == 0) throw new Exception("Can't connect to jdwp server "+host+":"+port);
        /*
        loopThread = new Thread(new Runnable(){
            @Override
            public void run() {
                try {
                    debuggerLoop(host, port);
                }catch(Exception e){
                    e.printStackTrace();
                }
            }
        }, "Debugger Thread");
        loopThread.start();
        */
    }
    
    static boolean startSent;
    static OutBuffer outBuffer2 = new OutBuffer();
    public static void tick() throws Exception {
        //process incoming packets
        int readed = DebuggerSocket.read(clientSocket, clientBuffer, 0, clientBuffer.length);
        if(readed < 0) {
            DebuggerSocket.close(clientSocket);
            clientSocket = 0;
            System.out.println("jdwp disconnected");
            return;
        }
        if(readed > 0) {
            receive(clientBuffer, 0, readed);
            OutBuffer output = process();
            while(output != null) {
                write(output.getBuffer(), 0, output.getSize());
                output = process();
            }

            if(!startSent && handsShaken) {
                Debugger.sendEventData(new EventData(JdwpConsts.EventKind.VM_START, null, 0));
                startSent = true;
            }
        } 
        
        
        while(!outputQueue.isEmpty()) {
            EventData data = null;
            synchronized(outputQueue) {
                data = outputQueue.remove(0);
            }
            if(data != null) {
                outBuffer2.reset();
                outBuffer2.writeByte(JdwpConsts.SuspendPolicy.ALL);
                outBuffer2.writeInt(1); //event count
                data.dump(outBuffer2);
                outBuffer2.completeEvent();
                write(outBuffer2.getBuffer(), 0, outBuffer2.getSize());
            }
        }        
    }
    /*
    public static boolean isDebuggerThread(Thread thread) {
        return thread == loopThread || thread == processThread;
    }
    */
    
    static boolean debugSessionActive;
    
    static void debuggerLoop(String host, int port) throws Exception {
        /*
        System.out.println("Waiting debugger to connect "+host+":"+port);
        final Socket s = new Socket(host, 10000);
        
        byte[] bytes = new byte[1024*16];
        Debugger debugger = new Debugger();
        InputStream in = s.getInputStream();
        socketOut = s.getOutputStream();
        resetState();
        debugSessionActive = true;
        
        processThread = new Thread(new Runnable(){
            @Override
            public void run() {
                debuggerProcessLoop();
            }
        }, "Debugger Process Thread");
        processThread.start();
        
        try {
            boolean startSent = false;
            while(true) {
                int readed = in.read(bytes);
                if(readed > 0) {
                    debugger.receive(bytes, 0, readed);
                    OutBuffer output = debugger.process();
                    while(output != null) {
                        write(output.getBuffer(), 0, output.getSize());
                        output = debugger.process();
                    }
                    
                    if(!startSent && handsShaken) {
                        Debugger.sendEventData(new EventData(JdwpConsts.EventKind.VM_START, null, 0));
                        startSent = true;
                    }
                }   
            }    
        } catch(Exception e){
            s.close();
            e.printStackTrace();
            System.out.println("Debug client disconnected");
        }
        debugSessionActive = false;
        //}
        */
    }
    
    static void debuggerProcessLoop() {
        OutBuffer buffer = new OutBuffer();
        while(debugSessionActive) {
            while(outputQueue.isEmpty()) try{Thread.sleep(10); }catch(Exception e){}
            while(!outputQueue.isEmpty()) {
                EventData data = null;
                synchronized(outputQueue) {
                    data = outputQueue.remove(0);
                }
                if(data != null) {
                    buffer.reset();
                    buffer.writeByte(JdwpConsts.SuspendPolicy.ALL);
                    buffer.writeInt(1); //event count
                    data.dump(buffer);
                    buffer.completeEvent();
                    try {
                        write(buffer.getBuffer(), 0, buffer.getSize());
                    }catch(Exception e) {
                        System.out.println("process thread exited");
                        break;
                    }
                }
            }
        }
    }
    
}
