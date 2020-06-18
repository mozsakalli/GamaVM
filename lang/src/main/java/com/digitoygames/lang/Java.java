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

package com.digitoygames.lang;

import com.digitoygames.lang.model.ClassSyntax;
import com.digitoygames.lang.model.Namespace;

/**
 *
 * @author mustafa
 */
public class Java {
    com.digitoygames.lang.model.Module module;
    public SourceWriter out = new SourceWriter();
    
    public Java(com.digitoygames.lang.model.Module module) {
        this.module = module;
    }
    
    public void generate() {
        for(Namespace n : module.namespaces) {
            out.println("package %s;", n.name);
            for(ClassSyntax cls : n.classes) {
                cls(cls);
            }
        }
    }
    
    void cls(ClassSyntax cls) {
        
    }
}
