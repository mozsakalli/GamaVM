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
public class GLShader2D {
    long handle;
    
    public GLShader2D(String code) {
        if(code == null) throw new NullPointerException();
        handle = compile(code);
        if(handle <= 0) throw new RuntimeException("Can't compile GLShader2D");
    }
    
    native static long compile(String code);
}
