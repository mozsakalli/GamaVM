/*
 * Copyright (C) 2019 Digitoy Games.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.digitoygames.compiler.model;

import com.digitoygames.compiler.SourceWriter;
import com.digitoygames.compiler.Util;
import com.digitoygames.compiler.model.op.Op;
import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author mustafa
 */
public class MethodCompiler {
    
    Method method;
    SourceWriter out;
    Code code;
    List<Op> ops = new ArrayList();
    
    public MethodCompiler(Method method) {
        this.method = method;
    }
    
    static String[] CMP = {"==","!=","<",">=",">","<="};
    static String[] TYPES = {"I","J","F","D","O","V"};
    
    public void compile(SourceWriter out) throws Exception {
        this.out = out;
        code = method.getCode();

        out.println("void %s(VM *vm, Method *method, VAR *args) {",method.getAOTName()).indent()
           .println("Frame *frame = &vm->frames[++vm->fp];")
           .println("frame->method = method;")
           .println("VAR stack[method->maxStack];")
           .println("VAR local[method->maxLocals];")
           .println("frame->stack = &stack[0];")
           .println("frame->local = &local[0];")
           .println("memset(stack, 0, sizeof(stack));")     
           .println("register jint sp = 0;")
           .println("int argCount = method->argCount;")
           .println("if(argCount > 0) {")
           .println("jint *map = method->argMap;")
           .println("for(int i=0; i<argCount; i++) {")
           .println("local[map[i]] = args[i];")
           .println("}")
           .println("}");

        if(code == null) {
            out.undent().println("}");
            return;
        }
        CodeStream in = code.getCodeStream();
        CP cp = method.declaringClass.cp;
        boolean wide = false;
        
                
        while(in.available() > 0) {
            int pc = in.getPC();
            int op = in.readUnsignedByte(); 
            //System.out.println("op = "+op);
            if(op == 196) {
                wide = true;
                continue;
            }
            out.print("PC%d: /*frame->pc=%d;*/ ",pc,pc);
            
            switch(op) {
                case 0: //nop
                    break;
                case 1: // null
                    pushConst(null,"O",pc);
                    break;
                    
                case 2: // iconst_m1
                case 3: // iconst_0
                case 4: // iconst_1
                case 5: // iconst_2
                case 6: // iconst_3
                case 7: // iconst_4
                case 8: // iconst_5
                    pushConst(op-3,"I", pc);
                    break;
                
                case 16: // bipush
                    pushConst(in.readByte(),"I", pc);
                    break;
                case 17: // sipush
                    pushConst(in.readShort(),"I", pc);
                    break;
                    
                case 18: // ldc
                    pushConst( cp.get( in.readUnsignedByte() ), pc);
                    break;
                    
                case 19: // ldc_w
                case 20: // ldc2_w
                    pushConst( cp.get( in.readUnsignedShort() ), pc );
                    break;                    
                    
                case 26: // iload_0
                case 27: // iload_1
                case 28: // iload_2
                case 29: // iload_3
                    loadLocal(op-26, "I", pc);
                    break;
                    
                case 38: // dload_0
                case 39: // dload_1
                case 40: // dload_2
                case 41: // dload_3
                    loadLocal(op-38, "D", pc);
                    break;
                    
                case 42: //aload_0
                case 43: //aload_1
                case 44: //aload_2
                case 45: //aload_3
                    loadLocal(op-42, "O", pc);
                    break;
                    
                case 59: // istore_0
                case 60: // istore_1
                case 61: // istore_2
                case 62: // istore_3
                    storeLocal(op-59, "I", pc);
                    break;
                    
                case 75: // astore_0
                case 76: // astore_1
                case 77: // astore_2
                case 78: // astore_3
                    storeLocal(op-75, "O", pc);
                    break;
                    
                case 96: // iadd
                case 97: // ladd
                case 98: // fadd
                case 99: // dadd
                    binary("+", TYPES[op-96], pc);
                    break;
                 
                case 132: // iinc
                    iinc(in.readUnsignedIndex(wide),(int)(wide ? in.readShort() : in.readByte()));
                    break;
                case 133: // i2l
                    convert("I","J",pc);
                    break;
                case 134: // i2f
                    convert("I","F",pc);
                    break;
                case 135: // i2d
                    convert("I","D",pc);
                    break;
                case 136: // l2i
                    convert("J","I",pc);
                    break;
                case 137: // l2f
                    convert("J","F",pc);
                    break;
                case 138: // l2d
                    convert("J","D",pc);
                    break;
                case 139: // f2i
                    convert("F","I",pc);
                    break;
                case 140: // f2l
                    convert("F","J",pc);
                    break;
                case 141: // f2d
                    convert("F","D",pc);
                    break;
                case 142: // d2i
                    convert("D","I",pc);
                    break;
                case 143: // d2l
                    convert("D","J",pc);
                    break;
                case 144: // d2f
                    convert("D","F",pc);
                    break;
                case 145: // i2b
                    convert("I","B",pc);
                    break;
                case 146: // i2c
                    convert("I","C",pc);
                    break;
                case 147: // i2s
                    convert("I","S",pc);
                    break;  
                    
                case 153: // ifeq
                case 154: // ifne
                case 155: // iflt
                case 156: // ifge
                case 157: // ifgt
                case 158: // ifle
                    ifBranch(CMP[op-153], true, in.readShort(), pc);
                    break;
                    
                case 159: // if_icmpeq
                case 160: // if_icmpne
                case 161: // if_icmplt
                case 162: // if_icmpge
                case 163: // if_icmpgt
                case 164: // if_icmple
                    ifBranch(CMP[op-159], false, in.readShort(), pc);
                    break;
                    
                case 167:
                    _goto(in.readShort(), pc);
                    break;
                    
                case 172: // ireturn
                case 173: // lreturn
                case 174: // freturn
                case 175: // dreturn
                case 176: // areturn
                case 177: // return void
                    _return(TYPES[op - 172]);
                    break;
                    
                case 182: // invokevirtual
                case 183: // invokespecial, invoke a constructor
                case 184: // invokestatic
                case 185: // invokeinterface
                    invoke(in.readUnsignedShort(), op-182, pc);
                    break;
                    
                case 196:
                    wide = true;
                    continue;
                    
                default:
                    out.println("!!!!!!!!!! op : "+op);
                    //throw new Exception("Unknown op: "+op);
            }
            out.ln();
            wide = false;
        }
        out.undent().println("}");
    }
    
    void pushConst(Object value, String type, int pc) {
        out.print("stack[sp++].%s = %s;", type, String.valueOf(value));
    }

    void pushConst(Object value, int pc) {
        String type;
        if(value.getClass() == String.class) type = "O";
        else if(value instanceof Integer) type = "I";
        else if(value instanceof Double) type = "D";
        else if(value instanceof Long) type = "J";
        else throw new RuntimeException("Unknown constant type: "+value.getClass());
        pushConst(value, type, pc);
    }
    
    void storeLocal(int index, String type, int pc) throws Exception {
        out.print("local[%d].%s = stack[--sp].%s;", index, type, type);
    }
    
    void loadLocal(int index, String type, int pc) throws Exception {
        out.print("stack[sp++].%s = local[%d].%s;", type, index, type);
    }
    
    void ifBranch(String op, boolean zero, int delta, int pc) {
        if(zero) {
            out.print("if(stack[--sp].I %s 0) goto ", op);
        } else {
            out.print("sp -= 2; if(stack[sp].I %s stack[sp+1].I) goto ",op);
        }
        out.print("PC%d;",pc+delta);
    }
    
    void binary(String op, String type, int pc) {
        out.print("stack[sp-2].%s = stack[sp-2].%s %s stack[sp-1].%s; sp--;", type, type, op, type);
    }
    
    void iinc(int index, int delta) throws Exception {
        out.print("local[%d].I %s= %d;", index, delta<0?"-":"+", Math.abs(delta));
    }
    
    void _goto(int delta, int pc) {
        out.print("goto PC%d;", pc+delta);
    }
    
    void _return(String type) {
        out.print("vm->fp--;");
        if(!type.equals("V"))
            out.print(" vm->frames[vm->fp].retVal.%s = stack[--sp].%s;",type,type);
        out.print(" return;");
    }
    
    void convert(String source, String target, int pc) {
        out.print("stack[sp-1].%s = stack[sp-1].%s;", target, source);
    }
    
    void invoke(int index, int callType, int pc) {
        CP cp = method.declaringClass.cp;
        String signature = cp.items[cp.items[cp.items[index].index2].index2].value.toString();
        String type = Util.getReturnType(signature);
        out.println("{").indent();
        out
        .println("static Method *invoke%d = NULL;",pc)
        .println("if(!invoke%d) {",pc).indent()
        .println("invoke%d = resolve_method_by_index(method->declaringClass, %d);", pc,index)
        .undent().println("}")
        .println("sp -= invoke%d->argCount;", pc)
        .println("VAR *call_args = &stack[sp];");
        if(!type.equals("V"))
            out.print("stack[sp++].%s = ",type);
        out.println("call_java_%s(vm,invoke%d,call_args);",type,pc);
        out.undent().print("}");
    }
    
}
