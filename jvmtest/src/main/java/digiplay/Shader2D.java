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

package digiplay;

/**
 *
 * @author mustafa
 */
public class Shader2D extends Shader {

final static String VERT="attribute vec3 pos;\n" +
"            attribute vec2 uv;\n" +
"            attribute vec4 color;\n" +
"            //attribute vec3 m1;\n" +
"            //attribute vec3 m2;\n" +
"\n" +
"            uniform mat4 projection;\n" +
"            varying vec4 vColor;\n" +
"            varying vec2 vUv;\n" +
"            //varying vec4 vPos;\n" +
"\n" +
"            void main()\n" +
"            {\n" +
"                vColor = color;\n" +
"                vUv = uv;\n" +
"                //vPos = pos;\n" +
"                gl_Position = projection * vec4(pos.xyz, 1.0);\n" +
"            }";    

final static String FRAG="#ifdef GL_ES\n" +
"            precision mediump float;\n" +
"            #endif\n" +
"            varying vec4 vColor;\n" +
"            //varying vec2 vUv;\n" +
"            //varying vec4 vPos;\n" +
"            uniform sampler2D texture;\n" +
"\n" +
"            uniform lowp vec4 userVec4;\n" +
"\n" +
//"            __CODE__\n" +
"\n" +
"            void main()\n" +
"            {\n" +
"                gl_FragColor=vColor;\n" +
"            }";
    public Shader2D() {
        super(VERT, FRAG);
        System.out.println("program = "+handle+" pos="+attrPos+" proj="+uniProjection+"  color="+attrColor);
    }

}
