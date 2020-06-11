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
import java.util.List;

/**
 *
 * @author mustafa
 */
public class Compiler {
    
    String[] classPath;
    
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
                Clazz cls = new Clazz(new FileInputStream(f));
                classes.add(cls);
            }
        }
        
        SourceWriter out = new SourceWriter();
        out.println("#include \"vm.h\"").ln();
        for(Clazz cls : classes) {
            compileClassMethods(cls, out);
        }

        compileMeta(classes, out);

        new FileOutputStream("/Users/mustafa/Desktop/aot.c").write(out.toString().getBytes());
        //System.out.println(out.toString());
    }
    
    public void compileClassMethods(Clazz cls, SourceWriter out) throws Exception {
        for(Method method : cls.methods) {
            if(!method.isAbstract() && !method.isNative()) {
                MethodCompiler2 mc = new MethodCompiler2(method);
                mc.compile(out);
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
}
