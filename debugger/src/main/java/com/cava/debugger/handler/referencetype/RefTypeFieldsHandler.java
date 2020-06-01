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

import com.cava.debugger.JdwpConsts;
import com.cava.debugger.JdwpUtil;
import com.cava.debugger.OutBuffer;
import com.cava.debugger.Packet;
import gamavm.VM;
import java.lang.reflect.Field;

/**
 *
 * @author mustafa
 */
public class RefTypeFieldsHandler extends RefTypeHandler {

    @Override
    public int handle(Packet packet, OutBuffer out) {
        long referenceTypeID = packet.readLong();
        try {
            Class cls = (Class)VM.getObject(referenceTypeID);
            Field[] fields = cls.getDeclaredFields();
            out.writeInt(fields.length);
            for (Field field : fields) {
                out.writeLong(VM.getAddress(field));
                out.writeString(field.getName());
                out.writeString(JdwpUtil.toSignature(field.getType()));
                String signatureWithGeneric = getGenericSignature();
                if (signatureWithGeneric != null)
                    out.writeString(signatureWithGeneric);
                out.writeInt(field.getModifiers());
            }
            
            return JdwpConsts.Error.NONE;
        }catch(Exception e){}
        
        return JdwpConsts.Error.INVALID_OBJECT;
    }

    @Override
    public int getCommand() {
        return 4;
    }
    
    String getGenericSignature() {
        return null;
    }
}
