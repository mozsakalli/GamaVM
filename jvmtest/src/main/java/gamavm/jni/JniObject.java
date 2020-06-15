
package gamavm.jni;

/**
 *
 * @author mustafa
 */
public class JniObject {
    long handle;

    @Override
    protected native void finalize() throws Throwable;
    
    
}
