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
public class Stage extends Sprite {
    
    public final static Stage I = new Stage();
    public float designWidth, designHeight, scaleFactor;
    
    public Stage() {
        flags |= IN_STAGE;
        color = 0xFF000000;
    }
    
    public static void setup(float width, float height) {
        I.designWidth = width;
        I.designHeight = height;
        I.resize();
    }
    
    public void resize() {
        float ww = designWidth;
        float hh = designHeight;

        float ratio = hh / ww;

        float sw = Platform.screenWidth;
        float sh = Platform.screenHeight;
        
        float w = sw;
        float h = (int) (w * ratio);
        if (h - 2 > sh) {
            h = sh;
            w = (int) (h / ratio);
            scaleFactor = h / hh;
        } else {
            scaleFactor = w / ww;
        }
        w = scaleFactor * designWidth;
        h = scaleFactor * designHeight;

        setScaleX(w / ww);
        setScaleY(h / hh);
        System.out.println("Stage2D::scaleFactor is " + scaleFactor + " resolution: " + sw + "x" + sh);

        setX((sw - w) / 2);
        setY((sh - h) / 2);

        setPivotX(0);
        setPivotY(0);
        setWidth(designWidth);
        setHeight(designHeight);
    }    
    public native void render(int width, int height);
    
}
