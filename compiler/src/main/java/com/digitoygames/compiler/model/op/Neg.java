package com.digitoygames.compiler.model.op;

import com.digitoygames.compiler.model.Method;
import com.digitoygames.compiler.model.Stack;
import com.digitoygames.compiler.model.StackValue;

public class Neg extends Op {

    @Override
    public void execute(Method method, Stack stack) {
        StackValue tmp = method.allocTemp(type);
        code = tmp.value+"=-"+tmp.value;
        stack.push(tmp);
    }
}
