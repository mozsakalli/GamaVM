
import digiplay.GL;
import digiplay.Game;
import digiplay.Point2D;
import digiplay.Stage2D;

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

/**
 *
 * @author mustafa
 */
public class MyGame implements Game {

    long program;
    long attrPos, uniProj;
    long vbo, ibo;
    
    @Override
    public void begin() {
        Stage2D.I.setup(new Point2D(1024,768));
        
        program = GL.compileProgram("attribute vec4 pos;\n" +
"            attribute vec2 uv;\n" +
"            attribute vec4 color;\n" +
"            //attribute vec3 m1;\n" +
"            //attribute vec3 m2;\n" +
"\n" +
"            uniform mat4 projection;\n" +
"            varying vec4 vColor;\n" +
"            varying vec2 vUv;\n" +
"            varying vec4 vPos;\n" +
"\n" +
"            void main()\n" +
"            {\n" +
"                vColor = color;\n" +
"                vUv = uv;\n" +
"                vPos = pos;\n" +
"                gl_Position = projection * vec4(pos.xyz, 1.0);\n" +
"            }", 
                "#ifdef GL_ES\n" +
"            precision mediump float;\n" +
"            #endif\n" +
"            varying vec4 vColor;\n" +
"            varying vec2 vUv;\n" +
"            varying vec4 vPos;\n" +
"            uniform sampler2D texture;\n" +
"\n" +
"            uniform lowp vec4 userVec4;\n" +
"\n" +
//"            __CODE__\n" +
"\n" +
"            void main()\n" +
"            {\n" +
"                gl_FragColor=vec4(1.0,0.0,0.0,1.0);\n" +
"            }");
        
        attrPos = GL.attribLocation(program, "pos");
        uniProj = GL.uniformLocation(program, "projection");
        vbo = GL.createVertexBuffer();
        ibo = GL.createIndexBuffer();
        GL.bufferVertexData(vbo, new float[]{
            -100, -100, 0,
             100, -100, 0,
             100,  100, 0
        }, 0, 0);
        GL.bufferIndexData(ibo, new short[]{
            0,1,2
        }, 0, 0);
        System.out.println("program = "+program+" pos="+attrPos+" proj="+uniProj);
        /*
        Image img = new Image();
        Stage2D.I.addChild(img);
        
        System.out.println("game:begin");
        */
    }

    @Override
    public void update() {
        //Stage2D.I.update();
    }

    @Override
    public void render() {
        GL.clearColor(0, 0, 0, 1);
        GL.viewport(0, 0, digiplay.Digiplay.graphics.getScreenWidth(), digiplay.Digiplay.graphics.getScreenHeight());
        GL.clear(GL.COLOR_BUFFER_BIT);
    }

}
