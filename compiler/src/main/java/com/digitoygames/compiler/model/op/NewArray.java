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
            code = String.format("alloc_array_%s(vm,%s,0)",prims[-index - 4],length.value);
        } else {
            code = "=alloc_array_O(vm,"+cp.getClassName(index)+","+length.value+",0)";
        }
        code = tmp.value+"="+code;
        stack.push(tmp);
    }
}
