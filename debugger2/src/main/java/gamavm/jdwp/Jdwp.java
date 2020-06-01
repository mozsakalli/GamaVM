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

/**
 *
 * @author mustafa
 */
public class Jdwp {
    static JdwpClient client;
    
    public static void start(String host, int port) {
        int fd = socketConnect(host, port);
        if(fd <= 0) {
            System.out.println("Can't connect to JDWP server "+host+":"+port);
            return;
        }
        client = new JdwpClient(fd);
        System.out.println("Connected to JDWP server "+host+":"+port);
    }
    
    public static void tick() {
        if(client == null || client.socket <= 0) return;
        JdwpPacket req = client.readPacket();
        while(req != null) {
            int cmd = (req.commandSet << 8) + req.command;
            switch(cmd) {
                default:
                    System.out.println("Unknown command = 0x"+Integer.toHexString(cmd));
            }
            req = client.readPacket();
        }
        
        client.flush();
    }
    
    public static void onVMStart() {
        JdwpPacket req = new JdwpPacket();
        req.reset();
        req.writeByte(JdwpConsts.SuspendPolicy.ALL);
        req.writeInt(1); //event count
        //event data
        req.writeByte(JdwpConsts.EventKind.VM_START); //event kind
        req.writeInt(0); //req id
        req.writeLong(0); //thread id
        req.completeEvent();
        client.outPackets.add(req);
        
        /*
        jdwppacket_set_id(req, jdwp_eventset_commandid++);
        jdwppacket_set_cmd(req, JDWP_CMD_Event_Composite);
        jdwppacket_write_byte(req, JDWP_SUSPENDPOLICY_ALL);
        jdwppacket_write_int(req, 1);
        jdwppacket_write_byte(req, JDWP_EVENTKIND_VM_START);
        jdwppacket_write_int(req, 0);
        jdwppacket_write_refer(req, jthread);
        jdwp_event_packet_put(req);
        */
    }
    
    static native int socketConnect(String host, int port);
    static native int socketRead(int fd, byte[] bytes, int offset, int length);
    static native int socketWrite(int id, byte[] bytes, int offset, int length);
}
