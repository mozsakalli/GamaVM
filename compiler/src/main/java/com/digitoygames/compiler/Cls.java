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

import de.inetsoftware.classparser.ClassFile;
import de.inetsoftware.classparser.MethodInfo;
import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author mustafa
 */
public class Cls {
    
    public ClassFile cf;
    List<Method> methods = new ArrayList();
    public String name;
    
    public Cls(ClassFile cf) {
        this.cf = cf;
        name = cf.getThisClass().getName();
    }
    
    public Method getMethod(String name, String signature) throws Exception {
        for(Method m : methods) {
            if(m.mi.getName().equals(name) && m.mi.getType().equals(signature))
                return m;
        }
        
        MethodInfo mi = cf.getMethod(name, signature);
        if(mi == null) throw new Exception("Can't find method: "+cf.getThisClass().getName()+"::"+name+"/"+signature);
        Method m = new Method(this, mi);
        methods.add(m);
        return m;
    }
}
