#include "vm.h"
#include <math.h>
Object **aot_strings;

//digiplay/Image
static Field *f1463228935_15=NULL,*f1463228935_21=NULL,*f1463228935_27=NULL,*f1463228935_31=NULL,*f1463228935_52=NULL,*f1463228935_58=NULL,*f1463228935_66=NULL,*f1463228935_70=NULL,*f1463228935_74=NULL,*f1463228935_77=NULL,*f1463228935_80=NULL,*f1463228935_93=NULL,*f1463228935_104=NULL;
static JLONG m1463228935_1=0,m1463228935_7=0,m1463228935_24=0,m1463228935_37=0,m1463228935_41=0,m1463228935_45=0,m1463228935_48=0,m1463228935_62=0,m1463228935_83=0,m1463228935_89=0,m1463228935_98=0,m1463228935_101=0,m1463228935_107=0;
static Object *c1463228935_2=NULL,*c1463228935_8=NULL,*c1463228935_16=NULL,*c1463228935_35=NULL,*c1463228935_53=NULL,*c1463228935_84=NULL,*c1463228935_94=NULL;
void digiplay_Image__init____V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JDOUBLE T0;
	JFLOAT T1,T2;
	Object *L0;
	L0=args[0].O;
BB0:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=1;
	  AOTMETHOD(m1463228935_1,0,1,2); //digiplay/Sprite2D:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m1463228935_1),entry)))(vm,m1463228935_1,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	{
	  frame->pc=5;
	  AOTMETHOD(m1463228935_7,3,4,5); //java/lang/Math:random:()D;
	  ((VM_CALL)(MTH(((Object*)m1463228935_7),entry)))(vm,m1463228935_7,NULL);
	  if(vm->exception) goto __EXCEPTION;
	  T0=frame->ret.D;
	}
	
	T1 = (JFLOAT)T0 * 10.0;
	T2 = T1 - 5.0;
	AOTFIELD(f1463228935_15,6,7,8); //digiplay/Image:dx:F;
	if(!L0) { frame->pc = 15; throw_null(vm); goto __EXCEPTION; }
	*FIELD_PTR_F(L0,f1463228935_15->offset) = T2;
	{
	  frame->pc=19;
	  ((VM_CALL)(MTH(((Object*)m1463228935_7),entry)))(vm,m1463228935_7,NULL);
	  if(vm->exception) goto __EXCEPTION;
	  T0=frame->ret.D;
	}
	
	T1 = (JFLOAT)T0 * 10.0;
	T2 = T1 - 5.0;
	AOTFIELD(f1463228935_21,6,9,8); //digiplay/Image:dy:F;
	if(!L0) { frame->pc = 29; throw_null(vm); goto __EXCEPTION; }
	*FIELD_PTR_F(L0,f1463228935_21->offset) = T2;
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=33;
	  AOTVMETHOD(m1463228935_24,6,10,2,vTableIndex); //digiplay/Image:markContentInvalid:()V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m1463228935_24];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Image_getSrc___Ljava_lang_String_(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	Object *L0,*T0;
	L0=args[0].O;
BB0:
	AOTFIELD(f1463228935_27,6,11,12); //digiplay/Image:src:Ljava/lang/String;
	if(!L0) { frame->pc = 1; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f1463228935_27->offset);
	vm->FP--;vm->frames[vm->FP].ret.O=T0;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Image_setSrc__Ljava_lang_String__V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
BB0:
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Image_invalidateContent___V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	Object *L0,*T0;
	L0=args[0].O;
BB0:
	AOTFIELD(f1463228935_31,6,13,14); //digiplay/Image:quad:Ldigiplay/QuadMesh;
	if(!L0) { frame->pc = 1; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f1463228935_31->offset);
	if(T0!=NULL) goto BB19;
BB7:
	AOTCLASS(c1463228935_35,15);
	T0=alloc_object(vm,c1463228935_35,0);
	{
	  VAR cargs[]={{.O=T0},{.I=1}};
	  frame->pc=13;
	  AOTMETHOD(m1463228935_37,15,1,16); //digiplay/QuadMesh:<init>:(I)V;
	  ((VM_CALL)(MTH(((Object*)m1463228935_37),entry)))(vm,m1463228935_37,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	//digiplay/Image:quad:Ldigiplay/QuadMesh;
	if(!L0) { frame->pc = 16; throw_null(vm); goto __EXCEPTION; }
	*FIELD_PTR_O(L0,f1463228935_31->offset) = T0;
BB19:
	{
	  VAR cargs[]={{.O=L0},{.F=50.0}};
	  frame->pc=22;
	  AOTVMETHOD(m1463228935_41,6,17,18,vTableIndex); //digiplay/Image:setWidth:(F)V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m1463228935_41];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	{
	  VAR cargs[]={{.O=L0},{.F=50.0}};
	  frame->pc=28;
	  AOTVMETHOD(m1463228935_45,6,19,18,vTableIndex); //digiplay/Image:setHeight:(F)V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m1463228935_45];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	//digiplay/Image:quad:Ldigiplay/QuadMesh;
	if(!L0) { frame->pc = 32; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f1463228935_31->offset);
	{
	  VAR cargs[]={{.O=T0},{.I=0},{.F=0},{.F=0},{.F=50.0},{.F=50.0},{.F=0},{.F=0},{.F=1},{.F=0},{.F=1},{.F=1},{.F=0},{.F=1}};
	  frame->pc=50;
	  AOTVMETHOD(m1463228935_48,15,20,21,vTableIndex); //digiplay/QuadMesh:set:(IFFFFFFFFFFFF)V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m1463228935_48];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Image_draw___V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JFLOAT L1,L2,T6,T8;
	JINT T2,T7;
	Object *L0,*T0,*T1,*T3,*T4,*T5;
	L0=args[0].O;
BB0:
	AOTFIELD(f1463228935_31,6,13,14); //digiplay/Image:quad:Ldigiplay/QuadMesh;
	if(!L0) { frame->pc = 1; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f1463228935_31->offset);
	if(T0==NULL) goto BB43;
BB7:
	AOTFIELD(f1463228935_52,22,23,24); //digiplay/Stage2D:QuadBatch:Ldigiplay/GLQuadBatch;
	T0 = *((Object**)(CLS(f1463228935_52->declaringClass,global) + f1463228935_52->offset));
	//digiplay/Image:quad:Ldigiplay/QuadMesh;
	if(!L0) { frame->pc = 11; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_O(L0,f1463228935_31->offset);
	AOTFIELD(f1463228935_58,6,25,26); //digiplay/Image:GLOBAL_FRAME_VERSION:I;
	T2 = *((JINT*)(CLS(f1463228935_58->declaringClass,global) + f1463228935_58->offset));
	{
	  VAR cargs[]={{.O=L0},{.I=T2}};
	  frame->pc=18;
	  AOTVMETHOD(m1463228935_62,6,27,28,vTableIndex); //digiplay/Image:getWorldMatrix:(I)Ldigiplay/Mat2D;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m1463228935_62];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T3=frame->ret.O;
	}
	
	AOTFIELD(f1463228935_66,22,29,30); //digiplay/Stage2D:DefaultShader:Ldigiplay/GLShader2D;
	T4 = *((Object**)(CLS(f1463228935_66->declaringClass,global) + f1463228935_66->offset));
	AOTFIELD(f1463228935_70,6,31,32); //digiplay/Image:texture:Ldigiplay/GLTexture;
	T5 = *((Object**)(CLS(f1463228935_70->declaringClass,global) + f1463228935_70->offset));
	AOTFIELD(f1463228935_74,6,33,26); //digiplay/Image:color:I;
	if(!L0) { frame->pc = 29; throw_null(vm); goto __EXCEPTION; }
	T2 = *FIELD_PTR_I(L0,f1463228935_74->offset);
	AOTFIELD(f1463228935_77,6,34,8); //digiplay/Image:worldAlpha:F;
	if(!L0) { frame->pc = 33; throw_null(vm); goto __EXCEPTION; }
	T6 = *FIELD_PTR_F(L0,f1463228935_77->offset);
	AOTFIELD(f1463228935_80,6,35,26); //digiplay/Image:blendMode:I;
	if(!L0) { frame->pc = 37; throw_null(vm); goto __EXCEPTION; }
	T7 = *FIELD_PTR_I(L0,f1463228935_80->offset);
	{
	  VAR cargs[]={{.O=T0},{.O=T1},{.O=T3},{.O=T4},{.O=T5},{.I=0},{.I=T2},{.F=T6},{.I=T7}};
	  frame->pc=40;
	  AOTVMETHOD(m1463228935_83,36,37,38,vTableIndex); //digiplay/GLQuadBatch:drawQuadMesh:(Ldigiplay/QuadMesh;Ldigiplay/Mat2D;Ldigiplay/GLShader2D;Ldigiplay/GLTexture;IIFI)V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m1463228935_83];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
BB43:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=44;
	  AOTVMETHOD(m1463228935_89,6,39,40,vTableIndex); //digiplay/Image:getX:()F;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m1463228935_89];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T6=frame->ret.F;
	}
	
	L1=T6;
	AOTFIELD(f1463228935_15,6,7,8); //digiplay/Image:dx:F;
	if(!L0) { frame->pc = 50; throw_null(vm); goto __EXCEPTION; }
	T6 = *FIELD_PTR_F(L0,f1463228935_15->offset);
	T8 = L1 + T6;
	L1=T8;
	if(L1>0) goto BB75;
BB61:
	L1=0;
	//digiplay/Image:dx:F;
	if(!L0) { frame->pc = 65; throw_null(vm); goto __EXCEPTION; }
	T6 = *FIELD_PTR_F(L0,f1463228935_15->offset);
	T8=-T6;
	//digiplay/Image:dx:F;
	if(!L0) { frame->pc = 69; throw_null(vm); goto __EXCEPTION; }
	*FIELD_PTR_F(L0,f1463228935_15->offset) = T8;
	goto BB98;
BB75:
	AOTFIELD(f1463228935_93,41,42,26); //digiplay/Platform:screenWidth:I;
	T2 = *((JINT*)(CLS(f1463228935_93->declaringClass,global) + f1463228935_93->offset));
	if(L1<(JFLOAT)T2) goto BB98;
BB84:
	//digiplay/Platform:screenWidth:I;
	T2 = *((JINT*)(CLS(f1463228935_93->declaringClass,global) + f1463228935_93->offset));
	L1=(JFLOAT)T2;
	AOTFIELD(f1463228935_15,6,7,8); //digiplay/Image:dx:F;
	if(!L0) { frame->pc = 91; throw_null(vm); goto __EXCEPTION; }
	T6 = *FIELD_PTR_F(L0,f1463228935_15->offset);
	T8=-T6;
	//digiplay/Image:dx:F;
	if(!L0) { frame->pc = 95; throw_null(vm); goto __EXCEPTION; }
	*FIELD_PTR_F(L0,f1463228935_15->offset) = T8;
BB98:
	{
	  VAR cargs[]={{.O=L0},{.F=L1}};
	  frame->pc=100;
	  AOTVMETHOD(m1463228935_98,6,43,18,vTableIndex); //digiplay/Image:setX:(F)V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m1463228935_98];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=104;
	  AOTVMETHOD(m1463228935_101,6,44,40,vTableIndex); //digiplay/Image:getY:()F;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m1463228935_101];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T6=frame->ret.F;
	}
	
	L2=T6;
	AOTFIELD(f1463228935_21,6,9,8); //digiplay/Image:dy:F;
	if(!L0) { frame->pc = 110; throw_null(vm); goto __EXCEPTION; }
	T6 = *FIELD_PTR_F(L0,f1463228935_21->offset);
	T8 = L2 + T6;
	L2=T8;
	if(L2>0) goto BB135;
BB121:
	L2=0;
	//digiplay/Image:dy:F;
	if(!L0) { frame->pc = 125; throw_null(vm); goto __EXCEPTION; }
	T6 = *FIELD_PTR_F(L0,f1463228935_21->offset);
	T8=-T6;
	//digiplay/Image:dy:F;
	if(!L0) { frame->pc = 129; throw_null(vm); goto __EXCEPTION; }
	*FIELD_PTR_F(L0,f1463228935_21->offset) = T8;
	goto BB158;
BB135:
	AOTFIELD(f1463228935_104,41,45,26); //digiplay/Platform:screenHeight:I;
	T2 = *((JINT*)(CLS(f1463228935_104->declaringClass,global) + f1463228935_104->offset));
	if(L2<(JFLOAT)T2) goto BB158;
BB144:
	//digiplay/Platform:screenHeight:I;
	T2 = *((JINT*)(CLS(f1463228935_104->declaringClass,global) + f1463228935_104->offset));
	L2=(JFLOAT)T2;
	AOTFIELD(f1463228935_21,6,9,8); //digiplay/Image:dy:F;
	if(!L0) { frame->pc = 151; throw_null(vm); goto __EXCEPTION; }
	T6 = *FIELD_PTR_F(L0,f1463228935_21->offset);
	T8=-T6;
	//digiplay/Image:dy:F;
	if(!L0) { frame->pc = 155; throw_null(vm); goto __EXCEPTION; }
	*FIELD_PTR_F(L0,f1463228935_21->offset) = T8;
BB158:
	{
	  VAR cargs[]={{.O=L0},{.F=L2}};
	  frame->pc=160;
	  AOTVMETHOD(m1463228935_107,6,46,18,vTableIndex); //digiplay/Image:setY:(F)V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m1463228935_107];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void aot_init(VM *vm) {
	static  int i=0; if(i) return; i=1;
	aot_strings = (Object**)malloc(sizeof(Object*)*47);
	aot_strings[46] = alloc_string_java(vm,(JCHAR[]){115,101,116,89},4,1);
	aot_strings[42] = alloc_string_java(vm,(JCHAR[]){115,99,114,101,101,110,87,105,100,116,104},11,1);
	aot_strings[43] = alloc_string_java(vm,(JCHAR[]){115,101,116,88},4,1);
	aot_strings[10] = alloc_string_java(vm,(JCHAR[]){109,97,114,107,67,111,110,116,101,110,116,73,110,118,97,108,105,100},18,1);
	aot_strings[33] = alloc_string_java(vm,(JCHAR[]){99,111,108,111,114},5,1);
	aot_strings[8] = alloc_string_java(vm,(JCHAR[]){70},1,1);
	aot_strings[0] = alloc_string_java(vm,(JCHAR[]){100,105,103,105,112,108,97,121,47,83,112,114,105,116,101,50,68},17,1);
	aot_strings[26] = alloc_string_java(vm,(JCHAR[]){73},1,1);
	aot_strings[38] = alloc_string_java(vm,(JCHAR[]){40,76,100,105,103,105,112,108,97,121,47,81,117,97,100,77,101,115,104,59,76,100,105,103,105,112,108,97,121,47,77,97,116,50,68,59,76,100,105,103,105,112,108,97,121,47,71,76,83,104,97,100,101,114,50,68,59,76,100,105,103,105,112,108,97,121,47,71,76,84,101,120,116,117,114,101,59,73,73,70,73,41,86},83,1);
	aot_strings[25] = alloc_string_java(vm,(JCHAR[]){71,76,79,66,65,76,95,70,82,65,77,69,95,86,69,82,83,73,79,78},20,1);
	aot_strings[34] = alloc_string_java(vm,(JCHAR[]){119,111,114,108,100,65,108,112,104,97},10,1);
	aot_strings[4] = alloc_string_java(vm,(JCHAR[]){114,97,110,100,111,109},6,1);
	aot_strings[23] = alloc_string_java(vm,(JCHAR[]){81,117,97,100,66,97,116,99,104},9,1);
	aot_strings[7] = alloc_string_java(vm,(JCHAR[]){100,120},2,1);
	aot_strings[9] = alloc_string_java(vm,(JCHAR[]){100,121},2,1);
	aot_strings[29] = alloc_string_java(vm,(JCHAR[]){68,101,102,97,117,108,116,83,104,97,100,101,114},13,1);
	aot_strings[21] = alloc_string_java(vm,(JCHAR[]){40,73,70,70,70,70,70,70,70,70,70,70,70,70,41,86},16,1);
	aot_strings[28] = alloc_string_java(vm,(JCHAR[]){40,73,41,76,100,105,103,105,112,108,97,121,47,77,97,116,50,68,59},19,1);
	aot_strings[3] = alloc_string_java(vm,(JCHAR[]){106,97,118,97,47,108,97,110,103,47,77,97,116,104},14,1);
	aot_strings[14] = alloc_string_java(vm,(JCHAR[]){76,100,105,103,105,112,108,97,121,47,81,117,97,100,77,101,115,104,59},19,1);
	aot_strings[20] = alloc_string_java(vm,(JCHAR[]){115,101,116},3,1);
	aot_strings[5] = alloc_string_java(vm,(JCHAR[]){40,41,68},3,1);
	aot_strings[40] = alloc_string_java(vm,(JCHAR[]){40,41,70},3,1);
	aot_strings[11] = alloc_string_java(vm,(JCHAR[]){115,114,99},3,1);
	aot_strings[32] = alloc_string_java(vm,(JCHAR[]){76,100,105,103,105,112,108,97,121,47,71,76,84,101,120,116,117,114,101,59},20,1);
	aot_strings[31] = alloc_string_java(vm,(JCHAR[]){116,101,120,116,117,114,101},7,1);
	aot_strings[24] = alloc_string_java(vm,(JCHAR[]){76,100,105,103,105,112,108,97,121,47,71,76,81,117,97,100,66,97,116,99,104,59},22,1);
	aot_strings[45] = alloc_string_java(vm,(JCHAR[]){115,99,114,101,101,110,72,101,105,103,104,116},12,1);
	aot_strings[27] = alloc_string_java(vm,(JCHAR[]){103,101,116,87,111,114,108,100,77,97,116,114,105,120},14,1);
	aot_strings[1] = alloc_string_java(vm,(JCHAR[]){60,105,110,105,116,62},6,1);
	aot_strings[19] = alloc_string_java(vm,(JCHAR[]){115,101,116,72,101,105,103,104,116},9,1);
	aot_strings[17] = alloc_string_java(vm,(JCHAR[]){115,101,116,87,105,100,116,104},8,1);
	aot_strings[15] = alloc_string_java(vm,(JCHAR[]){100,105,103,105,112,108,97,121,47,81,117,97,100,77,101,115,104},17,1);
	aot_strings[6] = alloc_string_java(vm,(JCHAR[]){100,105,103,105,112,108,97,121,47,73,109,97,103,101},14,1);
	aot_strings[36] = alloc_string_java(vm,(JCHAR[]){100,105,103,105,112,108,97,121,47,71,76,81,117,97,100,66,97,116,99,104},20,1);
	aot_strings[12] = alloc_string_java(vm,(JCHAR[]){76,106,97,118,97,47,108,97,110,103,47,83,116,114,105,110,103,59},18,1);
	aot_strings[39] = alloc_string_java(vm,(JCHAR[]){103,101,116,88},4,1);
	aot_strings[13] = alloc_string_java(vm,(JCHAR[]){113,117,97,100},4,1);
	aot_strings[44] = alloc_string_java(vm,(JCHAR[]){103,101,116,89},4,1);
	aot_strings[22] = alloc_string_java(vm,(JCHAR[]){100,105,103,105,112,108,97,121,47,83,116,97,103,101,50,68},16,1);
	aot_strings[35] = alloc_string_java(vm,(JCHAR[]){98,108,101,110,100,77,111,100,101},9,1);
	aot_strings[2] = alloc_string_java(vm,(JCHAR[]){40,41,86},3,1);
	aot_strings[30] = alloc_string_java(vm,(JCHAR[]){76,100,105,103,105,112,108,97,121,47,71,76,83,104,97,100,101,114,50,68,59},21,1);
	aot_strings[18] = alloc_string_java(vm,(JCHAR[]){40,70,41,86},4,1);
	aot_strings[37] = alloc_string_java(vm,(JCHAR[]){100,114,97,119,81,117,97,100,77,101,115,104},12,1);
	aot_strings[16] = alloc_string_java(vm,(JCHAR[]){40,73,41,86},4,1);
	aot_strings[41] = alloc_string_java(vm,(JCHAR[]){100,105,103,105,112,108,97,121,47,80,108,97,116,102,111,114,109},17,1);
}
NativeMethodInfo aot_native_methods[] = {
	{"digiplay/Image:<init>:()V",&digiplay_Image__init____V}
	,{"digiplay/Image:getSrc:()Ljava/lang/String;",&digiplay_Image_getSrc___Ljava_lang_String_}
	,{"digiplay/Image:setSrc:(Ljava/lang/String;)V",&digiplay_Image_setSrc__Ljava_lang_String__V}
	,{"digiplay/Image:invalidateContent:()V",&digiplay_Image_invalidateContent___V}
	,{"digiplay/Image:draw:()V",&digiplay_Image_draw___V}
	,NULL
};
