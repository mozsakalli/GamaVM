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

import digiplay.render.QuadGeometry;
import digiplay.render.Texture2D;

/**
 *
 * @author mustafa
 */
public class Image extends Sprite2D {
    
    QuadGeometry quad;
    Texture2D texture;
    
    @Override
    public void invalidateContent() {
        if(quad == null) quad = new QuadGeometry(1);
        float x2 = getNaturalWidth();
        float y2 = getNaturalHeight();
        quad.set(0, 0, 0, x2, 0, x2, y2, 0, y2, x, x, y, x, x, x, x, x, x, x, x, x);
    }
    
    
}
