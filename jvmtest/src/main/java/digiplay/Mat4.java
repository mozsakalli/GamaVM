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
public class Mat4 {

    public float M00;
    public float M10;
    public float M20;
    public float M30;
    public float M01;
    public float M11;
    public float M21;
    public float M31;
    public float M02;
    public float M12;
    public float M22;
    public float M32;
    public float M03;
    public float M13;
    public float M23;
    public float M33;
    int version, is3d;
    float cx, cy, sx, sy;

    public Mat4() {
        identity();
    }

    public void identity() {
        M00 = 1;
        M01 = 0;
        M02 = 0;
        M03 = 0;
        M10 = 0;
        M11 = 1;
        M12 = 0;
        M13 = 0;
        M20 = 0;
        M21 = 0;
        M22 = 1;
        M23 = 0;
        M30 = 0;
        M31 = 0;
        M32 = 0;
        M33 = 1;
    }

    public native void setup2DProjection(float width, float height);

    //public native void updateRot2D(float r, float sx, float sy);
    //public native void compose2d(float x, float y, float sx, float sy, float r, float px, float py);
}
