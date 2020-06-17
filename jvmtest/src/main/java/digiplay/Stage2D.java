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
public class Stage2D extends Sprite2D {

    public final static Stage2D I = new Stage2D();
    Point2D designSize;
    float scaleFactor;
    public final static GLQuadBatch QuadBatch = new GLQuadBatch(4096);
    public final static GLShader2D DefaultShader = new GLShader2D("gl_FragColor = texture2D(texture, vUv.xy).xyzw * vColor.xyzw;");
    
    public void setup(Point2D size) {
        designSize = size;
        setFlags(Sprite2D.INTERACTIVE | Sprite2D.INTERACTIVE_CHILD | Sprite2D.IN_STAGE);
        resize();
    }

    public void resize() {
        float ww = designSize.x;
        float hh = designSize.y;

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
        w = scaleFactor * designSize.x;
        h = scaleFactor * designSize.y;

        scaleX(w / ww);
        setScaleY(h / hh);
        System.out.println("Stage2D::scaleFactor is " + scaleFactor + " resolution: " + sw + "x" + sh);

        setX((sw - w) / 2);
        setY((sh - h) / 2);

        setPivotX(0);
        setPivotY(0);

    }


    void invalidateSprite(Sprite2D sprite) {
        sprite.invalidateContentIfRequired();
        Sprite2D ptr = sprite.firstChild;
        while (ptr != null) {
            invalidateSprite(ptr);
            ptr = ptr.next;
        }
    }

    public void update() {
        //ClearBackground = true;
        boolean invalidated = false;
        if (InvalidationCounter != 0) {
            InvalidationCounter = 0;
            invalidateSprite(this);
            if (InvalidationCounter != 0) {
                invalidateSprite(this);
            }
            invalidated = true;
        }
        
        /*
            if (_invokeLaterCount > 0)
            {
                for (int i = 0; i < _invokeLaterCount; i++)
                {
                    _invokeLaterList[i].Invoke();
                    _invokeLaterList[i] = null;
                }
                _invokeLaterCount = 0;
            }*/

        //var currentTime = Platform.GetTimer();
        //updateBehaviours(currentTime, true);
        if (InvalidationCounter != 0) {
            InvalidationCounter = 0;
            invalidateSprite(this);
            if (InvalidationCounter != 0) {
                invalidateSprite(this);
            }
            invalidated = true;
        }
        /*
            if(invalidated && Scene2D.currentScene != null && !Scene2D.currentScene._invalidationCalled)
            {
                Scene2D.currentScene._invalidationCalled = true;
                Scene2D.currentScene.InitCompleted();
            } 
         */
    }

    /*public void renderSprite(Sprite2D sprite) {
        renderSprite(sprite, true);
    }*/
    /*
    public void renderSprite(Sprite2D sprite, boolean drawChildren) {
        if((sprite.flags & VISIBLE) == 0) return;
        float wa = sprite.worldAlpha;
        if(wa <= 0) return;
        //Render2D.setGlobalAlpha(wa);
        //Render2D.setModelMatrix(sprite.getWorldMatrix());
        sprite.draw();
        if(drawChildren && sprite.firstChild != null) sprite.drawChildren();
    }
    */
    public void render() {
        GLOBAL_FRAME_VERSION++;
        QuadBatch.begin(Platform.screenWidth, Platform.screenHeight, true, 0xff000000);
        drawChildren();
        QuadBatch.end();
    }

}
