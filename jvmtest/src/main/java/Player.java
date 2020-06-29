
import digiplay.Game;
import digiplay.Image;
import digiplay.Platform;
import digiplay.Sprite;
import digiplay.Stage;

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
public class Player implements Game {

    long lastCheckTime, jarHash;
    Game currentGame;
    PlayerClassLoader classLoader;
    Sprite s;
    
    @Override
    public void begin() {
        Stage.setup(960, 640);
        for(int i=0; i<2000; i++) {
            Image img = new Image();
            //Sprite s = new Sprite();
            img.setX((float)Math.random()*Stage.I.designWidth/2);
            img.setY((float)Math.random()*Stage.I.designHeight/2);
            img.setSrc("bunny");
            img.setBlendMode(2);
            Stage.I.addChild(img);
            
            img.addBehaviour(new B());
            /*
            s.setWidth(50);
            s.setHeight(50);
            //s.setAlpha((float)Math.random()*.5f+.5f);
            
            Mesh m = new Mesh(Mesh.QUAD, 1);
            m.setQuad(0, 0, 0, 50, 50, 0, 0, 0, 0, 0, 0, 0, 0);
            s.setMesh(m);
            Stage.I.addChild(s);
            this.s = s;*/
        }
    }

    float dx = 1, dy = 1;
    @Override
    public void update() {
        /*
        Sprite ptr = Stage.I.getFirstChild();
        while(ptr != null) {
            ptr.setRotationX(ptr.getRotationX() + 2);
            ptr = ptr.getNext();
        }*/
        Stage.I.update();
        //s.setRotationY(s.getRotationY()+1);
        //s.setRotationX(s.getRotationX()+3);
        /*
        float x = s.getX();
        x += dx;
        if(x >= Stage.I.designWidth) {
            x = Stage.I.designWidth;
            dx = -dx;
        } else if(x < 0) {
            x = 0;
            dx = -dx;
        }
        
        s.setX(x);
        
        float y = s.getY();
        y += dy;
        if(y >= Stage.I.designHeight) {
            y = Stage.I.designHeight;
            dy = -dy;
        } else if(y < 0) {
            y = 0;
            dy = -dy;
        }
        s.setY(y);
        /*
        long now = System.currentTimeMillis();
        if(now - lastCheckTime >= 5000) {
            lastCheckTime = now;
            Net.Http http = new Net.Http("http://192.168.1.60:7777/jar"+jarHash) {
                @Override
                public void onComplete() {
                    if(this.bytes != null) {
                        try {
                            DataInputStream in = new DataInputStream(new ByteArrayInputStream(bytes));
                            jarHash = in.readLong();
                            if(in.available() > 0) {
                                System.out.println("--- new jar "+jarHash+" / "+in.available());
                                classLoader = new PlayerClassLoader(bytes, 8, bytes.length - 8);
                                Class gameClass = classLoader.loadClass("Game");
                                currentGame = (Game)gameClass.newInstance();
                                currentGame.begin();
                            }
                        } catch(Throwable e){
                            e.printStackTrace();
                        }
                    } else System.out.println("Http Failed!");
                }
            };
            http.start();
        }
        
        if(currentGame != null) currentGame.update();*/
        long now = System.currentTimeMillis();
        if(now - fpsTime <= 1000) fps++; else {
            System.out.println("FPS-X: "+fps);
            fpsTime = now;
            fps = 0;
        }
    }

    long fpsTime;
    int fps;
    
    @Override
    public void render() {
        Stage.I.render(Platform.screenWidth, Platform.screenHeight);
    }
}
