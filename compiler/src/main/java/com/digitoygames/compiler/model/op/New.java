package com.digitoygames.compiler.model.op;

import com.digitoygames.compiler.model.CP;
import com.digitoygames.compiler.model.Method;
import com.digitoygames.compiler.model.Stack;
import com.digitoygames.compiler.model.StackValue;

public class New extends Op {

    public int index;
    public CP cp;

    @Override
    public void execute(Method method, Stack stack) {
        StackValue tmp = method.allocTemp(type);
        code = String.format("if(!cls%d) cls%d=resolve_class(vm,method->declaringClass->cp[method->declaringClass->cp[%d].index1].value.O,1);\n",index,index,index);
        code += String.format("%s=alloc_object(vm,cls%d)",tmp.value,index);
                //tmp.value+"=new "+cp.getClassName(index);
        stack.push(tmp);
    }
}
