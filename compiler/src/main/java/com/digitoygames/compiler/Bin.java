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

package com.digitoygames.compiler;

/**
 *
 * @author mustafa
 */
public class Bin extends Op {
    
    public String operand;

    @Override
    public void execute(Method meth, Stack stack) {
        Stack.StackElement e = stack.getTemp(meth, type);
        if(operand.equals(">>>")) {
            code = e.value+" = ((unsigned ";
            if(type.equals("J")) code += "JLONG"; else code += "JINT";
            code += ")"+stack.get(stack.size() - 2).value+") >> "+operand+stack.get(stack.size()-1).value;
        }
        else
        code = e.value + " = "+stack.get(stack.size() - 2).value+operand+stack.get(stack.size()-1).value;
        
        stack.pop();
        stack.pop();
        stack.push(e);
    }

    
    @Override
    public int getStackDelta() {
        return -1;
    }

    
    @Override
    public String toString() {
        return "bin "+operand;
    }

    @Override
    public void generate(SourceWriter out) {
        out.println("ST[SP-2].%s = ST[SP-2].%s %s ST[SP-1].%s; SP--;", type, type, operand, type);
    }
    
    
}
