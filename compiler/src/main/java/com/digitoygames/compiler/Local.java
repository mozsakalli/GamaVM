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
public class Local extends Op {
    
    public int index;
    public boolean set;
    public Integer delta;
    public boolean isCaught;
    
    @Override
    public void execute(Method meth, Stack stack) {
        Method.LocalInfo local = meth.getLocal(index, type);
        if(delta != null) {
            code = "/*"+local.debugName+"*/"+local.name + (delta < 0 ? "-" : "+") + "=" + Math.abs(delta);
        } else if(set) {
            code = "/*"+local.debugName+"*/"+local.name+" = "+(isCaught ? "__caught" : stack.pop().value);
        } else {
            stack.push("/*"+local.debugName+"*/"+local.name, local.type);
        }
    }

    
    @Override
    public int getStackDelta() {
        return delta != null ? 0 : (set ? -1 : 1);
    }

    
    @Override
    public String toString() {
        String str = "local "+index+" ";
        if(set) str += "set "; else str += "get ";
        if(delta != null) str += " "+delta;
        return str+" @"+type;
    }

    @Override
    public void generate(SourceWriter out) {
        if(delta != null) {
            out.println("LOC[%d].%s %s= %d;",index,type,(delta < 0 ? "-" : "+"),Math.abs(delta));
        } else if(set) {
            out.println("LOC[%d].%s = ST[--SP].%s;", index,type,type);
        } else {
            out.println("ST[SP++].%s = LOC[%d].%s;", type,index,type);
        }
    }

    
}
