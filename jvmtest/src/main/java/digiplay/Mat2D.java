package digiplay;

import gamavm.VM;

/**
 *
 * @author mustafa
 */
public class Mat2D {
    long handle;
    
    public Mat2D() {
        handle = create();
    }
    native static long create();
    public native void identity();
    public native void compose(float x, float y, float scaleX, float scaleY, float pivotX, float pivotY, boolean updateRotSkew, float rotation, float skewX, float skewY);

    @Override
    protected void finalize() throws Throwable {
        if(handle != 0)
            VM.freeMem(handle);
    }
    
}
