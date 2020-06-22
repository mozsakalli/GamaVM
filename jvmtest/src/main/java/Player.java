
import digiplay.Game;
import digiplay.Net;
import digiplay.Platform;
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
public class Player implements Game {

    long lastCheckTime, jarHash;
    Game currentGame;
    PlayerClassLoader classLoader;
    
    @Override
    public void begin() {
        System.out.println(Class.class.getName());
    }

    @Override
    public void update() {
        long now = System.currentTimeMillis();
        if(now - lastCheckTime >= 5000) {
            lastCheckTime = now;
            Net.Http http = new Net.Http("http://192.168.1.46:7777/jar"+jarHash) {
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
                            }
                        } catch(Throwable e){
                            e.printStackTrace();
                        }
                    } else System.out.println("Http Failed!");
                }
            };
            http.start();
        }
        
        if(currentGame != null) currentGame.update();
    }

    @Override
    public void render() {
        if(currentGame != null) currentGame.render();
    }

}
