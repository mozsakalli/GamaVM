package digiplay;

/**
 *
 * @author mustafa
 */
public class Shader {
    
    long handle;
    public long attrPos,attrColor;
    long uniProjection;
    
    public Shader(String vertex, String fragment) {
        handle = GL.compileProgram(vertex, fragment);
        if(handle <= 0) throw new RuntimeException("Can't compile shader");
        attrPos = GL.attribLocation(handle, "pos");
        attrColor = GL.attribLocation(handle, "color");
        uniProjection = GL.uniformLocation(handle, "projection");
    }
    
    public void setProjection(Matrix3D matrix) {
        GL.uniformMatrix4f(uniProjection, matrix.raw, false);
    }
    
    public void bind() {
        GL.useProgram(handle);
    }
}
