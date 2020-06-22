package java.lang.reflect;

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
}
