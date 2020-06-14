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

import com.digitoygames.compiler.model.op.Cmp;
import com.digitoygames.compiler.model.op.If;

/**
 *
 * @author mustafa
 */
public class Optimizer {
    
    public static void optimize(Method method, BasicBlock bb) {
        while(optimizeCmp(bb)){}
    }
    
    static boolean optimizeCmp(BasicBlock bb) {
        for(int i=0; i<bb.ops.size()-1; i++) {
            if((bb.ops.get(i) instanceof Cmp) && (bb.ops.get(i+1) instanceof If)) {
                Cmp cmp = (Cmp)bb.ops.get(i);
                If f = (If)bb.ops.get(i+1);
                if(f.right != null) {
                    if(f.operand.equals("==") && f.right.equals("0")) {
                        //equality
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
