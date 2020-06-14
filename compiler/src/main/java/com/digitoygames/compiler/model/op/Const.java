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
import com.digitoygames.compiler.model.Stack;
import com.digitoygames.compiler.model.StackValue;
import com.digitoygames.compiler.model.Compiler;

/**
 *
 * @author mustafa
 */
public class Const extends Op {
    
    public Object value;
    public boolean classConst;
    public boolean stringConst;
    public Compiler compiler;
    
    @Override
    public void execute(Method method, Stack stack) {
        StackValue v = new StackValue();
        v.type = type;
        if(stringConst) {
            v.value = //String.format("CLS(method->declaringClass,cp)[%d].value.O", value);
                    "aot_strings["+compiler.getStringIndex(value.toString())+"]";
        } else if(classConst) {
            CP cp = method.declaringClass.cp;
            String clsName = cp.items[cp.items[(Integer)value].index1].value.toString();
            int index = compiler.getStringIndex(clsName);
            String ref = "c" + method.declaringClass.aotHash + "_" + value;
            code = String.format("AOTCLASS(%s,%d);", ref, value);
            v.value = ref;
                    //String.format("resolve_class(vm,STRCHARS(aot_strings[%d]),STRLEN(aot_strings[%d]),1,NULL)", index,index);
        }
        else v.value = value == null ? "NULL" : String.valueOf(value);
        if(!type.equals("O")) {
            switch(v.value) {
                case "Infinity": v.value = "INFINITY";break;
                case "-Infinity": v.value = "-INFINITY";break;
                case "NaN": v.value = "NAN";break;
            }
        }
        stack.push(v);
    }
    
    
}
