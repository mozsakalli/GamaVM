/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package gamavm.jni;

import java.lang.reflect.Method;

/**
 *
 * @author mustafa
 */
public class JniMethod extends JniObject {
    
    Method gamaMethod;
    
    public native Object invoke(Object base, Object...args);
}
