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
public class Image2D extends Sprite2D {
    
    QuadMesh quad;
    static GLTexture texture;
    String src;

    public Image2D() {
        markContentInvalid();
        if(texture == null) {
            texture = new GLTexture();
            texture.upload(Platform.readAsset("bunny.png"));
        }
    }
    public String getSrc() { return src; }
    public void setSrc(String src) {
    }

    @Override
    public void invalidateContent() {
        if (quad == null) quad = new QuadMesh(1);
        setWidth(texture.width);
        setHeight(texture.height);
        quad.set(0, 0, 0, texture.width, texture.height, 0, 0, 1, 0, 1, 1, 0, 1);
        /*
        if(texture != null) {
            if (quad == null) quad = new QuadMesh(1);
            setWidth(texture.width);
            setHeight(texture.height);
            quad.set(0, 0, 0, texture.width, texture.height, 0, 0, 1, 0, 1, 1, 0, 1);
        }*/
    }

    @Override
    public void draw() {
        //if(quad != null)
        //    Stage2D.QuadBatch.drawQuadMesh(quad, getWorldMatrix(GLOBAL_FRAME_VERSION), Stage2D.DefaultShader, texture, 0, color, this.worldAlpha, blendMode);
    }
    
    
}
