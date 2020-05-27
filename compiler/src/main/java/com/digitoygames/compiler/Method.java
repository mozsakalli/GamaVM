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

package com.digitoygames.compiler;

import de.inetsoftware.classparser.Code;
import de.inetsoftware.classparser.CodeInputStream;
import de.inetsoftware.classparser.ConstantClass;
import de.inetsoftware.classparser.ConstantPool;
import de.inetsoftware.classparser.ConstantRef;
import de.inetsoftware.classparser.LocalVariable;
import de.inetsoftware.classparser.LocalVariableTable;
import de.inetsoftware.classparser.MethodInfo;
import de.inetsoftware.classparser.TryCatchFinally;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 *
 * @author mustafa
 */
public class Method {
    
    public Cls cls;
    public MethodInfo mi;
    List<Op> ops = new ArrayList();
    LocalVariableTable varTable;
    TryCatchFinally[] exceptionTable;
    public Map<Integer, Integer> localIndexMap = new HashMap();
    public int maxLocals;
    public int maxStack;
    public String signature;
    public String name;
    
    public List<String> args;
    public String returnType;
    
    public Method(Cls cls, MethodInfo mi) throws Exception {
        this.cls = cls;
        this.mi = mi;
        name = mi.getName();
        signature = mi.getType();
        args = Util.parseMethodSignature(signature);
        returnType = signature.substring(signature.indexOf(")")+1);
        if(!mi.isStatic()) {
            args.add(0, "O");
        }
        String str = mi.getType();
        
        if(!mi.isAbstract())
            parse();
    }
    
    static String[] CMP = {"==","!=","<",">=",">","<="};
    static String[] TYPES = {"I","J","F","D","Ljava/lang/Object;","V"};
    
    boolean isCatchHandler(int pos) {
        for(TryCatchFinally t : exceptionTable) {
            if(t.getHandler() == pos) return true;
        }
        return false;
    }
    
    boolean isTryStart(int pos) {
        for(TryCatchFinally t : exceptionTable) {
            if(t.getStart() == pos) return true;
        }
        return false;
    }

    boolean isTryEnd(int pos) {
        for(TryCatchFinally t : exceptionTable) {
            if(t.getEnd() == pos) return true;
        }
        return false;
    }
    
    public String getMangled() {
        return Util.esc(cls.name+"_"+name+signature);
    }
    
    void parse() throws Exception {
        Code code = mi.getCode();
        maxStack = code.getMaxStack();
        varTable = code.getLocalVariableTable();
        //Arrays.sort(varTable.getTable(), (v1,v2) -> v1.getIndex() - v2.getIndex());
        for(int i=0; i<varTable.getTable().length; i++) {
            LocalVariable lv = varTable.getTable()[i];
            localIndexMap.put(lv.getIndex(), i);
        }
        maxLocals = varTable.getTable().length;
        
        exceptionTable = code.getExceptionTable();
        ConstantPool cp = code.getConstantPool();
        CodeInputStream bc = code.getByteCode();
        boolean wide = false;
        
        while(bc.available() > 0) {
            int pc = bc.getCodePosition();
            int line = bc.getLineNumber();
            int op = bc.readUnsignedByte();
            switch(op) {
                case 0: //nop
                    break;
                case 1: // null
                    addConst(null,null,pc,line);
                    break;
                    
                case 2: // iconst_m1
                case 3: // iconst_0
                case 4: // iconst_1
                case 5: // iconst_2
                case 6: // iconst_3
                case 7: // iconst_4
                case 8: // iconst_5
                    addConst(op-3,"I", pc, line);
                    break;
                    
                case 9: // lconst_0
                case 10: // lconst_1
                    addConst(Long.valueOf(op-9),"J", pc, line);
                    break;
                case 11: // fconst_0
                case 12: // fconst_1
                case 13: // fconst_2
                    addConst(Float.valueOf(op-11),"F", pc, line);
                    break;
                case 14: // dconst_0
                case 15: // dconst_1
                    addConst(Double.valueOf(op-14),"D", pc, line);
                    break;
                    
                case 16: // bipush
                    addConst(bc.readByte(),"I", pc, line);
                    break;
                case 17: // sipush
                    addConst(bc.readShort(),"I", pc, line);
                    break;
                    
                case 18: // ldc
                    addConst( cp.get( bc.readUnsignedByte() ), pc, line);
                    break;

                case 19: // ldc_w
                case 20: // ldc2_w
                    addConst( cp.get( bc.readUnsignedShort() ), pc, line);
                    break;
                    
                case 21: // iload
                    addLocal(bc.readUnsignedIndex(wide), false, "I", pc, line);
                    break;
                case 22: // lload
                    addLocal(bc.readUnsignedIndex(wide), false, "J", pc, line);
                    break;
                case 23: // fload
                    addLocal(bc.readUnsignedIndex(wide), false, "F", pc, line);
                    break;
                case 24: // dload
                    addLocal(bc.readUnsignedIndex(wide), false, "D", pc, line);
                    break;
                case 25: // aload
                    addLocal(bc.readUnsignedIndex(wide), false, "O", pc, line);
                    break;
                    
                case 26: // iload_0
                case 27: // iload_1
                case 28: // iload_2
                case 29: // iload_3
                    addLocal(op-26, false, "I", pc, line);
                    break;
                    
                case 30: // lload_0
                case 31: // lload_1
                case 32: // lload_2
                case 33: // lload_3
                    addLocal(op-30, false, "J", pc, line);
                    break;
                case 34: // fload_0
                case 35: // fload_1
                case 36: // fload_2
                case 37: // fload_3
                    addLocal(op-34, false, "F", pc, line);
                    break;
                case 38: // dload_0
                case 39: // dload_1
                case 40: // dload_2
                case 41: // dload_3
                    addLocal(op-38, false, "D", pc, line);
                    break;
                    
                case 42: //aload_0
                case 43: //aload_1
                case 44: //aload_2
                case 45: //aload_3
                    addLocal(op-42, false, "O", pc, line);
                    break;
                    
                case 46: // iaload
                    addArray(false, "I", pc, line);
                    break;
                case 47: // laload
                    addArray(false, "J", pc, line);
                    break;
                case 48: // faload
                    addArray(false, "F", pc, line);
                    break;
                case 49: // daload
                    addArray(false, "D", pc, line);
                    break;
                case 50: // aaload
                    addArray(false, "O", pc, line);
                    break;
                case 51: // baload
                    addArray(false, "B", pc, line);
                    break;
                case 52: // caload
                    addArray(false, "C", pc, line);
                    break;
                case 53: // saload
                    addArray(false, "S", pc, line);
                    break;                    
                    
                case 54: // istore
                    addLocal(bc.readUnsignedIndex(wide), true, "I", pc, line);
                    break;
                case 55: // lstore
                    addLocal(bc.readUnsignedIndex(wide), true, "J", pc, line);
                    break;
                case 56: // fstore
                    addLocal(bc.readUnsignedIndex(wide), true, "F", pc, line);
                    break;
                case 57: // dstore
                    addLocal(bc.readUnsignedIndex(wide), true, "D", pc, line);
                    break;
                case 58: // astore
                    addLocal(bc.readUnsignedIndex(wide), true, "O", pc, line);
                    break;
                    
                case 59: // istore_0
                case 60: // istore_1
                case 61: // istore_2
                case 62: // istore_3
                    addLocal(op-59, true, "I", pc, line);
                    break;

                case 71: // dstore_0
                case 72: // dstore_1
                case 73: // dstore_2
                case 74: // dstore_3
                    addLocal(op-71, true, "D", pc, line);
                    break;
                    
                case 75: // astore_0
                case 76: // astore_1
                case 77: // astore_2
                case 78: // astore_3
                    addLocal(op-75, true, "O", pc, line).isCaught = isCatchHandler(pc);
                    break;

                case 79: // iastore
                    addArray(true, "I", pc, line);
                    break;
                case 80: // lastore
                    addArray(true, "J", pc, line);
                    break;
                case 81: // fastore
                    addArray(true, "F", pc, line);
                    break;
                case 82: // dastore
                    addArray(true, "D", pc, line);
                    break;
                case 83: // aastore
                    addArray(true, "O", pc, line);
                    break;
                case 84: // bastore
                    addArray(true, "B", pc, line);
                    break;
                case 85: // castore
                    addArray(true, "C", pc, line);
                    break;
                case 86: // sastore
                    addArray(true, "S", pc, line);
                    break;                    
                    
                case 87: // pop
                case 88: // pop2
                case 89: // dup: duplicate the value on top of the stack
                case 92: // dup2
                case 90: // dup_x1
                case 91: // dup_x2
                case 93: // dup2_x1
                case 94: // dup2_x2
                case 95: // swap
                    StackOp sop = new StackOp();
                    sop.op = op;
                    sop.pc = pc;
                    sop.line = line;
                    ops.add(sop);
                    break;
                    
                case 96: // iadd
                case 97: // ladd
                case 98: // fadd
                case 99: // dadd
                    addBin("+", TYPES[op-96], pc, line);
                    break;
                    
                case 100: // isub
                case 101: // lsub
                case 102: // fsub
                case 103: // dsub
                    addBin("-", TYPES[op-100], pc, line);
                    break;
                    
                case 104: // imul;
                case 105: // lmul
                case 106: // fmul
                case 107: // dmul
                    addBin("*", TYPES[op-104], pc, line);
                    break;
                    
                case 108: // idiv
                case 109: // ldiv
                case 110: // fdiv
                case 111: // ddiv
                    addBin("/", TYPES[op-108], pc, line);
                    break;
                    
                case 112: // irem
                case 113: // lrem
                case 114: // frem
                case 115: // drem
                    addBin("%", TYPES[op-112], pc, line);
                    break;
                    
                case 120: // ishl
                    addBin("<<", "I", pc, line);
                    break;
                case 121: // lshl
                    addBin("<<", "J", pc, line);
                    break;
                case 122: // ishr
                    addBin(">>", "I", pc, line);
                    break;
                case 123: // lshr
                    addBin(">>", "J", pc, line);
                    break;
                case 124: // iushr
                    addBin(">>>", "I", pc, line);
                    break;
                case 125: // lushr
                    addBin(">>>", "J", pc, line);
                    break;
                case 126: // iand
                    addBin("&", "I", pc, line);
                    break;
                case 127: // land
                    addBin("&", "J", pc, line);
                    break;
                case 128: // ior
                    addBin("|", "I", pc, line);
                    break;
                case 129: // lor
                    addBin("|", "J", pc, line);
                    break;
                case 130: // ixor
                    addBin("^", "I", pc, line);
                    break;
                case 131: // lxor
                    addBin("^", "J", pc, line);
                    break;
                case 132: // iinc
                    addLocal(bc.readUnsignedIndex( wide ), true, "I", pc, line).delta = (int)(wide ? bc.readShort() : bc.readByte());
                    break;
                    
                case 133: // i2l
                    addConvert("I","J",pc,line);
                    break;
                case 134: // i2f
                    addConvert("I","F",pc,line);
                    break;
                case 135: // i2d
                    addConvert("I","D",pc,line);
                    break;
                case 136: // l2i
                    addConvert("J","I",pc,line);
                    break;
                case 137: // l2f
                    addConvert("J","F",pc,line);
                    break;
                case 138: // l2d
                    addConvert("J","D",pc,line);
                    break;
                case 139: // f2i
                    addConvert("F","I",pc,line);
                    break;
                case 140: // f2l
                    addConvert("F","J",pc,line);
                    break;
                case 141: // f2d
                    addConvert("F","D",pc,line);
                    break;
                case 142: // d2i
                    addConvert("D","I",pc,line);
                    break;
                case 143: // d2l
                    addConvert("D","J",pc,line);
                    break;
                case 144: // d2f
                    addConvert("D","F",pc,line);
                    break;
                case 145: // i2b
                    addConvert("I","B",pc,line);
                    break;
                case 146: // i2c
                    addConvert("I","C",pc,line);
                    break;
                case 147: // i2s
                    addConvert("I","S",pc,line);
                    break;    
                    
                case 148: // lcmp
                    addCmp("J", pc, line);
                    break;
                case 149: // fcmpl
                case 150: // fcmpg
                    addCmp("F", pc, line);
                    break;
                case 151: // dcmpl
                case 152: // dcmpg
                    addCmp("D", pc, line);
                    break;
                    
                case 153: // ifeq
                case 154: // ifne
                case 155: // iflt
                case 156: // ifge
                case 157: // ifgt
                case 158: // ifle
                    addIf(CMP[op-153], "0", "I", bc.readShort(), pc, line);
                    break;
                    
                case 159: // if_icmpeq
                case 160: // if_icmpne
                case 161: // if_icmplt
                case 162: // if_icmpge
                case 163: // if_icmpgt
                case 164: // if_icmple
                    addIf(CMP[op-159], null, "I", bc.readShort(), pc, line);
                    break;
                    
                case 165: // if_acmpeq
                    addIf("==", null, "O", bc.readShort(), pc, line);
                    break;
                case 166: // if_acmpeqNE
                    addIf("!=", null, "O", bc.readShort(), pc, line);
                    break;
                case 167:
                    addGoto(bc.readShort(), pc, line);
                    break;
                    
                case 170: // tableswitch
                case 171: // lookupswitch
                    addSwitch( bc, op == 171 );
                    break;
                    
                case 172: // ireturn
                case 173: // lreturn
                case 174: // freturn
                case 175: // dreturn
                case 176: // areturn
                case 177: // return void
                    Ret ret = new Ret();
                    ret.pc = pc;
                    ret.line = line;
                    if(op != 176) ret.type = TYPES[op - 172]; else ret.type = mi.getType();
                    ops.add(ret);
                    break;
                    
                case 178: // getstatic
                case 179: // putstatic
                case 180: // getfield
                case 181: // putfield
                    ConstantRef ref = (ConstantRef)cp.get( bc.readUnsignedShort() );
                    addField(ref, op < 180, op==179 || op==181, pc, line);
                    break;
                    
                case 182: // invokevirtual
                case 183: // invokespecial, invoke a constructor
                case 184: // invokestatic
                case 185: // invokeinterface
                    ref = (ConstantRef)cp.get(bc.readUnsignedShort());
                    addInvoke(ref, op-182, pc, line);
                    break;
                    
                case 187: // new
                    addAlloc(((ConstantClass)cp.get( bc.readUnsignedShort() )).getName(), pc, line);
                    break;
                    
                case 191: // athrow
                    Throw t = new Throw();
                    t.pc = pc;
                    t.line = line;
                    ops.add(t);
                    break;
                    
                case 196:
                    wide = true;
                    continue;
                  
                case 198: // ifnull
                    addIf("==", "null", "O", bc.readShort(), pc, line);
                    break;
                case 199: // ifnonnull
                    addIf("!=", "null", "O", bc.readShort(), pc, line);
                    break;
                    
                default:
                    throw new Exception("Unknown op "+op+" at "+cls.cf.getThisClass().getName()+"::"+mi.getName()+"::"+mi.getSignature());
            }
            wide = false;
        }
    }

    void addConst(Object value, int pc, int line) {
        if(value.getClass() == String.class) {
            addConst(value, "java/lang/String", pc, line);
        } else if(value instanceof Integer) {
            addConst(value, "I", pc, line);
        } else if(value instanceof Double) {
            addConst(value, "D", pc, line);
        } else if(value instanceof Float) {
            addConst(value, "F", pc, line);
        } 
        else throw new RuntimeException("Unknown constant type: "+value.getClass());
    }
    
    void addConst(Object value, String type,int pc, int line) {
        Const c = new Const();
        c.value = value;
        c.line = line;
        c.pc = pc;
        c.type = type;
        ops.add(c);
    }
    
    Local addLocal(int index, boolean isSet, String type, int pc, int line) {
        Local l = new Local();
        if(!localIndexMap.containsKey(index))
            System.out.println("...");
        l.index = localIndexMap.get(index);
        l.set = isSet;
        l.pc = pc;
        l.line = line;
        l.type = type;
        ops.add(l);
        return l;
    }
    
    void addIf(String operand, String right, String type, int offset, int pc, int line) {
        If i = new If();
        i.pc = pc;
        i.line = line;
        i.operand = operand;
        i.right = right;
        i.offset = offset;
        i.type = type;
        ops.add(i);
    }
    
    void addBin(String operand, String type, int pc, int line) {
        Bin b = new Bin();
        b.operand = operand;
        b.type = type;
        b.pc = pc;
        b.line = line;
        ops.add(b);
    }
    
    void addGoto(int offset, int pc, int line) {
        Goto g = new Goto();
        g.pc = pc;
        g.line = line;
        g.offset = offset;
        ops.add(g);
    }
    
    void addConvert(String source, String target, int pc, int line) {
        Convert c = new Convert();
        c.type = target;
        c.source = source;
        c.pc = pc;
        c.line = line;
        ops.add(c);
    }
    
    void addField(ConstantRef ref, boolean isStatic, boolean isSet, int pc, int line) {
        Field f = new Field();
        f.isStatic = isStatic;
        f.set = isSet;
        f.pc = pc;
        f.line = line;
        f.cls = ref.getClassName();
        f.type = ref.getType();
        f.name = ref.getName();
        ops.add(f);
    }
    
    void addAlloc(String cls, int pc, int line) {
        Alloc a = new Alloc();
        a.type = "O";
        a.cls = cls;
        a.pc = pc;
        a.line = line;
        ops.add(a);
    }
    void addInvoke(ConstantRef ref, int type, int pc, int line) {
        Invoke i = new Invoke();
        i.callType = type;
        i.pc = pc;
        i.line = line;
        i.name = ref.getName();
        i.type = ref.getType();
        i.cls = ref.getClassName();
        ops.add(i);
    }
    
    void addCmp(String type, int pc, int line) {
        Cmp c = new Cmp();
        c.type = type;
        c.pc = pc;
        c.line = line;
        ops.add(c);
    }
    
    void addArray(boolean set, String type, int pc, int line) {
        Array a = new Array();
        a.set = true;
        a.type = type;
        a.pc = pc;
        a.line = line;
        ops.add(a);
    }
    
    void addSwitch(CodeInputStream bc, boolean isLookup) throws Exception {
        int lineNumber = bc.getLineNumber();
        int codePos = bc.getCodePosition();
        int startPosition = codePos;
        int padding = startPosition % 4;
        if( padding > 0 ) {
            bc.skip( 4 - padding );
        }
        startPosition--;
        //int switchValuestartPosition = findBlockStartCodePosition( 1 );

        int defaultPosition = startPosition + bc.readInt();
        int[] keys;
        int[] positions;
        int low = 0;
        if( isLookup ) { // lookupswitch
            int count = bc.readInt();
            keys = new int[count];
            positions = new int[count];
            for( int i = 0; i < count; i++ ) {
                keys[i] = bc.readInt();
                positions[i] = startPosition + bc.readInt();
            }
            /*
            int tempI32 = getTempVariable( ValueType.i32, codePos, Integer.MAX_VALUE );
            int block = 0;
            int defaultBlock = -1;
            int currentPos = -1;
            addLoadStoreInstruction( ValueType.i32, false, tempI32, codePos, lineNumber );
            do {
                int nextPos = findNext( currentPos, positions );
                if( nextPos == currentPos ) {
                    break;
                }
                currentPos = nextPos;
                if( defaultBlock < 0 ) {
                    if( defaultPosition <= currentPos ) {
                        defaultBlock = block;
                        if( defaultPosition < currentPos ) {
                            block++;
                        }
                    }
                }
                for( int i = 0; i < positions.length; i++ ) {
                    if( positions[i] == currentPos ) {
                        addLoadStoreInstruction( ValueType.i32, true, tempI32, codePos, lineNumber );
                        addConstInstruction( keys[i], ValueType.i32, codePos, lineNumber );
                        addNumericInstruction( NumericOperator.eq, ValueType.i32, codePos, lineNumber );
                        addBlockInstruction( WasmBlockOperator.BR_IF, block, codePos, lineNumber );
                    }
                }
                block++;
            } while( true );
            if( defaultBlock < 0 ) {
                defaultBlock = block;
            }
            addBlockInstruction( WasmBlockOperator.BR, defaultBlock, codePos, lineNumber );
            */
            //throw new RuntimeException("Switch lookup not supported");
        } else {
            low = bc.readInt();
            int count = bc.readInt() - low + 1;
            positions = new int[count];
            keys = null;
            for( int i = 0; i < count; i++ ) {
                positions[i] = startPosition + bc.readInt();
            }
            //if( low != 0 ) { // the br_table starts ever with the value 0. That we need to subtract the start value if it different
            //    addConstInstruction( low, ValueType.i32, codePos, lineNumber );
            //    addNumericInstruction( NumericOperator.sub, ValueType.i32, codePos, lineNumber );
            //}
        }     
        Switch s = new Switch();
        s.low = low;
        s.keys = keys;
        s.positions = positions;
        s.pc = codePos;
        s.line = lineNumber;
        s.defaultPC = defaultPosition;
        ops.add(s);
    }
    
    public int getOpIndexByPC(int pc) {
        for(int i=0; i<ops.size(); i++)
            if(ops.get(i).pc == pc) return i;
        return -1;
    }
    
    
    
    public static class LocalInfo {
        public String debugName;
        public String name;
        public String type;
        public String debugType;
        public int index;
        public int startPC;
        public int endPC;
        public int startLine;
        public int endLine;        
    }
    
    public List<LocalInfo> locals = new ArrayList();
    public LocalInfo getLocal(int index, String type) {
        for(LocalInfo l : locals) {
            if(l.index == index && Util.typeSameStack(l.type, type)) return l;
        }
        LocalInfo l = new LocalInfo();
        l.index = index;
        l.type = type;
        l.debugType = type;
        l.name = "l"+Util.typeToStack(type)+index;
        for(LocalVariable var : varTable.getTable()) {
            if(var.getIndex() == index) {
                String sign = var.getSignature();
                //Type cs = Type.getType(sign);
                if(Util.typeSameStack(type, sign)) {
                    l.debugName = var.getName();
                    l.startPC = var.getStartPosition();
                    l.endPC = var.getLengthPosition();
                    break;
                }
            }
        }
        locals.add(l);
        return l;
    }
    
    Map<String,Stack.StackElement> allTemps = new HashMap();
    public Stack.StackElement getTemp(String type) {
        for(int i=0; i<99; i++) {
            String t = "t"+Util.typeToStack(type)+i;
            if(!allTemps.containsKey(t)) {
                Stack.StackElement e = new Stack.StackElement();
                e.isTemp = true;
                e.type = type;
                e.value = t;
                allTemps.put(t, e);
                return e;        
            }
        }
        return null;
    }
    
    public List getDependencies() {
        return Collections.EMPTY_LIST;
    }
}
