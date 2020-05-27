package com.digitoygames.compiler.model.op;

import com.digitoygames.compiler.model.CP;
import com.digitoygames.compiler.model.Method;
import com.digitoygames.compiler.model.Stack;
import com.digitoygames.compiler.model.StackValue;

public class MultiANewArray extends Op {

    public int index;
    public int count;
    public CP cp;

    @Override
    public void execute(Method method, Stack stack) {
        StackValue tmp = method.allocTemp(type);
        code = tmp.value+"=MultiNewArray ("+cp.getClassName(index)+")[";
        StackValue[] dims = new StackValue[count];
        for(int i=0; i<count; i++) {
            dims[i] = stack.pop();
            code += dims[i].value+",";
        }
        code += "]";
        stack.push(tmp);
    }
}
