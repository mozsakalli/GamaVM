/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package gamavm.apple;

import java.util.HashMap;
import java.util.Map;

/**
 *
 * @author mustafa
 */
public class ObjCClass extends NSObject {
    
    static Map<String, ObjCClass> classes = new HashMap();
    
    public static ObjCClass get(String name) {
        ObjCClass cls = classes.get(name);
        if(cls == null) {
            long handle = ObjC.objc_getClass(name);
            if(handle == 0) throw new RuntimeException("Can't find ObjC class: "+name);
            cls = new ObjCClass();
            cls.handle = handle;
            classes.put(name, cls);
        }
        return cls;
    }
    
    public static ObjCClass register(Class cls) {
        /*
        Class[] interfaces = cls.getInterfaces();
        for(Class intf : interfaces) {
            String protocolName = intf.getSimpleName();
            
        }*/
        return null;
    }
}
