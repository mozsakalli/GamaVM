package com.digitoygames.compiler.model.op;

import com.digitoygames.compiler.model.Method;
import com.digitoygames.compiler.model.Stack;
import com.digitoygames.compiler.model.StackValue;

public class Switch extends Op {

    public int[] keys;
    public int[] positions;
    public int defaultPosition;
    public boolean isLookup;

    @Override
    public void execute(Method method, Stack stack) {
        StackValue var = stack.pop();
        code = "switch("+var.value+") {\n";
        for(int i=0; i<keys.length; i++)
            code += "case "+keys[i]+": goto BB"+positions[i]+";\n";
        code += "default: goto BB"+defaultPosition+";\n";
        code += "}";
    }
}
