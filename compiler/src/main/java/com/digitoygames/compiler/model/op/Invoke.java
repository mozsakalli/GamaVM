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

import com.digitoygames.compiler.Util;
import com.digitoygames.compiler.model.CP;
import com.digitoygames.compiler.model.Method;
import com.digitoygames.compiler.model.Stack;
import com.digitoygames.compiler.model.StackValue;
import com.digitoygames.compiler.model.Compiler;

/**
 *
 * @author mustafa
 */
public class Invoke extends Op {

    public final static int VIRTUAL = 0;
    public final static int SPECIAL = 1;
    public final static int STATIC  = 2;
    public final static int INTERFACE = 3;
    
    public int index;
    public int callType;
    CP cp;
    Compiler compiler;
    public boolean resolved;
    
    public String ref(Method method) {
        return "m" + method.declaringClass.aotHash + "_" + index;
    }
    /*
    void generate(Method method) {
        Object clsName = cp.items[cp.items[cp.items[index].index1].index1].value;
        Object name = cp.items[cp.items[cp.items[index].index2].index1].value;
        Object signature = cp.items[cp.items[cp.items[index].index2].index2].value;
        
        clsName = compiler.getStringIndex(clsName.toString());
        name = compiler.getStringIndex(name.toString());
        signature = compiler.getStringIndex(signature.toString());
        
        String ref = ref(method);
        code = String.format("if(!%s) {\n" +
                "Object *fld = resolve_field(vm, STRCHARS(aot_strings[%d]),STRLEN(aot_strings[%d]), "+
                "STRCHARS(aot_strings[%d]),STRLEN(aot_strings[%d]),"+
                "STRCHARS(aot_strings[%d]),STRLEN(aot_strings[%d]));\n" +
                "%s = fld->instance;\n}"
                , ref, clsName, clsName, name, name, signature, signature,ref);
    }
    */
    int getClsIndex() {
        Object n = cp.items[cp.items[cp.items[index].index1].index1].value;
        return compiler.getStringIndex(n.toString());
    }
    int getNameIndex() {
        Object n = cp.items[cp.items[cp.items[index].index2].index1].value;
        return compiler.getStringIndex(n.toString());
    }
    int getSignatureIndex() {
        Object n = cp.items[cp.items[cp.items[index].index2].index2].value;
        return compiler.getStringIndex(n.toString());
    }
    
    @Override
    public void execute(Method method, Stack stack) {
        String clsName = cp.getRefClassName(index);
        String name = cp.getRefName(index);
        String signature = cp.getRefSignature(index);
        int argCount = Util.countArguments(signature);
        if(callType != STATIC) argCount++;
        StackValue[] args = new StackValue[argCount];
        for(int i=0; i<argCount; i++)
            args[argCount - 1 - i] = stack.pop();
        String ret = Util.getReturnType(signature);
        
        String ref = ref(method);
        
        code ="{\n";
        if(argCount > 0) {
        code += "  VAR cargs[]={";// call_java_"+ret+"("; 
        for(int i=0; i<argCount; i++) {
            if(i > 0) code += ",";
            code += "{."+args[i].type+"="+args[i].value+"}";
        }
        code += "};\n";
        }
        code += "  frame->pc="+pc+"\n";                
        if(callType == SPECIAL || callType == STATIC) {
            if(!resolved) {
                code += String.format("  AOTMETHOD(%s,%d,%d,%d); //%s:%s:%s\n",ref,getClsIndex(), getNameIndex(), getSignatureIndex(),
                        clsName,name,signature);
            }
            code += String.format("  ((VM_CALL)(MTH(((Object*)%s),entry)))(vm,%s,%s)\n",ref,ref,argCount>0 ? "&cargs[0]" : "NULL");
        } else {
            if(!resolved) {
            code += String.format("  AOTVMETHOD(%s,%d,%d,%d,%s); //%s:%s:%s\n",ref,getClsIndex(), getNameIndex(), getSignatureIndex(),
                    callType == INTERFACE ? "iTableIndex" : "vTableIndex",clsName,name,signature);
            }
            code += String.format(
                    "  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }\n"+
                    "  Class *cls = cargs[0].O->cls->instance;\n"+
                    "  Object *mth = cls->%s[%s];\n"+
                    "  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);\n"        
                    ,callType == INTERFACE ? "itable" : "vtable", ref
            );
        }
        code += String.format("  if(vm->exception) goto __EXCEPTION;\n");
        if(!ret.equals("V")) {
            StackValue tmp = method.allocTemp(ret);
            code += String.format("  %s=frame->ret.%s;\n",tmp.value,ret);
            stack.push(tmp);
        }
        code += "}\n";
    }
    
    
}
