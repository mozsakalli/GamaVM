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


    public native static long callLong(NSObject target,Selector selector, Object...args);
    public native static double callDouble(NSObject target,Selector selector, Object...args);
    public native static String callString(NSObject target,Selector selector, Object...args);
    public native static <T extends NSObject> T callObject(NSObject target,Selector selector, Class<T> cls, Object...args);
    public native static void callVoid(NSObject target,Selector selector, Object...args);
    
    
}
