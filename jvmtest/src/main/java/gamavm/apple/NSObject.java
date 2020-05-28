/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package gamavm.apple;

/**
 *
 * @author mustafa
 */
public class NSObject {
    
    protected long handle;
    
    public long getHandle() {
        return handle;
    }
    
    @Override
    protected void finalize() throws Exception {
        //todo: dealloc
    }
}
