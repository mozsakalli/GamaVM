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
public class If extends Branch {
    
    public String right;
    public String operand;

    @Override
    public void execute(Method meth, Stack stack) {
        if(right != null) {
            code = "if("+stack.pop().value+operand+right+")";
        } else {
            code = "if("+stack.get(stack.size()-2).value+operand+stack.get(stack.size()-1).value+")";
            stack.pop();
            stack.pop();
        }
        /*
        if(zero) {
            code = "if("+stack.pop().value+operand+"0)";
        } else {
            code = "if("+stack.get(stack.size()-2).value+operand+stack.get(stack.size()-1).value+")";
            stack.pop();
            stack.pop();
        }*/
        code +=  " goto BC"+(pc+offset)+";";// "{flow="+(pc+offset)+";break outer;}";
    }

    
    @Override
    public int getStackDelta() {
        return right == null ? -2 : -1;
    }

    
    @Override
    public String toString() {
        return "if "+operand+" go "+(pc+offset);
    }

    @Override
    public void generate(SourceWriter out) {
        /*
        if(zero) {
            out.print("if(ST[--SP].I %s 0) goto");
        } else {
            out.print("SP-=2;");
            out.print("if(ST[SP].%s %s ST[SP+1].%s) goto", type, operand, type);
        }
        out.println(" BC%d;", pc+offset);
        */
    }
 
    
}
