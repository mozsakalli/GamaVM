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

/**
 *
 * @author mustafa
 */
public class ClassCompiler {
    
    Clazz cls;
    SourceWriter out;// = new SourceWriter();
    
    public ClassCompiler(Clazz cls) {
        this.cls = cls;
    }
    
    public void compile(SourceWriter out) throws Exception {
        cls.getBootstrapMethods();
        this.out = out;
        out.println("#include \"jvm.h\"").ln();

        for(Method method : cls.methods) {
            if(!method.isAbstract() && !method.isNative()) {
                MethodCompiler2 mc = new MethodCompiler2(method);
                mc.compile(out);
            }
        }
        //System.out.println(o.toString());

        byte[] meta = cls.dump();
        out.print("const unsigned char %s_META[]={",cls.getAOTName());
        for(int i=0; i<meta.length; i++) {
            if(i > 0) out.print(",");
            out.print(meta[i]);
        }
        out.println("};");
        out.print("const void* %s_METHODS[]={",cls.getAOTName());
        for(int i=0; i<cls.methods.size(); i++) {
            if(i > 0) out.print(",");
            out.print("&%s",cls.methods.get(i).getAOTName());
        }
        out.println("};");
        
        out.println("AOTClassData AOT[] = {").indent();
        out.println("{.name=\"%s\", .data=&%s_META[0], .methods=&%s_METHODS[0]}", cls.getName(), cls.getAOTName(), cls.getAOTName());
        out.undent().println("};");
        //System.out.println(out.toString());
    }
    

}
