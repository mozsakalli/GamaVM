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

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

/**
 *
 * @author mustafa
 */
public class Code extends Field {
    
    public int maxStack;
    public int maxLocals;
    LocalVar[] locals;
    byte[] bc;
    public TryCatchInfo[] tryCatchInfos;
    Set<Integer> tryCatchPC = new HashSet();

    public Code(Clazz cls, DataInputStream in) throws Exception {
        declaringClass = cls;
        maxStack = in.readUnsignedShort();
        maxLocals = in.readUnsignedShort();
        int size = in.readInt();
        bc = new byte[size];
        in.readFully(bc);
        
        int count = in.readUnsignedShort();
        tryCatchInfos = new TryCatchInfo[count];

        for(int i=0; i<count; i++) {
            TryCatchInfo tc = new TryCatchInfo();
            tc.start = in.readUnsignedShort(); //start
            tc.end = in.readUnsignedShort(); //end
            tc.handler = in.readUnsignedShort(); //handler
            tc.type = in.readUnsignedShort(); //type
            tryCatchInfos[i] = tc;
            tryCatchPC.add(tc.handler);
        }
        
        cls.readAttrs(attrs, in);
    }
    
    public LocalVar[] getLocals() throws Exception {
        if(locals != null) return locals;
        Attr a = getAttr("LocalVariableTable");
        DataInputStream in = a.getStream();
        int count = in.readUnsignedShort();
        List<LocalVar> vars = new ArrayList();
        for(int i=0; i<count; i++) {
            LocalVar v = new LocalVar();
            v.start = in.readUnsignedShort();
            v.length = in.readUnsignedShort();
            v.nameIndex = in.readUnsignedShort();
            v.signatureIndex = in.readUnsignedShort();
            v.index = in.readUnsignedShort();
            v.name = declaringClass.cp.getFieldName(v.nameIndex);
            v.signature = declaringClass.cp.getFieldName(v.signatureIndex);
            vars.add(v);
        }
        vars.sort((v1,v2) -> v1.index - v2.index);
        locals = new LocalVar[vars.size()];
        vars.toArray(locals);
        for(LocalVar v : vars) {
            System.out.println(v.index+" = "+v.name+":"+v.signature);
        }
        System.out.println("-------");
        return locals;
    }
    
    public CodeStream getCodeStream() {
        return new CodeStream(this);
    }

    public boolean isTryCatchHandler(int pc) {
        return tryCatchPC.contains(pc);
    }
}
