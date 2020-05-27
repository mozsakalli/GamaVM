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

import com.digitoygames.compiler.model.op.*;

import java.util.ArrayList;
import java.util.List;
import java.util.Set;
import java.util.HashSet;

/**
 *
 * @author mustafa
 */
public class BasicBlock {
    
    public int id;
    public List<BasicBlock> next = new ArrayList();
    public BasicBlock parent;
    public List<Op> ops = new ArrayList();
    public Stack stack = new Stack();
    public List<StackValue> spills = new ArrayList();
    public String code;
    public Set<BasicBlock> sources = new HashSet();
    public boolean isTryCatchHandler;
    
    public static List<BasicBlock> build(Method method, Code code, List<Op> ops) {
        Set<Integer> blockStart = new HashSet();
        for(int i=0; i<ops.size(); i++) {
            Op o = ops.get(i);
            if(o instanceof Goto) {
                blockStart.add(((Goto)o).offset + o.pc);
            } else if(o instanceof If) {
                blockStart.add(((If)o).offset + o.pc);
                blockStart.add(ops.get(i+1).pc);
            } else if(o instanceof Return || o instanceof Throw) {
                if(i < ops.size() - 1)
                    blockStart.add(ops.get(i+1).pc);
            } else if(o instanceof Switch) {
                Switch s = (Switch)o;
                for(int p : s.positions)
                    blockStart.add(p);
                blockStart.add(s.defaultPosition);
            }
        }

        for(int pc : code.tryCatchPC) blockStart.add(pc);

        List<BasicBlock> blocks = new ArrayList();
        BasicBlock bb = new BasicBlock();
        bb.id = 0;
        blocks.add(bb);
        
        for(Op o : ops) {
            if(blockStart.contains(o.pc)) {
                BasicBlock nb = new BasicBlock();
                nb.id = o.pc;
                blocks.add(bb = nb);
                nb.isTryCatchHandler = code.isTryCatchHandler(o.pc);
            }
            bb.ops.add(o);
        }
        
        for(int i=0; i<blocks.size()-1; i++) {
            bb = blocks.get(i);
            Op last = bb.ops.isEmpty() ? null : bb.ops.get(bb.ops.size() - 1);
            int[] targets = null;
            if(last != null) {
                if (last instanceof Goto) {
                    targets = new int[]{((Goto) last).offset + last.pc};
                } else if (last instanceof If) {
                    If f = (If) last;
                    targets = new int[]{f.offset + f.pc, blocks.get(i + 1).id};
                } else if (last instanceof Return || last instanceof Throw) {
                    continue;
                }
            }
            if(targets != null) {
                for(int t : targets) {

                    BasicBlock target = blocks.stream().filter(b -> b.id == t).findFirst().orElse(null);
                    if(target != bb) {
                        target.sources.add(bb);
                        bb.next.add(target);
                    }
                    //if(target != null && target.parent == null) target.parent = bb;
                }
            } else {

                blocks.get(i+1).sources.add(bb);
                bb.next.add(blocks.get(i+1));
            }
        }
        
        return blocks;
    }

    public void buildSpills(Method method, StringBuilder code) {
        int spillIndex = stack.getSpillCount();
        while (stack.size() > 0) {
            StackValue val = stack.pop();
            //code.append("//spil:"+val.value+" -> "+val.spillIndex+"\n");
            if(val.spillIndex == -1) {
                StackValue spill = method.allocSpill(spillIndex, val.type);
                code.append("/*spill*/" + spill.value + "=" + val.value + ";\n");
                spills.add(spill);
            } else {
                spills.add(val);
                //if(val.spillIndex > spillIndex) spillIndex = val.spillIndex + 1;
                //code.append("/*spill*/" + spill.value + "=" + val.value + ";\n");
            }
            spillIndex++;
        }
    }
}
