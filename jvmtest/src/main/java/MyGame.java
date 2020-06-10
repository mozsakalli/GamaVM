
import digiplay.GLQuadBatch;
import digiplay.GLShader2D;
import digiplay.Game;
import digiplay.Digiplay;


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

    //long program;
    //long attrPos, uniProj;
    //long vbo, ibo;
    //Shader2D shader;
    
    //Matrix3D projection = new Matrix3D();
    
    GLQuadBatch batch;
    GLShader2D shader;
    
    /*
    QuadBatch batch;
    List<T> items = new ArrayList();
    
    static class T {
        public float x,y,dx,dy,width,height;
        public T() {
            x = (float)Math.random() * Digiplay.graphics.getScreenWidth();
            y = (float)Math.random() * Digiplay.graphics.getScreenHeight();
            dx = -4 + (float)Math.random() * 8;
            dy = -4 + (float)Math.random() * 8;
            width = (float)Math.random() * 100 + 16;
            height = (float)Math.random() * 100 + 16;
        }
        public void step(QuadBatch batch) {
            int w = Digiplay.graphics.getScreenWidth();
            int h = Digiplay.graphics.getScreenHeight();
            x += dx;
            if(x < 0) {x = 0; dx = (float)Math.random() * 4; }
            else if(x > w) { x = w; dx = -(float)Math.random() * 4; }
            
            y += dy;
            if(y < 0) {y = 0; dy = (float)Math.random() * 4; }
            else if(y > h) { y = h; dy = -(float)Math.random() * 4; }
            
            batch.quad(x, y, width, height, 0xff0000ff);
        }
    }
    */
    @Override
    public void begin() {
        System.out.println("BEGIN");
        shader = new GLShader2D("gl_FragColor = vec4(1.0,0.0,0.0,1.0);");
        batch = new GLQuadBatch(4096);
        /*
        Stage2D.I.setup(new Point2D(1024,768));
        batch = new QuadBatch(2048);
        for(int i=0; i<1000; i++)
            items.add(new T());
        //shader = new Shader2D();
        /*
        program = GL.compileProgram("attribute vec3 pos;\n" +
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
"            }", 
                "#ifdef GL_ES\n" +
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
"                gl_FragColor=vec4(1.0,0.0,0.0,1.0);\n" +
"            }");
        
        attrPos = GL.attribLocation(program, "pos");
        uniProj = GL.uniformLocation(program, "projection");*/
        //vbo = GL.createVertexBuffer();
        //ibo = GL.createIndexBuffer();
        /*
        GL.bufferVertexData(vbo, new float[]{
            -1000,   -1000, 0,
             1000,   -1000, 0,
             1000,    1000, 0
        }, 0, 0);*/
        /*
        GL.bufferVertexData(vbo, new float[]{
            0,   0, 0,
             1000,   0, 0,
             1000,    1000, 0
        }, 0, 0);
        GL.bufferIndexData(ibo, new short[]{
            0,1,2
        }, 0, 0);
        
        Matrix3D proj = new Camera().setupFor2D(Digiplay.graphics.getScreenWidth(), Digiplay.graphics.getScreenHeight());
        Matrix3D cam = new Matrix3D();
        cam.identity();
        Matrix3D.multiply(proj, cam, projection);
        for(int i=0; i<projection.raw.length; i++)
            System.out.println(i+": "+projection.raw[i]);
        
        
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
        batch.begin(Digiplay.platform.screenWidth, Digiplay.platform.screenHeight, true, 0);
        /*
        batch.begin();
        for(int i=0; i<items.size(); i++)
            items.get(i).step(batch);
        /*
        int sw = Digiplay.graphics.getScreenWidth();
        int sh = Digiplay.graphics.getScreenHeight();
        for(int i=0; i<10; i++) {
            float x = (float)(Math.random()*sw);
            float y = (float)(Math.random()*sh);
            float w = (float)(Math.random()*400);
            float h = (float)(Math.random()*400);
            //System.out.println(x+"x"+y+" - "+w+"x"+h);
            batch.quad(x,y,w,h,
                    0xffff0000);
        }*/
        //batch.flush();
        /*
        GL.clearColor(0, 1, 0, 1);
        GL.viewport(0, 0, digiplay.Digiplay.graphics.getScreenWidth(), digiplay.Digiplay.graphics.getScreenHeight());
        GL.clear(GL.COLOR_BUFFER_BIT);
        GL.disable(GL.CULL_FACE);
        GL.disable(GL.DEPTH_TEST);
        shader.bind();
        //GL.useProgram(program);
        GL.enableVertexAttribArray(shader.attrPos);
        GL.bindVertexBuffer(vbo);
        GL.vertexAttribPointer(shader.attrPos, 3, GL.FLOAT, false, 12, 0);
        GL.bindVertexBuffer(0);
        shader.setProjection(projection);
        //GL.uniformMatrix4f(uniProj, projection.raw, false);
        GL.bindIndexBuffer(ibo);
        GL.drawElements(GL.TRIANGLES, 3, 0);*/
    }

}
