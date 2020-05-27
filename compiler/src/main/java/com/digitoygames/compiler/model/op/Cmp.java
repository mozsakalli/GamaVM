package com.digitoygames.compiler.model.op;

import com.digitoygames.compiler.model.Method;
import com.digitoygames.compiler.model.Stack;
import com.digitoygames.compiler.model.StackValue;

public class Cmp extends Op {

    @Override
    public void execute(Method method, Stack stack) {
        StackValue v1 = stack.pop();
        StackValue v2 = stack.pop();
        StackValue tmp = method.allocTemp(type);
        code = String.format("%s = %s == %s ? 0 : (%s > %s ? 1 : -1)",tmp.value,v1.value,v2.value,v1.value,v2.value);
        stack.push(tmp);
    }
}
