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
public class SpriteAction {
    Sprite2D parent;
    SpriteAction next;
    int startTime, duration;
    boolean disposed;
    
    public boolean update(int time) { return false; }
    
    public static class AnimPosition extends SpriteAction {
        float fromX, fromY, toX, toY;
        public AnimPosition(float x1, float y1, float x2, float y2, int duration) {
            fromX = x1;
            fromY = y1;
            toX = x2;
            toY = y2;
            this.duration = duration;
        }
        @Override public native boolean update(int time);
    }
    
    public static class AnimRotation extends SpriteAction {
        float fromX, fromY, toX, toY;
        public AnimRotation(float x1, float y1, float x2, float y2, int duration) {
            fromX = x1;
            fromY = y1;
            toX = x2;
            toY = y2;
            this.duration = duration;
        }
        @Override public native boolean update(int time);
    }
    
}
