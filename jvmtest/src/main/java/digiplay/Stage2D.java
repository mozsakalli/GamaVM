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

    public void setup(Point2D size) {
        designSize = size;
        setFlags(Sprite2D.INTERACTIVE | Sprite2D.INTERACTIVE_CHILD | Sprite2D.IN_STAGE);
        resize();
    }

    public void resize() {
        Graphics g = Digiplay.graphics;
        System.out.println(g.getScreenWidth() + "x" + g.getScreenHeight());
        float ww = designSize.x;
        float hh = designSize.y;

        float ratio = hh / ww;

        float w = g.getScreenWidth();
        float h = (int) (w * ratio);
        if (h - 2 > g.getScreenHeight()) {
            h = g.getScreenHeight();
            w = (int) (h / ratio);
            scaleFactor = h / hh;
        } else {
            scaleFactor = w / ww;
        }
        w = scaleFactor * designSize.x;
        h = scaleFactor * designSize.y;

        setScaleX(w / ww);
        setScaleY(h / hh);
        System.out.println("Stage2D::scaleFactor is " + scaleFactor + " resolution: " + g.getScreenWidth() + "x" + g.getScreenHeight());

        setX((g.getScreenWidth() - w) / 2);
        setY((g.getScreenHeight() - h) / 2);

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

    public void render() {

    }

}
