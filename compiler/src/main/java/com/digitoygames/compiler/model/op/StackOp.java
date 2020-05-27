package com.digitoygames.compiler.model.op;

import com.digitoygames.compiler.model.Method;
import com.digitoygames.compiler.model.Stack;
import com.digitoygames.compiler.model.StackValue;

public class StackOp extends Op {

    public int op;

    @Override
    public void execute(Method method, Stack stack) {
        switch (op) {
            case 87: // pop
                stack.pop();
                break;

            case 88: // pop2
                StackValue v1 = stack.pop();
                if(!v1.is2Word()) stack.pop();
                break;

            case 89: // dup: duplicate the value on top of the stack
                v1 = stack.pop();
                stack.push(v1);
                stack.push(v1);
                break;
            case 92: // dup2
                v1 = stack.peek(0);
                if(v1.is2Word()) {
                    stack.push(v1);
                } else {
                    StackValue v2 = stack.peek(1);
                    stack.push(v2);
                    stack.push(v1);
                }
                break;

            case 90: // dup_x1
                v1 = stack.pop();
                StackValue v2 = stack.pop();
                stack.push(v1);
                stack.push(v2);
                stack.push(v1);
                break;

            case 91: // dup_x2
                v1 = stack.pop();
                v2 = stack.pop();
                if(v2.is2Word()) {
                    stack.push(v1);
                    stack.push(v2);
                    stack.push(v1);
                } else {
                    StackValue v3 = stack.pop();
                    stack.push(v1);
                    stack.push(v3);
                    stack.push(v2);
                    stack.push(v1);
                }
                break;
            //case 93: // dup2_x1
            //case 94: // dup2_x2
            //case 95: // swap

            default:
                throw new RuntimeException("Unknown stackop:"+op);
        }
    }
}
