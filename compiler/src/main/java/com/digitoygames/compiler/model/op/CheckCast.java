package com.digitoygames.compiler.model.op;

import com.digitoygames.compiler.model.CP;
import com.digitoygames.compiler.model.Method;
import com.digitoygames.compiler.model.Stack;

public class CheckCast extends Op {

    public int index;
    public CP cp;

    @Override
    public void execute(Method method, Stack stack) {
        code = "check_cast("+stack.peek(0).value+","+index+")";
    }
}
