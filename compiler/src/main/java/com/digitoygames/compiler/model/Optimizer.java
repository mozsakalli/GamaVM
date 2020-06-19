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

import com.digitoygames.compiler.model.op.Binary;
import com.digitoygames.compiler.model.op.Cmp;
import com.digitoygames.compiler.model.op.If;
import com.digitoygames.compiler.model.op.Invoke;
import com.digitoygames.compiler.model.op.Op;
import com.digitoygames.compiler.model.op.StoreLocal;
import java.util.HashSet;
import java.util.Set;

/**
 *
 * @author mustafa
 */
public class Optimizer {
    
    public static void optimize(Method method, BasicBlock bb) {
        while(optimizeCmp(bb)){}
        optimizeFieldMethod(bb);
        optimizeBinaryLocalStore(bb);
    }
    
    static void optimizeBinaryLocalStore(BasicBlock bb) {
        for(int i=0; i<bb.ops.size()-1; i++) {
            if((bb.ops.get(i) instanceof Binary) && (bb.ops.get(i+1) instanceof StoreLocal)) {
                ((Binary)bb.ops.get(i)).targetLocal = ((StoreLocal)bb.ops.get(i+1)).index;
                bb.ops.remove(i+1);
                i--;
            }
        }
    }
    
    static void optimizeFieldMethod(BasicBlock bb) {
        Set<Integer> seen = new HashSet();
        for(BasicBlock src : bb.sources) {
            if(src.id > bb.id)  continue;
            for(Op o : src.ops) {
                int index = -1;
                if(o instanceof com.digitoygames.compiler.model.op.Field)
                    index = ((com.digitoygames.compiler.model.op.Field)o).index;
                else if(o instanceof Invoke)
                    index = ((Invoke)o).index;
                
                if(index != -1) seen.add(index);
            }
        }
        
        for(Op o : bb.ops) {
            if(o instanceof com.digitoygames.compiler.model.op.Field) {
                com.digitoygames.compiler.model.op.Field f = (com.digitoygames.compiler.model.op.Field)o;
                if(seen.contains(f.index)) f.resolved = true; else {
                    seen.add(f.index);
                }
            } else if(o instanceof Invoke) {
                Invoke i = (Invoke)o;
                if(seen.contains(i.index)) i.resolved = true; else seen.add(i.index);
            }
        }
    }
    
    static boolean optimizeCmp(BasicBlock bb) {
        for(int i=0; i<bb.ops.size()-1; i++) {
            if((bb.ops.get(i) instanceof Cmp) && (bb.ops.get(i+1) instanceof If)) {
                Cmp cmp = (Cmp)bb.ops.get(i);
                If f = (If)bb.ops.get(i+1);
                if(f.right != null && f.right.equals("0")) {
                    switch(f.operand) {
                        case "==":
                            f.right = null;
                            bb.ops.remove(i);
                            return true;
                            
                        case ">":
                            f.right = null;
                            bb.ops.remove(i);
                            return true;
                            
                        case "<":
                            f.right = null;
                            bb.ops.remove(i);
                            return true;
                    }
                }
            }
        }
        return false;
    }
}
