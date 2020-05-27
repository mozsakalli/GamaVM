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

import com.digitoygames.compiler.model.ClassCompiler;
import com.digitoygames.compiler.model.Clazz;
import de.inetsoftware.classparser.ClassFile;
import java.io.FileInputStream;
/**
 *
 * @author mustafa
 */
public class Main {
  
    public static void main(String...args) throws Exception {
        System.out.println(Test.main() );
        //String f = "/Users/mustafa/Work/experimental/jjj/compiler/target/classes/com/digitoygames/compiler/StbTTF.class";
        //String f = "/Users/mustafa/Work/experimental/jjj/classpath/target/classes/java/lang/Long.class";
        String f = "/Users/mustafa/Work/experimental/jjj/jvmtest/target/classes/Main.class";
        Clazz src = new Clazz(new FileInputStream(f));
        ClassCompiler cc = new ClassCompiler(src);
        SourceWriter out = new SourceWriter();
        cc.compile(out);
        System.out.println(out.toString());
        if(true) return;
        /*
        System.out.println(Test.test());
        Clazz src = new Clazz(new FileInputStream("/Users/mustafa/Work/experimental/jjj/compiler/target/classes/com/digitoygames/compiler/Test.class"));
        //Clazz cls = new Clazz(new FileInputStream("/Users/mustafa/Work/experimental/jjj/compiler/target/classes/com/digitoygames/compiler/Test.class"));
        Clazz cls = new Clazz(new ByteArrayInputStream(src.dump()));
        ClassCompiler cc = new ClassCompiler(src);
        cc.compile();
        /*System.out.println(cls.getSuperName());
        for(com.digitoygames.compiler.model.Field f : cls.fields)
            System.out.println("field: "+f.getName()+":"+f.getSignature());
        for(com.digitoygames.compiler.model.Method m : cls.methods)
            System.out.println("m: "+m.getName()+":"+m.getSignature());

        Code code = cls.methods.get(2).getCode();
        for(LocalVar v : code.getLocals()) {
            System.out.println(v.index+" -> "+v.name+":"+v.signature);
        }
        
        //MethodCompiler mc = new MethodCompiler(cls.methods.get(2));
        //mc.compile();
        //genConstantPool(cls);
        */
        
        System.out.println(new Test().main());
        Cls cls = new Cls(new ClassFile(new FileInputStream("/Users/mustafa/Work/experimental/jjj/compiler/target/classes/com/digitoygames/compiler/Test.class")));
        //Cls cls = new Cls(new ClassFile(new FileInputStream("/Users/mustafa/Work/experimental/cava/compiler/test/jbox2d-library-2.2.1.1/org/jbox2d/dynamics/World.class")));
        //Cls cls = new Cls(new ClassFile(new FileInputStream("/Users/mustafa/Work/experimental/jjj/compiler/target/classes/com/digitoygames/compiler/StbTTF.class")));
        try {
            Method mth = cls.getMethod("test", "()I");
                    //cls.getMethod("stbtt_FindGlyphIndex", "(Lcom/digitoygames/compiler/StbTTF$Stbtt_fontinfo;I)I");
            //Compiler cmp = new Compiler(mth);
            /*
            Method mth = cls.getMethod("test", "()I");
            Compiler cmp = new Compiler(mth);
            mth = cls.getMethod("val", "(DI)I");
            cmp = new Compiler(mth);
            */
        }catch(Exception e){
            e.printStackTrace();
        }
        
        //genConstantPool(cls);
        //cmp.generate();
        //for(Op o : mth.ops) {
        //    System.out.println(o.pc+": "+o);
        //}*/
    }
    
}
