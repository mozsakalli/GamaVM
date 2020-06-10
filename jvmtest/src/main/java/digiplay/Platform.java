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
    
    protected Game game;
    /*
    public abstract Graphics getGraphics();
    public abstract Files getFiles();
    */
    
    long lastTime = System.currentTimeMillis();
    boolean initialized;
    public int screenWidth, screenHeight;
            
    private Platform(Game game) {
        this.game = game;
        //Digiplay.graphics = this.graphics = new IosGraphics();
    }
    
    public static void run(Game game) {
        Platform p = new Platform(game);
        Digiplay.platform = p;
        p.run();
    }
    private native void run();
    
    private void resize(int width, int height) {
        try {
            screenWidth = width;
            screenHeight = height;
            /*
            Graphics g = Digiplay.graphics;
            if(g != null) {
                g.resize(width, height, safeLeft, safeTop, safeRight, safeBottom);
            }
            */
            if(!initialized) {
                initialized = true;
                game.begin();
            }
        }catch(Exception e){
            e.printStackTrace();
        }
    }
    
    private void step() {
        long now = System.currentTimeMillis();
        int delta = (int)(now - lastTime);
        lastTime = now;
        try {
            game.update();
            game.render();
        }catch(Exception e){
            e.printStackTrace();
        }
        //System.out.println("Step - "+delta);
        System.gc();
    }
    
    private void pause() {
        
    }
    
    private void resume() {
        
    }
    
}
