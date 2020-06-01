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

package com.cava.debugger.handler.thread;

import com.cava.debugger.JdwpConsts;
import com.cava.debugger.OutBuffer;
import com.cava.debugger.Packet;

/**
 *
 * @author mustafa
 */
public class ThreadSuspendCountHandler extends ThreadHandler {

    @Override
    public int handle(Packet packet, OutBuffer out) {
        try {
            long threadId = packet.readLong();
            int suspendCount =0;// NativeCode.Int("((JvmThread*)%s)->suspendCount", threadId);
            System.out.println("Thread suspend count="+suspendCount);
            if(suspendCount == 0)
                 return JdwpConsts.Error.THREAD_NOT_SUSPENDED;
            
            out.writeInt(suspendCount);
            return JdwpConsts.Error.NONE;
        }catch(Exception e){
            e.printStackTrace();
        }
        return JdwpConsts.Error.INVALID_THREAD;
    }

    @Override
    public int getCommand() {
        return 12;
    }
    
}
