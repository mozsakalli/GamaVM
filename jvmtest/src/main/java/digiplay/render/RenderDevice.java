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
package digiplay.render;

/**
 *
 * @author mustafa
 */
public class RenderDevice {

    public final static int PM_VIEWPORT = (1 << 0);
    public final static int PM_INDEXBUF = (1 << 1);
    public final static int PM_VERTLAYOUT = (1 << 2);
    public final static int PM_TEXTURES = (1 << 3);
    public final static int PM_SCISSOR = (1 << 4);
    public final static int PM_BLEND = (1 << 5);
    public final static int PM_CULLMODE = (1 << 6);
    public final static int PM_DEPTH_TEST = (1 << 7);
    public final static int PM_BLEND_EQ = (1 << 8);
    public final static int PM_DEPTH_MASK = (1 << 9);

    public final static int BLENDEQ_ADD = 0;
    public final static int BLENDEQ_SUBTRACT = 1;
    public final static int BLENDEQ_REVERSE_SUBTRACT = 2;
    public final static int BLENDEQ_MIN = 3;
    public final static int BLENDEQ_MAX = 4;

    public final static int BLENDFUNC_ZERO = 0;
    public final static int BLENDFUNC_ONE = 1;
    public final static int BLENDFUNC_SRC_COLOR = 2;
    public final static int BLENDFUNC_ONE_MINUS_SRC_COLOR = 3;
    public final static int BLENDFUNC_SRC_ALPHA = 4;
    public final static int BLENDFUNC_ONE_MINUS_SRC_ALPHA = 5;
    public final static int BLENDFUNC_DST_ALPHA = 6;
    public final static int BLENDFUNC_ONE_MINUS_DST_ALPHA = 7;
    public final static int BLENDFUNC_DST_COLOR = 8;
    public final static int BLENDFUNC_ONE_MINUS_DST_COLOR = 9;
    
    public final static int CLEAR_NONE = 0;
    public final static int CLEAR_COLOR = 1;
    public final static int CLEAR_DEPTH = 2;
    public final static int CLEAR_ALL = 3;

    public final static int PRIM_LINES = 0;
    public final static int PRIM_LINESSTRIP = 1;
    public final static int PRIM_TRIANGLES = 2;
    public final static int PRIM_TRISTRIP = 3;
    public final static int PRIM_QUADS = 4;
    
    //viewport
    int vpX, vpY, vpWidth, vpHeight;
    //scissor
    int scX, scY, scWidth, scHeight;

    int pendingMask;

    public void setViewPort(int x, int y, int width, int height) {
        vpX = x;
        vpY = y;
        vpWidth = width;
        vpHeight = height;
        pendingMask |= PM_VIEWPORT;
    }

    public void setScissor(int x, int y, int width, int height) {
        scX = x;
        scY = y;
        scWidth = width;
        scHeight = height;
        pendingMask |= PM_SCISSOR;
    }

}
