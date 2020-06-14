package com.digitoygames.compiler.model.op;

import com.digitoygames.compiler.model.CP;
import com.digitoygames.compiler.model.Method;
import com.digitoygames.compiler.model.Stack;
import com.digitoygames.compiler.model.StackValue;

public class NewArray extends Op {

    public int index;
    public CP cp;

    static String[] prims = {"Z","C","F","D","B","S","I","J"};
    @Override
    public void execute(Method method, Stack stack) {
        StackValue length = stack.pop();
        StackValue tmp = method.allocTemp("O");

        if(index < 0) {
            code = String.format("%s = alloc_array_%s(vm,%s,0)",tmp.value,prims[-index - 4],length.value);
        } else {
            String ref = "c"+method.declaringClass.aotHash+"_"+index;
            code = String.format("if(!%s) %s=resolve_class_by_index(vm,method->declaringClass,%d);\n",ref,ref,index);
            code += tmp.value+" = alloc_array_O(vm,"+ref+","+length.value+",0);\n";
        }
        //code = tmp.value+"="+code;
        stack.push(tmp);
    }
}
