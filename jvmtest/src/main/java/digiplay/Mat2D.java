/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package digiplay;

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
}
