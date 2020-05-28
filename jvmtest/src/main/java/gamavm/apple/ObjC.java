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
public class ObjC {
    
    
    public native static long sel_registerName(String name);
    public native static long objc_getClass(String name);


    public native static Object call(Object target,Selector selector, Object...args);
    
}
