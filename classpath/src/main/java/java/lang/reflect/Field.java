package java.lang.reflect;

public class Field {
    
    int accessFlags;
    Class declaringClass;
    String name;
    String signature;
    int offset;
    Class type;
    
    public String getName() {
        return name;
    }
    
    public Class getType() {
        return type;
    } 
}
