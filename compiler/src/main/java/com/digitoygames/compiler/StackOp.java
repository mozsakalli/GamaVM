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
public class StackOp extends Op {
    
    public int op;

    @Override
    public void execute(Method meth, Stack stack) {
        switch(op) {
            case 87: // pop
                stack.pop();
                break;
                
            //case 88: // pop2
            case 89: // dup: duplicate the value on top of the stack
                Stack.StackElement last = stack.peek(0);
                Stack.StackElement tmp = stack.getTemp(meth, last.type);
                code = tmp.value+"="+last.value;
                stack.push(tmp);
                break;
            //case 92: // dup2
            //case 90: // dup_x1
            //case 91: // dup_x2
            //case 93: // dup2_x1
            //case 94: // dup2_x2
            //case 95: // swap
            default:
                throw new RuntimeException("Unknown stack op "+op);
        }
    }
    
    
}
