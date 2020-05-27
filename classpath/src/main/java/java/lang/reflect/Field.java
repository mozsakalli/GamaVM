package java.lang.reflect;

public class Field {
    
    int accessFlags;
    Class declaringClass;
    String name;
    String signature;
    int offset;
    
    public String getName() {
        return name;
    }
}
