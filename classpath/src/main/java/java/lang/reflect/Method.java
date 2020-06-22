package java.lang.reflect;

import java.util.ArrayList;
import java.util.List;

public class Method {
    String name;
    String signature;
    public Class declaringClass;
    int flags;
    Object argMap;
    int argCount;
    int maxStack;
    int maxLocals;
    int codeSize;
    Object code;
    int lineNumberTableSize;
    Object lineNumberTable;
    int catchTableSize;
    Object catchTable;
    int localVarTableSize;
    Object localVarTable;
    int iTableIndex;
    int vTableIndex;
    Object entry;
    Object compiled;
    int breakpoint;
    int externalFlags;
    String externalName;
    Object externalData;
    
    public Class getDeclaringClass() {
        return declaringClass;
    }
    
    public Class[] getParameterTypes() {
        List<Class> types = new ArrayList();
        int ptr = 1;
        int len = signature.length();
        while(ptr < len) {
            char ch = signature.charAt(ptr++);
            switch(ch) {
                case 'B': types.add(byte.class); break;
                case 'Z': types.add(boolean.class); break;
                case 'C': types.add(char.class); break;
                case 'S': types.add(short.class); break;
                case 'I': types.add(int.class); break;
                case 'F': types.add(float.class); break;
                case 'J': types.add(long.class); break;
                case 'D': types.add(double.class); break;
                case '[': {
                    int start = ptr - 1;
                    while(signature.charAt(ptr) == '[') ptr++;
                    if(signature.charAt(ptr) == 'L') {
                        ptr++;
                        while(signature.charAt(ptr) != ';') ptr++;
                        ptr++;
                    }
                    //ch = signature.charAt(ptr);
                    
                } break;
            }
        }
    }
    
}
