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

package com.digitoygames.compiler.model.op;

import com.digitoygames.compiler.Util;
import com.digitoygames.compiler.model.CP;
import com.digitoygames.compiler.model.Code;
import com.digitoygames.compiler.model.CodeStream;
import com.digitoygames.compiler.model.Method;
import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author mustafa
 */
public class OpBuilder {
    
    public Method method;
    List<Op> ops = new ArrayList();
    Code code;
    
    public OpBuilder(Method method, Code code) {
        this.method = method;
        this.code = code;
    }
    
    
    static String[] CMP = {"==","!=","<",">=",">","<="};
    static String[] TYPES = {"I","J","F","D","O","V"};
    
    public List<Op> build() throws Exception {
        CodeStream in = code.getCodeStream();
        CP cp = method.declaringClass.cp;
        boolean wide = false;
        
                
        while(in.available() > 0) {
            int pc = in.getPC();
            int op = in.readUnsignedByte(); 
            //System.out.println("op = "+op+" -> "+pc);
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
                case 9: // lconst_0
                case 10: // lconst_1
                    pushConst(op-9,"J", pc);
                    break;
                case 11: // fconst_0
                case 12: // fconst_1
                case 13: // fconst_2
                    pushConst(op-11,"F", pc);
                    break;
                case 14: // dconst_0
                case 15: // dconst_1
                    pushConst(op-14,"D", pc);
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
                case 21: // iload
                    loadLocal( in.readUnsignedIndex( wide ), "I", pc );
                    break;
                case 22: // lload
                    loadLocal( in.readUnsignedIndex( wide ), "J", pc );
                    break;
                case 23: // fload
                    loadLocal( in.readUnsignedIndex( wide ), "F", pc );
                    break;
                case 24: // dload
                    loadLocal( in.readUnsignedIndex( wide ), "D", pc );
                    break;
                case 25: // aload
                    loadLocal( in.readUnsignedIndex( wide ), "O", pc );
                    break;
                case 26: // iload_0
                case 27: // iload_1
                case 28: // iload_2
                case 29: // iload_3
                    loadLocal(op-26, "I", pc);
                    break;
                case 30: // lload_0
                case 31: // lload_1
                case 32: // lload_2
                case 33: // lload_3
                    loadLocal(op-30, "J", pc);
                    break;
                case 34: // fload_0
                case 35: // fload_1
                case 36: // fload_2
                case 37: // fload_3
                    loadLocal(op-34, "F", pc);
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
                    
                case 46: // iaload
                    loadArray("I",pc);
                    break;
                case 47: // laload
                    loadArray("J",pc);
                    break;
                case 48: // faload
                    loadArray("F",pc);
                    break;
                case 49: // daload
                    loadArray("D",pc);
                    break;
                case 50: // aaload
                    loadArray("O",pc);
                    break;
                case 51: // baload
                    loadArray("B",pc);
                    break;
                case 52: // caload
                    loadArray("C",pc);
                    break;
                case 53: // saload
                    loadArray("S",pc);
                    break;

                case 54: // istore
                    storeLocal(in.readUnsignedIndex(wide), "I", pc);
                    break;
                case 55: // lstore
                    storeLocal(in.readUnsignedIndex(wide), "J", pc);
                    break;
                case 56: // fstore
                    storeLocal(in.readUnsignedIndex(wide), "F", pc);
                    break;
                case 57: // dstore
                    storeLocal(in.readUnsignedIndex(wide), "D", pc);
                    break;
                case 58: // astore
                    storeLocal(in.readUnsignedIndex(wide), "O", pc);
                    break;      

                case 59: // istore_0
                case 60: // istore_1
                case 61: // istore_2
                case 62: // istore_3
                    storeLocal(op-59, "I", pc);
                    break;
                case 63: // lstore_0
                case 64: // lstore_1
                case 65: // lstore_2
                case 66: // lstore_3
                    storeLocal(op-63, "J", pc);
                    break;
                case 67: // fstore_0
                case 68: // fstore_1
                case 69: // fstore_2
                case 70: // fstore_3
                    storeLocal(op-67, "F", pc);
                    break;
                case 71: // dstore_0
                case 72: // dstore_1
                case 73: // dstore_2
                case 74: // dstore_3
                    storeLocal(op-71, "D", pc);
                    break;
                case 75: // astore_0
                case 76: // astore_1
                case 77: // astore_2
                case 78: // astore_3
                    storeLocal(op-75, "O", pc);
                    break;
                case 79: // iastore
                    storeArray("I",pc);
                    break;
                case 80: // lastore
                    storeArray("J",pc);
                    break;
                case 81: // fastore
                    storeArray("F",pc);
                    break;
                case 82: // dastore
                    storeArray("D",pc);
                    break;
                case 83: // aastore
                    storeArray("O",pc);
                    break;
                case 84: // bastore
                    storeArray("B",pc);
                    break;
                case 85: // castore
                    storeArray("C",pc);
                    break;
                case 86: // sastore
                    storeArray("S",pc);
                    break;
                case 87: // pop
                case 88: // pop2
                case 89: // dup: duplicate the value on top of the stack
                case 92: // dup2
                case 90: // dup_x1
                case 93: // dup2_x1
                case 91: // dup_x2
                case 94: // dup2_x2
                    StackOp sop = new StackOp();
                    sop.op = op;
                    sop.pc = pc;
                    ops.add(sop);
                    break;

                case 96: // iadd
                case 97: // ladd
                case 98: // fadd
                case 99: // dadd
                    binary("+", TYPES[op-96], pc);
                    break;
                case 100: // isub
                case 101: // lsub
                case 102: // fsub
                case 103: // dsub
                    binary("-", TYPES[op-100], pc);
                    break;
                    
                case 104: // imul;
                case 105: // lmul
                case 106: // fmul
                case 107: // dmul
                    binary("*", TYPES[op-104], pc);
                    break;
                    
                case 108: // idiv
                case 109: // ldiv
                case 110: // fdiv
                case 111: // ddiv
                    binary("/", TYPES[op-108], pc);
                    break;
                    
                case 112: // irem
                case 113: // lrem
                case 114: // frem
                case 115: // drem
                    binary("%", TYPES[op-112], pc);
                    break;
                case 116: // ineg
                case 117: // lneg
                case 118: // fneg
                case 119: // dneg
                    Neg neg = new Neg();
                    neg.type = TYPES[op-116];
                    neg.pc = pc;
                    ops.add(neg);
                    break;

                case 120: // ishl
                    binary("<<", "I", pc);
                    break;
                case 121: // lshl
                    binary("<<", "J", pc);
                    break;
                case 122: // ishr
                    binary(">>", "I", pc);
                    break;
                case 123: // lshr
                    binary(">>", "J", pc);
                    break;
                case 124: // iushr
                    binary(">>>", "I", pc);
                    break;
                case 125: // lushr
                    binary(">>>", "J", pc);
                    break;
                case 126: // iand
                    binary("&", "I", pc);
                    break;
                case 127: // land
                    binary("&", "J", pc);
                    break;
                case 128: // ior
                    binary("|", "I", pc);
                    break;
                case 129: // lor
                    binary("|", "J", pc);
                    break;
                case 130: // ixor
                    binary("^", "I", pc);
                    break;
                case 131: // lxor
                    binary("^", "J", pc);
                    break;                 
                case 132: // iinc
                    iinc(in.readUnsignedIndex(wide),(int)(wide ? in.readShort() : in.readByte()),pc);
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
                case 148: // lcmp
                    cmp("J",pc);
                    break;
                case 149: // fcmpl
                case 150: // fcmpg
                    cmp("F",pc);
                    break;
                case 151: // dcmpl
                case 152: // dcmpg
                    cmp("D",pc);
                    break;
                case 153: // ifeq
                case 154: // ifne
                case 155: // iflt
                case 156: // ifge
                case 157: // ifgt
                case 158: // ifle
                    _if(CMP[op-153], "0", "I", in.readShort(), pc);
                    break;
                    
                case 159: // if_icmpeq
                case 160: // if_icmpne
                case 161: // if_icmplt
                case 162: // if_icmpge
                case 163: // if_icmpgt
                case 164: // if_icmple
                    _if(CMP[op-159], null, "I", in.readShort(), pc);
                    break;

                case 165: // if_acmpeq
                    _if( "==", "NULL", "O", in.readShort(), pc );
                    break;
                case 166: // if_acmpne
                    _if( "!=", "NULL", "O", in.readShort(), pc );
                    break;

                case 167:
                    _goto(in.readShort(), pc);
                    break;

                case 170: // tableswitch
                case 171: // lookupswitch
                    _switch( in, op == 171 , pc);
                    break;

                case 172: // ireturn
                case 173: // lreturn
                case 174: // freturn
                case 175: // dreturn
                case 176: // areturn
                case 177: // return void
                    _return(TYPES[op - 172], pc);
                    break;
                    
                case 178: // getstatic
                    getField(in.readUnsignedShort(), true, pc);
                    break;
                case 179: // putstatic
                    setField(in.readUnsignedShort(), true, pc);
                    break;
                case 180: // getfield
                    getField(in.readUnsignedShort(), false, pc);
                    break;
                case 181: // putfield
                    setField(in.readUnsignedShort(), false, pc);
                    break;                    
                    
                case 182: // invokevirtual
                case 183: // invokespecial, invoke a constructor
                case 184: // invokestatic
                case 185: // invokeinterface
                    invoke(in.readUnsignedShort(), op-182, pc);
                    if(op == 185) {
                        in.read(); // count
                        in.read(); // 0
                    }
                    break;
                    
                case 186: // invokedynamic
                    invokeDynamic(in.readUnsignedShort(),  pc);
                    break;

                case 187: // new
                    _new(in.readUnsignedShort(), pc);
                    break;

                case 188:
                NewArray na = new NewArray();
                    na.index = -in.readByte();
                    na.pc = pc;
                    na.cp = method.declaringClass.cp;
                    na.type = "O";
                    ops.add(na);
                    break;

                case 189: // anewarray
                    NewArray no = new NewArray();
                    no.index = in.readUnsignedShort();
                    no.cp = method.declaringClass.cp;
                    no.pc = pc;
                    no.type = "O";
                    ops.add(no);
                    break;

                case 190: // arraylength
                    arrayLength(pc);
                    break;                    

                case 191: // athrow
                    Throw thr = new Throw();
                    thr.type = "O";
                    thr.pc = pc;
                    ops.add(thr);
                    break;

                case 192: // checkcast
                    CheckCast cc = new CheckCast();
                    cc.index = in.readUnsignedShort();
                    cc.cp = method.declaringClass.cp;
                    cc.pc = pc;
                    cc.type = "I";
                    ops.add(cc);
                    break;

                case 193: // instanceof
                    InstanceOf io = new InstanceOf();
                    io.index = in.readUnsignedShort();
                    io.cp = method.declaringClass.cp;
                    io.pc = pc;
                    io.type = "I";
                    ops.add(io);
                    break;

                case 194: // monitorenter
                case 195: // monitorexit
                    Monitor mon = new Monitor();
                    mon.isEnter = op == 194;
                    mon.pc = pc;
                    ops.add(mon);
                    break;

                case 196:
                    nop(pc);
                    wide = true;
                    continue;

                case 197: // multianewarray
                    MultiANewArray ma = new MultiANewArray();
                    ma.index = in.readUnsignedShort();
                    int count = in.readUnsignedByte();
                    ma.pc = pc;
                    ma.type = "O";
                    ma.cp = method.declaringClass.cp;
                    ops.add(ma);
                    break;

                case 198: // ifnull
                    _if("==", "NULL", "O", in.readShort(), pc);
                    break;
                case 199: // ifnonnull
                    _if("!=", "NULL", "O", in.readShort(), pc);
                    break;

                default:
                    throw new Exception("!!!!!!!!!! op : "+op);
                    //throw new Exception("Unknown op: "+op);
            }
            wide = false;
        }
        return ops;
    }
    
    void pushConst(Object value, String type, int pc) {
        Const c = new Const();
        c.value = value;
        c.type = type;
        c.pc = pc;
        ops.add(c);
    }

    void pushConst(Object value, int pc) {
        String type;
        if(value == null || value.getClass() == String.class) type = "O";
        else if(value instanceof Integer) type = "I";
        else if(value instanceof Double) type = "D";
        else if(value instanceof Long) type = "J";
        else if(value instanceof Float) type="F";
        else throw new RuntimeException("Unknown constant type: "+value.getClass());
        pushConst(value, type, pc);
    }
    
    void storeLocal(int index, String type, int pc) throws Exception {
        StoreLocal l = new StoreLocal();
        l.index = index;
        l.type = type;
        l.pc = pc;
        ops.add(l);
    }
    
    void loadLocal(int index, String type, int pc) throws Exception {
        LoadLocal l = new LoadLocal();
        l.index = index;
        l.type = type;
        l.pc = pc;
        ops.add(l);
    }
    
    void _if(String operand, String right, String type, int delta, int pc) {
        If i = new If();
        i.operand = operand;
        i.right = right;
        i.type = type;
        i.offset = delta;
        i.pc = pc;
        ops.add(i);
    }
    
    void binary(String op, String type, int pc) {
        Binary b = new Binary();
        b.operand = op;
        b.type = type;
        b.pc = pc;
        ops.add(b);
    }
    
    void iinc(int index, int delta, int pc) throws Exception {
        IInc i = new IInc();
        i.index = index;
        i.type = "I";
        i.delta = delta;
        i.pc = pc;
        ops.add(i);
    }
    
    void _goto(int delta, int pc) {
        Goto g = new Goto();
        g.offset = delta;
        g.pc = pc;
        ops.add(g);
    }
    
    void _return(String type, int pc) {
        Return r = new Return();
        r.type = type;
        r.pc = pc;
        ops.add(r);
    }
    
    void convert(String source, String target, int pc) {
        Convert c = new Convert();
        c.sourceType = source;
        c.type = target;
        c.pc = pc;
        ops.add(c);
    }
    
    void invoke(int index, int callType, int pc) {
        Invoke i = new Invoke();
        CP cp = method.declaringClass.cp;
        i.pc = pc;
        i.cp = cp;
        i.index = index;
        i.callType = callType;
        i.type = Util.getReturnType(cp.getRefSignature(index));
        ops.add(i);
    }    

    void invokeDynamic(int index, int pc) {
        System.out.println("InvokeDynamic: "+index);
        InvokeDynamic i = new InvokeDynamic();
        CP cp = method.declaringClass.cp;
        i.pc = pc;
        i.cp = cp;
        i.index = index;
        i.type = Util.getReturnType(cp.getRefSignature(index));
        ops.add(i);
        
    }    
    
    void getField(int index, boolean isStatic, int pc) {
        GetField f = new GetField();
        f.index = index;
        f.cp = method.declaringClass.cp;
        f.isStatic = isStatic;
        f.pc = pc;
        f.type = Util.typeToStack(f.cp.getRefSignature(index));
        ops.add(f);
    }

    void setField(int index, boolean isStatic, int pc) {
        SetField f = new SetField();
        f.index = index;
        f.cp = method.declaringClass.cp;
        f.isStatic = isStatic;
        f.pc = pc;
        f.type = Util.typeToStack(f.cp.getRefSignature(index));
        ops.add(f);
    }

    void arrayLength(int pc) {
        ArrayLength a = new ArrayLength();
        a.pc = pc;
        a.type = "I";
        ops.add(a);
    }
    
    void loadArray(String type, int pc) {
        LoadArray a = new LoadArray();
        a.type = type;
        a.pc = pc;
        ops.add(a);
    }
    
    void storeArray(String type, int pc) {
        StoreArray a = new StoreArray();
        a.type = type;
        a.pc = pc;
        ops.add(a);
    }

    void _new(int index, int pc) {
        New n = new New();
        n.index = index;
        n.pc = pc;
        n.cp = method.declaringClass.cp;
        n.type = "O";
        ops.add(n);
    }

    void cmp(String type, int pc) {
        Cmp c = new Cmp();
        c.pc = pc;
        c.type = type;
        ops.add(c);
    }

    void _switch(CodeStream in, boolean isLookup, int startPosition) throws Exception {
        int padding = (startPosition + 1) % 4;
        if( padding > 0 ) {
            in.skip( 4 - padding );
        }

        int defaultPosition = startPosition + in.readInt();
        int[] keys;
        int[] positions;
        if( isLookup ) { // lookupswitch
            int count = in.readInt();
            keys = new int[count];
            positions = new int[count];
            for( int i = 0; i < count; i++ ) {
                keys[i] = in.readInt();
                positions[i] = startPosition + in.readInt();
            }
        } else {
            int low = in.readInt();
            int high = in.readInt();
            System.out.println(low+" ---> "+high);
            int count = high - low + 1;
            keys = new int[count];
            positions = new int[count];
            for( int i = 0; i < count; i++ ) {
                keys[i] = low + i;
                positions[i] = startPosition + in.readInt();
            }
        }

        Switch s = new Switch();
        s.pc = startPosition;
        s.isLookup = isLookup;
        s.keys = keys;
        s.positions = positions;
        s.defaultPosition = defaultPosition;
        ops.add(s);
    }

    void nop(int pc) {
        Nop n = new Nop();
        n.pc = pc;
        ops.add(n);
    }
}
