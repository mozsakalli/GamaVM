#include "jvm.h"

void com_digitoygames_compiler_Test__init____V(VM *vm, Method *method, VAR *args) {
    Frame *frame = &vm->frames[++vm->FP];
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
    frame=&vm->frames[--vm->FP]; return;
}
void com_digitoygames_compiler_Test_fibonacci__I_I(VM *vm, Method *method, VAR *args) {
    Frame *frame = &vm->frames[++vm->FP];
    frame->method = method;
    jint L0,T0,T1,T2;
    static Method *call2=NULL;
    L0=args[0].I;
BB0:
    if(L0==0) goto BB9;
BB4:
    if(L0!=1) goto BB11;
BB9:
    frame=&vm->frames[--vm->FP]; frame->retVal.I=L0;return;
BB11:
    T0=L0-1;
    // com/digitoygames/compiler/Test:fibonacci:(I)I;
    if(!call2) {;
      call2=resolve_method_by_index(vm,method->declaringClass,2);
      if(!call2) ;//todo: throw;
    };
    VAR args14[]={{.I=T0}};
    frame->pc=14;
    ((JVM_CALL)(call2->entry))(vm,call2,&args14[0]);
    T0=frame->retVal.I;;
    T1=L0-2;
    // com/digitoygames/compiler/Test:fibonacci:(I)I;
    if(!call2) {;
      call2=resolve_method_by_index(vm,method->declaringClass,2);
      if(!call2) ;//todo: throw;
    };
    VAR args20[]={{.I=T1}};
    frame->pc=20;
    ((JVM_CALL)(call2->entry))(vm,call2,&args20[0]);
    T1=frame->retVal.I;;
    T2=T0+T1;
    frame=&vm->frames[--vm->FP]; frame->retVal.I=T2;return;
}
void com_digitoygames_compiler_Test_main___I(VM *vm, Method *method, VAR *args) {
    Frame *frame = &vm->frames[++vm->FP];
    frame->method = method;
    jint L0,L1,T0;
BB0:
    L0=0;
    L1=0;
BB4:
    if(L1>=1000000) goto BB20;
BB10:
    T0=L0+L1;
    L0=T0;
    L1+=1;
    goto BB4;
BB20:
    frame=&vm->frames[--vm->FP]; frame->retVal.I=L0;return;
}
const unsigned char com_digitoygames_compiler_Test_META[]={-54,-2,-70,-66,0,0,0,0,0,28,10,0,5,0,24,10,0,4,0,25,3,0,15,66,64,7,0,26,7,0,27,1,0,6,60,105,110,105,116,62,1,0,3,40,41,86,1,0,4,67,111,100,101,1,0,15,76,105,110,101,78,117,109,98,101,114,84,97,98,108,101,1,0,18,76,111,99,97,108,86,97,114,105,97,98,108,101,84,97,98,108,101,1,0,4,116,104,105,115,1,0,32,76,99,111,109,47,100,105,103,105,116,111,121,103,97,109,101,115,47,99,111,109,112,105,108,101,114,47,84,101,115,116,59,1,0,9,102,105,98,111,110,97,99,99,105,1,0,4,40,73,41,73,1,0,1,110,1,0,1,73,1,0,13,83,116,97,99,107,77,97,112,84,97,98,108,101,1,0,4,109,97,105,110,1,0,3,40,41,73,1,0,1,107,1,0,1,114,1,0,10,83,111,117,114,99,101,70,105,108,101,1,0,9,84,101,115,116,46,106,97,118,97,12,0,6,0,7,12,0,13,0,14,1,0,30,99,111,109,47,100,105,103,105,116,111,121,103,97,109,101,115,47,99,111,109,112,105,108,101,114,47,84,101,115,116,1,0,16,106,97,118,97,47,108,97,110,103,47,79,98,106,101,99,116,0,33,0,4,0,5,0,0,0,0,0,3,0,1,0,6,0,7,0,1,0,8,0,0,0,42,0,1,0,1,0,0,0,0,0,0,0,2,0,9,0,0,0,6,0,1,0,0,0,23,0,10,0,0,0,12,0,1,0,0,0,5,0,11,0,12,0,0,0,8,0,13,0,14,0,1,0,8,0,0,0,60,0,3,0,1,0,0,0,0,0,0,0,3,0,9,0,0,0,14,0,3,0,0,0,26,0,9,0,27,0,11,0,29,0,10,0,0,0,12,0,1,0,0,0,25,0,15,0,16,0,0,0,17,0,0,0,4,0,2,9,1,0,9,0,18,0,19,0,1,0,8,0,0,0,76,0,2,0,2,0,0,0,0,0,0,0,3,0,9,0,0,0,14,0,3,0,0,0,33,0,2,0,34,0,20,0,35,0,10,0,0,0,22,0,2,0,4,0,16,0,20,0,16,0,1,0,2,0,20,0,21,0,16,0,0,0,17,0,0,0,10,0,2,-3,0,4,1,1,-6,0,15,0,0,0,22,0,0,0,2,0,23};
const void* com_digitoygames_compiler_Test_METHODS[]={&com_digitoygames_compiler_Test__init____V,&com_digitoygames_compiler_Test_fibonacci__I_I,&com_digitoygames_compiler_Test_main___I};
AOTClassData AOT[] = {
    {.name="com/digitoygames/compiler/Test", .data=&com_digitoygames_compiler_Test_META[0], .methods=&com_digitoygames_compiler_Test_METHODS[0]}
};
