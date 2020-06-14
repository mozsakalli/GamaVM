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
    Compiler compiler;
    
    public ClassCompiler(Compiler compiler, Clazz cls) {
        this.cls = cls;
        this.compiler = compiler;
    }
    
    public void compile(SourceWriter out) throws Exception {
        cls.getBootstrapMethods();
        this.out = out;
        //out.println("#include \"vm.h\"").ln();
        out.println("//%s", cls.getName());
        int fieldCount = 0;
        int methodCount = 0;
        int clsCount = 0;
        for(int i=0; i<cls.cp.items.length; i++) {
            CP.Item ci = cls.cp.items[i];
            if(ci == null) continue;
            switch(ci.type) {
                case CP.FIELDREF:
                    if(fieldCount==0) out.print("static Field "); else out.print(",");
                    out.print("*f%s_%d=NULL", cls.aotHash,i);
                    fieldCount++;
            }
        }
        if(fieldCount > 0) out.println(";");
        
        for(int i=0; i<cls.cp.items.length; i++) {
            CP.Item ci = cls.cp.items[i];
            if(ci == null) continue;
            switch(ci.type) {
                case CP.METHODREF:
                case CP.IMETHODREF:
                    if(methodCount==0) out.print("static JLONG "); else out.print(",");
                    out.print("m%s_%d=0",cls.aotHash,i);
                    methodCount++;
            }
        }
        if(methodCount > 0) out.println(";");
        for(int i=0; i<cls.cp.items.length; i++) {
            CP.Item ci = cls.cp.items[i];
            if(ci == null) continue;
            switch(ci.type) {
                case CP.CLASSREF:
                    if(clsCount==0) out.print("static Object "); else out.print(",");
                    out.print("*c%s_%d=NULL",cls.aotHash,i);
                    clsCount++;
            }
        }
        if(clsCount > 0) out.println(";");
        
        
        
        for(Method method : cls.methods) {
            if(!method.isAbstract() && !method.isNative()) {
                MethodCompiler2 mc = new MethodCompiler2(this, method);
                mc.compile(out);
            }
        }
        
        /*
        out.println("NativeMethodInfo aot_native_methods[] = {").indent();
        int cnt = 0;
        for(int i=0; i<cls.methods.size(); i++) {
            Method m = cls.methods.get(i);
            if(!m.isAbstract() && !m.isNative()) {
                if(cnt > 0) out.print(",");
                out.println("{\"%s:%s:%s\",&%s}",cls.getName(),m.getName(),m.getSignature(), cls.methods.get(i).getAOTName());
                cnt++;
            }
        }
        out.println(",NULL") .undent().println("};");
        //System.out.println(o.toString());
        /*
        byte[] bytes = cls.dump();
        out.println("char sprite_data%d[]={",ndx);
        for(int i=0; i<bytes.length; i++) {
            if(i>0) out.print(",");
            out.print(bytes[i]);
        }
        out.println("};");
        /*
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
        //System.out.println(out.toString());*/
    }
    

}
