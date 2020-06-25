
import digiplay.Image;
import digiplay.Platform;
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
public class Game implements digiplay.Game {

    @Override
    public void begin() {
        Stage2D.setup(new Point2D(Platform.screenWidth, Platform.screenHeight));
        for(int i=0; i<2000; i++) {
        Image img = new Image();
        img.setX(400);
        img.setY(400);
        img.setScaleY(1);
        img.scaleX(1);
        img.addBehaviour(new BB());
        Stage2D.I.addChild(img);
        }
    }

    long fpsTime;
    int fps;
    
    @Override
    public void update() {
        long now = System.currentTimeMillis();
        if(now - fpsTime <= 1000) fps++; else {
            System.out.println("FPS-X: "+fps);
            fpsTime = now;
            fps = 0;
        }
        Stage2D.I.update();
    }

    @Override
    public void render() {
        Stage2D.I.render();
    }

}
