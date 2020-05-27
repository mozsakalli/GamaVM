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

import java.util.HashSet;

/**
 *
 * @author mustafa
 */
public class Compiler2 {
    
    Method method;
    
    public Compiler2(Method method) {
        this.method = method;
        compile();
    }

    
    void compile() {
        HashSet<Integer> jumpTargets = new HashSet();
        for(Op o : method.ops) {
            if(o instanceof Branch) {
                jumpTargets.add(((Branch)o).offset + o.pc);
            }
        }
        SourceWriter out = new SourceWriter();
        out.print("%s %s(", Util.getPlatformType(method.returnType), method.getMangled());
        for(int i=0; i<method.args.size(); i++) {
            if(i>0) out.print(",");
            out.print("%s ARG%d",Util.getPlatformType(method.args.get(i)), i);
        }
        out.println(") {").indent();
        out.println("VAR LOC[%d];", method.maxLocals);
        for(int i=0; i<method.args.size(); i++) {
            out.println("LOC[%d].%s = ARG%d;", i, method.args.get(i), i);
        }
        out.println("VAR ST[%d];", method.maxStack).println("jint SP = 0;");
        
        for(Op o : method.ops) {
            out.startOp(o, jumpTargets.contains(o.pc));
            o.generate(out);
        }
        
        out.undent().println("}");
        System.out.println(out.toString());
    }
}
