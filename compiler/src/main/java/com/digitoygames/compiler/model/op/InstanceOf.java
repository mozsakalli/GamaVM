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
        code = tmp.value+"=instanceof("+val.value+","+index+")";
        stack.push(tmp);
    }
}
