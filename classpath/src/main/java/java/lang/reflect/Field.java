package java.lang.reflect;

public class Field {
    
    String name;
    String signature;
    Class declaringClass;
    int flags;
    int offset;
    Object constantValue;
    
    public String getName() {
        return name;
    }
    
    public Class getType() {
        return null;
    } 
}
