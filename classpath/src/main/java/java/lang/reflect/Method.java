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
    int compiledSize;
    int breakpoint;
    int externalFlags;
    String externalName;
    Object externalData;

    public Class getDeclaringClass() {
        return declaringClass;
    }

    public Class[] getParameterTypes() {
        int count = argCount;
        if ((flags & 0x0008) == 0) {
            count--; //static
        }
        Class[] result = new Class[count];
        int ptr = 1;
        int len = signature.length();
        int index = 0;
        while (ptr < len) {
            char ch = signature.charAt(ptr++);
            if (ch == ')') {
                break;
            }
            switch (ch) {
                case 'B':
                    result[index++] = byte.class;
                    break;
                case 'Z':
                    result[index++] = boolean.class;
                    break;
                case 'C':
                    result[index++] = char.class;
                    break;
                case 'S':
                    result[index++] = short.class;
                    break;
                case 'I':
                    result[index++] = int.class;
                    break;
                case 'F':
                    result[index++] = float.class;
                    break;
                case 'J':
                    result[index++] = long.class;
                    break;
                case 'D':
                    result[index++] = double.class;
                    break;
                case '[': {
                    int start = ptr - 1;
                    while (signature.charAt(ptr) == '[') {
                        ptr++;
                    }
                    if (signature.charAt(ptr) == 'L') {
                        ptr++;
                        while (signature.charAt(ptr) != ';') {
                            ptr++;
                        }
                        ptr++;
                    }

                    result[index++] = Class.forName(signature.substring(start, ptr));
                }
                break;
                case 'L': {
                    int start = ptr++;
                    while (signature.charAt(ptr) != ';') {
                        ptr++;
                    }
                    ptr++;
                    result[index++] = Class.forName(signature.substring(start, ptr));
                }
                break;
            }
        }
        return result;
    }

    public String getName() {
        return name;
    }

    public native Object invoke(Object instance, Object... arguments) throws InvocationTargetException, IllegalAccessException;

}
