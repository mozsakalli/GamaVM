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
import com.digitoygames.compiler.model.Method;
import com.digitoygames.compiler.model.Stack;
import com.digitoygames.compiler.model.StackValue;

/**
 *
 * @author mustafa
 */
public class StoreArray extends Op {

    @Override
    public void execute(Method method, Stack stack) {
        StackValue val = stack.pop();
        StackValue index = stack.pop();
        StackValue array = stack.pop();

        code = String.format("((%s*)((Array*)%s)->data)[%s]=%s", Util.getPlatformType(type),array.value,index.value,val.value);
    }
}
