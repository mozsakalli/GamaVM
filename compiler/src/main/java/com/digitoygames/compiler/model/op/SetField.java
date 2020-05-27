package com.digitoygames.compiler.model.op;

import com.digitoygames.compiler.Util;
import com.digitoygames.compiler.model.CP;
import com.digitoygames.compiler.model.Method;
import com.digitoygames.compiler.model.Stack;
import com.digitoygames.compiler.model.StackValue;

public class SetField extends Op {
    public int index;
    public CP cp;
    public boolean isStatic;

    @Override
    public void execute(Method method, Stack stack) {
        String ref = "field"+index;
        StackValue val = stack.pop();
        code = "if(!"+ref+") {\n" +
                "  "+ref+"=resolve_field_by_index(vm,method->declaringClass,"+index+");\n"
                +"}\n";

        if(isStatic) {
            code += "GLOBAL_PTR("+ref+","+ Util.getPlatformType(type)+")=";
            //code += ref+"->declaringClass->globals["+ref+"->offset]."+type+"=";
        } else {
            StackValue base = stack.pop();
            code += "((char*)"+base.value+" + "+ref+"->offset.I) = "+base.value;
        }
        code +=val.value;
    }
}
