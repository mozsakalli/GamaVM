
import digiplay.Mesh;
import digiplay.Sprite;

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
public class My extends Sprite {
    
    public My() {
        mesh = new Mesh(Mesh.POLYGON,0);
        mesh.setPolygon(new float[]{
            0,0,0,
            100,0,0,
            100,100,0
        }, new float[]{
            0,0,0,0,0,0
        }, new int[]{
            0xffffffff,0xffffffff,0xffffffff
        }, new short[]{
            0,1,2
        }, 3);
    }
}
