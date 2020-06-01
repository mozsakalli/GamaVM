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

package com.cava.debugger.handler.referencetype;

import com.cava.debugger.OutBuffer;
import com.cava.debugger.Packet;

/**
 *
 * @author ozsak
 */
public class RefTypeMethodsWithGenericHandler extends RefTypeMethodsHandler {

    @Override
    public int handle(Packet packet, OutBuffer out) {
        return super.handle(packet, out); 
    }

    @Override
    public String getGenericSignature() {
        return "";
    }
    
    
    @Override
    public int getCommand() {
        return 15;
    }    
}
