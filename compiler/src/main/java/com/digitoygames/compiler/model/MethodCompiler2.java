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

import com.digitoygames.compiler.SourceWriter;
import com.digitoygames.compiler.Util;
import com.digitoygames.compiler.model.op.*;

import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;

/**
 *
 * @author mustafa
 */
public class MethodCompiler2 {
    
    Method method;
    
    public MethodCompiler2(Method method) {
        this.method = method;
    }
    
    void addLocal(Map<String,String> map, StackValue v) {
        String str = map.computeIfAbsent(v.type, (k) -> "");
        if(!str.isEmpty()) str += ",";
        str += v.value;
        map.put(v.type, str);
    }
    public void compile(SourceWriter out) throws Exception {
        String key = method.declaringClass.getName()+":"+method.getName()+":"+method.getSignature();
        if(method.getName().equals("setupFor2D"))
            System.out.println("");
        System.out.println(key);
        out.println("void %s(VM *vm, Method *method, VAR *args) {",method.getAOTName()).indent()
           .println("Frame *frame = &vm->frames[++vm->fp];")
           .println("frame->method = method;");
           //.println("VAR local[method->maxLocals];");

        Code code = method.getCode();
        //System.out.println(code.tryCatchPC);

        OpBuilder builder = new OpBuilder(method, code);
        List<Op> ops = builder.build();
        //for(Op o : ops)
        //    System.out.println("    "+o.pc+":"+o);
        List<BasicBlock> blocks = BasicBlock.build(method, code, ops);
        for(BasicBlock bb : blocks) {
            out.println("BB"+bb.id);
            if(!bb.sources.isEmpty()) {
            for(BasicBlock src : bb.sources)
                out.print("   src="+src.id);
            out.ln();
            }
        }
        Set<BasicBlock> executed = new HashSet();
        for(BasicBlock bb : blocks)
            executeBlock(bb, executed);
        
        Map<String,String> locals = new HashMap();
        for(StackValue v : method.allLocals) addLocal(locals, v);
        for(StackValue v : method.allTemps) addLocal(locals, v);
        for(StackValue v : method.allSpills) addLocal(locals, v);
        for(Map.Entry<String,String> e : locals.entrySet())
            out.println("%s %s;", Util.getPlatformType(e.getKey()), e.getValue());
        Set<Integer> calls = new HashSet();
        Set<Integer> fields = new HashSet();
        Set<Integer> refs = new HashSet();
        for(Op o : ops) {
            if(o instanceof Invoke) {
                int index = ((Invoke)o).index;
                calls.add(index);
            } else if(o instanceof GetField) {
                fields.add(((GetField)o).index);
            } else if(o instanceof SetField) {
                fields.add(((SetField)o).index);
            } else if(o instanceof New) {
                refs.add(((New)o).index);
            }
        }
        if(!calls.isEmpty()) {
            out.print("static Method ");
            int count = 0;
            for(int index : calls) {
                if(count++ > 0) out.print(",");
                out.print("*call%d=NULL",index);
            }
            out.println(";");
        }
        if(!fields.isEmpty()) {
            out.print("static Field ");
            int count = 0;
            for(int index : fields) {
                if(count++ > 0) out.print(",");
                out.print("*field%d=NULL",index);
            }
            out.println(";");
        }
        if(!refs.isEmpty()) {
            out.print("static Class ");
            int count = 0;
            for(int index : refs) {
                if(count++ > 0) out.print(",");
                out.print("*cls%d=NULL",index);
            }
            out.println(";");
        }
        List<String> args = Util.parseMethodSignature(method.getSignature());
        if(!method.isStatic()) args.add(0, "O");
        
        int index = 0;
        int cindex = 0;
        //System.out.println("args = "+args);
        for(String argType : args) {
            StackValue local = method.findLocal(index, argType);
            if(local != null) // set only used locals
                out.println("%s=args[%d].%s;", local.value,cindex++,argType);
            index++;
            if(argType.equals("D") || argType.equals("J")) index++;
        }
        for(BasicBlock bb : blocks) {
            out.undent().println("BB"+bb.id+":").indent();
            //BasicBlock parent = bb.sources.isEmpty() ? null : bb.sources.iterator().next();
            //if(parent != null)
            //    out.println("spill-count="+parent.spills.size());
            for(String l : bb.code.split("\n"))
                out.println(l+";");
        }
        out.undent().println("}");
        /*
        for(BasicBlock b : blocks) {
            System.out.print("BB"+b.id+":");
            for(BasicBlock sb : b.sources)
                System.out.print(" From:"+sb.id);
            //if(b.parent != null) System.out.print(" PB:"+b.parent.id);
            System.out.println();
            //for(Op o : b.ops) {
            //    System.out.println("   "+o);
            //}
        }*/
    }
    
    void executeBlock(BasicBlock bb, Set<BasicBlock> executed) {
        if(executed.contains(bb)) return;
        executed.add(bb);
        for(BasicBlock b : bb.sources)
            if(!executed.contains(b))
                executeBlock(b, executed);

        System.out.println("BB:"+bb.id);
        StringBuilder code = new StringBuilder();
        BasicBlock parent = bb.sources.isEmpty() ? null : bb.sources.iterator().next();
        if(parent != null) {
            for(int i=parent.spills.size()-1; i>=0; i--) {
                bb.stack.push(parent.spills.get(i));
                //code.append("// spil = "+parent.spills.get(i).value+"\n");
            }
        }
        if(bb.isTryCatchHandler) {
            StackValue ex = new StackValue();
            ex.type = "O";
            ex.value = "__caught__";
            bb.stack.push(ex);
        }

        Op lastOp = bb.ops.isEmpty() ? null : bb.ops.get(bb.ops.size() - 1);
        for(Op o : bb.ops) {
            o.execute(method, bb.stack);
            System.out.println("   "+o.pc+":"+o.getClass().getSimpleName()+":"+o+" : stack="+bb.stack.size());
            if(o == lastOp && o instanceof Branch) {
                bb.buildSpills(method, code);
            }
            if(o.code != null)
                code.append(o.code).append("\n");
        }
        bb.buildSpills(method, code);
        bb.code = code.toString();
    }
    
}
