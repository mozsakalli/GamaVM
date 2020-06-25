#include "vm.h"
#include <math.h>
Object **aot_strings;

//Main
static Field *f2390489_4=NULL;
static JLONG m2390489_1=0,m2390489_3=0,m2390489_7=0,m2390489_8=0;
static Object *c2390489_2=NULL,*c2390489_6=NULL,*c2390489_9=NULL,*c2390489_10=NULL,*c2390489_29=NULL;
void Main__init____V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	VAR* ARGBUF = &vm->stack[vm->SP];
	vm->SP += 1;
	Object *L0;
	L0=args[0].O;
	if(!L0) goto __EXCEPTION;
BB0:
	{
	ARGBUF[0].O=L0;  frame->pc=1;
	  AOTMETHOD(m2390489_1,0,1,2); //java/lang/Object:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m2390489_1),entry)))(vm,m2390489_1,ARGBUF);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;vm->SP -= 1;return;
__EXCEPTION: {
	vm->FP--; vm->SP -= 1; return;
}
}
void Main_main___V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	VAR* ARGBUF = &vm->stack[vm->SP];
	vm->SP += 4;
	JFLOAT T1,T2,T3;
	Object *L0,*T0;
BB0:
	AOTCLASS(c2390489_2,3);
	T0=alloc_object(vm,c2390489_2,0);
	{
	ARGBUF[0].O=T0;  frame->pc=4;
	  AOTMETHOD(m2390489_3,3,1,2); //Main$T:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m2390489_3),entry)))(vm,m2390489_3,ARGBUF);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	L0=T0;
	AOTFIELD(f2390489_4,3,4,5); //Main$T:a:F;
	if(!L0) { frame->pc = 10; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_F(L0,f2390489_4->offset);
	//Main$T:a:F;
	if(!L0) { frame->pc = 14; throw_null(vm); goto __EXCEPTION; }
	T2 = *FIELD_PTR_F(L0,f2390489_4->offset);
	T3 = T2 * 12.0;
	T2 = T1 + T3;
	//Main$T:a:F;
	if(!L0) { frame->pc = 22; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_F(L0,f2390489_4->offset);
	T3 = T2 - T1;
	//Main$T:a:F;
	if(!L0) { frame->pc = 26; throw_null(vm); goto __EXCEPTION; }
	*FIELD_PTR_F(L0,f2390489_4->offset) = T3;
	AOTCLASS(c2390489_6,6);
	T0=alloc_object(vm,c2390489_6,0);
	{
	ARGBUF[0].O=T0;  frame->pc=33;
	  AOTMETHOD(m2390489_7,6,1,2); //Player:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m2390489_7),entry)))(vm,m2390489_7,ARGBUF);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	{
	ARGBUF[0].O=T0;  frame->pc=36;
	  AOTMETHOD(m2390489_8,7,8,9); //digiplay/Platform:run:(Ldigiplay/Game;)V;
	  ((VM_CALL)(MTH(((Object*)m2390489_8),entry)))(vm,m2390489_8,ARGBUF);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;vm->SP -= 4;return;
__EXCEPTION: {
	vm->FP--; vm->SP -= 4; return;
}
}
void aot_init(VM *vm) {
	static  int i=0; if(i) return; i=1;
	aot_strings = (Object**)malloc(sizeof(Object*)*10);
	aot_strings[4] = alloc_string_java(vm,(JCHAR[]){97},1,1);
	aot_strings[6] = alloc_string_java(vm,(JCHAR[]){80,108,97,121,101,114},6,1);
	aot_strings[0] = alloc_string_java(vm,(JCHAR[]){106,97,118,97,47,108,97,110,103,47,79,98,106,101,99,116},16,1);
	aot_strings[9] = alloc_string_java(vm,(JCHAR[]){40,76,100,105,103,105,112,108,97,121,47,71,97,109,101,59,41,86},18,1);
	aot_strings[3] = alloc_string_java(vm,(JCHAR[]){77,97,105,110,36,84},6,1);
	aot_strings[2] = alloc_string_java(vm,(JCHAR[]){40,41,86},3,1);
	aot_strings[5] = alloc_string_java(vm,(JCHAR[]){70},1,1);
	aot_strings[8] = alloc_string_java(vm,(JCHAR[]){114,117,110},3,1);
	aot_strings[1] = alloc_string_java(vm,(JCHAR[]){60,105,110,105,116,62},6,1);
	aot_strings[7] = alloc_string_java(vm,(JCHAR[]){100,105,103,105,112,108,97,121,47,80,108,97,116,102,111,114,109},17,1);
}
NativeMethodInfo aot_native_methods[] = {
	{"Main:<init>:()V",&Main__init____V}
	,{"Main:main:()V",&Main_main___V}
	,NULL
};
