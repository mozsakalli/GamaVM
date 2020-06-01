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
public class Matrix2D {

    int modifyCounter, cacheVersion;
    public float m00;
    public float m10;
    public float m01;
    public float m11;
    public float m02;
    public float m12;

    private float _cx;
    private float _cy;
    private float _sx;
    private float _sy;

    public Matrix2D() {
        identity();
    }
    public void set(float m00, float m10, float m01, float m11, float m02, float m12) {
        this.m00 = m00;
        this.m01 = m01;
        this.m02 = m02;
        this.m10 = m10;
        this.m11 = m11;
        this.m12 = m12;
    }

    public void copyFrom(Matrix2D s) {
        this.m00 = s.m00;
        this.m01 = s.m01;
        this.m02 = s.m02;
        this.m10 = s.m10;
        this.m11 = s.m11;
        this.m12 = s.m12;
    }

    /**
     * Sets this matrix to the identity matrix.
     */
    public void identity() {
        set(1, 0, 0, 1, 0, 0);
        this._cx = 1; // cos rotation + skewY;
        this._sx = 0; // sin rotation + skewY;
        this._cy = 0; // cos rotation + Math.PI/2 - skewX;
        this._sy = 1; // sin rotation + Math.PI/2 - skewX;     
        modifyCounter++;
    }

    public void updateRotAndSkew(float rotation, float skewX, float skewY) {
        rotation = (float) (rotation / 180.0f * Math.PI);
        skewX = (float) (skewX / 180.0f * Math.PI);
        skewY = (float) (skewY / 180.0f * Math.PI);
        this._cx = (float) Math.cos(rotation + skewY);
        this._sx = (float) Math.sin(rotation + skewY);
        this._cy = (float) -Math.sin(rotation - skewX); // cos, added PI/2
        this._sy = (float) Math.cos(rotation - skewX); // sin, added PI/2
    }

    public void compose(float x, float y, float scaleX, float scaleY, float pivotX, float pivotY) {
        float a = this._cx * scaleX;
        float b = this._sx * scaleX;
        float c = this._cy * scaleY;
        float d = this._sy * scaleY;

        this.m02 = x - ((pivotX * a) + (pivotY * c)); //tx
        this.m12 = y - ((pivotX * b) + (pivotY * d)); //ty
        this.m00 = a;
        this.m10 = b;
        this.m01 = c;
        this.m11 = d;

    }

    public static void multiply(Matrix2D lhs, Matrix2D rhs, Matrix2D result) {
        //local variables are always faster than fields!
        float lhsm00 = lhs.m00;
        float lhsm01 = lhs.m01;
        float lhsm10 = lhs.m10;
        float lhsm11 = lhs.m11;

        float rhsm00 = rhs.m00;
        float rhsm01 = rhs.m01;
        float rhsm02 = rhs.m02;
        float rhsm10 = rhs.m10;
        float rhsm11 = rhs.m11;
        float rhsm12 = rhs.m12;

        // First row
        result.m00 = lhsm00 * rhsm00 + lhsm01 * rhsm10;
        result.m01 = lhsm00 * rhsm01 + lhsm01 * rhsm11;
        result.m02 = lhsm00 * rhsm02 + lhsm01 * rhsm12 + lhs.m02;

        // Second row
        result.m10 = lhsm10 * rhsm00 + lhsm11 * rhsm10;
        result.m11 = lhsm10 * rhsm01 + lhsm11 * rhsm11;
        result.m12 = lhsm10 * rhsm02 + lhsm11 * rhsm12 + lhs.m12;
    }

}
