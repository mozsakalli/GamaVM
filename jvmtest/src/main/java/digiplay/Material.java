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
public class Material {

    int flags;

    public final static int CULL_NONE = 0;
    public final static int CULL_BACK = 1;
    public final static int CULL_FRONT = 2;
    public final static int CULL_BOTH = 3;
    final static int CULL_SHIFT = 0;
    final static int CULL_MASK = 3;

    public final static int POLY_FILL = 0;
    public final static int POLY_LINE = 1;
    final static int POLY_SHIFT = 2;
    final static int POLY_MASK = 1;

    public final static int BLEND_NONE = 0;
    public final static int BLEND_NORMAL = 1;
    public final static int BLEND_ADD = 2;
    final static int BLEND_SHIFT = 3;
    final static int BLEND_MASK = 3;

    public final static int FILTER_LINEAR = 0;
    public final static int FILTER_NEAR = 1;
    final static int FILTER_SHIFT = 5;
    final static int FILTER_MASK = 1;

    public final static int WRAP_CLAMP = 0;
    public final static int WRAP_REPEAT = 1;
    final static int WRAP_SHIFT = 6;
    final static int WRAP_MASK = 1;

    final static int DEPTH_WRITE_SHIFT = 7;
    final static int DEPTH_WRITE_MASK = 1;

    public final static int DEPTH_TEST_NONE = 0;
    public final static int DEPTH_TEST_ALWAYS = 1;
    public final static int DEPTH_TEST_NEVER = 2;
    public final static int DEPTH_TEST_EQ = 3;
    public final static int DEPTH_TEST_NEQ = 4;
    public final static int DEPTH_TEST_GT = 5;
    public final static int DEPTH_TEST_GE = 6;
    public final static int DEPTH_TEST_LT = 7;
    public final static int DEPTH_TEST_LE = 8;
    final static int DEPTH_TEST_SHIFT = 8;
    final static int DEPTH_TEST_MASK = 15;

    final static int COLOR_SHIFT = 12;
    final static int COLOR_MASK = 15;

    public final static int STENCIL_OFF = 0;
    public final static int STENCIL_WRITE = 1;
    public final static int STENCIL_TEST = 2;
    final static int STENCIL_SHIFT = 16;
    final static int STENCIL_MASK = 3;

    public final static int SHADER_NORMAL = 0;
    public final static int SHADER_ALPHATEST = 1;
    final static int SHADER_SHIFT = 18;
    final static int SHADER_MASK = 7;

    public Material setCulling(int cull) {
        flags = (flags & ~CULL_MASK) | (cull & CULL_MASK);
        return this;
    }

    public Material setPolygon(int poly) {
        flags = (flags & ~(POLY_MASK<<POLY_SHIFT)) | ((poly & POLY_MASK) << POLY_SHIFT);
        return this;
    }

    public Material setBlendMode(int mode) {
        flags = (flags & ~(BLEND_MASK<<BLEND_SHIFT)) | ((mode & BLEND_MASK) << BLEND_SHIFT);
        return this;
    }
    
    public Material setFilter(int mode) {
        flags = (flags & ~(FILTER_MASK<<FILTER_SHIFT)) | ((mode & FILTER_MASK) << FILTER_SHIFT);
        return this;
    }
    
    public Material setWrap(int mode) {
        flags = (flags & ~(WRAP_MASK<<WRAP_SHIFT)) | ((mode & WRAP_MASK) << WRAP_SHIFT);
        return this;
    }
    
    public Material setDepthWrite(boolean on) {
        flags = (flags & ~(DEPTH_WRITE_MASK<<DEPTH_WRITE_SHIFT)) | ((on ? 1 : 0) << DEPTH_WRITE_SHIFT);
        return this;
    }

    public Material setDepthTest(int mode) {
        flags = (flags & ~(DEPTH_TEST_MASK<<DEPTH_TEST_SHIFT)) | ((mode & DEPTH_TEST_MASK) << DEPTH_TEST_SHIFT);
        return this;
    }

    public Material setStencil(int mode) {
        flags = (flags & ~(STENCIL_MASK<<STENCIL_SHIFT)) | ((mode & STENCIL_MASK) << STENCIL_SHIFT);
        return this;
    }

    public Material setShader(int mode) {
        flags = (flags & ~(SHADER_MASK<<SHADER_SHIFT)) | ((mode & SHADER_MASK) << SHADER_SHIFT);
        return this;
    }
    
    public Material setColorMask(boolean red, boolean green, boolean blue, boolean alpha) {
        int mode = ((red ? 1 : 0) << 3) | ((green ? 1 : 0) << 2) | ((blue ? 1 : 0) << 1) | (alpha ? 1 : 0);
        flags = (flags & ~(COLOR_MASK<<COLOR_SHIFT)) | ((mode & COLOR_MASK) << COLOR_SHIFT);
        return this;
    }
}
