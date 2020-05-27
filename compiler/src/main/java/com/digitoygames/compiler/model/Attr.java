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

package com.digitoygames.compiler.model;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;

/**
 *
 * @author mustafa
 */
public class Attr {
    
    public Clazz declaringClass;
    
    public int nameIndex;
    public byte[] data;
    
    public DataInputStream getStream() {
        return new DataInputStream(new ByteArrayInputStream(data));
    }
    
    public String getName() {
        return declaringClass.cp.getFieldName(nameIndex);
    }
    
    public void dump(DataOutputStream out) throws Exception {
        out.writeShort(nameIndex);
        if(getName().equals("Code")) {
            byte[] code = getAOTCode();
            out.writeInt(code.length);
            out.write(code);
        } else {
            out.writeInt(data.length);
            out.write(data);
        }
    }
    
    byte[] getAOTCode() throws Exception {
        ByteArrayOutputStream bytes = new ByteArrayOutputStream();
        DataOutputStream out = new DataOutputStream(bytes);
        DataInputStream in = getStream();
        out.writeShort(in.readShort()); //maxstack
        out.writeShort(in.readShort()); //maxlocals
        int size = in.readInt();
        //in.skipBytes(size);
        while(size-- > 0) in.read();
        out.writeInt(0);
        while(in.available() > 0) out.write(in.read());
        return bytes.toByteArray();
    }
}
