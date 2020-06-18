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
package com.digitoygames.compiler.model.op;

import com.digitoygames.compiler.model.CP;
import com.digitoygames.compiler.model.Method;
import com.digitoygames.compiler.model.Compiler;

/**
 *
 * @author mustafa
 */
public class Field extends Op {

    public int index;
    public CP cp;
    public boolean isStatic;
    public Compiler compiler;
    public boolean resolved;
    
    public String ref(Method method) {
        return "f" + method.declaringClass.aotHash + "_" + index;
    }

    void generate(Method method) {
        Object clsName = cp.items[cp.items[cp.items[index].index1].index1].value;
        Object name = cp.items[cp.items[cp.items[index].index2].index1].value;
        Object signature = cp.items[cp.items[cp.items[index].index2].index2].value;
        String comment = clsName+":"+name+":"+signature;
        clsName = compiler.getStringIndex(clsName.toString());
        name = compiler.getStringIndex(name.toString());
        signature = compiler.getStringIndex(signature.toString());
        if(!resolved) {
            String ref = ref(method);
            code = String.format("AOTFIELD(%s,%d,%d,%d); //%s\n", ref, clsName, name, signature,comment);
            resolved = true;
        } else {
            code = String.format("//%s\n", comment);
        }
    }

    @Override
    public boolean equals(Object o) {
        if(o == null || !(o instanceof Field)) return false;
        if(o == this) return true;
        Field f = (Field)o;
        return f.cp == cp && f.index == index;
    }

    
}
