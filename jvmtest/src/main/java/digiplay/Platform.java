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
public class Platform {
    
    
    protected static Game game;
    
    static long lastTime = System.currentTimeMillis();
    static boolean initialized;
    static public int screenWidth, screenHeight;
    public static int gameTime;   
    
    public static void run(Game game) {
        Platform.game = game;
        run();
    }
    private native static void run();
    
    private static void resize(int width, int height) {
        try {
            screenWidth = width;
            screenHeight = height;
            if(!initialized) {
                initialized = true;
                game.begin();
            }
        }catch(Exception e){
            e.printStackTrace();
        }
    }
    
    private static void step() {
        long now = System.currentTimeMillis();
        int delta = (int)(now - lastTime);
        lastTime = now;
        try {
            for(int i=0; i<completableCount; i++) {
                completables[i].complete();
                completables[i] = null;
            }
            completableCount = 0;
            
            game.update();
            game.render();
        }catch(Throwable e){
            e.printStackTrace();
        }
        System.gc();
    }
 
    static Completable[] completables;
    static int completableCount;
    public static void completeOnGameThread(Completable action) {
        if(action != null) {
            if(completables == null) {
                completables = new Completable[32];
            } else {
                Completable[] tmp = new Completable[completables.length * 2];
                System.arraycopy(completables, 0, tmp, 0, completableCount);
                completables = tmp;
            }
            completables[completableCount++] = action;
        }
    }
}
