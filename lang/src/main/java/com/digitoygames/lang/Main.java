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

import com.digitoygames.lang.model.Module;

import java.io.File;

/**
 *
 * @author mustafa
 */
public class Main {
    
    public static void main(String...args) throws Exception {
        Parser p = new Parser(new File("/Users/mustafa/Work/digitoygames/digiplay-net/Digiplay/Digiplay.Core/core/Sprite2D.cs"));
        //Parser p = new Parser(new File("/Users/mustafa/Desktop/test.cs"));
        Module m = p.parse();

        SourceWriter out = new SourceWriter();
        m.generateCPP(out);
        System.out.println(out.toString());
    }
    
}
