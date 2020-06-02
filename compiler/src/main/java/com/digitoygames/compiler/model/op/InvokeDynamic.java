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

/**
 *
 * @author mustafa
 */
public class InvokeDynamic extends Op {
    
    public int index;
    public CP cp;

    @Override
    public void execute(Method method, Stack stack) {
        //BootstrapM method.declaringClass.getBootstrapMethods()[cp.items[index].index1];
        //super.execute(method, stack); //To change body of generated methods, choose Tools | Templates.
    }
    
    
}
