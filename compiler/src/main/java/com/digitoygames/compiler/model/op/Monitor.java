package com.digitoygames.compiler.model.op;

import com.digitoygames.compiler.model.Method;
import com.digitoygames.compiler.model.Stack;

public class Monitor extends Op {

    public boolean isEnter;

    @Override
    public void execute(Method method, Stack stack) {
        stack.pop();
    }
}
