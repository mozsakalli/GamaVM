package com.digitoygames.compiler.model.op;

import com.digitoygames.compiler.model.CP;
import com.digitoygames.compiler.model.Method;
import com.digitoygames.compiler.model.Stack;
import com.digitoygames.compiler.model.StackValue;
import com.digitoygames.compiler.model.Compiler;

public class New extends Op {

    public int index;
    public CP cp;
    public Compiler compiler;
    
    @Override
    public void execute(Method method, Stack stack) {
        StackValue tmp = method.allocTemp(type);
        String ref = "c"+method.declaringClass.aotHash+"_"+index;
        String clsName =  cp.items[cp.items[index].index1].value.toString();
        int clsIndex = compiler.getStringIndex(clsName);
        code = String.format("AOTCLASS(%s,%d);\n"+
                "%s=alloc_object(vm,%s,0)", ref, clsIndex, tmp.value,ref);
        /*
                String.format("if(!%s) %s=resolve_class_by_index(vm,method->declaringClass,%d);\n",ref,ref,index);
        code += String.format("%s=alloc_object(vm,%s,0)",tmp.value,ref);
                //tmp.value+"=new "+cp.getClassName(index);
        */
        stack.push(tmp);
    }
}
