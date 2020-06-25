package com.digitoygames.compiler.model.op;

import com.digitoygames.compiler.Util;
import com.digitoygames.compiler.model.Method;
import com.digitoygames.compiler.model.Stack;
import com.digitoygames.compiler.model.StackValue;

public class GetField extends Field {

    @Override
    public void execute(Method method, Stack stack) {
        String ref = ref(method); //"f"+method.declaringClass.aotHash+"_"+index;
        StackValue tmp = method.allocTemp(type);
        /*
        code = "if(!"+ref+") { //" + cp.getRefClassName(index)+":"+ cp.getRefName(index) + "\n" +
               "  Object *fld=resolve_field_by_index(vm,method->declaringClass,"+index+");\n"+
               "  "+ref+"=fld->instance;\n"+ 
               "}\n";
        */
        generate(method);
        if(isStatic) {
            code += tmp.value+" = ";
            code +=  "*(("+ Util.getPlatformType(type)+"*)("+ref+"->offset))";
            //code +=  "*(("+ Util.getPlatformType(type)+"*)(CLS("+ref+"->declaringClass,global) + "+ref+"->offset))";
        } else {
            StackValue base = stack.pop();
            if(!method.nullCheckedVars.contains(base.value)) {
                code += String.format("if(!%s) { frame->pc = %d; throw_null(vm); goto __EXCEPTION; }\n", base.value, this.pc);
                method.nullCheckedVars.add(base.value);
            }
            code += tmp.value+" = ";
            code += "*FIELD_PTR_"+type+"("+base.value+","+ref+"->offset)";
            //code += "((char*)"+base.value+" + "+ref+"->offset.I) = "+base.value;
        }
        stack.push(tmp);
        method.nullCheckedVars.remove(tmp.value);
    }
}
