/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package gamavm;

/**
 *
 * @author mustafa
 */
public @interface External {
    
    public String jni() default "";
    public String objc() default "";
    public boolean isField() default false;
    
}
