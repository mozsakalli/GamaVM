//
//  interpreter.c
//  Digiplay
//
//  Created by mustafa on 12.05.2020.
//  Copyright © 2020 mustafa. All rights reserved.
//

#include "jvm.h"

extern void jstr_print(String *str);

void interpreter_prepare(Method *method, void **handlers) {
    unsigned char *buf = (unsigned char*)method->code;
    unsigned char *start = buf;
    unsigned char *end = buf + method->codeSize;
    OpHandler *opc = method->compiled = (OpHandler*)malloc(sizeof(OpHandler) * method->codeSize);
    OpHandler *opstart = opc;
    
    int wide = 0;
    while(buf < end) {
        opc->pc = (int)(buf - start);
        int op = *buf++;
        //printf(">> op:%x : %d\n", op,op);
        switch(op) {
            case op_iconst_0:
            case op_iconst_1:
            case op_iconst_2:
            case op_iconst_3:
            case op_iconst_4:
            case op_iconst_5:
            case op_ireturn:
            case op_iadd:
            case op_imul:
            case op_idiv:
            case op_dadd:
            case op_dconst_0:
            case op_dconst_1:
            case op_i2d:
            case op_d2i:
            case op_istore_0:
            case op_istore_1:
            case op_istore_2:
            case op_istore_3:
            case op_iload_0:
            case op_iload_1:
            case op_iload_2:
            case op_iload_3:
            case op_dstore_0:
            case op_dstore_1:
            case op_dstore_2:
            case op_dstore_3:
            case op_dload_0:
            case op_dload_1:
            case op_dload_2:
            case op_dload_3:
            {
                opc->handler = handlers[op];
            }
            break;
                
            case op_istore:
            case op_iload:
            case op_dstore:
            case op_dload:
            {
                if(wide) printf("Wide store/load not supported\n");
                else {
                    opc->index = (unsigned)*buf++;
                    opc->handler = handlers[op];
                }
            }
            break;
                
            case op_ldc:
            case op_ldc_w:
            case op_ldc2_w:
            {
                int index;
                if(op == op_ldc)
                    index = *buf++;
                else {
                    Short2Char sc;
                    sc.c1 = (unsigned)*buf++;
                    sc.c0 = (unsigned)*buf++;
                    index = sc.us;
                }
                CPItem *item = &method->declaringClass->cp[index];
                opc->handler = handlers[op_ldc];
                opc->operand = item->value;
            }
            break;
            case op_bipush:
                opc->handler = handlers[op_bipush];
                opc->operand.I = (char)*buf++;
                break;
            case op_sipush:
            case op_if_icmpge:
            case op_goto:
            {
                Short2Char sc;
                sc.c1 = (unsigned)*buf++;
                sc.c0 = (unsigned)*buf++;
                opc->handler = handlers[op];
                opc->operand.I = sc.s;
            }
            break;
                
            case op_iinc:
            {
                if(wide) printf("Wide iinc not supported\n");
                else {
                    opc->handler = handlers[op_iinc];
                    opc->index = (unsigned char)*buf++;
                    opc->operand.I = (char)*buf++;
                }
            }
            break;
                
            case op_invokestatic:
            {
                Short2Char sc;
                sc.c1 = (unsigned)*buf++;
                sc.c0 = (unsigned)*buf++;
                opc->handler = handlers[op];
                opc->index = sc.us;
            }
            break;
                
            default:
                printf("Unknown op:%x / %d\n", op, op);
                return;

        }
        opc++;
    }

    //fix jump targets
    int count = (int)((void*)opc - method->compiled);
    for(int i=0; i<count; i++) {
        if(opstart[i].handler == handlers[op_goto] ||
           opstart[i].handler == handlers[op_ifeq] ||
           opstart[i].handler == handlers[op_ifne] ||
           opstart[i].handler == handlers[op_iflt] ||
           opstart[i].handler == handlers[op_ifge] ||
           opstart[i].handler == handlers[op_ifgt] ||
           opstart[i].handler == handlers[op_ifle] ||
           opstart[i].handler == handlers[op_if_icmpeq] ||
           opstart[i].handler == handlers[op_if_icmpne] ||
           opstart[i].handler == handlers[op_if_icmplt] ||
           opstart[i].handler == handlers[op_if_icmpge] ||
           opstart[i].handler == handlers[op_if_icmpgt] ||
           opstart[i].handler == handlers[op_if_icmple] ||
           opstart[i].handler == handlers[op_if_acmpeq] ||
           opstart[i].handler == handlers[op_if_acmpne] ||
           opstart[i].handler == handlers[op_ifnull] ||
           opstart[i].handler == handlers[op_ifnonnull]
           ) {
            int target = opstart[i].pc + opstart[i].operand.I;
            for(int k=0; k<count; k++)
                if(opstart[k].pc == target) {
                    opstart[i].operand.I = k - i;
                    break;
                }
        }
    }
}

/*
void aot(VM *vm, Method *method, VAR *args) {
    Frame *frame = &vm->frames[++vm->fp];
    frame->method = method;
    VAR stack[2];
    VAR local[2];
    frame->stack = &stack[0];
    memset(stack, 0, sizeof(stack));
    frame->local = &local[0];
    register jint sp = 0;
    
    if(method->argCount > 0)
       memcpy(frame->local, args, sizeof(VAR) * method->argCount);
PC0: frame->pc=0; stack[sp++].I = 0; frame->sp++;
    PC1: frame->pc=1; local[0].I = stack[--sp].I;frame->sp++;
    PC2: frame->pc=2; stack[sp++].I = 0;frame->sp++;
    PC3: frame->pc=3; local[1].I = stack[--sp].I;frame->sp++;
    PC4: frame->pc=4; stack[sp++].I = local[1].I;frame->sp++;
    PC5: frame->pc=5; stack[sp++].I = 1000000;frame->sp++;
    PC7: frame->pc=7; sp -= 2; if(stack[sp].I >= stack[sp+1].I) goto PC20;frame->sp++;
    PC10: frame->pc=10; stack[sp++].I = local[0].I;frame->sp++;
    PC11: frame->pc=11; stack[sp++].I = local[1].I;frame->sp++;
    PC12: frame->pc=12; stack[sp-2].I = stack[sp-2].I + stack[sp-1].I; sp--;frame->sp++;
    PC13: frame->pc=13; local[0].I = stack[--sp].I;frame->sp++;
    PC14: frame->pc=14; local[1].I += 1;frame->sp++;
    PC17: frame->pc=17; goto PC4;frame->sp++;
    PC20: frame->pc=20; stack[sp++].I = local[0].I;frame->sp++;
    PC21: frame->pc=21; vm->fp--; vm->frames[vm->fp].retVal.I = stack[--sp].I; return;
}*/

void interpreter_execute_direct(VM *vm, Method *method, VAR *args) {
    static void *handlers[] = {
        &&op_nop,
        &&op_aconst_null,
        &&op_iconst_m1,
        &&op_iconst_0,
        &&op_iconst_1,
        &&op_iconst_2,
        &&op_iconst_3,
        &&op_iconst_4,
        &&op_iconst_5,
        &&op_lconst_0,
        &&op_lconst_1,
        &&op_fconst_0,
        &&op_fconst_1,
        &&op_fconst_2,
        &&op_dconst_0,
        &&op_dconst_1,
        &&op_bipush,
        &&op_sipush,
        &&op_ldc, // op_ldc -  0x12
        &&op_notimplemented, // op_ldc_w -  0x13
        &&op_notimplemented, // op_ldc2_w -  0x14
        &&op_iload, // op_iload -  0x15
        &&op_notimplemented, // op_lload -  0x16
        &&op_notimplemented, // op_fload -  0x17
        &&op_dload, // op_dload -  0x18
        &&op_notimplemented, // op_aload -  0x19
        &&op_iload_0, // op_iload_0 -  0x1A
        &&op_iload_1, // op_iload_1 -  0x1B
        &&op_iload_2, // op_iload_2 -  0x1C
        &&op_iload_3, // op_iload_3 -  0x1D
        &&op_notimplemented, // op_lload_0 -  0x1E
        &&op_notimplemented, // op_lload_1 -  0x1F
        &&op_notimplemented, // op_lload_2 -  0x20
        &&op_notimplemented, // op_lload_3 -  0x21
        &&op_notimplemented, // op_fload_0 -  0x22
        &&op_notimplemented, // op_fload_1 -  0x23
        &&op_notimplemented, // op_fload_2 -  0x24
        &&op_notimplemented, // op_fload_3 -  0x25
        &&op_dload_0, // op_dload_0 -  0x26
        &&op_dload_1, // op_dload_1 -  0x27
        &&op_dload_2, // op_dload_2 -  0x28
        &&op_dload_3, // op_dload_3 -  0x29
        &&op_notimplemented, // op_aload_0 -  0x2A
        &&op_notimplemented, // op_aload_1 -  0x2B
        &&op_notimplemented, // op_aload_2 -  0x2C
        &&op_notimplemented, // op_aload_3 -  0x2D
        &&op_notimplemented, // op_iaload -  0x2E
        &&op_notimplemented, // op_laload -  0x2F
        &&op_notimplemented, // op_faload -  0x30
        &&op_notimplemented, // op_daload -  0x31
        &&op_notimplemented, // op_aaload -  0x32
        &&op_notimplemented, // op_baload -  0x33
        &&op_notimplemented, // op_caload -  0x34
        &&op_notimplemented, // op_saload -  0x35
        &&op_istore, // op_istore -  0x36
        &&op_notimplemented, // op_lstore -  0x37
        &&op_notimplemented, // op_fstore -  0x38
        &&op_dstore, // op_dstore -  0x39
        &&op_notimplemented, // op_astore -  0x3A
        &&op_istore_0, // op_istore_0 -  0x3B
        &&op_istore_1, // op_istore_1 -  0x3C
        &&op_istore_2, // op_istore_2 -  0x3D
        &&op_istore_3, // op_istore_3 -  0x3E
        &&op_notimplemented, // op_lstore_0 -  0x3F
        &&op_notimplemented, // op_lstore_1 -  0x40
        &&op_notimplemented, // op_lstore_2 -  0x41
        &&op_notimplemented, // op_lstore_3 -  0x42
        &&op_notimplemented, // op_fstore_0 -  0x43
        &&op_notimplemented, // op_fstore_1 -  0x44
        &&op_notimplemented, // op_fstore_2 -  0x45
        &&op_notimplemented, // op_fstore_3 -  0x46
        &&op_dstore_0, // op_dstore_0 -  0x47
        &&op_dstore_1, // op_dstore_1 -  0x48
        &&op_dstore_2, // op_dstore_2 -  0x49
        &&op_dstore_3, // op_dstore_3 -  0x4A
        &&op_notimplemented, // op_astore_0 -  0x4B
        &&op_notimplemented, // op_astore_1 -  0x4C
        &&op_notimplemented, // op_astore_2 -  0x4D
        &&op_notimplemented, // op_astore_3 -  0x4E
        &&op_notimplemented, // op_iastore -  0x4F
        &&op_notimplemented, // op_lastore -  0x50
        &&op_notimplemented, // op_fastore -  0x51
        &&op_notimplemented, // op_dastore -  0x52
        &&op_notimplemented, // op_aastore -  0x53
        &&op_notimplemented, // op_bastore -  0x54
        &&op_notimplemented, // op_castore -  0x55
        &&op_notimplemented, // op_sastore -  0x56
        &&op_notimplemented, // op_pop -  0x57
        &&op_notimplemented, // op_pop2 -  0x58
        &&op_notimplemented, // op_dup -  0x59
        &&op_notimplemented, // op_dup_x1 -  0x5A
        &&op_notimplemented, // op_dup_x2 -  0x5B
        &&op_notimplemented, // op_dup2 -  0x5C
        &&op_notimplemented, // op_dup2_x1 -  0x5D
        &&op_notimplemented, // op_dup2_x2 -  0x5E
        &&op_notimplemented, // op_swap -  0x5F
        &&op_iadd, // op_iadd -  0x60
        &&op_notimplemented, // op_ladd -  0x61
        &&op_notimplemented, // op_fadd -  0x62
        &&op_dadd, // op_dadd -  0x63
        &&op_notimplemented, // op_isub -  0x64
        &&op_notimplemented, // op_lsub -  0x65
        &&op_notimplemented, // op_fsub -  0x66
        &&op_notimplemented, // op_dsub -  0x67
        &&op_imul, // op_imul -  0x68
        &&op_notimplemented, // op_lmul -  0x69
        &&op_notimplemented, // op_fmul -  0x6A
        &&op_notimplemented, // op_dmul -  0x6B
        &&op_idiv, // op_idiv -  0x6C
        &&op_notimplemented, // op_ldiv -  0x6D
        &&op_notimplemented, // op_fdiv -  0x6E
        &&op_notimplemented, // op_ddiv -  0x6F
        &&op_notimplemented, // op_irem -  0x70
        &&op_notimplemented, // op_lrem -  0x71
        &&op_notimplemented, // op_frem -  0x72
        &&op_notimplemented, // op_drem -  0x73
        &&op_notimplemented, // op_ineg -  0x74
        &&op_notimplemented, // op_lneg -  0x75
        &&op_notimplemented, // op_fneg -  0x76
        &&op_notimplemented, // op_dneg -  0x77
        &&op_notimplemented, // op_ishl -  0x78
        &&op_notimplemented, // op_lshl -  0x79
        &&op_notimplemented, // op_ishr -  0x7A
        &&op_notimplemented, // op_lshr -  0x7B
        &&op_notimplemented, // op_iushr -  0x7C
        &&op_notimplemented, // op_lushr -  0x7D
        &&op_notimplemented, // op_iand -  0x7E
        &&op_notimplemented, // op_land -  0x7F
        &&op_notimplemented, // op_ior -  0x80
        &&op_notimplemented, // op_lor -  0x81
        &&op_notimplemented, // op_ixor -  0x82
        &&op_notimplemented, // op_lxor -  0x83
        &&op_iinc, // op_iinc -  0x84
        &&op_notimplemented, // op_i2l -  0x85
        &&op_notimplemented, // op_i2f -  0x86
        &&op_i2d, // op_i2d -  0x87
        &&op_notimplemented, // op_l2i -  0x88
        &&op_notimplemented, // op_l2f -  0x89
        &&op_notimplemented, // op_l2d -  0x8A
        &&op_notimplemented, // op_f2i -  0x8B
        &&op_notimplemented, // op_f2l -  0x8C
        &&op_notimplemented, // op_f2d -  0x8D
        &&op_d2i, // op_d2i -  0x8E
        &&op_notimplemented, // op_d2l -  0x8F
        &&op_notimplemented, // op_d2f -  0x90
        &&op_notimplemented, // op_i2b -  0x91
        &&op_notimplemented, // op_i2c -  0x92
        &&op_notimplemented, // op_i2s -  0x93
        &&op_notimplemented, // op_lcmp -  0x94
        &&op_notimplemented, // op_fcmpl -  0x95
        &&op_notimplemented, // op_fcmpg -  0x96
        &&op_notimplemented, // op_dcmpl -  0x97
        &&op_notimplemented, // op_dcmpg -  0x98
        &&op_notimplemented, // op_ifeq -  0x99
        &&op_notimplemented, // op_ifne -  0x9A
        &&op_notimplemented, // op_iflt -  0x9B
        &&op_notimplemented, // op_ifge -  0x9C
        &&op_notimplemented, // op_ifgt -  0x9D
        &&op_notimplemented, // op_ifle -  0x9E
        &&op_notimplemented, // op_if_icmpeq -  0x9F
        &&op_notimplemented, // op_if_icmpne -  0xA0
        &&op_notimplemented, // op_if_icmplt -  0xA1
        &&op_if_icmpge, // op_if_icmpge -  0xA2
        &&op_notimplemented, // op_if_icmpgt -  0xA3
        &&op_notimplemented, // op_if_icmple -  0xA4
        &&op_notimplemented, // op_if_acmpeq -  0xA5
        &&op_notimplemented, // op_if_acmpne -  0xA6
        &&op_goto, // op_goto -  0xA7
        &&op_notimplemented, // op_jsr -  0xA8
        &&op_notimplemented, // op_ret -  0xA9
        &&op_notimplemented, // op_tableswitch -  0xAA
        &&op_notimplemented, // op_lookupswitch -  0xAB
        &&op_ireturn, // op_ireturn -  0xAC
        &&op_notimplemented, // op_lreturn -  0xAD
        &&op_notimplemented, // op_freturn -  0xAE
        &&op_notimplemented, // op_dreturn -  0xAF
        &&op_notimplemented, // op_areturn -  0xB0
        &&op_notimplemented, // op_return -  0xB1
        &&op_notimplemented, // op_getstatic -  0xB2
        &&op_notimplemented, // op_putstatic -  0xB3
        &&op_notimplemented, // op_getfield -  0xB4
        &&op_notimplemented, // op_putfield -  0xB5
        &&op_notimplemented, // op_invokevirtual -  0xB6
        &&op_notimplemented, // op_invokespecial -  0xB7
        &&op_invokestatic, // op_invokestatic -  0xB8
        &&op_notimplemented, // op_invokeinterface -  0xB9
        &&op_notimplemented, // op_invokedynamic -  0xBA
        &&op_notimplemented, // op_new -  0xBB
        &&op_notimplemented, // op_newarray -  0xBC
        &&op_notimplemented, // op_anewarray -  0xBD
        &&op_notimplemented, // op_arraylength -  0xBE
        &&op_notimplemented, // op_athrow -  0xBF
        &&op_notimplemented, // op_checkcast -  0xC0
        &&op_notimplemented, // op_instanceof -  0xC1
        &&op_notimplemented, // op_monitorenter -  0xC2
        &&op_notimplemented, // op_monitorexit -  0xC3
        &&op_notimplemented, // op_wide -  0xC4
        &&op_notimplemented, // op_multianewarray -  0xC5
        &&op_notimplemented, // op_ifnull -  0xC6
        &&op_notimplemented, // op_ifnonnull -  0xC7
        &&op_notimplemented, // op_goto_w -  0xC8
        &&op_notimplemented, // op_jsr_w -  0xC9
        &&op_notimplemented, // op_breakpoint -  0xCA
        &&op_notimplemented, // op_getstatic_ref -  0xCB //
        &&op_notimplemented, // op_getstatic_long -  0xCC
        &&op_notimplemented, // op_getstatic_int -  0xCD
        &&op_notimplemented, // op_getstatic_short -  0xCE
        &&op_notimplemented, // op_getstatic_jchar -  0xCF
        &&op_notimplemented, // op_getstatic_byte -  0xD0
        &&op_notimplemented, // op_putstatic_ref -  0xD1
        &&op_notimplemented, // op_putstatic_long -  0xD2
        &&op_notimplemented, // op_putstatic_int -  0xD3
        &&op_notimplemented, // op_putstatic_short -  0xD4
        &&op_notimplemented, // op_putstatic_byte -  0xD5
        &&op_notimplemented, // op_getfield_ref -  0xD6
        &&op_notimplemented, // op_getfield_long -  0xD7
        &&op_notimplemented, // op_getfield_int -  0xD8
        &&op_notimplemented, // op_getfield_short -  0xD9
        &&op_notimplemented, // op_getfield_jchar -  0xDA
        &&op_notimplemented, // op_getfield_byte -  0xDB
        &&op_notimplemented, // op_putfield_ref -  0xDC
        &&op_notimplemented, // op_putfield_long -  0xDD
        &&op_notimplemented, // op_putfield_int -  0xDE
        &&op_notimplemented, // op_putfield_short -  0xDF
        &&op_notimplemented, // op_putfield_byte -  0xE0
        &&op_notimplemented, // op_invokevirtual_fast -  0xE1
        &&op_notimplemented, // op_invokespecial_fast -  0xE2
        &&op_invokestatic_fast, // op_invokestatic_fast -  0xE3
        &&op_notimplemented, // op_invokeinterface_fast -  0xE4
        &&op_notimplemented, // op_invokedynamic_fast -  0xE5
        &&op_notimplemented, // op_0xF6 -  0xE6
        &&op_notimplemented, // op_0xF -  0xE7
        &&op_notimplemented, // op_0xF7 -  0xE8
        &&op_notimplemented, // op_0xF8 -  0xE9
        &&op_notimplemented, // op_0xF9 -  0xEA
        &&op_notimplemented, // op_0xFA -  0xEB
        &&op_notimplemented, // op_0xFB -  0xEC
        &&op_notimplemented, // op_0xFC -  0xED
        &&op_notimplemented, // op_0xFD -  0xEE
        &&op_notimplemented, // op_0xFE -  0xEF
    };

    Frame *frame = &vm->frames[++vm->fp];
    frame->method = method;

    OpHandler *op = (OpHandler *)frame->method->compiled;
    if(!op) {
        interpreter_prepare(frame->method, handlers);
        free(frame->method->code);
        frame->method->code = NULL;
        op = (OpHandler *)frame->method->compiled;
    }

    VAR stack[frame->method->maxStack];
    VAR local[frame->method->maxLocals];
    
    frame->stack = &stack[0];
    frame->local = &local[0];
    memset(stack, 0, sizeof(stack));
    jint sp = 0;

    int argCount = method->argCount;
    if(argCount > 0) {
        jint *map = method->argMap;
        for(int i=0; i<argCount; i++) {
            //printf("argmap %d -> %d for i:%d f:%lf\n", i, map[i],args[i].I,args[i].D);
            local[map[i]] = args[i];
        }
    }

    #define NEXT(d) op += d; /*frame->pc = op->pc; */goto *op->handler;
    NEXT(0);
            
    op_nop:
        NEXT(1);
        
    op_aconst_null:
        stack[sp++].O = NULL;
        NEXT(1);
        
    op_iconst_m1:
        stack[sp++].I = -1;
        NEXT(1);
        
    op_iconst_0:
        stack[sp++].I = 0;
        NEXT(1);
    op_iconst_1:
        stack[sp++].I = 1;
        NEXT(1);
    op_iconst_2:
        stack[sp++].I = 2;
        NEXT(1);
    op_iconst_3:
        stack[sp++].I = 3;
        NEXT(1);
    op_iconst_4:
        stack[sp++].I = 4;
        NEXT(1);
    op_iconst_5:
        stack[sp++].I = 5;
        NEXT(1);
    op_lconst_0:
        stack[sp++].J = 0;
        NEXT(1);
    op_lconst_1:
        stack[sp++].J = 1;
        NEXT(1);
    op_fconst_0:
        stack[sp++].F = 0.0f;
        NEXT(1);
    op_fconst_1:
        stack[sp++].F = 1.0f;
        NEXT(1);
    op_fconst_2:
        stack[sp++].F = 2.0f;
        NEXT(1);
    op_dconst_0:
        stack[sp++].D = 0;
        NEXT(1);
    op_dconst_1:
        stack[sp++].D = 1;
        NEXT(1);
    op_bipush:
        stack[sp++].I = op->operand.I;
        NEXT(1);
    op_sipush:
        stack[sp++].I = op->operand.I;
        NEXT(1);
    op_ldc:
        stack[sp++] = op->operand;
        NEXT(1);
    op_istore_0:
        local[0].I = stack[--sp].I;
        NEXT(1);
    op_istore_1:
        local[1].I = stack[--sp].I;
        NEXT(1);
    op_istore_2:
        local[2].I = stack[--sp].I;
        NEXT(1);
    op_istore_3:
        local[3].I = stack[--sp].I;
        NEXT(1);
    op_istore:
        local[op->index].I = stack[--sp].I;
        NEXT(1);
    op_iload_0:
        stack[sp++].I = local[0].I;
        NEXT(1);
    op_iload_1:
        stack[sp++].I = local[1].I;
        NEXT(1);
    op_iload_2:
        stack[sp++].I = local[2].I;
        NEXT(1);
    op_iload_3:
        stack[sp++].I = local[3].I;
        NEXT(1);
    op_iload:
        stack[sp++].I = local[op->index].I;
        NEXT(1);
    op_dstore_0:
        local[0].D = stack[--sp].D;
        NEXT(1);
    op_dstore_1:
        local[1].D = stack[--sp].D;
        NEXT(1);
    op_dstore_2:
        local[2].D = stack[--sp].D;
        NEXT(1);
    op_dstore_3:
        local[3].D = stack[--sp].D;
        NEXT(1);
    op_dstore:
        local[op->index].D = stack[--sp].D;
        NEXT(2);
    op_dload_0:
        stack[sp++].D = local[0].D;
        NEXT(1);
    op_dload_1:
        stack[sp++].D = local[1].D;
        NEXT(1);
    op_dload_2:
        stack[sp++].D = local[2].D;
        NEXT(1);
    op_dload_3:
        stack[sp++].D = local[3].D;
        NEXT(1);
    op_dload:
        stack[sp++].D = local[op->index].D;
        NEXT(1);
    op_iadd:
        stack[sp-2].I += stack[sp-1].I;
        sp--;
        NEXT(1);
    op_imul:
        stack[sp-2].I *= stack[sp-1].I;
        sp--;
        NEXT(1);
    op_idiv:
        //todo: check zero
        stack[sp-2].I /= stack[sp-1].I;
        sp--;
        NEXT(1);
    op_dadd:
        stack[sp-2].D += stack[sp-1].D;
        sp--;
        NEXT(1);
    op_iinc:
        local[op->index].I += op->operand.I;
        NEXT(1);
    op_if_icmpge:
        sp -= 2;
        if(stack[sp].I >= stack[sp+1].I) {
            NEXT(op->operand.I);
        } else NEXT(1);
    op_goto:
        NEXT(op->operand.I);
    op_ireturn:
        vm->fp--;
        vm->frames[vm->fp].retVal.I = stack[--sp].I;
        return;
    op_i2d:
        stack[sp-1].D = stack[sp-1].I;
        NEXT(1);
    op_d2i:
        stack[sp-1].I = (jint)stack[sp-1].D;
        NEXT(1);
    op_invokestatic:
    {
        Method *m = resolve_method_by_index(vm, method->declaringClass, op->index);
        if(!m) {
            //todo: throw exception
        }
        op->operand.O = (Object*)m;
        op->handler = handlers[op_invokestatic_fast];
        NEXT(0);
    }
    op_invokestatic_fast:
    {
        Method *m = (Method*)op->operand.O;
        //for(int i=0; i<sp; i++)
        //    printf("stack-%d = i:%d f:%lf\n", i, stack[i].I, stack[i].D);
        sp -= m->argCount;
        VAR* args = &stack[sp];
        frame->pc = op->pc;
        int retType = ((jchar*)m->signature->chars->data)[m->signature->length-1];
        switch(retType) {
            case 'I':
                stack[sp++].I = call_java_I(vm, m, args);
                break;
            default:
                printf("Unknown return type: %c\n",retType);
        }
        NEXT(1);
    }

    op_notimplemented:
        printf("Not implemented!\n");
        vm->fp--;
        return;
}

void call_java_V(VM *vm, Method *method, VAR *args) {
    ((JVM_CALL)(method->entry))(vm,method,args);
}

jint call_java_I(VM *vm, Method *method, VAR *args) {
    ((JVM_CALL)(method->entry))(vm,method,args);
    return vm->frames[vm->fp].retVal.I;
}

ObjectPtr call_java_O(VM *vm, Method *method, VAR *args) {
    ((JVM_CALL)(method->entry))(vm,method,args);
    return vm->frames[vm->fp].retVal.O;
}


