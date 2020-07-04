
import digiplay.Behaviour;
import digiplay.Platform;
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
public class B extends Behaviour {
    float dx = (float)Math.random()*10 - 5;
    float dy = (float)Math.random()*10 - 5;
    float dr = (float)Math.random()*10 - 5;
    
    @Override
    public boolean update(float time) {
        /*
        float x = parent.getX();
        x += dx;
        if(x <= 0) { x = 0; dx = -dx; }
        else if(x >= Stage.I.designWidth) { x = Stage.I.designWidth; dx = -dx;}
        parent.setX(x);
        
        float y = parent.getY();
        y += dy;
        if(y <= 0) { y = 0; dy = -dy; }
        else if(y >= Stage.I.designHeight) { y = Stage.I.designHeight; dy = -dy;}
        parent.setY(y);
        
        parent.setRotation(parent.getRotation()+dr);     
        */
        parent.setRotationY(parent.getRotationY() + 1);
        return true;
    }
}
