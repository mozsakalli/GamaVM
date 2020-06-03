
import digiplay.Game;
import digiplay.Image;
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

    @Override
    public void begin() {
        Stage2D.I.setup(new Point2D(1024,768));
        /*
        Image img = new Image();
        Stage2D.I.addChild(img);
        
        System.out.println("game:begin");
        */
    }

    @Override
    public void update() {
        Stage2D.I.update();
    }

    @Override
    public void render() {
        Stage2D.I.render();
    }

}
