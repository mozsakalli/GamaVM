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
public class ThreadFrameCountHandler extends ThreadHandler {

    @Override
    public int handle(Packet packet, OutBuffer out) {
        long threadId = packet.readLong();
        try {
            int suspendCount = 0;//NativeCode.Int("((JvmThread*)%s)->suspendCount", threadId);
            if(suspendCount == 0)
                return JdwpConsts.Error.THREAD_NOT_SUSPENDED;
            
            int frameCount = 0;//NativeCode.Int("((JvmThread*)%s)->framePtr", threadId);
            out.writeInt(frameCount);
            return JdwpConsts.Error.NONE;
        } catch(Exception e){
            
        }
        return JdwpConsts.Error.INVALID_THREAD;
    }

    @Override
    public int getCommand() {
        return 7;
    }
    
}
