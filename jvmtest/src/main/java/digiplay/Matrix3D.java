package digiplay;

public class Matrix3D {
    //col x row

    public final static int M00 = 0;
    public final static int M01 = 4;
    public final static int M02 = 8;
    public final static int M03 = 12;
    public final static int M10 = 1;
    public final static int M11 = 5;
    public final static int M12 = 9;
    public final static int M13 = 13;
    public final static int M20 = 2;
    public final static int M21 = 6;
    public final static int M22 = 10;
    public final static int M23 = 14;
    public final static int M30 = 3;
    public final static int M31 = 7;
    public final static int M32 = 11;
    public final static int M33 = 15;

    public float[] raw = new float[16];

    public static Matrix3D IDENTITY = new Matrix3D();
    public static Matrix3D TMP = new Matrix3D();

    public Matrix3D() {
        identity();
    }

    public void identity() {
        raw[M00] = 1;
        raw[M01] = 0;
        raw[M02] = 0;
        raw[M03] = 0;
        raw[M10] = 0;
        raw[M11] = 1;
        raw[M12] = 0;
        raw[M13] = 0;
        raw[M20] = 0;
        raw[M21] = 0;
        raw[M22] = 1;
        raw[M23] = 0;
        raw[M30] = 0;
        raw[M31] = 0;
        raw[M32] = 0;
        raw[M33] = 1;
    }

    /*
        static Quaternion Quat = new Quaternion();
        public void SetRotation(float x, float y, float z, float radians)
        {
            Quat.setFromRadians(x, y, z, radians);
            SetRotation(Quat);
        }

        public void SetEulerAnglesDegree(float x, float y, float z)
        {
            Quat.SetEulerAnglesDegree(x, y, z);
            SetRotation(Quat);
        }
        
        
        public void AppendRotation(float x, float y, float z, float radians)
        {
            TMP.SetRotation(x, y, z, radians);
            multiply(this, TMP, this);
        }
     */
    public void set(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33) {
        raw[M00] = m00;
        raw[M01] = m01;
        raw[M02] = m02;
        raw[M03] = m03;
        raw[M10] = m10;
        raw[M11] = m11;
        raw[M12] = m12;
        raw[M13] = m13;
        raw[M20] = m20;
        raw[M21] = m21;
        raw[M22] = m22;
        raw[M23] = m23;
        raw[M30] = m30;
        raw[M31] = m31;
        raw[M32] = m32;
        raw[M33] = m33;
    }

    public void set2(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33) {
        raw[M00] = m00;
        raw[M10] = m01;
        raw[M20] = m02;
        raw[M30] = m03;
        raw[M01] = m10;
        raw[M11] = m11;
        raw[M21] = m12;
        raw[M31] = m13;
        raw[M02] = m20;
        raw[M12] = m21;
        raw[M22] = m22;
        raw[M32] = m23;
        raw[M03] = m30;
        raw[M13] = m31;
        raw[M23] = m32;
        raw[M33] = m33;
    }

    public void perspective(float near, float far, float fovy, float aspectRatio) {
        identity();
        float l_fd = (float) (1.0f / Math.tan((fovy * (Math.PI / 180)) / 2.0f));
        float l_a1 = (far + near) / (near - far);
        float l_a2 = (2 * far * near) / (near - far);
        raw[M00] = l_fd / aspectRatio;
        raw[M10] = 0;
        raw[M20] = 0;
        raw[M30] = 0;
        raw[M01] = 0;
        raw[M11] = l_fd;
        raw[M21] = 0;
        raw[M31] = 0;
        raw[M02] = 0;
        raw[M12] = 0;
        raw[M22] = l_a1;
        raw[M32] = -1;
        raw[M03] = 0;
        raw[M13] = 0;
        raw[M23] = l_a2;
        raw[M33] = 0;
    }

    public void orthographic(float left, float right, float bottom, float top, float near, float far) {
        identity();
        float x_orth = 2 / (right - left);
        float y_orth = 2 / (top - bottom);
        float z_orth = -2 / (far - near);

        float tx = -(right + left) / (right - left);
        float ty = -(top + bottom) / (top - bottom);
        float tz = -(far + near) / (far - near);

        raw[M00] = x_orth;
        raw[M10] = 0;
        raw[M20] = 0;
        raw[M30] = 0;
        raw[M01] = 0;
        raw[M11] = y_orth;
        raw[M21] = 0;
        raw[M31] = 0;
        raw[M02] = 0;
        raw[M12] = 0;
        raw[M22] = z_orth;
        raw[M32] = 0;
        raw[M03] = tx;
        raw[M13] = ty;
        raw[M23] = tz;
        raw[M33] = 1;
    }

    static float TAN05 = (float) Math.tan(0.5f) * 0.5f;

    public void setup(float x, float y, float width, float height, float camX, float camY) {
        setup(x, y, width, height, camX, camY, false);
    }

    public void setup(float x, float y, float width, float height, float camX, float camY, boolean flipped) {
        identity();

        float stageWidth = width;
        float stageHeight = height;
        float camZ = stageWidth / TAN05;
        float focalLength = camZ < 0 ? -camZ : camZ;
        float offsetX = camX - stageWidth / 2;
        float offsetY = camY - stageHeight / 2;
        float far = focalLength * 20;
        float near = 1;
        float scaleX = stageWidth / width;
        float scaleY = stageHeight / height;
        //if(flipped) scaleY = -scaleY;

        // set up general perspective
        raw[0] = 2 * focalLength / stageWidth;  // 0,0
        raw[5] = 2 * focalLength / stageHeight * (flipped ? 1 : -1); // 1,1  [negative to invert y-axis]
        raw[10] = far / (far - near);            // 2,2
        raw[14] = -far * near / (far - near);     // 2,3
        raw[11] = 1;                             // 3,2

        // now zoom in to visible area
        raw[0] *= scaleX;
        raw[5] *= scaleY;
        raw[8] = scaleX - 1 - 2 * scaleX * (x - offsetX) / stageWidth;
        raw[9] = -scaleY + 1 + 2 * scaleY * (y - offsetY) / stageHeight;

        prependTranslation(
                -stageWidth / 2.0f - offsetX,
                -stageHeight / 2.0f - offsetY,
                focalLength);
    }

    public void prepend(Matrix3D rhs) {
        multiply(this, rhs, this);
    }

    static Matrix3D TRAMAT = new Matrix3D();

    public void prependTranslation(float x, float y, float z) {
        TRAMAT.raw[12] = x;
        TRAMAT.raw[13] = y;
        TRAMAT.raw[14] = z;
        prepend(TRAMAT);
    }

    public void copyFrom2D(Matrix2D src) {
        identity();
        raw[0] = src.m00;
        raw[1] = src.m10;
        raw[4] = src.m01;
        raw[5] = src.m11;
        raw[12] = src.m02;
        raw[13] = src.m12;
    }

    public void copyTo2D(Matrix2D target) {
        target.m00 = raw[0];
        target.m10 = raw[1];
        target.m01 = raw[4];
        target.m11 = raw[5];
        target.m02 = raw[12];
        target.m12 = raw[13];
    }

    static Matrix2D TMP2D = new Matrix2D();

    public Matrix2D to2D() {
        copyTo2D(TMP2D);
        return TMP2D;
    }

    static Matrix3D TMP3D = new Matrix3D();

    public static Matrix3D convertTo3D(Matrix2D matrix) {
        TMP3D.copyFrom2D(matrix);
        return TMP3D;
    }

    //static digiplay.geom.Point3D TRA3D = new digiplay.geom.Point3D();
    public void lookAt(float eyeX, float eyeY, float eyeZ, float atX, float atY, float atZ, float upX, float upY, float upZ) {
        //normalize(eye - at)
        float azX = eyeX - atX;
        float azY = eyeY - atY;
        float azZ = eyeZ - atZ;
        float tmp = 1.0f / (float) Math.sqrt(azX * azX + azY * azY + azZ * azZ);
        azX *= tmp;
        azY *= tmp;
        azZ *= tmp;

        //normalize(cross(up, az))
        float axX = upY * azZ - upZ * azY;
        float axY = upZ * azX - upX * azZ;
        float axZ = upX * azY - upY * azX;
        tmp = (float) Math.sqrt(axX * axX + axY * axY + axZ * axZ);
        if (tmp == 0) {
            axX = azX;
            axY = azY;
            axZ = azZ;
        } else {
            tmp = 1.0f / tmp;
            axX *= tmp;
            axY *= tmp;
            axZ *= tmp;
        }

        //cross(az, ax)
        float ayX = azY * axZ - azZ * axY;
        float ayY = azZ * axX - azX * axZ;
        float ayZ = azX * axY - azY * axX;

        set2(
                axX, ayX, azX, 0,
                axY, ayY, azY, 0,
                axZ, ayZ, azZ, 0,
                0, 0, 0, 1);

        Matrix3D T = TMP;
        T.set2(
                1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                -eyeX, -eyeY, -eyeZ, 1
        );
        Matrix3D.multiply(this, T, this);
    }

    public void compose(float _x, float _y, float _z, float _rx, float _ry, float _rz, float _sx, float _sy, float _sz) {
        _rx = (float) ((_rx / 180f) * Math.PI);
        _ry = (float) ((_ry / 180f) * Math.PI);
        _rz = (float) ((_rz / 180f) * Math.PI);
        float cx = (float) Math.cos(_rx);
        float cy = (float) Math.cos(_ry);
        float cz = (float) Math.cos(_rz);
        float sx = (float) Math.sin(_rx);
        float sy = (float) Math.sin(_ry);
        float sz = (float) Math.sin(_rz);
        float[] ptr = raw;
        ptr[0] = cy * cz * _sx;
        ptr[1] = cy * sz * _sx;
        ptr[2] = -sy * _sx;
        ptr[3] = 0;
        ptr[4] = (sx * sy * cz - cx * sz) * _sy;
        ptr[5] = (sx * sy * sz + cx * cz) * _sy;
        ptr[6] = sx * cy * _sy;
        ptr[7] = 0;
        ptr[8] = (cx * sy * cz + sx * sz) * _sz;
        ptr[9] = (cx * sy * sz - sx * cz) * _sz;
        ptr[10] = cx * cy * _sz;
        ptr[11] = 0;
        ptr[12] = _x;
        ptr[13] = _y;
        ptr[14] = _z;
        ptr[15] = 1;
    }

    public static void multiply(Matrix3D lhs, Matrix3D rhs, Matrix3D result) {
        float m111, m121, m131, m141, m112, m122, m132, m142, m113, m123, m133, m143, m114, m124, m134, m144;
        float[] ptr = rhs.raw;
        m111 = ptr[0];
        m121 = ptr[4];
        m131 = ptr[8];
        m141 = ptr[12];

        m112 = ptr[1];
        m122 = ptr[5];
        m132 = ptr[9];
        m142 = ptr[13];

        m113 = ptr[2];
        m123 = ptr[6];
        m133 = ptr[10];
        m143 = ptr[14];

        m114 = ptr[3];
        m124 = ptr[7];
        m134 = ptr[11];
        m144 = ptr[15];

        float m211, m221, m231, m241, m212, m222, m232, m242, m213, m223, m233, m243, m214, m224, m234, m244;

        ptr = lhs.raw;
        m211 = ptr[0];
        m221 = ptr[4];
        m231 = ptr[8];
        m241 = ptr[12];

        m212 = ptr[1];
        m222 = ptr[5];
        m232 = ptr[9];
        m242 = ptr[13];

        m213 = ptr[2];
        m223 = ptr[6];
        m233 = ptr[10];
        m243 = ptr[14];

        m214 = ptr[3];
        m224 = ptr[7];
        m234 = ptr[11];
        m244 = ptr[15];
        float[] raw = result.raw;
        raw[0] = m111 * m211 + m112 * m221 + m113 * m231 + m114 * m241;
        raw[1] = m111 * m212 + m112 * m222 + m113 * m232 + m114 * m242;
        raw[2] = m111 * m213 + m112 * m223 + m113 * m233 + m114 * m243;
        raw[3] = m111 * m214 + m112 * m224 + m113 * m234 + m114 * m244;

        raw[4] = m121 * m211 + m122 * m221 + m123 * m231 + m124 * m241;
        raw[5] = m121 * m212 + m122 * m222 + m123 * m232 + m124 * m242;
        raw[6] = m121 * m213 + m122 * m223 + m123 * m233 + m124 * m243;
        raw[7] = m121 * m214 + m122 * m224 + m123 * m234 + m124 * m244;

        raw[8] = m131 * m211 + m132 * m221 + m133 * m231 + m134 * m241;
        raw[9] = m131 * m212 + m132 * m222 + m133 * m232 + m134 * m242;
        raw[10] = m131 * m213 + m132 * m223 + m133 * m233 + m134 * m243;
        raw[11] = m131 * m214 + m132 * m224 + m133 * m234 + m134 * m244;

        raw[12] = m141 * m211 + m142 * m221 + m143 * m231 + m144 * m241;
        raw[13] = m141 * m212 + m142 * m222 + m143 * m232 + m144 * m242;
        raw[14] = m141 * m213 + m142 * m223 + m143 * m233 + m144 * m243;
        raw[15] = m141 * m214 + m142 * m224 + m143 * m234 + m144 * m244;

    }

}
