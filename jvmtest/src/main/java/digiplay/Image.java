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
public class Image extends Sprite2D {
    
    QuadMesh quad;
    GLTexture texture;
    
    float dx = (float)(-3 + Math.random() * 6);
    float dy = (float)(-3 + Math.random() * 6);
    float r = (float)(-5 + Math.random()*10);
    public Image() {
        markContentInvalid();
    }
    
    @Override
    public void invalidateContent() {
        if(quad == null) quad = new QuadMesh(1);
        /*
        GLTexture gl = new GLTexture();
        gl.load("special-offer.png");
        quad.set(0, 0,0,gl);
        texture = gl;
        */
        quad.set(0, 0, 0, 50,50,0,0,0,0,0,0,0,0);
    }

    @Override
    public void draw() {
        if(quad != null)
            Render2D.drawQuadMesh(quad, this.color, this.blendMode);
        
        rotation(rotation()+r);
        float x = this.x();
        x += dx;
        if(x <= 0) {
            x = 0;
            dx = -dx;
        } else if(x >= Digiplay.platform.screenWidth) {
            x = Digiplay.platform.screenWidth;
            dx = -dx;
        }
        x(x);

        float y = this.y();
        y += dy;
        if(y <= 0) {
            y = 0;
            dy = -dy;
        } else if(y >= Digiplay.platform.screenHeight) {
            y = Digiplay.platform.screenHeight;
            dy = -dy;
        }
        y(y);
        
    }

    
    @Override
    public float getNaturalWidth() {
        return 50;//texture != null ? texture.width : 0;
    }

    @Override
    public float getNaturalHeight() {
        return 50;//texture != null ? texture.height : 0;
    }
    
    
    
}
