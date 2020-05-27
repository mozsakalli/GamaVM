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

package com.digitoygames.compiler.model;

import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author mustafa
 */
public class Stack {

    List<StackValue> stack = new ArrayList();

    public int size() {
        return stack.size();
    }

    public void push(StackValue value) {
        value.live = true;
        stack.add(value);
    }

    public StackValue pop() {
        if(stack.isEmpty())
            System.out.println("...");
        StackValue v = stack.remove(stack.size() - 1);
        v.live = false;
        return v;
    }

    public StackValue peek(int offset) {
        return stack.get(stack.size() - 1 - offset);
    }

    public int getSpillCount() {
        int count = 0;
        for(int i=0; i<stack.size(); i++) {
            if(stack.get(i).spillIndex != -1) count++;
        }
        return count;
    }
}
