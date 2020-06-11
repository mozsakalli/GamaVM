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
public class GLQuadBatch {
    
    long handle;
    
    public GLQuadBatch(int capacity) {
        handle = create(capacity);
    }
    
    native static long create(int capacity); 
    public native void begin(int width, int height, boolean clear, int clearColor);
    public native void end();
    public native void drawQuadMesh(QuadMesh mesh, Mat2D mat, GLShader2D shader, int color, float alpha, int blendMode, GLTexture texture, int textureMode);

    @Override
    protected native void finalize() throws Throwable;
    
}
