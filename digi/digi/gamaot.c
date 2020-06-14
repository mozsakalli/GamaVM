#include "vm.h"
#include <math.h>
Object **aot_strings;

//Main
static Field *f2390489_2=NULL,*f2390489_7=NULL;
static JLONG m2390489_1=0,m2390489_4=0,m2390489_6=0,m2390489_8=0,m2390489_9=0,m2390489_10=0,m2390489_12=0;
static Object *c2390489_3=NULL,*c2390489_11=NULL,*c2390489_13=NULL,*c2390489_14=NULL,*c2390489_35=NULL,*c2390489_43=NULL;
void Main__init____V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	Object *L0;
	L0=args[0].O;
BB0:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=1;
	  AOTMETHOD(m2390489_1,0,1,2); //java/lang/Object:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m2390489_1),entry)))(vm,m2390489_1,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void Main_main___V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	Object *L0,*T0,*T1,*T2;
	Object *caughtException;
BB0:
	L0=NULL;
	AOTFIELD(f2390489_2,3,4,5); //java/lang/System:out:Ljava/io/PrintStream;
	T0 = *((Object**)(CLS(f2390489_2->declaringClass,global) + f2390489_2->offset));
	AOTCLASS(c2390489_3,6);
	T1=alloc_object(vm,c2390489_3,0);
	{
	  VAR cargs[]={{.O=T1}};
	  frame->pc=9;
	  AOTMETHOD(m2390489_4,6,1,2); //java/lang/StringBuilder:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m2390489_4),entry)))(vm,m2390489_4,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	{
	  VAR cargs[]={{.O=T1},{.O=aot_strings[7]}};
	  frame->pc=14;
	  AOTVMETHOD(m2390489_6,6,8,9,vTableIndex); //java/lang/StringBuilder:append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m2390489_6];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T1=frame->ret.O;
	}
	
	AOTFIELD(f2390489_7,10,11,12); //Main:obj:Ljava/lang/Object;
	if(!L0) { frame->pc = 18; throw_null(vm); goto __EXCEPTION; }
	T2 = *FIELD_PTR_O(L0,f2390489_7->offset);
	{
	  VAR cargs[]={{.O=T1},{.O=T2}};
	  frame->pc=21;
	  AOTVMETHOD(m2390489_8,6,8,13,vTableIndex); //java/lang/StringBuilder:append:(Ljava/lang/Object;)Ljava/lang/StringBuilder;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m2390489_8];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T1=frame->ret.O;
	}
	
	{
	  VAR cargs[]={{.O=T1}};
	  frame->pc=24;
	  AOTVMETHOD(m2390489_9,6,14,15,vTableIndex); //java/lang/StringBuilder:toString:()Ljava/lang/String;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m2390489_9];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T1=frame->ret.O;
	}
	
	{
	  VAR cargs[]={{.O=T0},{.O=T1}};
	  frame->pc=27;
	  AOTVMETHOD(m2390489_10,16,17,18,vTableIndex); //java/io/PrintStream:println:(Ljava/lang/String;)V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m2390489_10];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	goto BB38;
BB33:
	L0=caughtException;
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=35;
	  AOTVMETHOD(m2390489_12,19,20,2,vTableIndex); //java/lang/Exception:printStackTrace:()V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m2390489_12];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
BB38:
	vm->FP--;return;
__EXCEPTION: {
	caughtException = vm->exception;
	vm->exception = NULL;
	if(frame->pc >= 0 && frame->pc < 30) {
		AOTCLASS(c2390489_11,19);
		if(check_cast(vm,caughtException->cls,c2390489_11))
			goto BB33;
	}
	vm->exception = caughtException;
	vm->FP--; return;
}
}
void Main_main___Ljava_lang_String__V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
BB0:
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void aot_init(VM *vm) {
	static  int i=0; if(i) return; i=1;
	aot_strings = (Object**)malloc(sizeof(Object*)*21);
	aot_strings[19] = alloc_string_java(vm,(JCHAR[]){106,97,118,97,47,108,97,110,103,47,69,120,99,101,112,116,105,111,110},19,1);
	aot_strings[6] = alloc_string_java(vm,(JCHAR[]){106,97,118,97,47,108,97,110,103,47,83,116,114,105,110,103,66,117,105,108,100,101,114},23,1);
	aot_strings[20] = alloc_string_java(vm,(JCHAR[]){112,114,105,110,116,83,116,97,99,107,84,114,97,99,101},15,1);
	aot_strings[15] = alloc_string_java(vm,(JCHAR[]){40,41,76,106,97,118,97,47,108,97,110,103,47,83,116,114,105,110,103,59},20,1);
	aot_strings[12] = alloc_string_java(vm,(JCHAR[]){76,106,97,118,97,47,108,97,110,103,47,79,98,106,101,99,116,59},18,1);
	aot_strings[18] = alloc_string_java(vm,(JCHAR[]){40,76,106,97,118,97,47,108,97,110,103,47,83,116,114,105,110,103,59,41,86},21,1);
	aot_strings[1] = alloc_string_java(vm,(JCHAR[]){60,105,110,105,116,62},6,1);
	aot_strings[16] = alloc_string_java(vm,(JCHAR[]){106,97,118,97,47,105,111,47,80,114,105,110,116,83,116,114,101,97,109},19,1);
	aot_strings[4] = alloc_string_java(vm,(JCHAR[]){111,117,116},3,1);
	aot_strings[17] = alloc_string_java(vm,(JCHAR[]){112,114,105,110,116,108,110},7,1);
	aot_strings[0] = alloc_string_java(vm,(JCHAR[]){106,97,118,97,47,108,97,110,103,47,79,98,106,101,99,116},16,1);
	aot_strings[2] = alloc_string_java(vm,(JCHAR[]){40,41,86},3,1);
	aot_strings[11] = alloc_string_java(vm,(JCHAR[]){111,98,106},3,1);
	aot_strings[7] = alloc_string_java(vm,(JCHAR[]){72,101,108,108,111,32,65,79,84,33,33,32,45,62,32},15,1);
	aot_strings[14] = alloc_string_java(vm,(JCHAR[]){116,111,83,116,114,105,110,103},8,1);
	aot_strings[13] = alloc_string_java(vm,(JCHAR[]){40,76,106,97,118,97,47,108,97,110,103,47,79,98,106,101,99,116,59,41,76,106,97,118,97,47,108,97,110,103,47,83,116,114,105,110,103,66,117,105,108,100,101,114,59},45,1);
	aot_strings[5] = alloc_string_java(vm,(JCHAR[]){76,106,97,118,97,47,105,111,47,80,114,105,110,116,83,116,114,101,97,109,59},21,1);
	aot_strings[10] = alloc_string_java(vm,(JCHAR[]){77,97,105,110},4,1);
	aot_strings[9] = alloc_string_java(vm,(JCHAR[]){40,76,106,97,118,97,47,108,97,110,103,47,83,116,114,105,110,103,59,41,76,106,97,118,97,47,108,97,110,103,47,83,116,114,105,110,103,66,117,105,108,100,101,114,59},45,1);
	aot_strings[8] = alloc_string_java(vm,(JCHAR[]){97,112,112,101,110,100},6,1);
	aot_strings[3] = alloc_string_java(vm,(JCHAR[]){106,97,118,97,47,108,97,110,103,47,83,121,115,116,101,109},16,1);
}
NativeMethodInfo aot_native_methods[] = {
	{"Main:<init>:()V",&Main__init____V}
	,{"Main:main:()V",&Main_main___V}
	,{"Main:main:([Ljava/lang/String;)V",&Main_main___Ljava_lang_String__V}
	,NULL
};
