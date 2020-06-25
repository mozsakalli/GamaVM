package com.digitoygames.compiler.model.op;

import com.digitoygames.compiler.Util;
import com.digitoygames.compiler.model.Method;
import com.digitoygames.compiler.model.Stack;
import com.digitoygames.compiler.model.StackValue;

public class SetField extends Field {

    @Override
    public void execute(Method method, Stack stack) {
        generate(method);
        String ref = ref(method);
        StackValue tmp = stack.pop();
        if(isStatic) {
            //code +=  "*(("+ Util.getPlatformType(type)+"*)(CLS("+ref+"->declaringClass,global) + "+ref+"->offset)) = "+tmp.value;
            code +=  "*(("+ Util.getPlatformType(type)+"*)("+ref+"->offset)) = "+tmp.value;
        } else {
            StackValue base = stack.pop();
            //if(!base.value.equals("L0")) //dont null check this
            code += String.format("if(!%s) { frame->pc = %d; throw_null(vm); goto __EXCEPTION; }\n", base.value, this.pc);
            code += "*FIELD_PTR_"+type+"("+base.value+","+ref+"->offset) = "+tmp.value;
            //code += "((char*)"+base.value+" + "+ref+"->offset.I) = "+base.value;
        }
        
        /*
        String ref = "f"+method.declaringClass.aotHash+"_"+index;
        StackValue val = stack.pop();
        code = "if(!"+ref+") { //" + cp.getRefName(index) + "\n" +
               "  Object *fld=resolve_field_by_index(vm,method->declaringClass,"+index+");\n"+
               "  "+ref+"=fld->instance;\n"+ 
               "}\n";

        if(isStatic) {
            code += "*(("+Util.getPlatformType(type)+"*)((CLS("+ref+"->declaringClass,global))+"+ref+"->offset)) = ";
            //code += "GLOBAL_PTR("+ref+","+ Util.getPlatformType(type)+")=";
            //code += ref+"->declaringClass->globals["+ref+"->offset]."+type+"=";
        } else {
            StackValue base = stack.pop();
            code += "*FIELD_PTR_"+type+"("+base.value+","+ref+"->offset) = ";
                    //"((char*)"+base.value+" + "+ref+"->offset.I) = ";
        }
        code +=val.value;*/
    }
}
