/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package digiplay;

import gamavm.External;

/**
 *
 * @author mustafa
 */
@External
public class MainActivity {
    
    @External(isField=true) public native static Object deneme();
    public native static byte[] readFile(String path);
    
}
