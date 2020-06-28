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
public class Image extends Sprite {
    
    Texture2D texture2D;
    
    String src = "";
    public void setSrc(String src) {
        if(src != null && !src.equals(this.src)) {
            this.src = src;
            texture2D = Texture2D.get(src);
            markContentInvalid();
        }
    }
    
    @Override public void invalidateContent() {
        if(texture2D != null) {
            texture = texture2D.texture;
            if(mesh == null) mesh = new Mesh(Mesh.QUAD, 1);
            mesh.setQuad(0, texture2D.drawX, texture2D.drawY, texture2D.drawWidth, texture2D.drawHeight, 
                    texture2D.u1, texture2D.v1, 
                    texture2D.u2, texture2D.v2, 
                    texture2D.u3, texture2D.v3, 
                    texture2D.u4, texture2D.v4);
            setWidth(texture2D.width);
            setHeight(texture2D.height);
        }
    }
}
