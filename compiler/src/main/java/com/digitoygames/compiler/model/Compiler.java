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
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

/**
 *
 * @author mustafa
 */
public class Compiler {
    
    String[] classPath;
    public HashMap<String, Integer> strings = new HashMap();
    
    public Compiler() {
        
    }
    
    public void setClassPath(String[] path) {
        classPath = path;
    }
    
    public void compileBoot() throws Exception {
        List<Clazz> classes = new ArrayList();
        
        List<File> queue = new ArrayList();
        for(String str : classPath)
            queue.add(new File(str));
        
        while(!queue.isEmpty()) {
            File f = queue.remove(0);
            if(f.isDirectory()) {
                for(File d : f.listFiles())
                    queue.add(d);
            } else if(f.getName().endsWith(".class")) {
                System.out.println(f);
                Clazz cls = new Clazz(new FileInputStream(f));
                classes.add(cls);
            }
        }
        
        SourceWriter out = new SourceWriter();
        out.println("#include \"vm.h\"")
                .println("#include <math.h>")
                .println("Object **aot_strings;")
                .ln();
        for(Clazz cls : classes) {
            ClassCompiler cc = new ClassCompiler(this, cls);
            cc.compile(out);
            //compileClassMethods(cls, out);
        }

        //alloc_string_java(NULL, ((JCHAR[]){10,20}), 2, 0);
        out.println("void aot_init(VM *vm) {").indent();
        out.println("static  int i=0; if(i) return; i=1;");
        if(!strings.isEmpty()) {
            out.println("aot_strings = (Object**)malloc(sizeof(Object*)*%d);", strings.size());
            for(String k : strings.keySet()) {
                out.print("aot_strings[%d] = alloc_string_java(vm,(JCHAR[]){", strings.get(k));
                for(int i=0; i<k.length(); i++) {
                    if(i>0) out.print(",");
                    out.print((int)k.charAt(i));
                }
                out.println("},%d,1);", k.length());
            }
        }
        out.undent().println("}");
        
        out.println("NativeMethodInfo aot_native_methods[] = {").indent();
        int cnt = 0;
        for(Clazz cls : classes) {
            for(int i=0; i<cls.methods.size(); i++) {
                Method m = cls.methods.get(i);
                if(!m.isAbstract() && !m.isNative()) {
                    if(cnt > 0) out.print(",");
                    out.println("{\"%s:%s:%s\",&%s}",cls.getName(),m.getName(),m.getSignature(), cls.methods.get(i).getAOTName());
                    cnt++;
                }
            }
        }
        out.println(",NULL") .undent().println("};");
        
        for(Clazz cls : classes) {
            String name = cls.getName();
            byte[] bc = cls.dump();
            File file = new File("/Users/mustafa/Desktop/aot/",name+".class");
            file.getParentFile().mkdirs();
            new FileOutputStream(file).write(bc);
        }
        //compileMeta(classes, out);

        new FileOutputStream("/Users/mustafa/Work/GamaVM/digi/digi/gamaot.c").write(out.toString().getBytes());
        //System.out.println(out.toString());
    }
    
    public void compileClassMethods(Clazz cls, SourceWriter out) throws Exception {
        /*
        for(Method method : cls.methods) {
            if(!method.isAbstract() && !method.isNative()) {
                MethodCompiler2 mc = new MethodCompiler2(method);
                //mc.compile(out);
            }
        }
        //System.out.println(o.toString());
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

    void compileMeta(List<Clazz> list, SourceWriter out) throws Exception {
        for(Clazz cls : list) {
            byte[] meta = cls.dump();
            out.print("const unsigned char %s_META[]={",cls.getAOTName());
            for(int i=0; i<meta.length; i++) {
                if(i > 0) out.print(",");
                out.print(meta[i]);
            }
            out.println("};");
            out.print("const void* %s_METHODS[]={",cls.getAOTName());
            for(int i=0; i<cls.methods.size(); i++) {
                Method m = cls.methods.get(i);
                if(i > 0) out.print(",");
                if(m.isNative() || m.isAbstract()) out.print("NULL");
                else out.print("&%s",cls.methods.get(i).getAOTName());
            }
            out.println("};");
        }

        out.println("AOTClassData AOT[] = {").indent();
        for(Clazz cls : list) {
            out.println("{.name=\"%s\", .data=&%s_META[0], .methods=&%s_METHODS[0]},", cls.getName(), cls.getAOTName(), cls.getAOTName());
        }
        out.println("{.name=NULL}");
        out.undent().println("};");
    }
    
    public int getStringIndex(String value) {
        return strings.computeIfAbsent(value, (v) -> strings.size());
    }
}
