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

import com.digitoygames.compiler.Util;

import java.lang.reflect.Modifier;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

/**
 *
 * @author mustafa
 */
public class Method extends Field {
    
    Code code;
    
    public Code getCode() throws Exception {
        if(code != null) return code;
        Attr a = getAttr("Code");
        if(a == null) return null;
        code = new Code(declaringClass, a.getStream());
        return code;
    }
    
    public String getAOTName() {
        return Util.esc(declaringClass.getName()+"_"+getName()+"_"+getSignature());
    }
    
    public boolean isStatic() {
        return (accessFlags & 0x0008) > 0;
    }
    public boolean isAbstract()  { return (accessFlags & 0x0400) > 0; }
    public boolean isNative() { return (accessFlags & 0x00000100) > 0; }

    List<StackValue> allTemps = new ArrayList();
    public StackValue allocTemp(String type) {
        if(type.equals("B") || type.equals("Z") || type.equals("C") || type.equals("S"))
            type = "I";
        for(StackValue v : allTemps)
            if(!v.live && v.type.equals(type))
                return v;
        
        StackValue v = new StackValue();
        v.value = "T"+allTemps.size();
        v.type = type;
        allTemps.add(v);
        return v;
    }
    
    List<StackValue> allLocals = new ArrayList();
    public StackValue findLocal(int index, String type) {
        if(type.equals("B") || type.equals("Z") || type.equals("C") || type.equals("S"))
            type = "I";
        for(StackValue v : allLocals)
            if(v.localIndex == index && v.type.equals(type))
                return v;
        return null;
    }
    
    public StackValue getLocal(int index, String type) {
        if(type.equals("B") || type.equals("Z") || type.equals("C") || type.equals("S"))
            type = "I";
        for(StackValue v : allLocals)
            if(v.localIndex == index && v.type.equals(type))
                return v;

        StackValue v = new StackValue();
        v.value = "L"+allLocals.size();
        v.type = type;
        v.localIndex = index;
        allLocals.add(v);
        return v;        
    }
    
    List<StackValue> allSpills = new ArrayList();
    public StackValue allocSpill(int index, String type) {
        if(type.equals("B") || type.equals("Z") || type.equals("C") || type.equals("S"))
            type = "I";
        for(StackValue v : allSpills)
            if(v.spillIndex == index && v.type.equals(type)) return v;

        StackValue v = new StackValue();
        v.value = "S"+index+type;
        v.spillIndex = index;
        v.type = type;
        allSpills.add(v);
        return v;
    }
}
