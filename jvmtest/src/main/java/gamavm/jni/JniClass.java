
package gamavm.jni;

import java.lang.reflect.Method;
import java.util.HashMap;
import java.util.Map;

/**
 *
 * @author mustafa
 */
public class JniClass extends JniObject {
    
    static Map<String, JniClass> classes = new HashMap();
    public static JniClass get(String name) {
        JniClass cls = classes.get(name);
        if(cls == null) {
            long handle = nativeGet(name);
            if(handle == 0) throw new RuntimeException("Can't find jni class: "+name);
            cls = new JniClass();
            cls.handle = handle;
            classes.put(name, cls);
        }
        return cls;
    }  
    
    public native JniMethod getMethod(Method method);
    
    private native static long nativeGet(String name);

    @Override
    protected void finalize() throws Throwable {
        super.finalize(); 
    }
    
}
