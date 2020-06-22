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
package java.lang;

import gamavm.VM;

/**
 *
 * @author mustafa
 */
public abstract class ClassLoader {

    ClassLoader parent;
    Class classes;
    String strings;

    public ClassLoader() {
        this(VM.getSystemClassLoader());
    }
    
    public ClassLoader(ClassLoader parent) {
        this.parent = parent;
    }
    
    protected abstract byte[] readResource(String path);
    
    public Class loadClass(String name) throws ClassNotFoundException {
        return loadClass(name, false);
    }

    protected Class loadClass(String name, boolean resolve) throws ClassNotFoundException {
        String name0 = name.replace('.', '/');
        ClassLoader cl = this;
        while(cl != null) {
            Class ptr = cl.classes;
            while(ptr != null) {
                if(ptr.getName().equals(name0)) return ptr;
                ptr = ptr.next;
            }
            cl = cl.parent;
        }
        
        //can't find class
        byte[] bytes = readResource(name0+".class");
        if(bytes != null) return defineClass(name, bytes, 0, bytes.length);
        if(parent != null) return parent.loadClass(name, resolve);
        throw new ClassNotFoundException(name);
    }

    protected native Class defineClass(String name, byte[] b, int offset, int length);

    public final ClassLoader getParent() {
        return parent;
    }
}
