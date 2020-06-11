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
        
        code = "// "+cp.getRefClassName(index)+":"+cp.getRefName(index)+":"+cp.getRefSignature(index)+"\n";
        code +="{\n";
        code += "VAR cargs[]={";// call_java_"+ret+"("; 
        for(int i=0; i<argCount; i++) {
            if(i > 0) code += ",";
            code += "{."+args[i].type+"="+args[i].value+"}";
        }
        code += "}\n"+
             "frame->pc="+pc+"\n";                
        
        if(callType == SPECIAL || callType == STATIC) {
            code += String.format(
                    "if(!call%d){\n"+
                    "   call%d=resolve_method_by_index(vm,method->declaringClass,%d);\n"+
                    "}\n"        
                    ,index,index,index);
            code += String.format("((VM_CALL)(MTH(call%d,entry)))(vm,call%d,&cargs[0])\n",index,index);
        } else {
            code += String.format(
                    "if(call%d == -1){\n"+
                    "   Object *m = resolve_method_by_index(vm,method->declaringClass,%d);\n"+
                    "   call%d = MTH(m,%s);\n"+        
                    "}\n"        
                    ,index,index, index, callType == INTERFACE ? "iTableIndex" : "vTableIndex");
            code += String.format(
                    "if(!cargs[0].O) { throw_null(vm); }\n"+
                    "Class *cls = cargs[0].O->cls->instance;\n"+
                    "Object *mth = cls->%s[call%d];\n"+
                    "((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);\n"        
                    ,callType == INTERFACE ? "itable" : "vtable", index
            );
        }
        /*
        code = "// "+cp.getRefClassName(index)+":"+cp.getRefName(index)+":"+cp.getRefSignature(index)+"\n"+
               "if(!"+iname+") {\n"+
               "  "+iname+"=resolve_method_by_index(vm,method->declaringClass,"+index+")\n"+ 
               //"  if(!"+iname+") ;//todo: throw\n"+
               "}\n"+
               "VAR args"+pc+"[]={";// call_java_"+ret+"("; 
        //code = clsName+":"+name+":"+signature+"(";
        for(int i=0; i<argCount; i++) {
            if(i > 0) code += ",";
            code += "{."+args[i].type+"="+args[i].value+"}";
            //code += args[i].value;
        }
        code += "}\n"+
                "frame->pc="+pc+"\n";
        
        if(callType == SPECIAL || callType == STATIC)
            code += String.format("((VM_CALL)(MTH(%s,entry)))(vm,%s,&args%d[0])\n",iname,iname,pc);
        else if(callType == INTERFACE) {
            
        } else {
            
        }
        */
        if(!ret.equals("V")) {
            StackValue tmp = method.allocTemp(ret);
            code += String.format("%s=frame->ret.%s;\n",tmp.value,ret);
            stack.push(tmp);
        }
        code += "}\n";
    }
    
    
}
