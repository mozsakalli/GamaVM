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

import com.digitoygames.compiler.model.Method;
import com.digitoygames.compiler.model.Stack;
import com.digitoygames.compiler.model.StackValue;

/**
 *
 * @author mustafa
 */
public class Binary extends Op {
    
    public String operand;
    public int targetLocal = -1;
    
    @Override
    public void execute(Method method, Stack stack) {
        StackValue tmp = targetLocal == -1 ? method.allocTemp(type) : method.getLocal(targetLocal, type);
        StackValue v2 = stack.pop();
        StackValue v1 = stack.pop();
        if(operand.equals(">>>")) {
            code = tmp.value+" = ((";
            if(type.equals("J")) code += "JULONG"; else code += "JUINT";
            code += ")"+v1.value+") >> "+v2.value;
        }
        else
        code = tmp.value+" = "+v1.value+" "+operand+" "+v2.value;
        if(targetLocal == -1) stack.push(tmp);
    }
    
    
}
