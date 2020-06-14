package com.digitoygames.compiler.model.op;

import com.digitoygames.compiler.model.CP;
import com.digitoygames.compiler.model.Method;
import com.digitoygames.compiler.model.Stack;
import com.digitoygames.compiler.model.StackValue;

public class InstanceOf extends Op {

    public int index;
    public CP cp;

    @Override
    public void execute(Method method, Stack stack) {
        StackValue val = stack.pop();
        StackValue tmp = method.allocTemp(type);
        String ref = "c"+method.declaringClass.aotHash+"_"+index;
        code = String.format("if(!%s) %s=resolve_class_by_index(vm,method->declaringClass,%d);\n",ref,ref,index);
        code += tmp.value+" = check_cast(vm,"+val.value+","+ref+")";
        stack.push(tmp);
    }
}
