/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package digiplay;

import gamavm.External;
import gamavm.VM;

/**
 *
 * @author mustafa
 */
@External
public class MainActivity {
    
    public native static byte[] readFile(String path);
 
    @External 
    public native static void readFile(String path, long completable);
    
    public static void readFile(String path, Completable completable) {
        readFile(path, VM.getAddress(completable));
    }
}
