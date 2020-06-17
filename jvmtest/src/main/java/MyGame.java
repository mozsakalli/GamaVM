
import digiplay.GLQuadBatch;
import digiplay.Game;
import digiplay.Image;
import digiplay.MainActivity;
import digiplay.Platform;
import digiplay.Point2D;
import digiplay.SpriteAction;
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


    long httpTimer;
    
    @Override
    public void begin() {
        Stage2D.I.setup(new Point2D(Platform.screenWidth,Platform.screenHeight));
        for(int i=0; i<10; i++) {
            Image img = new Image();
            Stage2D.I.addChild(img);
            img.x(480);
            img.y(320);
            img.blendMode = 1;
            img.setAlpha((float)(Math.random()*.5)+.5f);
            img.rotation((float)Math.random()*360);
            img.addAction(new SpriteAction.AnimRotation(0,0,360,360,10000));
            //img.color = (((int)(Math.random()*255)) << 16) | (((int)(Math.random()*255)) << 8) | (((int)(Math.random()*255)));
        }
        

        /*
        new Asset() {
            @Override public void onComplete() {
                System.out.println("Bytes loaded: "+bytes.length);
                new Stb.Image() {
                    @Override public void onComplete() {
                        System.out.println("Image loaded: "+width+"x"+height+" len:"+this.pixels.length);
                    }
                }.decode(bytes);
            }
        }.load("special-offer.png");
        /*
        new Net.Http("https://www.google.com", null) {
            public void onComplete() {
                if(bytes != null)
                    System.out.println(new String(bytes));
            }
        }.start();
        */
        byte[] bytes = MainActivity.readFile("special-offer.png");
        System.out.println("png-bytes:"+bytes.length);
    }

    long fpsTimer;
    int fps;
    
    @Override
    public void update() {
        Stage2D.I.update();
        long now = System.currentTimeMillis();
        if(System.currentTimeMillis() - fpsTimer <= 1000) fps++; else {
            System.out.println("FPS: "+fps);
            fps = 0;
            fpsTimer = System.currentTimeMillis();
        }
        

    }

    //Mat2D mat = new Mat2D();
    //float speed = 1f;
    //float x=0,y=0,dy=speed,r=0;
    @Override
    public void render() {
        Stage2D.I.render();
        new GLQuadBatch(500);
        /*
        batch.begin(Digiplay.platform.screenWidth, Digiplay.platform.screenHeight, true, 0xFF300000);
        //x+=0.02f;
        //y+=0.5f;
        mat.compose(480, 320, 1, 1, 25, 25, true, r, 0, 0);
        r += speed;
        //mat.identity();
        batch.drawQuadMesh(q, mat, shader,0xFF0000FF, 1, 1);
        batch.end();
        
        y += dy;
        if(y >= 640) {
            y = 640;
            dy = -speed;
        } else if(y <= 0) {
            y = 0;
            dy = speed;
        }
        

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
