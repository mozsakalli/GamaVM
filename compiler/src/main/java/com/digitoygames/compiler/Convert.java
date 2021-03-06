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
public class Convert extends Op {
    
    public String source;

    @Override
    public void execute(Method meth, Stack stack) {
        Stack.StackElement tmp = stack.getTemp(meth, type);
        Stack.StackElement src = stack.pop();
        code = tmp.value+" = /*"+type+"*/"+src.value;
        stack.push(tmp);
    }

    @Override
    public void generate(SourceWriter out) {
        out.println("ST[SP-1].%s = ST[SP-1].%s;", type, source);
    }
    
    
}
