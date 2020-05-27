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

import de.inetsoftware.classparser.TryCatchFinally;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;

/**
 *
 * @author mustafa
 */
public class Compiler {
    
    public static class BasicBlock {
        public int id;
        public List<BasicBlock> next = new ArrayList();
        public BasicBlock parent;
        public List<Op> ops = new ArrayList();
        public Stack stack = new Stack();
        public List<Stack.StackElement> spills = new ArrayList();
        public String code;
    }
    
    Method method;
    
    public Compiler(Method method) {
        this.method = method;
        findBlocks();
    }

    void addLocalDef(Map<String,String> map, String type, String name) {
        String pt = Util.getPlatformType(type);
        String s = map.computeIfAbsent(pt, (q) -> "");
        if(s.length() > 0) s += ",";
        s += name;
        map.put(pt, s);
    }
    int spillIndex;
    void findBlocks() {
        Set<Integer> blockStart = new HashSet();
        for(int i=0; i<method.ops.size(); i++) {
            Op o = method.ops.get(i);
            if(o instanceof Goto) {
                blockStart.add(((Goto)o).offset + o.pc);
            } else if(o instanceof If) {
                blockStart.add(((If)o).offset + o.pc);
                blockStart.add(method.ops.get(i+1).pc);
            } else if(o instanceof Ret) {
                if(i < method.ops.size() - 1)
                    blockStart.add(method.ops.get(i+1).pc);
            } else if(o instanceof Switch) {
                Switch s = (Switch)o;
                for(int p : s.positions)
                    blockStart.add(p);
                blockStart.add(s.defaultPC);
            }
        }
        
        for(TryCatchFinally t : method.exceptionTable) {
            blockStart.add(t.getHandler());
        }
        
        List<BasicBlock> blocks = new ArrayList();
        BasicBlock bb = new BasicBlock();
        bb.id = 0;
        blocks.add(bb);
        
        for(Op o : method.ops) {
            if(blockStart.contains(o.pc)) {
                BasicBlock nb = new BasicBlock();
                nb.id = o.pc;
                nb.parent = bb;
                blocks.add(bb = nb);
            }
            bb.ops.add(o);
        }
        
        Map<String, Stack.StackElement> allSpills = new HashMap();
        
        for(BasicBlock b : blocks) {
            StringBuilder code = new StringBuilder();
            if(b.parent != null) {
                for(int i=b.parent.spills.size()-1; i>=0; i--)
                    b.stack.push(b.parent.spills.get(i));
            }
            
            for(Op o : b.ops) {
                o.execute(method, b.stack);
                if(o.code != null) {
                    code.append(o.code).append(";\n");
                }
            }
            
            int si = 0;
            while(!b.stack.isEmpty()) {
                Stack.StackElement e = b.stack.pop();
                Stack.StackElement s = b.stack.getSpill(si++, e.type);
                code.append(s.value).append(" = ").append(e.value).append(";\n");
                b.spills.add(s);
                allSpills.put(s.value, s);
            }
            b.code = code.toString();
        }
        System.out.println("function test(lI0){");
        Map<String, String> localDefs = new HashMap();
        for(Method.LocalInfo l : method.locals) {
            addLocalDef(localDefs, l.type, l.name);
        }
        
        for(Stack.StackElement e : allSpills.values())
            addLocalDef(localDefs, e.type, e.value);
        //for(String s : allSpills.keySet()) System.out.print(","+s);
        for(Stack.StackElement t : method.allTemps.values()) 
            addLocalDef(localDefs, t.type, t.value);
            //System.out.print(","+t.value);
        for(Map.Entry<String,String> e : localDefs.entrySet()) {
            System.out.println(e.getKey()+" "+e.getValue()+";");
        }
        
        //System.out.println(";");
        //System.out.println("var flow=0,l1,l2,spill_0,spill_1,tmp;");
        //System.out.println("while(true) outer: switch(flow){");        
        for(BasicBlock b : blocks) {
            System.out.println("BC"+b.id+":");
            //System.out.println("case "+b.id+":");
            //if(b.parent != null) System.out.print(" (parent="+b.parent.id+")");
            System.out.println(b.code);
            //System.out.println("  stack="+stack);
            /*
            int line = -1;
            for(Op o : b.ops) {
                if(o.code != null)
                    System.out.println("  "+o.pc+" "+o.code);
            }*/
        }  
        System.out.println("}}");
    }
    
}
