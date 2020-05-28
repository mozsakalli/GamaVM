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
public class Selector extends NSObject {
    
    final static Map<String, Selector> selectors = new HashMap();
    
    
    public static Selector register(String name) {
        Selector sel = selectors.get(name);
        if(sel == null) {
            sel = new Selector();
            sel.handle = ObjC.sel_registerName(name);
            if(sel.handle == 0) throw new RuntimeException("Can't register selector: "+name);
            selectors.put(name, sel);
        }
        return sel;
    }
    
}
