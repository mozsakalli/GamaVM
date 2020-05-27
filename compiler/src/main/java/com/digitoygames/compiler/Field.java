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
public class Field extends Ref {
    
    public boolean isStatic;
    public boolean set;

    @Override
    public void execute(Method meth, Stack stack) {
        if(set) {
            Stack.StackElement val = stack.pop();
            String f = (isStatic ? cls+"::" : stack.pop().value+".") + name;
            code = f+"="+val.value;
        } else {
            String t = type;
            Stack.StackElement tmp = stack.getTemp(meth, type);
            String f = (isStatic ? cls+"::" : stack.pop().value+".") + name;
            code = tmp.value+"="+f;
            stack.push(tmp);
        }
    }
    
    
}
