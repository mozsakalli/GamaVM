package java.lang.reflect;

public class Method {
    int accessFlags;
    int nameIndex;
    int signatureIndex;
    int maxStack;
    int maxLocals;
    Class declaringClass;
    String name;
    String signature;
    Object localVarTable;
    int argCount;
    Object argMap;
    int iTableIndex;
    int vTableIndex;
    
    int lineNumberTableSize;
    Object lineNumberTable;
    int catchTableSize;
    Object catchTable;
    
    Object entry;
    
    //interpreter
    Object code;
    int codeSize;
    Object compiled;
    int breakpoint;
    
    public Class getDeclaringClass() {
        return declaringClass;
    }
}
