package com.digitoygames.compiler.model.op;

import com.digitoygames.compiler.Util;
import com.digitoygames.compiler.model.CP;
import com.digitoygames.compiler.model.Method;
import com.digitoygames.compiler.model.Stack;
import com.digitoygames.compiler.model.StackValue;

public class GetField extends Op {
    public int index;
    public CP cp;
    public boolean isStatic;

    @Override
    public void execute(Method method, Stack stack) {
        String ref = "field"+index;
        StackValue tmp = method.allocTemp(type);
        code = "if(!"+ref+") {\n" +
               "  Object *fld=resolve_field_by_index(vm,method->declaringClass,"+index+");\n"+
               "  "+ref+"=fld->instance;\n"+ 
               "}\n";

        code += tmp.value+"=";
        if(isStatic) {
            code +=  "*(("+ Util.getPlatformType(type)+"*)(CLS("+ref+"->declaringClass,global) + "+ref+"->offset))";
            //code += ref+"->declaringClass->globals["+ref+"->offset]."+type;
        } else {
            StackValue base = stack.pop();
            code += "((char*)"+base.value+" + "+ref+"->offset.I) = "+base.value;
        }
        stack.push(tmp);
    }
}
