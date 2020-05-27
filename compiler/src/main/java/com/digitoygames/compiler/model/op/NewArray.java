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
            code = "alloc_array_"+prims[-index - 4]+"(vm,"+length.value+")";
        } else {
            code = "=alloc_array_O(vm,"+cp.getClassName(index)+","+length.value+")";
        }
        code = tmp.value+"="+code;
        stack.push(tmp);
    }
}
