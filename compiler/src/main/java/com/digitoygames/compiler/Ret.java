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
public class Ret extends Op {

    @Override
    public void execute(Method meth, Stack stack) {
        code = "return";
        if(!type.equals("V")) {
            code += " "+stack.pop().value;
        }
    }

    
    @Override
    public int getStackDelta() {
        return type.equals("V") ? 0 : -1;
    }

    
    @Override
    public String toString() {
        return "return "+type;
    }

    @Override
    public void generate(SourceWriter out) {
        out.print("return");
        if(!type.equals("V")) {
            out.print(" ST[--SP].%s", type);
        }
        out.println(";");
    }
    
    
}
