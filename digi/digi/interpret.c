//
//  compiler.c
//  Digiplay
//
//  Created by mustafa on 19.05.2020.
//  Copyright © 2020 mustafa. All rights reserved.
//

#include <stdio.h>
#include "vm.h"
#include "opcodes.h"

#ifdef __ANDROID__
#include <android/log.h>
#define GLOG(...) __android_log_print(ANDROID_LOG_ERROR, "GamaVM", __VA_ARGS__)
#else
#define GLOG(...) printf( __VA_ARGS__)
#endif

enum {
    OP_UNIMPLEMENTED,   //0
    OP_NOP,   //1
    OP_CONST,   //2
    OP_CONST_CLS,   //3
    OP_LOADLOCAL,   //4
    OP_STORELOCAL,   //5
    OP_GOTO,   //6
    OP_IF0,   //7
    OP_IF,   //8
    OP_RETURN,   //9
    OP_BINARY,   //10
    OP_CONVERT,   //11
    OP_IINC,   //12
    OP_STACK,   //13
    OP_INVOKE,   //14
    OP_INVOKEDIRECT,   //15
    OP_INVOKEINTERFACE,   //16
    OP_INVOKEVIRTUAL,   //17
    OP_GETFIELD,   //18
    OP_PUTFIELD,   //19
    OP_IFEQ,   //20
    OP_IFNE,   //21
    OP_IFLT,   //22
    OP_IFGE,   //23
    OP_IFGT,   //24
    OP_IFLE,   //25
    OP_IFICMPEQ,   //26
    OP_IFICMPNE,   //27
    OP_IFICMPLT,   //28
    OP_IFICMPGE,   //29
    OP_IFICMPGT,   //30
    OP_IFICMPLE,   //31
    OP_IFACMPEQ,   //32
    OP_IFACMPNE,   //33
    OP_NEWARRAY,   //34
    OP_NEWARRAYRESOLVED,   //35
    OP_NEW,   //36
    OP_NEWRESOLVED,   //37
    OP_ANEWARRAY,   //38
    OP_ANEWARRAYRESOLVED,   //39
    OP_POP,   //40
    OP_POP2,   //41
    OP_DUP,   //42
    OP_DUPX1,   //43
    OP_GETSTATIC_B,   //44
    OP_GETSTATIC_Z,   //45
    OP_GETSTATIC_C,   //46
    OP_GETSTATIC_S,   //47
    OP_GETSTATIC_I,   //48
    OP_GETSTATIC_F,   //49
    OP_GETSTATIC_J,   //50
    OP_GETSTATIC_D,   //51
    OP_GETSTATIC_O,   //52
    OP_PUTSTATIC_B,   //53
    OP_PUTSTATIC_Z,   //54
    OP_PUTSTATIC_C,   //55
    OP_PUTSTATIC_S,   //56
    OP_PUTSTATIC_I,   //57
    OP_PUTSTATIC_F,   //58
    OP_PUTSTATIC_J,   //59
    OP_PUTSTATIC_D,   //60
    OP_PUTSTATIC_O,   //61
    OP_GETFIELD_B,   //62
    OP_GETFIELD_Z,   //63
    OP_GETFIELD_C,   //64
    OP_GETFIELD_S,   //65
    OP_GETFIELD_I,   //66
    OP_GETFIELD_F,   //67
    OP_GETFIELD_J,   //68
    OP_GETFIELD_D,   //69
    OP_GETFIELD_O,   //70
    OP_PUTFIELD_B,   //71
    OP_PUTFIELD_Z,   //72
    OP_PUTFIELD_C,   //73
    OP_PUTFIELD_S,   //74
    OP_PUTFIELD_I,   //75
    OP_PUTFIELD_F,   //76
    OP_PUTFIELD_J,   //77
    OP_PUTFIELD_D,   //78
    OP_PUTFIELD_O,   //79
    OP_I2L,   //80
    OP_I2F,   //81
    OP_I2D,   //82
    OP_L2I,   //83
    OP_L2F,   //84
    OP_L2D,   //85
    OP_F2I,   //86
    OP_F2L,   //87
    OP_F2D,   //88
    OP_D2I,   //89
    OP_D2L,   //90
    OP_D2F,   //91
    OP_I2B,   //92
    OP_I2C,   //93
    OP_I2S,   //94
    OP_LCMP,   //95
    OP_FCMPL,   //96
    OP_FCMPG,   //97
    OP_DCMPL,   //98
    OP_DCMPG,   //99
    OP_IADD,   //100
    OP_LADD,   //101
    OP_FADD,   //102
    OP_DADD,   //103
    OP_ISUB,   //104
    OP_LSUB,   //105
    OP_FSUB,   //106
    OP_DSUB,   //107
    OP_IMUL,   //108
    OP_LMUL,   //109
    OP_FMUL,   //110
    OP_DMUL,   //111
    OP_IDIV,   //112
    OP_LDIV,   //113
    OP_FDIV,   //114
    OP_DDIV,   //115
    OP_IREM,   //116
    OP_LREM,   //117
    OP_FREM,   //118
    OP_DREM,   //119
    OP_INEG,   //120
    OP_LNEG,   //121
    OP_FNEG,   //122
    OP_DNEG,   //123
    OP_ISHL,   //124
    OP_LSHL,   //125
    OP_ISHR,   //126
    OP_LSHR,   //127
    OP_IUSHR,   //128
    OP_LUSHR,   //129
    OP_IAND,   //130
    OP_LAND,   //131
    OP_IOR,   //132
    OP_LOR,   //133
    OP_IXOR,   //134
    OP_LXOR,   //135
    OP_THROW,   //136
    OP_CHECKCAST,   //137
    OP_CHECKCASTRESOLVED,   //138
    OP_LOADARRAY_I,   //139
    OP_LOADARRAY_J,   //140
    OP_LOADARRAY_F,   //141
    OP_LOADARRAY_D,   //142
    OP_LOADARRAY_O,   //143
    OP_LOADARRAY_B,   //144
    OP_LOADARRAY_C,   //145
    OP_LOADARRAY_S,   //146
    OP_STOREARRAY_I,   //147
    OP_STOREARRAY_J,   //148
    OP_STOREARRAY_F,   //149
    OP_STOREARRAY_D,   //150
    OP_STOREARRAY_O,   //151
    OP_STOREARRAY_B,   //152
    OP_STOREARRAY_C,   //153
    OP_STOREARRAY_S,   //154
    OP_ARRAYLENGTH,   //155
    OP_IFNULL,   //156
    OP_IFNOTNULL,   //157
    OP_MONITORENTER,
    OP_MONITOREXIT,
    OP_TABLE,
    OP_LOOKUP,
    OP_INSTANCEOF,
    OP_INSTANCEOFRESOLVED,
};

typedef struct OPSwitch {
    int def, count, low, high;
    int *keys, *offsets;
} OPSwitch;

typedef struct OP {
    int pc;
    char type;
    int bc;
    int code;
    int index;
    VAR var;
    JINT line;
    void *handler;
    OPSwitch *sw;
} OP;

typedef struct BB {
    int id;
    OP *ops;
    int opCount;
    char stack[16];
    int sp;
    struct BB *src[16];
    int srcCount;
    int processed;
    int isCatchHandler;
} BB;

typedef struct COMPILERCTX {
    Method *method;
    int opCount;
    int opCapacity;
    OP *ops;
    
} COMPILERCTX;

unsigned char* vm_compiler_readu2(unsigned char *bc, JINT *target) {
    Short2Char sc;
    sc.c1 = (unsigned)*bc++;
    sc.c0 = (unsigned)*bc++;
    *target = sc.us;
    return bc;
}
unsigned char* vm_compiler_reads2(unsigned char *bc, JINT *target) {
    Short2Char sc;
    sc.c1 = (unsigned)*bc++;
    sc.c0 = (unsigned)*bc++;
    *target = sc.s;
    return bc;
}
unsigned char* vm_compiler_reads4(unsigned char *bc, JINT *target) {
    Int2Float i2f;
    i2f.c3 = (unsigned char)*bc++;
    i2f.c2 = (unsigned char)*bc++;
    i2f.c1 = (unsigned char)*bc++;
    i2f.c0 = (unsigned char)*bc++;
    *target = i2f.i;
    return bc;
}

int vm_compiler_cp_type(int type) {
    switch(type) {
        case 3: return 'I';
        case 4: return 'F';
        case 5: return 'J';
        case 6: return 'D';
    }
    return 'O';
}

int get_line_number(Method *method, int pc) {
    if(method->lineNumberTable) {
        for(int i=0; i<method->lineNumberTableSize; i++) {
            LineNumberInfo *l = &method->lineNumberTable[i];
            if(pc >= l->pc) {
                if(i == method->lineNumberTableSize - 1 ||
                   pc < method->lineNumberTable[i+1].pc) return l->line;
            }
        }
        /*for(int i=method->lineNumberTableSize - 1; i>=0; i--) {
            LineNumberInfo *l = &method->lineNumberTable[i];
            if(l->pc <= pc)
                return l->line;
        }*/
    }
    return -1;
}

CatchInfo *find_catch_block(VM *vm, Object *omethod, Object *exception, int pc) {
    Method *method = omethod->instance;
    for(int i=0; i<method->catchTableSize; i++) {
        CatchInfo *c = &method->catchTable[i];
        if(pc >= c->start && pc < c->end) {
            if(c->type != 0) {
                Object *caughtClass = resolve_class_by_index(vm, method->declaringClass, c->type);
                if(!caughtClass) {
                    vm->exception = NULL;
                    continue;
                }
                
                if(!check_cast(vm, exception, caughtClass)) continue;
            }
            return c;
        }
    }
    return NULL;
}

void vm_compiler_free_code(Method *m) {
    if(m->compiled) {
        OP *ops = m->compiled;
        for(int i=0; i<m->compiledSize; i++) {
            OPSwitch *s = ops[i].sw;
            if(s) {
                if(s->keys) free(s->keys);
                if(s->offsets) free(s->offsets);
            }
            free(s);
        }
        free(m->compiled);
    }
}
int vm_compiler_method_type(CPItem *cp, int index) {
    Object *str = cp[cp[cp[index].index2].index2].value.O;
    JCHAR *ch = STRCHARS(str);
    while(*ch != ')') ch++;
    ch++;
    return *ch=='L' || *ch=='[' ? 'O' : *ch;
}

int vm_compiler_field_type(CPItem *cp, int index) {
    Object *str = cp[cp[cp[index].index2].index2].value.O;
    char type = STRCHARS(str)[0];
    if(type == '[' || type == 'L') return 'O';
    return type;
}

void vm_compiler_build_ops(COMPILERCTX *ctx) {
    Method *method = ctx->method;
    unsigned char *bc = (unsigned char *)method->code;
    unsigned char *end = bc + method->codeSize;
    int wide = 0;

    const char* TYPE0 = "IJFDOBCS";
    CPItem *item;
    CPItem *cp = CLS(method->declaringClass,cp);
    
    while(bc < end) {
        if(ctx->opCount == ctx->opCapacity) {
            int len = (ctx->opCapacity == 0 ? 16 : ctx->opCapacity * 2);
            OP* tmp = malloc(sizeof(OP) * len);
            memset(tmp, 0, sizeof(OP) * len);
            if(ctx->ops) {
                memcpy(tmp, ctx->ops, sizeof(OP) * ctx->opCount);
                free(ctx->ops);
            }
            ctx->ops = tmp;//(OP*)realloc(ctx->ops, sizeof(OP) * len);
            ctx->opCapacity = len;
        }
        OP* op = &ctx->ops[ctx->opCount++];
        int pc = op->pc = (int)((void*)bc - method->code);
        unsigned char opcode = *bc++;
        //printf("  pc: %d op:0x%x\n", pc,opcode );
        op->bc = opcode;
        op->line = get_line_number(method, pc);
        
        switch(opcode) {
            case op_nop:
                op->code = OP_NOP;
                break;
            case op_aconst_null:
                op->code = OP_CONST;
                op->type = 'O';
                op->var.O = NULL;
                break;
            case op_iconst_m1:
            case op_iconst_0:
            case op_iconst_1:
            case op_iconst_2:
            case op_iconst_3:
            case op_iconst_4:
            case op_iconst_5:
                op->code = OP_CONST;
                op->type = 'I';
                op->var.I = opcode - op_iconst_0;
                break;
                
            case op_lconst_0:
            case op_lconst_1:
                op->code = OP_CONST;
                op->type = 'J';
                op->var.J = opcode - op_lconst_0;
                break;
                
            case op_fconst_0:
            case op_fconst_1:
            case op_fconst_2:
                op->code = OP_CONST;
                op->type = 'F';
                op->var.F = opcode - op_fconst_0;
                break;

            case op_dconst_0:
            case op_dconst_1:
                op->code = OP_CONST;
                op->type = 'D';
                op->var.D = opcode - op_dconst_0;
                break;

            case op_bipush:
                op->code = OP_CONST;
                op->type = 'I';
                op->var.I = (JBYTE)*bc++;
                break;

            case op_sipush:
                op->code = OP_CONST;
                op->type = 'I';
                bc = vm_compiler_reads2(bc, &op->var.I);
                break;

            case op_ldc:
                op->index = *bc++;
                item = &cp[op->index];
                switch(item->type) {
                    case 7: //class constant
                        op->code = OP_CONST_CLS;
                        break;
                        
                    case 8: //string constant
                        op->code = OP_CONST;
                        op->var.O = cp[item->index1].value.O;
                        break;
                        
                    default:
                        op->code = OP_CONST;
                        op->var = item->value;
                        break;
                }
                /*op->code = item->type == 7 ? OP_CONST_CLS : OP_CONST;
                op->var = item->value;
                op->type = vm_compiler_cp_type(item->type);*/
                break;
                
            case op_ldc_w:
            case op_ldc2_w:
                bc = vm_compiler_readu2(bc, &op->index);
                item = &cp[op->index];
                op->code = item->type == 7 ? OP_CONST_CLS : OP_CONST;
                op->var = item->value;
                op->type = vm_compiler_cp_type(item->type);
                break;

            case op_iload_0:
            case op_iload_1:
            case op_iload_2:
            case op_iload_3:
                op->code = OP_LOADLOCAL;
                op->type = 'I';
                op->index = opcode - op_iload_0;
                break;

            case op_lload_0:
            case op_lload_1:
            case op_lload_2:
            case op_lload_3:
                op->code = OP_LOADLOCAL;
                op->type = 'J';
                op->index = opcode - op_lload_0;
                break;

            case op_dload_0:
            case op_dload_1:
            case op_dload_2:
            case op_dload_3:
                op->code = OP_LOADLOCAL;
                op->type = 'D';
                op->index = opcode - op_dload_0;
                break;

            case op_fload_0:
            case op_fload_1:
            case op_fload_2:
            case op_fload_3:
                op->code = OP_LOADLOCAL;
                op->type = 'F';
                op->index = opcode - op_fload_0;
                break;

            case op_aload_0:
            case op_aload_1:
            case op_aload_2:
            case op_aload_3:
                op->code = OP_LOADLOCAL;
                op->type = 'O';
                op->index = opcode - op_aload_0;
                break;

            case op_iload:
            case op_lload:
            case op_fload:
            case op_dload:
            case op_aload:
                if(wide) bc = vm_compiler_readu2(bc, &op->index); else op->index = *bc++;
                op->code = OP_LOADLOCAL;
                op->type = TYPE0[opcode - op_istore];
                break;

            case op_istore_0:
            case op_istore_1:
            case op_istore_2:
            case op_istore_3:
                op->code = OP_STORELOCAL;
                op->type = 'I';
                op->index = opcode - op_istore_0;
                break;

            case op_fstore_0:
            case op_fstore_1:
            case op_fstore_2:
            case op_fstore_3:
                op->code = OP_STORELOCAL;
                op->type = 'F';
                op->index = opcode - op_fstore_0;
                break;

            case op_dstore_0:
            case op_dstore_1:
            case op_dstore_2:
            case op_dstore_3:
                op->code = OP_STORELOCAL;
                op->type = 'D';
                op->index = opcode - op_dstore_0;
                break;

            case op_lstore_0:
            case op_lstore_1:
            case op_lstore_2:
            case op_lstore_3:
                op->code = OP_STORELOCAL;
                op->type = 'J';
                op->index = opcode - op_lstore_0;
                break;

            case op_astore_0:
            case op_astore_1:
            case op_astore_2:
            case op_astore_3:
                op->code = OP_STORELOCAL;
                op->type = 'O';
                op->index = opcode - op_astore_0;
                break;


            case op_istore:
            case op_lstore:
            case op_fstore:
            case op_dstore:
            case op_astore:
                if(wide) bc = vm_compiler_readu2(bc, &op->index); else op->index = *bc++;
                op->code = OP_STORELOCAL;
                op->type = TYPE0[opcode - op_istore];
                break;
                
            case op_ireturn:
            case op_lreturn:
            case op_freturn:
            case op_dreturn:
            case op_areturn:
                op->code = OP_RETURN;
                op->type = TYPE0[opcode - op_ireturn];
                break;
            case op_return:
                op->code = OP_RETURN;
                op->type = 'V';
                break;
                
            case op_pop:
            case op_pop2:
            case op_dup:
            case op_dup_x1:
            case op_dup_x2:
            case op_dup2:
            case op_dup2_x1:
            case op_dup2_x2:
                op->code = OP_STACK;
                break;

            case op_iadd:
            case op_ladd:
            case op_fadd:
            case op_dadd:
                op->code = OP_BINARY;
                op->type = TYPE0[opcode - op_iadd];
                break;

            case op_isub:
            case op_lsub:
            case op_fsub:
            case op_dsub:
                op->code = OP_BINARY;
                op->type = TYPE0[opcode - op_isub];
                break;

            case op_idiv:
            case op_ldiv:
            case op_fdiv:
            case op_ddiv:
                op->code = OP_BINARY;
                op->type = TYPE0[opcode - op_idiv];
                break;

            case op_irem:
            case op_lrem:
            case op_frem:
            case op_drem:
                op->code = OP_BINARY;
                op->type = TYPE0[opcode - op_irem];
                break;

            case op_imul:
            case op_lmul:
            case op_fmul:
            case op_dmul:
                op->code = OP_BINARY;
                op->type = TYPE0[opcode - op_imul];
                break;

            case op_ineg:
            case op_lneg:
            case op_fneg:
            case op_dneg:
                op->code = OP_BINARY;
                op->type = TYPE0[opcode - op_ineg];
                break;

            case op_ishl:
            case op_lshl:
            case op_ishr:
            case op_lshr:
            case op_iushr:
            case op_lushr:
            case op_iand:
            case op_land:
            case op_ior:
            case op_lor:
            case op_ixor:
            case op_lxor:
                op->code = OP_BINARY;
                op->type = TYPE0[(opcode - op_ishl) % 2];
                break;
                
            case op_iinc:
                if(wide) {
                    printf("!!!!!!!!!!!!!!!!!!! Wide iinc not supported\n");
                }
                else {
                    op->code = OP_IINC;
                    op->type = 'I';
                    op->index = (unsigned char)*bc++;
                    op->var.I = (JBYTE)*bc++;
                }
                break;
                
            case op_l2i:
            case op_f2i:
            case op_d2i:
            case op_i2b:
            case op_i2c:
            case op_i2s:
                op->type = 'I';
                op->code = OP_CONVERT;
                break;
            case op_i2l:
            case op_f2l:
            case op_d2l:
                op->type = 'J';
                op->code = OP_CONVERT;
                break;

            case op_i2f:
            case op_l2f:
            case op_d2f:
                op->type = 'F';
                op->code = OP_CONVERT;
                break;

            case op_i2d:
            case op_l2d:
            case op_f2d:
                op->type = 'D';
                op->code = OP_CONVERT;
                break;

            case op_lcmp:
            case op_fcmpl:
            case op_fcmpg:
            case op_dcmpl:
            case op_dcmpg:
                op->type = 'I';
                op->code = OP_LCMP + opcode - op_lcmp;
                break;
                
            case op_ifeq:
            case op_ifne:
            case op_iflt:
            case op_ifge:
            case op_ifgt:
            case op_ifle:
                op->code = OP_IF0;
                op->type = 'I';
                bc = vm_compiler_reads2(bc, &op->index);
                break;

            case op_if_icmpeq:
            case op_if_icmpne:
            case op_if_icmplt:
            case op_if_icmpge:
            case op_if_icmpgt:
            case op_if_icmple:
            case op_if_acmpeq:
            case op_if_acmpne:
                op->code = OP_IF;
                op->type = opcode == op_if_acmpeq || opcode == op_if_acmpne ? 'O' : 'I';
                bc = vm_compiler_reads2(bc, &op->index);
                break;
                
            case op_ifnull:
            case op_ifnonnull:
                op->code = OP_IF0;
                op->type = 'O';
                bc = vm_compiler_reads2(bc, &op->index);
                break;

            case op_getstatic:
            case op_getfield:
                op->code = OP_GETFIELD;
                bc = vm_compiler_readu2(bc, &op->index);
                op->type = vm_compiler_field_type(cp, op->index);
                break;
                
            case op_putstatic:
            case op_putfield:
                op->code = OP_PUTFIELD;
                bc = vm_compiler_readu2(bc, &op->index);
                op->type = vm_compiler_field_type(cp, op->index);
                break;

            case op_new:
                op->code = OP_NEW;
                op->type = 'O';
                bc = vm_compiler_readu2(bc, &op->index);
                break;
            case op_anewarray:
                op->code = OP_ANEWARRAY;
                op->type = 'O';
                bc = vm_compiler_readu2(bc, &op->index);
                break;
            case op_checkcast:
                op->code = OP_CHECKCAST;
                op->type = 'O';
                bc = vm_compiler_readu2(bc, &op->index);
                break;
                
            case op_instanceof:
                op->code = OP_INSTANCEOF;
                op->type = 'I';
                bc = vm_compiler_readu2(bc, &op->index);
                break;

            case op_newarray:
                op->code = OP_NEWARRAY;
                op->type = 'O';
                op->index = *bc++;
                break;
                
            case op_invokevirtual:
            case op_invokespecial:
            case op_invokestatic:
            case op_invokeinterface:
            //case op_invokedynamic:
                op->code = OP_INVOKE;
                bc = vm_compiler_readu2(bc, &op->index);
                op->type = vm_compiler_method_type(cp, op->index);
                if(opcode == op_invokeinterface) bc += 2;
                break;

            case op_goto:
                op->code = OP_GOTO;
                bc = vm_compiler_reads2(bc, &op->index);
                break;
                
            case op_athrow:
                op->code = OP_THROW;
                op->type = 'O';
                break;
                
            case op_iaload:
            case op_laload:
            case op_faload:
            case op_daload:
            case op_aaload:
            case op_baload:
            case op_caload:
            case op_saload:
                op->code = OP_LOADARRAY_I + opcode - op_iaload;
                op->type = TYPE0[opcode - op_iaload];
                break;

            case op_iastore:
            case op_lastore:
            case op_fastore:
            case op_dastore:
            case op_aastore:
            case op_bastore:
            case op_castore:
            case op_sastore:
                op->code = OP_STOREARRAY_I + opcode - op_iastore;
                op->type = TYPE0[opcode - op_iastore];
                break;
                
            case op_arraylength:
                op->code = OP_ARRAYLENGTH;
                op->type = 'I';
                break;
                
            case op_monitorenter:
            case op_monitorexit:
                op->code = opcode - op_monitorenter + OP_MONITORENTER;
                op->type = 'O';
                break;
                
            case op_lookupswitch:
            {
                int padding = ((pc + 1) % 4);
                if(padding > 0) bc += 4 - padding;
                OPSwitch *sw = vm_alloc(sizeof(OPSwitch));
                bc = vm_compiler_reads4(bc, &sw->def);
                bc = vm_compiler_reads4(bc, &sw->count);
                sw->keys = malloc(sizeof(int) * sw->count);
                sw->offsets = malloc(sizeof(int) * sw->count);
                op->code = OP_LOOKUP;
                //OP *keys = (OP*)malloc(sizeof(OP) * (count + 1));
                for(int i=0; i<sw->count; i++) {
                    bc = vm_compiler_reads4(bc, &sw->keys[i]); //key
                    bc = vm_compiler_reads4(bc, &sw->offsets[i]); //offset
                }
                op->sw = sw;
                //keys[count].pc = 0xFFFFFFFF;
                //op->var.O = (Object*)keys;
            }
            break;
            
            case op_tableswitch:
            {
                int padding = ((pc + 1) % 4);
                if(padding > 0) bc += 4 - padding;
                OPSwitch *sw = vm_alloc(sizeof(OPSwitch));
                bc = vm_compiler_reads4(bc, &sw->def);
                bc = vm_compiler_reads4(bc, &sw->low);
                bc = vm_compiler_reads4(bc, &sw->high);
                sw->count = sw->high - sw->low + 1;
                sw->offsets = malloc(sizeof(int) * sw->count);
                op->code = OP_TABLE;
                for(int i=0; i<sw->count; i++) {
                    bc = vm_compiler_reads4(bc, &sw->offsets[i]); //offset
                }
                op->sw = sw;
            }
            break;
            default:
                printf("UNKNOWN op:0x%x / %d\n", opcode, opcode);
                return;

        }
    }
}


int vm_compile_count_args_by_index(Object *cls, int index, int isStatic) {
    CPItem *cp = CLS(cls,cp);
    Object *signature = cp[cp[cp[index].index2].index2].value.O;
    JCHAR *ch = STRCHARS(signature);
    ch++; //(
    int count = 0;
    if(!isStatic) {
        count++;
    }
    while(1) {
        if(*ch == ')') break;
        count++;
        while(*ch == '[') ch++;
        if(*ch == 'L') {
            while(*ch != ';') ch++;
        }
        ch++;
    }
    
    //printf(" --arg-count %s = %d\n", string2c(signature), count);
    return count;
}

void vm_optimize_bb(BB *bb) {

}


void vm_process_bb(Method *method, BB *bb, void **handlers) {
    if(bb->processed) return;
    bb->processed = 1;
    
    if(bb->srcCount > 0) {
        for(int i=0; i<bb->srcCount; i++)
            vm_process_bb(method, bb->src[i], handlers);
        
        BB *src = bb->src[0];
        for(int i=0; i<src->sp; i++) {
            bb->stack[bb->sp++] = src->stack[i];
        }
    }
    
    if(bb->isCatchHandler) bb->stack[bb->sp++] = 'O';
    
    int check = bb->opCount;
    for(int i=0; i<bb->opCount; i++) {
        if(bb->sp < 0) {
            printf("!!!!!!!!!!!!Stack Invalid!!!!!!\n");
            return;
        }
        OP *op = &bb->ops[i];
        op->handler = handlers[OP_UNIMPLEMENTED];
        switch(op->code) {
            case OP_NOP:
                op->handler = handlers[OP_NOP];
                break;
            case OP_CONST:
            case OP_CONST_CLS:
            case OP_LOADLOCAL:
                bb->stack[bb->sp++] = op->type;
                op->handler = handlers[op->code];
                break;
                
            case OP_STORELOCAL:
                bb->sp--;
                op->handler = handlers[op->code];
                break;
                
            case OP_RETURN:
                if(op->type != 'V') bb->sp--;
                op->handler = handlers[OP_RETURN];
                break;
                
            case OP_NEW:
                bb->stack[bb->sp++] = 'O';
                op->handler = handlers[op->code];
                break;
                
            case OP_NEWARRAY:
            case OP_ANEWARRAY:
                bb->stack[bb->sp-1] = 'O';
                op->handler = handlers[op->code];
                break;

            case OP_IF0:
                bb->sp--;
                op->handler = handlers[op->bc >= op_ifnull ? op->bc - op_ifnull + OP_IFNULL : op->bc - op_ifeq + OP_IFEQ];
                break;

            case OP_IF:
                bb->sp -= 2;
                op->handler = handlers[op->bc - op_ifeq + OP_IFEQ];
                break;
                
            case OP_INVOKE:
            {
                int argCount = vm_compile_count_args_by_index(method->declaringClass,op->index,op->bc == op_invokestatic);
                bb->sp -= argCount;
                if(op->type != 'V')
                    bb->stack[bb->sp++] = op->type;
                op->handler = handlers[OP_INVOKE];
            }
                break;
                
            case OP_BINARY:
                if(op->bc < op_ineg || op->bc > op_dneg)
                    bb->stack[--bb->sp] = op->type;
                else bb->stack[bb->sp-1] = op->type;
                op->handler = handlers[op->bc - op_iadd + OP_IADD];
                break;
                
            case OP_IINC:
            case OP_GOTO:
                op->handler = handlers[op->code];
                break;
                
            case OP_STACK:
                switch(op->bc) {
                    case op_pop:
                        op->handler = handlers[OP_POP];
                        bb->sp--;
                        break;
                        
                    case op_dup:
                        op->handler = handlers[OP_DUP];
                        bb->stack[bb->sp] = bb->stack[bb->sp-1];
                        bb->sp++;
                        break;
                        
                    case op_dup_x1:
                    {
                        int v1 = bb->stack[--bb->sp];
                        int v2 = bb->stack[--bb->sp];
                        bb->stack[bb->sp++] = v1;
                        bb->stack[bb->sp++] = v2;
                        bb->stack[bb->sp++] = v1;
                        op->handler = handlers[OP_DUPX1];
                    } break;
                        
                    case op_pop2: {
                        switch(bb->stack[bb->sp-1]) {
                            case 'J':
                            case 'D':
                                op->handler = handlers[OP_POP];
                                bb->sp--;
                                break;
                            default:
                                op->handler = handlers[OP_POP2];
                                bb->sp -= 2;
                                break;
                        }
                    } break;
                    
                    default:
                        printf("Unknown stack operation 0x%x\n", op->bc);
                        return;
                }
                break;
                
            case OP_CONVERT:
                bb->stack[bb->sp-1] = op->type;
                op->handler = handlers[OP_I2L + op->bc - op_i2l];
                break;
                
            case OP_LCMP:
            case OP_FCMPL:
            case OP_FCMPG:
            case OP_DCMPL:
            case OP_DCMPG:
                bb->sp--;
                bb->stack[bb->sp - 1] = 'I';
                op->handler = handlers[op->code];
                break;

            case OP_PUTFIELD:
                bb->sp--;
                if(op->bc == op_putfield) bb->sp--;
                op->handler = handlers[OP_PUTFIELD];
                break;
                
            case OP_GETFIELD:
                if(op->bc == op_getfield) bb->sp--;
                bb->stack[bb->sp++] = op->type;
                op->handler = handlers[OP_GETFIELD];
                break;
                
            case OP_THROW:
                bb->sp--;
                op->handler = handlers[OP_THROW];
                break;
                
            case OP_CHECKCAST:
                op->handler = handlers[OP_CHECKCAST];
                break;
                
            case OP_INSTANCEOF:
                op->handler = handlers[OP_INSTANCEOF];
                break;
                
            case OP_LOADARRAY_I:
            case OP_LOADARRAY_J:
            case OP_LOADARRAY_F:
            case OP_LOADARRAY_D:
            case OP_LOADARRAY_O:
            case OP_LOADARRAY_B:
            case OP_LOADARRAY_C:
            case OP_LOADARRAY_S:
                op->handler = handlers[op->code];
                bb->sp--;
                bb->stack[bb->sp-1] = op->code >= OP_LOADARRAY_B ? 'I' : op->type;
                break;
            case OP_STOREARRAY_I:
            case OP_STOREARRAY_J:
            case OP_STOREARRAY_F:
            case OP_STOREARRAY_D:
            case OP_STOREARRAY_O:
            case OP_STOREARRAY_B:
            case OP_STOREARRAY_C:
            case OP_STOREARRAY_S:
                op->handler = handlers[op->code];
                bb->sp -= 3;
                break;
                
            case OP_ARRAYLENGTH:
                op->handler = handlers[OP_ARRAYLENGTH];
                bb->stack[bb->sp - 1] = 'I';
                break;
                
            case OP_MONITORENTER:
            case OP_MONITOREXIT:
                bb->sp--;
                op->handler = handlers[op->code];
                break;
                
            case OP_LOOKUP:
                bb->sp--;
                op->handler = handlers[OP_LOOKUP];
                break;
                
            case OP_TABLE:
                bb->sp--;
                op->handler = handlers[OP_TABLE];
                break;

            default:
                printf("UNKNOWN CODE: %d bc:0x%x", op->code, op->bc);
                printf("   %s",string_to_ascii(CLS(method->declaringClass,name)));
                printf(":%s",string_to_ascii(method->name));
                printf(":%s",string_to_ascii(method->signature));
                printf(" at line=%d pc=%d\n",get_line_number(method, op->pc), op->pc);
                return;
        }
        //printf("    %d:%d OP: 0x%x sp:%d\n", i, op->pc, op->bc, bb->sp);
    }
}

void pm(VM *vm, char *m, Object *omethod) {
    Method *method = omethod->instance;
    char tmp[1024];
    char *ptr = tmp;

    ptr += sprintf(tmp, "%s : %s", m, string_to_ascii(CLS(method->declaringClass,name)));
    ptr += sprintf(ptr, ":%s", string_to_ascii(method->name));
    ptr += sprintf(ptr, ":%s = %d args:%d", string_to_ascii(method->signature), method->maxStack + method->maxLocals, method->argCount);
    for(int i=0; i<method->argCount; i++)
        ptr += sprintf(ptr, " %d=%d", i, method->argMap[i].localIndex);
    ptr += sprintf(ptr, " SP=%d FP=%d", vm->SP, vm->FP);
    GLOG("%s\n", tmp);
}

int vm_compile_find_op(COMPILERCTX *ctx, int pc, int *target) {
    for(int k=0; k<ctx->opCount; k++) {
        if(ctx->ops[k].pc == pc) {
            *target = k;
            return 1;
        }
    }
    return 0;
}

void vm_compile_method(VM *vm, Method *method, void **handlers) {
    COMPILERCTX ctx;
    memset(&ctx, 0, sizeof(ctx));
    ctx.method = method;
    vm_compiler_build_ops(&ctx);
    //printf("OP-Count: %d\n", ctx.opCount);
    //fix jump targets
    for(int i=0; i<ctx.opCount; i++) {
        OP *op = &ctx.ops[i];
        if(op->code == OP_GOTO || op->code == OP_IF || op->code == OP_IF0) {
            int pc = op->pc + op->index;
            int k;
            if(vm_compile_find_op(&ctx, pc, &k)) {
                op->index = k - i;
            } else printf("!!!!!! JUMPTARGET NOT FOUND pc=%d!!!!!!\n", pc);
            /*
            int found = 0;
            for(int k=0; k<ctx.opCount; k++) {
                if(ctx.ops[k].pc == pc) {
                    op->index = k - i;
                    found = 1;
                    break;
                }
            }
            if(!found) printf("!!!!!! JUMPTARGET NOT FOUND pc=%d!!!!!!\n", pc);
            */
        } else if(op->code == OP_LOOKUP || op->code == OP_TABLE) {
            OPSwitch *sw = op->sw;
            int pc = op->pc + sw->def;
            int k;
            if(vm_compile_find_op(&ctx, pc, &k)) {
                sw->def = k - i;
            } else printf("!!!!!! JUMPTARGET NOT FOUND pc=%d!!!!!!\n", pc);
            for(int j=0; j<sw->count; j++) {
                pc = op->pc + sw->offsets[j];
                if(vm_compile_find_op(&ctx, pc, &k)) {
                    sw->offsets[j] = k - i;
                } else printf("!!!!!! JUMPTARGET NOT FOUND pc=%d!!!!!!\n", pc);

            }
        }
    }
    //build basic blocks
    char bb_targets[ctx.opCount];
    memset(bb_targets, 0, sizeof(bb_targets));
    for(int i=0; i<ctx.opCount; i++) {
        OP *op = &ctx.ops[i];
        int target = -1;
        switch(op->code) {
            case OP_GOTO:
                bb_targets[i + op->index] = 1;
                break;
                
            case OP_IF:
            case OP_IF0:
                bb_targets[i + op->index] = 1;
                bb_targets[i+1] = 1;
                break;

            case OP_THROW:
            case OP_RETURN:
                if(i+1 < ctx.opCount) {
                    bb_targets[i+1] = 1;
                }
                break;
                
            case OP_TABLE:
            case OP_LOOKUP: {
                OPSwitch *sw = op->sw;
                bb_targets[i + sw->def] = 1;
                for(int j=0; j<sw->count; j++) {
                    bb_targets[sw->offsets[j] + i] = 1;
                }
                }
                break;
                
        }
    }
    
    for(int i=0; i<method->catchTableSize; i++) {
        CatchInfo *c = &method->catchTable[i];
        //printf("Catch: %d %d %d\n", c->start, c->end, c->pc);
        for(int k=0; k<ctx.opCount; k++) {
            if(ctx.ops[k].pc == c->pc) {
                bb_targets[k] = 2;
                break;
            }
        }
    }
    
    int bb_count = 1;
    for(int i=0; i<ctx.opCount; i++) if(bb_targets[i]) bb_count++;
    
    BB bb[bb_count];
    memset(bb, 0, sizeof(bb));
    bb_count = 1;
    
    bb[0].id = 0;
    bb[0].ops = &ctx.ops[0];
    
    for(int i=0; i<ctx.opCount; i++) {
        OP *op = &ctx.ops[i];
        if(bb_targets[i]) {
            bb_count++;
            bb[bb_count-1].id = op->pc;
            bb[bb_count-1].ops = op;
            bb[bb_count-1].isCatchHandler = bb_targets[i] == 2;
        }
        bb[bb_count-1].opCount++;
    }
    
    //find source bb
    int opndx = 0;
    for(int i=0; i<bb_count-1; i++) {
        int targets[] = {-1, -1};
        int targetCount = 0;
        if(bb[i].opCount > 0) {
            OP *last = &bb[i].ops[bb[i].opCount - 1];
            switch(last->code) {
                case OP_GOTO:
                    targets[0] = opndx + bb[i].opCount - 1 + last->index;
                    targetCount = 1;
                    break;
                    
                case OP_IF:
                case OP_IF0:
                    targets[0] = opndx + bb[i].opCount - 1 + last->index;
                    targets[1] = opndx + bb[i].opCount;
                    targetCount = 1;
                    break;
                    
                case OP_RETURN:
                case OP_THROW:
                    targetCount = -1;
                    break;
            }
        }
        opndx += bb[i].opCount;
        if(targetCount == -1) continue;
        
        if(targetCount == 1) {
            for(int k=0; k<2; k++) {
                if(targets[k] == -1) continue;
                int pc = ctx.ops[targets[k]].pc;
                int found = 0;
                for(int j=0; j<bb_count; j++)
                    if(j!=i && bb[j].id == pc) {
                        bb[j].src[bb[j].srcCount++] = &bb[i];
                        found = 1;
                        break;
                    }
                if(!found)
                    printf("!!!! target %d not found\n", pc);
            }
        } else {
            bb[i+1].src[bb[i+1].srcCount++] = &bb[i];
        }

    }
    /*
    for(int k=0; k<bb_count; k++) {
        BB *b = &bb[k];
        printf("BB %d  count:%d\n", b->id, b->opCount);
        if(b->srcCount > 0) {
            for(int i=0; i<b->srcCount; i++) {
                printf("  src:%d ",b->src[i]->id, b->src[i]->sp);
            }
            printf("\n");
        }
    }*/

    for(int i=0; i<bb_count; i++)
        vm_process_bb(method, &bb[i], handlers);
    
    //setup catch handlers
    for(int i=0; i<method->catchTableSize; i++) {
        CatchInfo *c = &method->catchTable[i];
        int found = 0;
        for(int k=0; k<ctx.opCount; k++) {
            if(ctx.ops[k].pc == c->pc) {
                c->label = &ctx.ops[k];
                found = 1;
                break;
            }
        }
        if(!found) printf("!!!! CATCH HANDLER NOT FOUND !!!!\n");
    }

    method->compiled = ctx.ops;
    method->compiledSize = ctx.opCount;
}

void dpc(VAR *stack, int sp, VAR *local, Method *m, OP *op) {
    char tmp[4096];
    char *ptr = tmp;
    ptr += sprintf(ptr, "%s", string_to_ascii(CLS(m->declaringClass,name)));
    ptr += sprintf(ptr, ":%s:%d:%d:0x%x", string_to_ascii(m->name),op->line,op->pc,op->bc);
    ptr += sprintf(ptr, " stack=");
    //for(int i=0; i<sp; i++) {
    //    ptr += sprintf(ptr, "[%d %ld %p]", stack[i].I, stack[i].J, stack[i].O);
    //}
    ptr += sprintf(ptr, " local=");
    if(m->maxLocals > 6)
    //for(int i=0; i<m->maxLocals; i++)
        ptr += sprintf(ptr, "[%d %ld %p]", local[6].I, local[6].J, local[6].O);
    GLOG("%s\n", tmp);
    
}
void vm_interpret_exec(VM *vm, Object *omethod, VAR *args) {
    static void* handlers[] = {
        &&OP_UNIMPLEMENTED,
        &&OP_NOP,
        &&OP_CONST,
        &&OP_CONST_CLS,
        &&OP_LOADLOCAL,
        &&OP_STORELOCAL,
        &&OP_GOTO,
        &&OP_IF0,
        &&OP_IF,
        &&OP_RETURN,
        &&OP_BINARY,
        &&OP_CONVERT,
        &&OP_IINC,
        &&OP_STACK,
        &&OP_INVOKE,
        &&OP_INVOKEDIRECT,
        &&OP_INVOKEINTERFACE,
        &&OP_INVOKEVIRTUAL,
        &&OP_GETFIELD,
        &&OP_PUTFIELD,
        &&OP_IFEQ,
        &&OP_IFNE,
        &&OP_IFLT,
        &&OP_IFGE,
        &&OP_IFGT,
        &&OP_IFLE,
        &&OP_IFICMPEQ,
        &&OP_IFICMPNE,
        &&OP_IFICMPLT,
        &&OP_IFICMPGE,
        &&OP_IFICMPGT,
        &&OP_IFICMPLE,
        &&OP_IFACMPEQ,
        &&OP_IFACMPNE,
        &&OP_NEWARRAY,
        &&OP_NEWARRAYRESOLVED,
        &&OP_NEW,
        &&OP_NEWRESOLVED,
        &&OP_ANEWARRAY,
        &&OP_ANEWARRAYRESOLVED,
        &&OP_POP,
        &&OP_POP2,
        &&OP_DUP,
        &&OP_DUPX1,
        &&OP_GETSTATIC_B,
        &&OP_GETSTATIC_Z,
        &&OP_GETSTATIC_C,
        &&OP_GETSTATIC_S,
        &&OP_GETSTATIC_I,
        &&OP_GETSTATIC_F,
        &&OP_GETSTATIC_J,
        &&OP_GETSTATIC_D,
        &&OP_GETSTATIC_O,
        &&OP_PUTSTATIC_B,
        &&OP_PUTSTATIC_Z,
        &&OP_PUTSTATIC_C,
        &&OP_PUTSTATIC_S,
        &&OP_PUTSTATIC_I,
        &&OP_PUTSTATIC_F,
        &&OP_PUTSTATIC_J,
        &&OP_PUTSTATIC_D,
        &&OP_PUTSTATIC_O,
        &&OP_GETFIELD_B,
        &&OP_GETFIELD_Z,
        &&OP_GETFIELD_C,
        &&OP_GETFIELD_S,
        &&OP_GETFIELD_I,
        &&OP_GETFIELD_F,
        &&OP_GETFIELD_J,
        &&OP_GETFIELD_D,
        &&OP_GETFIELD_O,
        &&OP_PUTFIELD_B,
        &&OP_PUTFIELD_Z,
        &&OP_PUTFIELD_C,
        &&OP_PUTFIELD_S,
        &&OP_PUTFIELD_I,
        &&OP_PUTFIELD_F,
        &&OP_PUTFIELD_J,
        &&OP_PUTFIELD_D,
        &&OP_PUTFIELD_O,
        &&OP_I2L,
        &&OP_I2F,
        &&OP_I2D,
        &&OP_L2I,
        &&OP_L2F,
        &&OP_L2D,
        &&OP_F2I,
        &&OP_F2L,
        &&OP_F2D,
        &&OP_D2I,
        &&OP_D2L,
        &&OP_D2F,
        &&OP_I2B,
        &&OP_I2C,
        &&OP_I2S,
        &&OP_LCMP,
        &&OP_FCMPL,
        &&OP_FCMPG,
        &&OP_DCMPL,
        &&OP_DCMPG,
        &&OP_IADD,
        &&OP_LADD,
        &&OP_FADD,
        &&OP_DADD,
        &&OP_ISUB,
        &&OP_LSUB,
        &&OP_FSUB,
        &&OP_DSUB,
        &&OP_IMUL,
        &&OP_LMUL,
        &&OP_FMUL,
        &&OP_DMUL,
        &&OP_IDIV,
        &&OP_LDIV,
        &&OP_FDIV,
        &&OP_DDIV,
        &&OP_IREM,
        &&OP_LREM,
        &&OP_FREM,
        &&OP_DREM,
        &&OP_INEG,
        &&OP_LNEG,
        &&OP_FNEG,
        &&OP_DNEG,
        &&OP_ISHL,
        &&OP_LSHL,
        &&OP_ISHR,
        &&OP_LSHR,
        &&OP_IUSHR,
        &&OP_LUSHR,
        &&OP_IAND,
        &&OP_LAND,
        &&OP_IOR,
        &&OP_LOR,
        &&OP_IXOR,
        &&OP_LXOR,
        &&OP_THROW,
        &&OP_CHECKCAST,
        &&OP_CHECKCASTRESOLVED,
        &&OP_LOADARRAY_I,
        &&OP_LOADARRAY_J,
        &&OP_LOADARRAY_F,
        &&OP_LOADARRAY_D,
        &&OP_LOADARRAY_O,
        &&OP_LOADARRAY_B,
        &&OP_LOADARRAY_C,
        &&OP_LOADARRAY_S,
        &&OP_STOREARRAY_I,
        &&OP_STOREARRAY_J,
        &&OP_STOREARRAY_F,
        &&OP_STOREARRAY_D,
        &&OP_STOREARRAY_O,
        &&OP_STOREARRAY_B,
        &&OP_STOREARRAY_C,
        &&OP_STOREARRAY_S,
        &&OP_ARRAYLENGTH,
        &&OP_IFNULL,
        &&OP_IFNOTNULL,
        &&OP_MONITORENTER,
        &&OP_MONITOREXIT,
        &&OP_TABLE,
        &&OP_LOOKUP,
        &&OP_INSTANCEOF,
        &&OP_INSTANCEOFRESOLVED
    };
    
    Method *method = omethod->instance;
    if(IS_ABSTRACT(method->flags)) {
        throw_abstractmethod(vm, STRCHARS(CLS(method->declaringClass,name)), STRLEN(CLS(method->declaringClass,name)),
                             STRCHARS(method->name), STRLEN(method->name),
                             STRCHARS(method->signature), STRLEN(method->signature)
                );
        return;
    }
    //VAR stack[method->maxStack];
    //VAR local[method->maxLocals];
    VAR* local = &vm->stack[vm->SP];
    VAR* stack = local + method->maxLocals;
    vm->SP += method->maxStack + method->maxLocals;
    JINT sp = 0;
    
    //if(!strcmp(string2c(method->name),"main"))
    //    printf("...");
    //pm(vm, "Executing", omethod);
    //printf("SP=%d\n", vm->SP);
    if(!method->compiled) {
        //pm("Compiling", omethod);
        vm_compile_method(vm, method, &handlers[0]);
        free(method->code);
        method->code = NULL;
    }
    //printf("Started...\n");

    int argCount = method->argCount;
    if(argCount > 0) {
        MethodArg *map = method->argMap;
        for(int i=0; i<argCount; i++) {
            //GLOG("arg%d = I:%d O:%p J:%ld\n", map[i], args->I, args->O, args->J);
            local[map[i].localIndex] = *args;
            args++;
        }
    }

    Object *field;
    JINT fp = ++vm->FP;
    vm->frames[fp].method = omethod;
    vm->frames[fp].SP = local;
    //Frame *frame = &vm->frames[++vm->fp];
    
    OP* op = &((OP*)method->compiled)[0];
#ifdef PLAYERMODE
    int last_jdwp_line = -1;
#define NEXT(d) { \
    vm->frames[fp].line = op->line; \
    vm->frames[fp].pc = op->pc; \
    jdwp_tick(vm, omethod, op->pc, op->line, op->line != last_jdwp_line); \
    last_jdwp_line = op->line; \
    op += d; \
    goto *op->handler; \
}
    
#else

#define NEXT(d) { \
    op += d; \
    goto *op->handler; \
}
    
#endif
    
#define REDISPATCH() { \
    goto *op->handler; \
}

#define NULL_CHECK(o) \
if(!o) { \
    vm->frames[fp].line = op->line; \
    throw_null(vm); \
    goto __EXCEPTION; \
}
    
#define SAVE_PC vm->frames[fp].line = op->line;

    NEXT(0);
    
OP_NOP:
    NEXT(1);
OP_UNIMPLEMENTED:   //0
    printf("UNIMPLEMENTED OP = %d : 0x%x code=%d\n", op->bc, op->bc, op->code);
    return;
    
OP_CONST:           //1
    stack[sp++] = op->var;
    NEXT(1)
    
OP_CONST_CLS:
    {
        Object *cls = resolve_class_by_index(vm, method->declaringClass, op->index);
        if(vm->exception) goto __EXCEPTION;
        op->var.O = cls;
        op->handler = handlers[OP_CONST];
        REDISPATCH();
    }
OP_LOADLOCAL:       //2
    stack[sp++] = local[op->index];
    NEXT(1)
    
OP_STORELOCAL:      //3
    local[op->index] = stack[--sp];
    NEXT(1)
    
OP_GOTO:            //4
    NEXT(op->index);

OP_IF0:              //5
    printf("OP_IF0 CALLED!\n");
    return;
OP_IF:              //5
    printf("OP_IF CALLED!\n");
    return;
OP_RETURN:          //6
    vm->FP--;
    if(op->type != 'V')
        vm->frames[vm->FP].ret = stack[--sp];
    vm->SP -= method->maxStack + method->maxLocals;
    //pm("Finished", omethod);
    return;
    
OP_BINARY:          //7
    printf("OP_BINARY CALLED!\n");
    return;
    
OP_CONVERT:         //8
    printf("OP_CONVERT CALLED!\n");
    return;

OP_IINC:            //9
    local[op->index].I += op->var.I;
    NEXT(1);
OP_STACK:           //11
    printf("OP_STACK CALLED!\n");
    return;
    
OP_INVOKE:          //12
{
    Object *m = resolve_method_by_index(vm, method->declaringClass, op->index);
    if(vm->exception) goto __EXCEPTION;
    NULL_CHECK(m);
    op->var.O = (Object*)m;
    switch(op->bc) {
        case op_invokestatic:
        case op_invokespecial:
            op->handler = handlers[OP_INVOKEDIRECT];
            break;
            
        case op_invokeinterface:
            op->handler = handlers[OP_INVOKEINTERFACE];
            break;
            
        case op_invokevirtual:
            op->handler = handlers[OP_INVOKEVIRTUAL];
            break;
            
        default:
            printf("Unknown Invoke type: %d\n", op->bc);
            return;
    }
    REDISPATCH();
}
    
OP_GETFIELD:        //13
    field = resolve_field_by_index(vm, method->declaringClass, op->index);
    if(vm->exception) goto __EXCEPTION;
    //printf("GetField: %s",string2c(field->declaringClass->name));
    //printf(":%s\n", string2c(field->name));

    op->index = (int)FLD(field,offset);
    op->var.O = (Object*)FLD(field,offset); //(CLS(FLD(field,declaringClass),global) + op->index); //static access
    switch(op->type) {
        case 'B': op->handler = handlers[op->bc == op_getstatic ? OP_GETSTATIC_B : OP_GETFIELD_B]; break;
        case 'Z': op->handler = handlers[op->bc == op_getstatic ? OP_GETSTATIC_Z : OP_GETFIELD_Z]; break;
        case 'C': op->handler = handlers[op->bc == op_getstatic ? OP_GETSTATIC_C : OP_GETFIELD_C]; break;
        case 'S': op->handler = handlers[op->bc == op_getstatic ? OP_GETSTATIC_S : OP_GETFIELD_S]; break;
        case 'I': op->handler = handlers[op->bc == op_getstatic ? OP_GETSTATIC_I : OP_GETFIELD_I]; break;
        case 'O': op->handler = handlers[op->bc == op_getstatic ? OP_GETSTATIC_O : OP_GETFIELD_O]; break;
        case 'J': op->handler = handlers[op->bc == op_getstatic ? OP_GETSTATIC_J : OP_GETFIELD_J]; break;
        case 'D': op->handler = handlers[op->bc == op_getstatic ? OP_GETSTATIC_D : OP_GETFIELD_D]; break;
        case 'F': op->handler = handlers[op->bc == op_getstatic ? OP_GETSTATIC_F : OP_GETFIELD_F]; break;
        default:
            printf("Unknown getfield type: %c\n", op->type);
            return;
    }
    //op->handler = handlers[op->bc == op_getstatic ? OP_GETSTATICRESOLVED : OP_GETFIELDRESOLVED];
    REDISPATCH();
OP_PUTFIELD: {        //14
    field = resolve_field_by_index(vm, method->declaringClass, op->index);
    if(vm->exception) goto __EXCEPTION;
    op->index = (int)FLD(field, offset);
    op->var.O = (Object*)FLD(field,offset); //(Object*)(CLS(FLD(field,declaringClass),global) + op->index); //static access
    switch(op->type) {
        case 'B': op->handler = handlers[op->bc == op_putstatic ? OP_PUTSTATIC_B : OP_PUTFIELD_B]; break;
        case 'Z': op->handler = handlers[op->bc == op_putstatic ? OP_PUTSTATIC_Z : OP_PUTFIELD_Z]; break;
        case 'C': op->handler = handlers[op->bc == op_putstatic ? OP_PUTSTATIC_C : OP_PUTFIELD_C]; break;
        case 'S': op->handler = handlers[op->bc == op_putstatic ? OP_PUTSTATIC_S : OP_PUTFIELD_S]; break;
        case 'I': op->handler = handlers[op->bc == op_putstatic ? OP_PUTSTATIC_I : OP_PUTFIELD_I]; break;
        case 'O': op->handler = handlers[op->bc == op_putstatic ? OP_PUTSTATIC_O : OP_PUTFIELD_O]; break;
        case 'J': op->handler = handlers[op->bc == op_putstatic ? OP_PUTSTATIC_J : OP_PUTFIELD_J]; break;
        case 'D': op->handler = handlers[op->bc == op_putstatic ? OP_PUTSTATIC_D : OP_PUTFIELD_D]; break;
        case 'F': op->handler = handlers[op->bc == op_putstatic ? OP_PUTSTATIC_F : OP_PUTFIELD_F]; break;
        default:
            printf("Unknown putfield type: %c\n", op->type);
            return;
    }
    //op->handler = handlers[op->bc == op_putstatic ? OP_PUTSTATICRESOLVED : OP_PUTFIELDRESOLVED];
    REDISPATCH();
}
OP_IFEQ:            //15
    sp--;
    if(stack[sp].I == 0) { NEXT(op->index); } else NEXT(1);
OP_IFNE:            //16
    sp--;
    if(stack[sp].I != 0) { NEXT(op->index); } else NEXT(1);
OP_IFLT:            //17
    sp--;
    if(stack[sp].I < 0) { NEXT(op->index); } else NEXT(1);
OP_IFGE:            //18
    sp--;
    if(stack[sp].I >= 0) { NEXT(op->index); } else NEXT(1);
OP_IFGT:            //19
    sp--;
    if(stack[sp].I > 0) { NEXT(op->index); } else NEXT(1);
OP_IFLE:            //20
    sp--;
    if(stack[sp].I <= 0) { NEXT(op->index); } else NEXT(1);
OP_IFICMPEQ:        //21
    sp -= 2;
    if(stack[sp].I == stack[sp+1].I) { NEXT(op->index); } else NEXT(1);
OP_IFICMPNE:        //22
    sp -= 2;
    if(stack[sp].I != stack[sp+1].I) { NEXT(op->index); } else NEXT(1);
OP_IFICMPLT:        //23
    sp -= 2;
    if(stack[sp].I < stack[sp+1].I) { NEXT(op->index); } else NEXT(1);
OP_IFICMPGE:        //24
    sp -= 2;
    if(stack[sp].I >= stack[sp+1].I) { NEXT(op->index); } else NEXT(1);
OP_IFICMPGT:        //25
    sp -= 2;
    if(stack[sp].I > stack[sp+1].I) { NEXT(op->index); } else NEXT(1);
OP_IFICMPLE:        //26
    sp -= 2;
    if(stack[sp].I <= stack[sp+1].I) { NEXT(op->index); } else NEXT(1);
OP_IFACMPEQ:        //27
    sp -= 2;
    if(stack[sp].O == stack[sp+1].O) { NEXT(op->index); } else NEXT(1);
OP_IFACMPNE:        //28
    sp -= 2;
    if(stack[sp].O != stack[sp+1].O) { NEXT(op->index); } else NEXT(1);

OP_NEWARRAY:
{
    switch(op->index) {
        case 4:
            op->var.O = get_arrayclass_of(vm, vm->primClasses[PRIM_Z]);
            break;
        case 5:
            op->var.O = get_arrayclass_of(vm, vm->primClasses[PRIM_C]);
            break;
        case 6:
            op->var.O = get_arrayclass_of(vm, vm->primClasses[PRIM_F]);
            break;
        case 7:
            op->var.O = get_arrayclass_of(vm, vm->primClasses[PRIM_D]);
            break;
        case 8:
            op->var.O = get_arrayclass_of(vm, vm->primClasses[PRIM_B]);
            break;
        case 9:
            op->var.O = get_arrayclass_of(vm, vm->primClasses[PRIM_S]);
            break;
        case 10:
            op->var.O = get_arrayclass_of(vm, vm->primClasses[PRIM_I]);
            break;
        case 11:
            op->var.O = get_arrayclass_of(vm, vm->primClasses[PRIM_J]);
            break;
        default:
            vm->FP--;
            vm->SP -= method->maxStack + method->maxLocals;
            throw_null(vm);
            printf("Unknown new array type: %d\n", op->index);
            return;
    }
    if(vm->exception) goto __EXCEPTION;
    op->handler = handlers[OP_NEWARRAYRESOLVED];
    REDISPATCH();
}
OP_NEWARRAYRESOLVED:
    stack[sp-1].O = alloc_array(vm, op->var.O, stack[sp-1].I, 0);
    NEXT(1);
OP_NEW:             //10
    op->var.O = resolve_class_by_index(vm,method->declaringClass,op->index);
    if(vm->exception) goto __EXCEPTION;
    op->handler = handlers[OP_NEWRESOLVED];
    REDISPATCH();
OP_NEWRESOLVED:
    stack[sp].O = alloc_object(vm, op->var.O, 0); sp++;
    NEXT(1)
OP_ANEWARRAY: {
    Object *element = resolve_class_by_index(vm, method->declaringClass, op->index);
    if(vm->exception) goto __EXCEPTION;
    op->var.O = get_arrayclass_of(vm, element);
    //op->var.O = resolve_class_by_index(vm, method->declaringClass, op->index);
    if(vm->exception) goto __EXCEPTION;
    op->handler = handlers[OP_ANEWARRAYRESOLVED];
    REDISPATCH();
    }
OP_ANEWARRAYRESOLVED:
    stack[sp-1].O = alloc_array(vm, op->var.O, stack[sp-1].I, 0);
    NEXT(1);
OP_POP:
    sp--;
    NEXT(1);
OP_POP2:
    sp-=2;
    NEXT(1);
OP_DUP:
    stack[sp] = stack[sp-1]; sp++;
    NEXT(1)
OP_DUPX1:
    {
    VAR v1 = stack[--sp];
    VAR v2 = stack[--sp];
    stack[sp++] = v1;
    stack[sp++] = v2;
    stack[sp++] = v1;
    NEXT(1)
    }
    
OP_GETSTATIC_B:
    stack[sp++].I = *((JBYTE*)op->var.O);
    NEXT(1);
OP_GETSTATIC_Z:
    stack[sp++].I = *((JBOOL*)op->var.O);
    NEXT(1);
OP_GETSTATIC_C:
    stack[sp++].I = *((JCHAR*)op->var.O);
    NEXT(1);
OP_GETSTATIC_S:
    stack[sp++].I = *((JSHORT*)op->var.O);
    NEXT(1);
OP_GETSTATIC_I:
    stack[sp++].I = *((JINT*)op->var.O);
    NEXT(1);
OP_GETSTATIC_F:
    stack[sp++].F = *((JFLOAT*)op->var.O);
    NEXT(1);
OP_GETSTATIC_J:
    stack[sp++].J = *((JLONG*)op->var.O);
    NEXT(1);
OP_GETSTATIC_D:
    stack[sp++].D = *((JDOUBLE*)op->var.O);
    NEXT(1);
OP_GETSTATIC_O:
    stack[sp++].O = *((Object**)op->var.O);
    NEXT(1);
    
OP_PUTSTATIC_B:
    *((JBYTE*)op->var.O) = stack[--sp].I;
    NEXT(1);
OP_PUTSTATIC_Z:
    *((JBOOL*)op->var.O) = stack[--sp].I;
    NEXT(1);
OP_PUTSTATIC_C:
    *((JCHAR*)op->var.O) = stack[--sp].I;
    NEXT(1);
OP_PUTSTATIC_S:
    *((JSHORT*)op->var.O) = stack[--sp].I;
    NEXT(1);
OP_PUTSTATIC_I:
    *((JINT*)op->var.O) = stack[--sp].I;
    NEXT(1);
OP_PUTSTATIC_F:
    *((JFLOAT*)op->var.O) = stack[--sp].F;
    NEXT(1);
OP_PUTSTATIC_J:
    *((JLONG*)op->var.O) = stack[--sp].J;
    NEXT(1);
OP_PUTSTATIC_D:
    *((JDOUBLE*)op->var.O) = stack[--sp].D;
    NEXT(1);
OP_PUTSTATIC_O:
    *((Object**)op->var.O) = stack[--sp].O;
    NEXT(1);
OP_GETFIELD_B:
    {
        Object *object = stack[sp-1].O;
        NULL_CHECK(object);
        stack[sp-1].I = *FIELD_PTR_B(object, op->index);
        NEXT(1);
    }
OP_GETFIELD_Z:
    {
        Object *object = stack[sp-1].O;
        NULL_CHECK(object);
        stack[sp-1].I = *FIELD_PTR_Z(object, op->index);
        NEXT(1);
    }
OP_GETFIELD_C:
    {
        Object *object = stack[sp-1].O;
        NULL_CHECK(object);
        stack[sp-1].I = *FIELD_PTR_C(object, op->index);
        NEXT(1);
    }
OP_GETFIELD_S:
    {
        Object *object = stack[sp-1].O;
        NULL_CHECK(object);
        stack[sp-1].I = *FIELD_PTR_S(object, op->index);
        NEXT(1);
    }
OP_GETFIELD_I:
    {
        Object *object = stack[sp-1].O;
        NULL_CHECK(object);
        //printf("GetField_I => %d %p + %d\n",*((jint*)(object+sizeof(Object)+op->index)), object, op->index);
        stack[sp-1].I = *FIELD_PTR_I(object, op->index);
        NEXT(1);
    }
OP_GETFIELD_F:
    {
        Object *object = stack[sp-1].O;
        NULL_CHECK(object);
        stack[sp-1].F = *FIELD_PTR_F(object, op->index);
        NEXT(1);
    }
OP_GETFIELD_J:
    {
        Object *object = stack[sp-1].O;
        NULL_CHECK(object);
        stack[sp-1].J = *FIELD_PTR_J(object, op->index);
        NEXT(1);
    }
OP_GETFIELD_D:
    {
        Object *object = stack[sp-1].O;
        NULL_CHECK(object);
        stack[sp-1].D = *FIELD_PTR_D(object, op->index);
        NEXT(1);
    }
OP_GETFIELD_O:
    {
        Object *object = stack[sp-1].O;
        NULL_CHECK(object);
        stack[sp-1].O = *FIELD_PTR_O(object, op->index);
        NEXT(1);
    }
OP_PUTFIELD_B:
    {
        Object *object = stack[sp-2].O;
        NULL_CHECK(object);
        *FIELD_PTR_B(object, op->index) = (JBYTE)stack[sp-1].I;
        sp -= 2;
        NEXT(1);
    }
OP_PUTFIELD_Z:
    {
        Object *object = stack[sp-2].O;
        NULL_CHECK(object);
        *FIELD_PTR_Z(object, op->index) = (JBOOL)stack[sp-1].I;
        sp -= 2;
        NEXT(1);
    }
OP_PUTFIELD_C:
    {
        Object *object = stack[sp-2].O;
        NULL_CHECK(object);
        *FIELD_PTR_C(object, op->index) = (JSHORT)stack[sp-1].I;
        sp -= 2;
        NEXT(1);
    }
OP_PUTFIELD_S:
    {
        Object *object = stack[sp-2].O;
        NULL_CHECK(object);
        *FIELD_PTR_S(object, op->index) = stack[sp-1].I;
        sp -= 2;
        NEXT(1);
    }
OP_PUTFIELD_I:
    {
        Object *object = stack[sp-2].O;
        NULL_CHECK(object);
        //printf("PutField_I => %d for %p at %d\n",stack[sp-1].I, object, op->index);
        *FIELD_PTR_I(object, op->index) = stack[sp-1].I;
        sp -= 2;
        NEXT(1);
    }
OP_PUTFIELD_F:
    {
        Object *object = stack[sp-2].O;
        NULL_CHECK(object);
        *FIELD_PTR_F(object, op->index) = stack[sp-1].F;
        sp -= 2;
        NEXT(1);
    }
OP_PUTFIELD_J:
    {
        Object *object = stack[sp-2].O;
        NULL_CHECK(object);
        *FIELD_PTR_J(object, op->index) = stack[sp-1].J;
        sp -= 2;
        NEXT(1);
    }
OP_PUTFIELD_D:
    {
        Object *object = stack[sp-2].O;
        NULL_CHECK(object);
        *FIELD_PTR_D(object, op->index) = stack[sp-1].D;
        sp -= 2;
        NEXT(1);
    }
OP_PUTFIELD_O:
    {
        Object *object = stack[sp-2].O;
        NULL_CHECK(object);
        *FIELD_PTR_O(object, op->index) = stack[sp-1].O;
        sp -= 2;
        NEXT(1);
    }
OP_INVOKEDIRECT:          //35
    {
        Object *om = op->var.O;
        Method *m = om->instance;
        int call_sp = sp - m->argCount;
        SAVE_PC;
        ((VM_CALL)m->entry)(vm, om, &stack[call_sp]);
        sp = call_sp;
        if(vm->exception) goto __EXCEPTION;
        if(op->type != 'V') {
            stack[sp++] = vm->frames[fp].ret;
        }
        NEXT(1);
    }
OP_INVOKEINTERFACE:
    {
        Object *om = op->var.O;
        Method *m = om->instance;
        int call_sp = sp - m->argCount;
        SAVE_PC;
        Object *object = stack[call_sp].O;
        NULL_CHECK(object);
        Object *imethod = CLS(object->cls,itable)[m->iTableIndex];
        if(!imethod) {
            printf("Invalid interface call!!!\n");
            return;
        }
        ((VM_CALL)((Method*)imethod->instance)->entry)(vm, imethod, &stack[call_sp]);
        sp = call_sp;
        if(vm->exception) goto __EXCEPTION;
        if(op->type != 'V') {
            stack[sp++] = vm->frames[fp].ret;
        }
        NEXT(1);
    }
OP_INVOKEVIRTUAL:
    {
        Object *om = op->var.O;
        Method *m = om->instance;
        //printf("--- invoke-virtual: %s", string_to_ascii(CLS(m->declaringClass,name)));
        //printf(":%s",string_to_ascii(m->name));
        //printf(":%s\n",string_to_ascii(m->signature));

        int call_sp = sp - m->argCount;
        SAVE_PC;
        Object *object = stack[call_sp].O;
        NULL_CHECK(object);
        VMClass *cls = object->cls->instance;
        if(m->vTableIndex >= cls->vTableSize)
            printf("VTABLW!!!!!!!!!!!!\n");
        //printf(" ---- %s\n", string2c(CLS_FIELD(object->cls,name)));
        Object *vmethod = CLS(object->cls,vtable)[m->vTableIndex];
        if(!vmethod) {
            printf("Invalid virtual call!!! for %s\n", string_to_ascii(CLS(object->cls,name)));
            return;
        }
        ((VM_CALL)((Method*)vmethod->instance)->entry)(vm, vmethod, &stack[call_sp]);
        sp = call_sp;
        if(vm->exception) goto __EXCEPTION;
        if(op->type != 'V') {
            stack[sp++] = vm->frames[fp].ret;
        }
        NEXT(1);
    }
OP_I2L:  //36
    stack[sp-1].J = stack[sp-1].I;
    NEXT(1)
OP_I2F:  //37
    stack[sp-1].F = stack[sp-1].I;
    NEXT(1)
OP_I2D:  //38
    stack[sp-1].D = stack[sp-1].I;
    NEXT(1)
OP_L2I:  //39
    stack[sp-1].I = (JINT)stack[sp-1].J;
    NEXT(1)
OP_L2F:  //40
    stack[sp-1].F = (JFLOAT)stack[sp-1].J;
    NEXT(1)
OP_L2D:  //41
    stack[sp-1].D = (JDOUBLE)stack[sp-1].J;
    NEXT(1)
OP_F2I:  //42
    stack[sp-1].I = (JINT)stack[sp-1].F;
    NEXT(1)
OP_F2L:  //43
    stack[sp-1].J = (JLONG)stack[sp-1].F;
    NEXT(1)
OP_F2D:  //44
    stack[sp-1].D = stack[sp-1].F;
    NEXT(1)
OP_D2I:  //45
    stack[sp-1].I = (JINT)stack[sp-1].D;
    NEXT(1)
OP_D2L:  //46
    stack[sp-1].J = (JLONG)stack[sp-1].D;
    NEXT(1)
OP_D2F:  //47
    stack[sp-1].F = (JFLOAT)stack[sp-1].D;
    NEXT(1)
OP_I2B:  //48
    stack[sp-1].I = (JBYTE)stack[sp-1].I;
    NEXT(1)
OP_I2C:  //49
    stack[sp-1].I = (JCHAR)stack[sp-1].I;
    NEXT(1)
OP_I2S:  //50
    stack[sp-1].I = (JSHORT)stack[sp-1].I;
    NEXT(1)
OP_LCMP: {
    JLONG v2 = stack[sp-1].J;
    JLONG v1 = stack[sp-2].J;
    stack[sp-2].I = v1 == v2 ? 0 : (v1 < v2 ? -1 : 1);
    sp--;
    NEXT(1)
}
#define FCMP(TYPE, SIGN, isNan)           \
    int res;                        \
    TYPE v2 = stack[sp-1].SIGN;      \
    TYPE v1 = stack[sp-2].SIGN;      \
    if(v1 == v2)                    \
        res = 0;                    \
    else if(v1 < v2)                \
        res = -1;                   \
    else if(v1 > v2)                \
         res = 1;                   \
    else                            \
         res = isNan;               \
    stack[sp-2].I = res;            \
    sp--;
    
OP_FCMPL: {
    FCMP(JFLOAT, F, -1);
    NEXT(1)
}
OP_FCMPG: {
    FCMP(JFLOAT, F, 1);
    NEXT(1)
}
OP_DCMPL: {
    FCMP(JDOUBLE, D, -1);
    NEXT(1)
}
OP_DCMPG: {
    FCMP(JDOUBLE, D, 1);
    NEXT(1)
}

OP_IADD: //51
    stack[sp-2].I += stack[sp-1].I;
    sp--;
    NEXT(1);
OP_LADD: //52
    stack[sp-2].J += stack[sp-1].J;
    sp--;
    NEXT(1);
OP_FADD: //53
    stack[sp-2].F += stack[sp-1].F;
    sp--;
    NEXT(1);
OP_DADD: //54
    stack[sp-2].D += stack[sp-1].D;
    sp--;
    NEXT(1);
OP_ISUB: //55
    stack[sp-2].I -= stack[sp-1].I;
    sp--;
    NEXT(1);
OP_LSUB: //56
    stack[sp-2].J -= stack[sp-1].J;
    sp--;
    NEXT(1);
OP_FSUB: //57
    stack[sp-2].F -= stack[sp-1].F;
    sp--;
    NEXT(1);
OP_DSUB: //58
    stack[sp-2].D -= stack[sp-1].D;
    sp--;
    NEXT(1);
OP_IMUL: //59
    stack[sp-2].I *= stack[sp-1].I;
    sp--;
    NEXT(1);
OP_LMUL: //60
    stack[sp-2].J *= stack[sp-1].J;
    sp--;
    NEXT(1);
OP_FMUL: //61
    stack[sp-2].F *= stack[sp-1].F;
    sp--;
    NEXT(1);
OP_DMUL: //62
    stack[sp-2].D *= stack[sp-1].D;
    sp--;
    NEXT(1);
OP_IDIV: //63
    {
        JINT divisor = stack[sp-1].I;
        stack[sp-2].I /= divisor;
        sp--;
        NEXT(1);
    }
OP_LDIV: //64
    {
        JLONG divisor = stack[sp-1].J;
        stack[sp-2].J /= divisor;
        sp--;
        NEXT(1);
    }
OP_FDIV: //65
    {
        JFLOAT divisor = stack[sp-1].F;
        stack[sp-2].F /= divisor;
        sp--;
        NEXT(1);
    }
OP_DDIV: //66
    {
        JDOUBLE divisor = stack[sp-1].D;
        stack[sp-2].D /= divisor;
        sp--;
        NEXT(1);
    }
OP_IREM: //67
    stack[sp-2].I %= stack[sp-1].I;
    sp--;
    NEXT(1);
OP_LREM: //68
    stack[sp-2].J %= stack[sp-1].J;
    sp--;
    NEXT(1);
OP_FREM: //69
    printf("Missing op: 0x%x\n", op->bc);
    return;
OP_DREM: //70
    printf("Missing op: 0x%x\n", op->bc);
    return;
OP_INEG: //71
    stack[sp-1].I = -stack[sp-1].I;
    NEXT(1);
OP_LNEG: //72
    stack[sp-1].J = -stack[sp-1].J;
    NEXT(1);
OP_FNEG: //73
    stack[sp-1].F = -stack[sp-1].F;
    NEXT(1);
OP_DNEG: //74
    stack[sp-1].D = -stack[sp-1].D;
    NEXT(1);
OP_ISHL: //75
    stack[sp-2].I <<= stack[sp-1].I;
    sp--;
    NEXT(1);
OP_LSHL: //76
    stack[sp-2].J <<= stack[sp-1].I;
    sp--;
    NEXT(1);
OP_ISHR: //77
    stack[sp-2].I >>= stack[sp-1].I;
    sp--;
    NEXT(1);
OP_LSHR: //78
    stack[sp-2].J >>= stack[sp-1].I;
    sp--;
    NEXT(1);
OP_IUSHR: //79
    stack[sp-2].I = (((unsigned int)stack[sp-2].I) >> (0x1f & ((unsigned int)stack[sp-1].I)));
    sp--;
    NEXT(1);
OP_LUSHR: //80
    stack[sp-2].J = (((unsigned long long)stack[sp-2].J) >> (0x3f & ((unsigned long long)stack[sp-1].I)));
    sp--;
    NEXT(1);
OP_IAND: //81
    stack[sp-2].I &= stack[sp-1].I;
    sp--;
    NEXT(1);
OP_LAND: //82
    stack[sp-2].J &= stack[sp-1].J;
    sp--;
    NEXT(1);
OP_IOR: //83
    stack[sp-2].I |= stack[sp-1].I;
    sp--;
    NEXT(1);
OP_LOR: //84
    stack[sp-2].J |= stack[sp-1].J;
    sp--;
    NEXT(1);
OP_IXOR: //85
    stack[sp-2].I ^= stack[sp-1].I;
    sp--;
    NEXT(1);
OP_LXOR: //86
    stack[sp-2].J ^= stack[sp-1].J;
    sp--;
    NEXT(1);
OP_THROW:
    vm->frames[fp].line = op->line;
    throw_exception(vm, stack[--sp].O);
    goto __EXCEPTION;
OP_CHECKCAST:
    op->var.O = (Object*)resolve_class_by_index(vm, method->declaringClass, op->index);
    if(vm->exception) goto __EXCEPTION;
    op->handler = handlers[OP_CHECKCASTRESOLVED];
    REDISPATCH();
OP_CHECKCASTRESOLVED:
    if(!check_cast(vm, stack[sp-1].O, op->var.O)) {
        vm->frames[fp].line = op->line;
        throw_cast(vm, stack[sp-1].O->cls, op->var.O);
        goto __EXCEPTION;
    }
    NEXT(1);

#define ARRAY_CHECK \
if(!object) { \
    vm->frames[fp].line = op->line; \
    throw_null(vm); \
    goto __EXCEPTION; \
} \
if(index < 0 || index >= object->length) { \
    vm->frames[fp].line = op->line; \
    throw_arraybounds(vm, index, object->length); \
    goto __EXCEPTION; \
}

OP_LOADARRAY_I:
{
    int index = stack[--sp].I;
    Object *object = stack[--sp].O;
    ARRAY_CHECK;
    stack[sp++].I = ARRAY_DATA_I(object)[index];
    NEXT(1);
}
OP_LOADARRAY_J:
{
    int index = stack[--sp].I;
    Object *object = stack[--sp].O;
    ARRAY_CHECK;
    stack[sp++].J = ARRAY_DATA_J(object)[index];
    NEXT(1);
}
OP_LOADARRAY_F:
{
    int index = stack[--sp].I;
    Object *object = stack[--sp].O;
    ARRAY_CHECK;
    stack[sp++].F = ARRAY_DATA_F(object)[index];
    NEXT(1);
}
OP_LOADARRAY_D:
{
    int index = stack[--sp].I;
    Object *object = stack[--sp].O;
    ARRAY_CHECK;
    stack[sp++].D = ARRAY_DATA_D(object)[index];
    NEXT(1);
}
OP_LOADARRAY_O:
{
    int index = stack[--sp].I;
    Object *object = stack[--sp].O;
    ARRAY_CHECK;
    stack[sp++].O = ARRAY_DATA_O(object)[index];
    NEXT(1);
}
OP_LOADARRAY_B:
{
    int index = stack[--sp].I;
    Object *object = stack[--sp].O;
    ARRAY_CHECK;
    stack[sp++].I = ARRAY_DATA_B(object)[index];
    NEXT(1);
}
OP_LOADARRAY_C:
{
    int index = stack[--sp].I;
    Object *object = stack[--sp].O;
    ARRAY_CHECK;
    stack[sp++].I = ARRAY_DATA_C(object)[index];
    NEXT(1);
}
OP_LOADARRAY_S:
{
    int index = stack[--sp].I;
    Object *object = stack[--sp].O;
    ARRAY_CHECK;
    stack[sp++].I = ARRAY_DATA_S(object)[index];
    NEXT(1);
}
OP_STOREARRAY_I:
{
    JINT val = stack[--sp].I;
    int index = stack[--sp].I;
    Object *object = stack[--sp].O;
    ARRAY_CHECK;
    ARRAY_DATA_I(object)[index] = val;
    NEXT(1);
}
OP_STOREARRAY_J:
{
    JLONG val = stack[--sp].J;
    int index = stack[--sp].I;
    Object *object = stack[--sp].O;
    ARRAY_CHECK;
    ARRAY_DATA_J(object)[index] = val;
    NEXT(1);
}
OP_STOREARRAY_F:
{
    JFLOAT val = stack[--sp].F;
    int index = stack[--sp].I;
    Object *object = stack[--sp].O;
    ARRAY_CHECK;
    ARRAY_DATA_F(object)[index] = val;
    NEXT(1);
}
OP_STOREARRAY_D:
{
    JDOUBLE val = stack[--sp].D;
    int index = stack[--sp].I;
    Object *object = stack[--sp].O;
    ARRAY_CHECK;
    ARRAY_DATA_D(object)[index] = val;
    NEXT(1);
}
OP_STOREARRAY_O:
{
    Object* val = stack[--sp].O;
    int index = stack[--sp].I;
    Object *object = stack[--sp].O;
    ARRAY_CHECK;
    ARRAY_DATA_O(object)[index] = val;
    NEXT(1);
}
OP_STOREARRAY_B:
{
    int val = stack[--sp].I;
    int index = stack[--sp].I;
    Object *object = stack[--sp].O;
    ARRAY_CHECK;
    ARRAY_DATA_B(object)[index] = (JBYTE)val;
    NEXT(1);
}
OP_STOREARRAY_C:
{
    int val = stack[--sp].I;
    int index = stack[--sp].I;
    Object *object = stack[--sp].O;
    ARRAY_CHECK;
    ARRAY_DATA_C(object)[index] = (JCHAR)val;
    NEXT(1);
}
OP_STOREARRAY_S:
{
    int val = stack[--sp].I;
    int index = stack[--sp].I;
    Object *object = stack[--sp].O;
    ARRAY_CHECK;
    ARRAY_DATA_S(object)[index] = (JCHAR)val;
    NEXT(1);
}
OP_ARRAYLENGTH:
{
    Object *array = stack[sp-1].O;
    NULL_CHECK(array);
    stack[sp-1].I = array->length;
    NEXT(1);
}
OP_IFNULL:
    sp--;
    if(stack[sp].O == NULL) { NEXT(op->index); } else NEXT(1);
    
OP_IFNOTNULL:
    sp--;
    if(stack[sp].O != NULL) { NEXT(op->index); } else NEXT(1);
OP_MONITORENTER:
    sp--;
    NEXT(1)
OP_MONITOREXIT:
    sp--;
    NEXT(1)
OP_TABLE: {
    int key = stack[--sp].I;
    OPSwitch *sw = op->sw;
    if(key < sw->low || key > sw->high) NEXT(sw->def);
    NEXT(sw->offsets[key - sw->low]);
}
OP_LOOKUP:
    {
        int key = stack[--sp].I;
        OPSwitch *sw = op->sw;
        for(int j=0; j<sw->count; j++) {
            if(sw->keys[j] == key) { NEXT(sw->offsets[j]); }
        }
        NEXT(sw->def);
    }
OP_INSTANCEOF:
    op->var.O = (Object*)resolve_class_by_index(vm, method->declaringClass, op->index);
    if(vm->exception) goto __EXCEPTION;
    op->handler = handlers[OP_INSTANCEOFRESOLVED];
    REDISPATCH();
OP_INSTANCEOFRESOLVED:
    stack[sp-1].I = check_cast(vm, stack[sp-1].O, op->var.O);
    NEXT(1);

__EXCEPTION:
    {
        Object *exception = vm->exception;
        vm->exception = NULL;
        
        vm->frames[fp].line = op->line;
        CatchInfo *caught = find_catch_block(vm, omethod, exception, op->pc);
        if(!caught) {
            vm->exception = exception;
            vm->FP--;
            vm->SP -= method->maxStack + method->maxLocals;
            return;
        }
        stack[sp++].O = exception;
        op = (OP*)caught->label;
        NEXT(0);
    }
}
