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

import java.util.ArrayList;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.Set;

/**
 *
 * @author mustafa
 */
public class Stack {
    
    public static class StackElement {
        public String value;
        public String type;
        public boolean isTemp;
        public int spillIndex = -1;
    }
    
    List<StackElement> stack = new ArrayList();
    public Set<StackElement> availableTemps = new HashSet();
    public List<StackElement> spills = new ArrayList();
    
    public int size() { return stack.size(); }
    public StackElement get(int index) { return stack.get(index); }
    public boolean isEmpty() { return stack.isEmpty(); }
    
    public StackElement pop() {
        if(stack.isEmpty()) {
            System.out.println("...");
        }
        StackElement ret = stack.remove(stack.size()-1);
        if(ret.isTemp) availableTemps.add(ret);
        return ret;
    }
    
    public void push(StackElement e) {
        stack.add(e);
    }
    public void push(String value, String type) {
        StackElement e = new StackElement();
        e.value = value;
        e.type = type;
        stack.add(e);
    }

    public StackElement peek(int size) {
        return stack.get(stack.size() - 1 - size);
    }
    
    public StackElement getTemp(Method method, String type) {
        if(!availableTemps.isEmpty()) {
            Iterator<StackElement> it = availableTemps.iterator();
            while(it.hasNext()) {
                StackElement e = it.next();
                if(Util.typeSameStack(e.type, type)) {
                    it.remove();
                    return e;
                }
            }
        }
        
        return method.getTemp(type);
    }
    
    public StackElement getSpill(int index, String type) {
        for(StackElement s : spills) {
            if(s.spillIndex == index && Util.typeSameStack(s.type, type)) return s;
        }
        StackElement s = new StackElement();
        s.spillIndex = index;
        s.type = type;
        s.value = "s"+Util.typeToStack(type)+index;
        spills.add(s);
        return s;
    }
    
}
