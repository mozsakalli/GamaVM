#include "jvm.h"

void com_digitoygames_compiler_Test__init____V(VM *vm, Method *method, VAR *args) {
    Frame *frame = &vm->frames[++vm->fp];
    frame->method = method;
    ObjectPtr L0;
    static Method *call1=NULL;
    L0=args[0].O;
    BB0:
    // java/lang/Object:<init>:()V;
    if(!call1) {;
        call1=resolve_method_by_index(vm,method->declaringClass,1);
        if(!call1) ;//todo: throw;
    };
    VAR args1[]={{.O=L0}};
    frame->pc=1;
    ((JVM_CALL)(call1->entry))(vm,call1,&args1[0]);
    ;
    frame=&vm->frames[--vm->fp]; return;
}
void com_digitoygames_compiler_Test_val__DI_I(VM *vm, Method *method, VAR *args) {
    Frame *frame = &vm->frames[++vm->fp];
    frame->method = method;
    jdouble L0;
    jint L1,T0,T1,T2;
    static Field *field2=NULL;
    L0=args[0].D;
    L1=args[1].I;
    BB0:
    T0=(jint)L0;
    T1=T0+12;
    T0=T1+L1;
    if(!field2) {;
        field2=resolve_field_by_index(vm,method->declaringClass,2);;
    };
    T1=field2->declaringClass->globals[field2->offset].I;
    T2=T0+T1;
    frame=&vm->frames[--vm->fp]; frame->retVal.I=T2;return;
}
void com_digitoygames_compiler_Test_test___I(VM *vm, Method *method, VAR *args) {
    Frame *frame = &vm->frames[++vm->fp];
    frame->method = method;
    jint L1,L2,T1,T2;
    ObjectPtr L0,T0;
    BB0:
    T0=alloc_array_B(12);
    L0=T0;
    L1=0;
    BB7:
    T1=((Array*)L0)->length;
    if(L1>=T1) goto BB26;
    BB13:
    T1=L1%2;
    T2=(jbyte)T1;
    L0[L1]=T2;
    L1+=1;
    goto BB7;
    BB26:
    L1=0;
    L2=0;
    BB30:
    if(L2>=12) goto BB48;
    BB36:
    T1=L1+L0[L2];
    L1=T1;
    L2+=1;
    goto BB30;
    BB48:
    frame=&vm->frames[--vm->fp]; frame->retVal.I=L1;return;
}
void com_digitoygames_compiler_Test__clinit____V(VM *vm, Method *method, VAR *args) {
    Frame *frame = &vm->frames[++vm->fp];
    frame->method = method;
    static Field *field2=NULL;
    BB0:
    if(!field2) {;
        field2=resolve_field_by_index(vm,method->declaringClass,2);;
    };
    field2->declaringClass->globals[field2->offset].I=100;
    frame=&vm->frames[--vm->fp]; return;
}
const unsigned char com_digitoygames_compiler_Test_META[]={-54,-2,-70,-66,0,0,0,0,0,33,10,0,4,0,29,9,0,3,0,30,7,0,31,7,0,32,1,0,9,116,101,115,116,70,105,101,108,100,1,0,1,73,1,0,6,60,105,110,105,116,62,1,0,3,40,41,86,1,0,4,67,111,100,101,1,0,15,76,105,110,101,78,117,109,98,101,114,84,97,98,108,101,1,0,18,76,111,99,97,108,86,97,114,105,97,98,108,101,84,97,98,108,101,1,0,4,116,104,105,115,1,0,32,76,99,111,109,47,100,105,103,105,116,111,121,103,97,109,101,115,47,99,111,109,112,105,108,101,114,47,84,101,115,116,59,1,0,3,118,97,108,1,0,5,40,68,73,41,73,1,0,1,100,1,0,1,68,1,0,1,105,1,0,4,116,101,115,116,1,0,3,40,41,73,1,0,5,98,121,116,101,115,1,0,2,91,66,1,0,1,114,1,0,13,83,116,97,99,107,77,97,112,84,97,98,108,101,7,0,22,1,0,8,60,99,108,105,110,105,116,62,1,0,10,83,111,117,114,99,101,70,105,108,101,1,0,9,84,101,115,116,46,106,97,118,97,12,0,7,0,8,12,0,5,0,6,1,0,30,99,111,109,47,100,105,103,105,116,111,121,103,97,109,101,115,47,99,111,109,112,105,108,101,114,47,84,101,115,116,1,0,16,106,97,118,97,47,108,97,110,103,47,79,98,106,101,99,116,0,33,0,3,0,4,0,0,0,1,0,9,0,5,0,6,0,0,0,4,0,1,0,7,0,8,0,1,0,9,0,0,0,42,0,1,0,1,0,0,0,0,0,0,0,2,0,10,0,0,0,6,0,1,0,0,0,23,0,11,0,0,0,12,0,1,0,0,0,5,0,12,0,13,0,0,0,8,0,14,0,15,0,1,0,9,0,0,0,52,0,2,0,3,0,0,0,0,0,0,0,2,0,10,0,0,0,6,0,1,0,0,0,28,0,11,0,0,0,22,0,2,0,0,0,12,0,16,0,17,0,0,0,0,0,12,0,18,0,6,0,2,0,9,0,19,0,20,0,1,0,9,0,0,0,122,0,4,0,3,0,0,0,0,0,0,0,3,0,10,0,0,0,30,0,7,0,0,0,32,0,5,0,33,0,13,0,34,0,20,0,33,0,26,0,36,0,28,0,37,0,48,0,38,0,11,0,0,0,42,0,4,0,7,0,19,0,18,0,6,0,1,0,30,0,18,0,18,0,6,0,2,0,5,0,45,0,21,0,22,0,0,0,28,0,22,0,23,0,6,0,1,0,24,0,0,0,20,0,4,-3,0,7,7,0,25,1,-6,0,18,-3,0,3,1,1,-6,0,17,0,8,0,26,0,8,0,1,0,9,0,0,0,24,0,1,0,0,0,0,0,0,0,0,0,1,0,10,0,0,0,6,0,1,0,0,0,25,0,0,0,27,0,0,0,2,0,28};
const void* com_digitoygames_compiler_Test_METHODS[]={&com_digitoygames_compiler_Test__init____V,&com_digitoygames_compiler_Test_val__DI_I,&com_digitoygames_compiler_Test_test___I,&com_digitoygames_compiler_Test__clinit____V};
AOTClassData AOT[] = {
        {.name="com/digitoygames/compiler/Test", .data=&com_digitoygames_compiler_Test_META[0], .methods=&com_digitoygames_compiler_Test_METHODS[0]},
        {.name=NULL}
};
