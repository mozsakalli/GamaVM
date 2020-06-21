
import digiplay.Game;
import digiplay.Image;
import digiplay.Net;
import digiplay.Platform;
import digiplay.Point2D;
import digiplay.Stage2D;
import java.io.ByteArrayInputStream;
import java.io.DataInputStream;


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
        System.out.println(byte.class);
        Stage2D.I.setup(new Point2D(Platform.screenWidth,Platform.screenHeight));
        for(int i=0; i<5; i++) {
            Image img = new Image();
            Stage2D.I.addChild(img);
            img.setX(480);
            img.setY(320);
            img.blendMode = 0;
            img.setAlpha((float)(Math.random()*.5)+.5f);
            img.setRotation((float)Math.random()*360);
            img.color = (((int)(Math.random()*255)) << 16) | (((int)(Math.random()*255)) << 8) | (((int)(Math.random()*255)));
            /*img.onShow = new Action1<Sprite2D>() {
                @Override
                public void invoke(Sprite2D value) {
                    System.out.println(value.getClass()+" shown");
                }
                
            };*/
            System.out.println(img);
            img.addBehaviour(new B());
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
    }

    long fpsTimer;
    int fps;
    long jarTimer;
    long jarTime;
    
    @Override
    public void update() {
        Stage2D.I.update();
        long now = System.currentTimeMillis();
        if(now - fpsTimer <= 1000) fps++; else {
            System.out.println("FPS: "+fps);
            fps = 0;
            fpsTimer = now;
        }
        
        if(now - jarTimer >= 5000) {
            jarTimer = now;
            Net.Http http = new Net.Http("http://192.168.1.39:7777/jar"+jarTime) {
                @Override
                public void onComplete() {
                    if(this.bytes != null) {
                        try {
                            /*
                            DataInputStream in = new DataInputStream(new ByteArrayInputStream(bytes));
                            jarTime = in.readLong();
                            if(in.available() > 0) {
                                System.out.println("--- new jar "+jarTime+" / "+in.available());
                                Platform.reload(bytes, 8, bytes.length - 8);
                                return;
                            }*/
                        } catch(Throwable e){
                            e.printStackTrace();
                        }
                    }
                }
            };
            http.start();
        }
    }

    @Override
    public void render() {
        Stage2D.I.render();

    }

}
