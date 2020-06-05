package digiplay;

/**
 *
 * @author mustafa
 */
public class Camera {

    Matrix3D projectionMatrix = new Matrix3D();
    Matrix3D invertMatrix = new Matrix3D();
    Matrix3D combinedMatrix = new Matrix3D();
    Matrix3D localMatrix = new Matrix3D();

    public float width;
    public float height;
    public boolean isOrtho;
    public float near = 1;
    public float far = 2000;
    public float fov = 20;
    public float YUp = 1;
    float targetX, targetY, targetZ;
    public boolean dirty = true;
    public float x, y, z, rotationX, rotationY, rotationZ, scaleX = 1, scaleY = 1, scaleZ = 1;

    public Camera() {
        //markTransformDirty();
        //target = new Vec3();
    }

    public void setTarget(float x, float y, float z) {
        targetX = x;
        targetY = y;
        targetZ = z;
        dirty = true;
    }

    public Matrix3D getCombinedMatrix() {
        if (dirty) {
            float x = this.x;
            float y = this.y;
            float z = this.z;

            float w = width;
            float h = height;

            if (isOrtho) {
                //if (viewport != null)
                //{
                //    w = viewport.width;
                //    h = viewport.height;
                //}
                x = -x + w / 2;
                y = -y + h / 2;
                z = -z;

                localMatrix.compose(x, y, z,
                        rotationX, rotationY, rotationZ,
                        scaleX, scaleY, scaleZ);
                projectionMatrix.orthographic(0, w, h, 0, -999999, 999999);
            } else {
                localMatrix.lookAt(this.x, this.y, this.z, targetX, targetY, targetZ, 0, YUp, 0);
                projectionMatrix.perspective(near, far, fov, w / h);
            }
            dirty = false;

            Matrix3D.multiply(projectionMatrix, localMatrix, combinedMatrix);
        }

        return combinedMatrix;
    }

    final static float FOV = 20;
    //2 * tan(fov_in_radian / 2) * z = height
    final static float ZDIVISOR = (float) (2f * Math.tan(FOV / 180f * Math.PI / 2f));

    public Matrix3D setupFor2D(float width, float height) {
        //float width = Device.screenWidth;
        //float height = Device.screenHeight;
        //GL.Viewport(0, 0, (int)width, (int)height);
        targetX = x = width / 2;
        targetY = y = height / 2;
        //Camera.z = -height / Z;
        YUp = -1;
        fov = FOV;
        far = 100000;
        z = -height / ZDIVISOR;
        targetZ = 0;
        this.width = width;
        this.height = height;
        dirty = true;
        return getCombinedMatrix();
    }
}
