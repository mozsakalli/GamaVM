#include "vm.h"
#include <math.h>
Object **aot_strings;

//digiplay/Image
static Field *f1463228935_5=NULL,*f1463228935_6=NULL,*f1463228935_8=NULL,*f1463228935_9=NULL,*f1463228935_16=NULL,*f1463228935_17=NULL,*f1463228935_19=NULL,*f1463228935_20=NULL,*f1463228935_21=NULL,*f1463228935_22=NULL,*f1463228935_23=NULL,*f1463228935_26=NULL,*f1463228935_29=NULL;
static JLONG m1463228935_1=0,m1463228935_2=0,m1463228935_7=0,m1463228935_11=0,m1463228935_13=0,m1463228935_14=0,m1463228935_15=0,m1463228935_18=0,m1463228935_24=0,m1463228935_25=0,m1463228935_27=0,m1463228935_28=0,m1463228935_30=0,m1463228935_31=0,m1463228935_32=0;
static Object *c1463228935_10=NULL,*c1463228935_33=NULL,*c1463228935_34=NULL,*c1463228935_65=NULL,*c1463228935_77=NULL,*c1463228935_86=NULL,*c1463228935_89=NULL;
void digiplay_Image__init____V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	VAR* ARGBUF = &vm->stack[vm->SP];
	vm->SP += 3;
	JDOUBLE T0;
	JFLOAT T1,T2;
	Object *L0;
	L0=args[0].O;
	if(!L0) goto __EXCEPTION;
BB0:
	{
	ARGBUF[0].O=L0;  frame->pc=1;
	  AOTMETHOD(m1463228935_1,0,1,2); //digiplay/Sprite2D:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m1463228935_1),entry)))(vm,m1463228935_1,ARGBUF);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	{
	  frame->pc=5;
	  AOTMETHOD(m1463228935_2,3,4,5); //java/lang/Math:random:()D;
	  ((VM_CALL)(MTH(((Object*)m1463228935_2),entry)))(vm,m1463228935_2,NULL);
	  if(vm->exception) goto __EXCEPTION;
	  T0=frame->ret.D;
	}
	
	T1 = (JFLOAT)T0 * 10.0;
	T2 = T1 - 5.0;
	AOTFIELD(f1463228935_5,6,7,8); //digiplay/Image:dx:F;
	*FIELD_PTR_F(L0,f1463228935_5->offset) = T2;
	{
	  frame->pc=19;
	  ((VM_CALL)(MTH(((Object*)m1463228935_2),entry)))(vm,m1463228935_2,NULL);
	  if(vm->exception) goto __EXCEPTION;
	  T0=frame->ret.D;
	}
	
	T1 = (JFLOAT)T0 * 10.0;
	T2 = T1 - 5.0;
	AOTFIELD(f1463228935_6,6,9,8); //digiplay/Image:dy:F;
	*FIELD_PTR_F(L0,f1463228935_6->offset) = T2;
	{
	ARGBUF[0].O=L0;  frame->pc=33;
	  AOTVMETHOD(m1463228935_7,6,10,2,vTableIndex); //digiplay/Image:markContentInvalid:()V;
	  Class *cls = ARGBUF[0].O->cls->instance;
	  Object *mth = cls->vtable[m1463228935_7];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, ARGBUF);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;vm->SP -= 3;return;
__EXCEPTION: {
	vm->FP--; vm->SP -= 3; return;
}
}
void digiplay_Image_getSrc___Ljava_lang_String_(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	VAR* ARGBUF = &vm->stack[vm->SP];
	vm->SP += 1;
	Object *L0,*T0;
	L0=args[0].O;
	if(!L0) goto __EXCEPTION;
BB0:
	AOTFIELD(f1463228935_8,6,11,12); //digiplay/Image:src:Ljava/lang/String;
	T0 = *FIELD_PTR_O(L0,f1463228935_8->offset);
	vm->FP--;vm->frames[vm->FP].ret.O=T0;vm->SP -= 1;return;
__EXCEPTION: {
	vm->FP--; vm->SP -= 1; return;
}
}
void digiplay_Image_setSrc__Ljava_lang_String__V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	VAR* ARGBUF = &vm->stack[vm->SP];
	vm->SP += 0;
BB0:
	vm->FP--;vm->SP -= 0;return;
__EXCEPTION: {
	vm->FP--; vm->SP -= 0; return;
}
}
void digiplay_Image_invalidateContent___V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	VAR* ARGBUF = &vm->stack[vm->SP];
	vm->SP += 14;
	Object *L0,*T0;
	L0=args[0].O;
	if(!L0) goto __EXCEPTION;
BB0:
	AOTFIELD(f1463228935_9,6,13,14); //digiplay/Image:quad:Ldigiplay/QuadMesh;
	T0 = *FIELD_PTR_O(L0,f1463228935_9->offset);
	if(T0!=NULL) goto BB19;
BB7:
	AOTCLASS(c1463228935_10,15);
	T0=alloc_object(vm,c1463228935_10,0);
	{
	ARGBUF[0].O=T0;ARGBUF[1].I=1;  frame->pc=13;
	  AOTMETHOD(m1463228935_11,15,1,16); //digiplay/QuadMesh:<init>:(I)V;
	  ((VM_CALL)(MTH(((Object*)m1463228935_11),entry)))(vm,m1463228935_11,ARGBUF);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	//digiplay/Image:quad:Ldigiplay/QuadMesh;
	*FIELD_PTR_O(L0,f1463228935_9->offset) = T0;
BB19:
	{
	ARGBUF[0].O=L0;ARGBUF[1].F=50.0;  frame->pc=22;
	  AOTVMETHOD(m1463228935_13,6,17,18,vTableIndex); //digiplay/Image:setWidth:(F)V;
	  Class *cls = ARGBUF[0].O->cls->instance;
	  Object *mth = cls->vtable[m1463228935_13];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, ARGBUF);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	{
	ARGBUF[0].O=L0;ARGBUF[1].F=50.0;  frame->pc=28;
	  AOTVMETHOD(m1463228935_14,6,19,18,vTableIndex); //digiplay/Image:setHeight:(F)V;
	  Class *cls = ARGBUF[0].O->cls->instance;
	  Object *mth = cls->vtable[m1463228935_14];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, ARGBUF);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	//digiplay/Image:quad:Ldigiplay/QuadMesh;
	T0 = *FIELD_PTR_O(L0,f1463228935_9->offset);
	{
	ARGBUF[0].O=T0;ARGBUF[1].I=0;ARGBUF[2].F=0;ARGBUF[3].F=0;ARGBUF[4].F=50.0;ARGBUF[5].F=50.0;ARGBUF[6].F=0;ARGBUF[7].F=0;ARGBUF[8].F=1;ARGBUF[9].F=0;ARGBUF[10].F=1;ARGBUF[11].F=1;ARGBUF[12].F=0;ARGBUF[13].F=1;  frame->pc=50;
	  AOTVMETHOD(m1463228935_15,15,20,21,vTableIndex); //digiplay/QuadMesh:set:(IFFFFFFFFFFFF)V;
	  if(!ARGBUF[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = ARGBUF[0].O->cls->instance;
	  Object *mth = cls->vtable[m1463228935_15];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, ARGBUF);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;vm->SP -= 14;return;
__EXCEPTION: {
	vm->FP--; vm->SP -= 14; return;
}
}
void digiplay_Image_draw___V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	VAR* ARGBUF = &vm->stack[vm->SP];
	vm->SP += 9;
	JFLOAT L1,L2,T6,T8;
	JINT T2,T7;
	Object *L0,*T0,*T1,*T3,*T4,*T5;
	L0=args[0].O;
	if(!L0) goto __EXCEPTION;
BB0:
	AOTFIELD(f1463228935_9,6,13,14); //digiplay/Image:quad:Ldigiplay/QuadMesh;
	T0 = *FIELD_PTR_O(L0,f1463228935_9->offset);
	if(T0==NULL) goto BB43;
BB7:
	AOTFIELD(f1463228935_16,22,23,24); //digiplay/Stage2D:QuadBatch:Ldigiplay/GLQuadBatch;
	T0 = *((Object**)(f1463228935_16->offset));
	//digiplay/Image:quad:Ldigiplay/QuadMesh;
	T1 = *FIELD_PTR_O(L0,f1463228935_9->offset);
	AOTFIELD(f1463228935_17,6,25,26); //digiplay/Image:GLOBAL_FRAME_VERSION:I;
	T2 = *((JINT*)(f1463228935_17->offset));
	{
	ARGBUF[0].O=L0;ARGBUF[1].I=T2;  frame->pc=18;
	  AOTVMETHOD(m1463228935_18,6,27,28,vTableIndex); //digiplay/Image:getWorldMatrix:(I)Ldigiplay/Mat2D;
	  Class *cls = ARGBUF[0].O->cls->instance;
	  Object *mth = cls->vtable[m1463228935_18];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, ARGBUF);
	  if(vm->exception) goto __EXCEPTION;
	  T3=frame->ret.O;
	}
	
	AOTFIELD(f1463228935_19,22,29,30); //digiplay/Stage2D:DefaultShader:Ldigiplay/GLShader2D;
	T4 = *((Object**)(f1463228935_19->offset));
	AOTFIELD(f1463228935_20,6,31,32); //digiplay/Image:texture:Ldigiplay/GLTexture;
	T5 = *((Object**)(f1463228935_20->offset));
	AOTFIELD(f1463228935_21,6,33,26); //digiplay/Image:color:I;
	T2 = *FIELD_PTR_I(L0,f1463228935_21->offset);
	AOTFIELD(f1463228935_22,6,34,8); //digiplay/Image:worldAlpha:F;
	T6 = *FIELD_PTR_F(L0,f1463228935_22->offset);
	AOTFIELD(f1463228935_23,6,35,26); //digiplay/Image:blendMode:I;
	T7 = *FIELD_PTR_I(L0,f1463228935_23->offset);
	{
	ARGBUF[0].O=T0;ARGBUF[1].O=T1;ARGBUF[2].O=T3;ARGBUF[3].O=T4;ARGBUF[4].O=T5;ARGBUF[5].I=0;ARGBUF[6].I=T2;ARGBUF[7].F=T6;ARGBUF[8].I=T7;  frame->pc=40;
	  AOTVMETHOD(m1463228935_24,36,37,38,vTableIndex); //digiplay/GLQuadBatch:drawQuadMesh:(Ldigiplay/QuadMesh;Ldigiplay/Mat2D;Ldigiplay/GLShader2D;Ldigiplay/GLTexture;IIFI)V;
	  if(!ARGBUF[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = ARGBUF[0].O->cls->instance;
	  Object *mth = cls->vtable[m1463228935_24];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, ARGBUF);
	  if(vm->exception) goto __EXCEPTION;
	}
BB43:
	{
	ARGBUF[0].O=L0;  frame->pc=44;
	  AOTVMETHOD(m1463228935_25,6,39,40,vTableIndex); //digiplay/Image:getX:()F;
	  Class *cls = ARGBUF[0].O->cls->instance;
	  Object *mth = cls->vtable[m1463228935_25];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, ARGBUF);
	  if(vm->exception) goto __EXCEPTION;
	  T6=frame->ret.F;
	}
	
	L1=T6;
	AOTFIELD(f1463228935_5,6,7,8); //digiplay/Image:dx:F;
	T6 = *FIELD_PTR_F(L0,f1463228935_5->offset);
	L1 = L1 + T6;
	if(L1>0) goto BB75;
BB61:
	L1=0;
	//digiplay/Image:dx:F;
	T6 = *FIELD_PTR_F(L0,f1463228935_5->offset);
	T8=-T6;
	//digiplay/Image:dx:F;
	*FIELD_PTR_F(L0,f1463228935_5->offset) = T8;
	goto BB98;
BB75:
	AOTFIELD(f1463228935_26,41,42,26); //digiplay/Platform:screenWidth:I;
	T2 = *((JINT*)(f1463228935_26->offset));
	if(L1<(JFLOAT)T2) goto BB98;
BB84:
	//digiplay/Platform:screenWidth:I;
	T2 = *((JINT*)(f1463228935_26->offset));
	L1=(JFLOAT)T2;
	AOTFIELD(f1463228935_5,6,7,8); //digiplay/Image:dx:F;
	T6 = *FIELD_PTR_F(L0,f1463228935_5->offset);
	T8=-T6;
	//digiplay/Image:dx:F;
	*FIELD_PTR_F(L0,f1463228935_5->offset) = T8;
BB98:
	{
	ARGBUF[0].O=L0;ARGBUF[1].F=L1;  frame->pc=100;
	  AOTVMETHOD(m1463228935_27,6,43,18,vTableIndex); //digiplay/Image:setX:(F)V;
	  Class *cls = ARGBUF[0].O->cls->instance;
	  Object *mth = cls->vtable[m1463228935_27];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, ARGBUF);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	{
	ARGBUF[0].O=L0;  frame->pc=104;
	  AOTVMETHOD(m1463228935_28,6,44,40,vTableIndex); //digiplay/Image:getY:()F;
	  Class *cls = ARGBUF[0].O->cls->instance;
	  Object *mth = cls->vtable[m1463228935_28];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, ARGBUF);
	  if(vm->exception) goto __EXCEPTION;
	  T6=frame->ret.F;
	}
	
	L2=T6;
	AOTFIELD(f1463228935_6,6,9,8); //digiplay/Image:dy:F;
	T6 = *FIELD_PTR_F(L0,f1463228935_6->offset);
	L2 = L2 + T6;
	if(L2>0) goto BB135;
BB121:
	L2=0;
	//digiplay/Image:dy:F;
	T6 = *FIELD_PTR_F(L0,f1463228935_6->offset);
	T8=-T6;
	//digiplay/Image:dy:F;
	*FIELD_PTR_F(L0,f1463228935_6->offset) = T8;
	goto BB158;
BB135:
	AOTFIELD(f1463228935_29,41,45,26); //digiplay/Platform:screenHeight:I;
	T2 = *((JINT*)(f1463228935_29->offset));
	if(L2<(JFLOAT)T2) goto BB158;
BB144:
	//digiplay/Platform:screenHeight:I;
	T2 = *((JINT*)(f1463228935_29->offset));
	L2=(JFLOAT)T2;
	AOTFIELD(f1463228935_6,6,9,8); //digiplay/Image:dy:F;
	T6 = *FIELD_PTR_F(L0,f1463228935_6->offset);
	T8=-T6;
	//digiplay/Image:dy:F;
	*FIELD_PTR_F(L0,f1463228935_6->offset) = T8;
BB158:
	{
	ARGBUF[0].O=L0;ARGBUF[1].F=L2;  frame->pc=160;
	  AOTVMETHOD(m1463228935_30,6,46,18,vTableIndex); //digiplay/Image:setY:(F)V;
	  Class *cls = ARGBUF[0].O->cls->instance;
	  Object *mth = cls->vtable[m1463228935_30];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, ARGBUF);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	{
	ARGBUF[0].O=L0;  frame->pc=165;
	  AOTVMETHOD(m1463228935_31,6,47,40,vTableIndex); //digiplay/Image:getRotation:()F;
	  Class *cls = ARGBUF[0].O->cls->instance;
	  Object *mth = cls->vtable[m1463228935_31];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, ARGBUF);
	  if(vm->exception) goto __EXCEPTION;
	  T6=frame->ret.F;
	}
	
	T8 = T6 + 1;
	{
	ARGBUF[0].O=L0;ARGBUF[1].F=T8;  frame->pc=170;
	  AOTVMETHOD(m1463228935_32,6,48,18,vTableIndex); //digiplay/Image:setRotation:(F)V;
	  Class *cls = ARGBUF[0].O->cls->instance;
	  Object *mth = cls->vtable[m1463228935_32];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, ARGBUF);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;vm->SP -= 9;return;
__EXCEPTION: {
	vm->FP--; vm->SP -= 9; return;
}
}
//digiplay/Platform
static Field *f_130471865_2=NULL,*f_130471865_4=NULL,*f_130471865_6=NULL,*f_130471865_7=NULL,*f_130471865_8=NULL,*f_130471865_12=NULL,*f_130471865_13=NULL;
static JLONG m_130471865_1=0,m_130471865_3=0,m_130471865_5=0,m_130471865_9=0,m_130471865_11=0,m_130471865_14=0,m_130471865_15=0,m_130471865_16=0;
static Object *c_130471865_10=NULL,*c_130471865_17=NULL,*c_130471865_18=NULL,*c_130471865_60=NULL,*c_130471865_67=NULL;
void digiplay_Platform__init____V(VM *vm, Object *omethod, VAR *args) {
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
	  AOTMETHOD(m_130471865_1,49,1,2); //java/lang/Object:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m_130471865_1),entry)))(vm,m_130471865_1,ARGBUF);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;vm->SP -= 1;return;
__EXCEPTION: {
	vm->FP--; vm->SP -= 1; return;
}
}
void digiplay_Platform_run__Ldigiplay_Game__V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	VAR* ARGBUF = &vm->stack[vm->SP];
	vm->SP += 2;
	JLONG T0;
	Object *L0;
	L0=args[0].O;
BB0:
	AOTFIELD(f_130471865_2,41,50,51); //digiplay/Platform:game:Ldigiplay/Game;
	*((Object**)(f_130471865_2->offset)) = L0;
	{
	  frame->pc=4;
	  AOTMETHOD(m_130471865_3,52,53,54); //java/lang/System:currentTimeMillis:()J;
	  ((VM_CALL)(MTH(((Object*)m_130471865_3),entry)))(vm,m_130471865_3,NULL);
	  if(vm->exception) goto __EXCEPTION;
	  T0=frame->ret.J;
	}
	
	AOTFIELD(f_130471865_4,41,55,56); //digiplay/Platform:gameStartTime:J;
	*((JLONG*)(f_130471865_4->offset)) = T0;
	{
	  frame->pc=10;
	  AOTMETHOD(m_130471865_5,41,57,2); //digiplay/Platform:run:()V;
	  ((VM_CALL)(MTH(((Object*)m_130471865_5),entry)))(vm,m_130471865_5,NULL);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;vm->SP -= 2;return;
__EXCEPTION: {
	vm->FP--; vm->SP -= 2; return;
}
}
void digiplay_Platform_resize__II_V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	VAR* ARGBUF = &vm->stack[vm->SP];
	vm->SP += 1;
	JINT L0,L1,T0;
	Object *L2,*T1;
	Object *caughtException;
	L0=args[0].I;
	L1=args[1].I;
BB0:
	AOTFIELD(f_130471865_6,41,42,26); //digiplay/Platform:screenWidth:I;
	*((JINT*)(f_130471865_6->offset)) = L0;
	AOTFIELD(f_130471865_7,41,45,26); //digiplay/Platform:screenHeight:I;
	*((JINT*)(f_130471865_7->offset)) = L1;
	AOTFIELD(f_130471865_8,41,58,59); //digiplay/Platform:initialized:Z;
	T0 = *((JBOOL*)(f_130471865_8->offset));
	if(T0!=0) goto BB26;
BB14:
	//digiplay/Platform:initialized:Z;
	*((JBOOL*)(f_130471865_8->offset)) = 1;
	AOTFIELD(f_130471865_2,41,50,51); //digiplay/Platform:game:Ldigiplay/Game;
	T1 = *((Object**)(f_130471865_2->offset));
	{
	ARGBUF[0].O=T1;  frame->pc=21;
	  AOTVMETHOD(m_130471865_9,60,61,2,iTableIndex); //digiplay/Game:begin:()V;
	  if(!ARGBUF[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = ARGBUF[0].O->cls->instance;
	  Object *mth = cls->itable[m_130471865_9];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, ARGBUF);
	  if(vm->exception) goto __EXCEPTION;
	}
BB26:
	goto BB34;
BB29:
	L2=caughtException;
	{
	ARGBUF[0].O=L2;  frame->pc=31;
	  AOTVMETHOD(m_130471865_11,62,63,2,vTableIndex); //java/lang/Throwable:printStackTrace:()V;
	  if(!ARGBUF[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = ARGBUF[0].O->cls->instance;
	  Object *mth = cls->vtable[m_130471865_11];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, ARGBUF);
	  if(vm->exception) goto __EXCEPTION;
	}
BB34:
	vm->FP--;vm->SP -= 1;return;
__EXCEPTION: {
	caughtException = vm->exception;
	vm->exception = NULL;
	if(frame->pc >= 0 && frame->pc < 26) {
		AOTCLASS(c_130471865_10,62);
		if(check_cast(vm,caughtException->cls,c_130471865_10))
			goto BB29;
	}
	vm->exception = caughtException;
	vm->FP--; vm->SP -= 1; return;
}
}
void digiplay_Platform_step___V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	VAR* ARGBUF = &vm->stack[vm->SP];
	vm->SP += 4;
	JINT L1;
	JLONG L0,T0,T1;
	Object *L2,*T2;
	Object *caughtException;
BB0:
	{
	  frame->pc=0;
	  AOTMETHOD(m_130471865_3,52,53,54); //java/lang/System:currentTimeMillis:()J;
	  ((VM_CALL)(MTH(((Object*)m_130471865_3),entry)))(vm,m_130471865_3,NULL);
	  if(vm->exception) goto __EXCEPTION;
	  T0=frame->ret.J;
	}
	
	L0=T0;
	AOTFIELD(f_130471865_4,41,55,56); //digiplay/Platform:gameStartTime:J;
	T0 = *((JLONG*)(f_130471865_4->offset));
	T1 = L0 - T0;
	AOTFIELD(f_130471865_12,41,64,26); //digiplay/Platform:gameTime:I;
	*((JINT*)(f_130471865_12->offset)) = (JINT)T1;
	AOTFIELD(f_130471865_13,41,65,56); //digiplay/Platform:lastTime:J;
	T0 = *((JLONG*)(f_130471865_13->offset));
	T1 = L0 - T0;
	L1=(JINT)T1;
	//digiplay/Platform:lastTime:J;
	*((JLONG*)(f_130471865_13->offset)) = L0;
	AOTFIELD(f_130471865_2,41,50,51); //digiplay/Platform:game:Ldigiplay/Game;
	T2 = *((Object**)(f_130471865_2->offset));
	{
	ARGBUF[0].O=T2;  frame->pc=27;
	  AOTVMETHOD(m_130471865_14,60,66,2,iTableIndex); //digiplay/Game:update:()V;
	  if(!ARGBUF[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = ARGBUF[0].O->cls->instance;
	  Object *mth = cls->itable[m_130471865_14];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, ARGBUF);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	//digiplay/Platform:game:Ldigiplay/Game;
	T2 = *((Object**)(f_130471865_2->offset));
	{
	ARGBUF[0].O=T2;  frame->pc=35;
	  AOTVMETHOD(m_130471865_15,60,67,2,iTableIndex); //digiplay/Game:render:()V;
	  if(!ARGBUF[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = ARGBUF[0].O->cls->instance;
	  Object *mth = cls->itable[m_130471865_15];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, ARGBUF);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	goto BB48;
BB43:
	L2=caughtException;
	{
	ARGBUF[0].O=L2;  frame->pc=45;
	  AOTVMETHOD(m_130471865_11,62,63,2,vTableIndex); //java/lang/Throwable:printStackTrace:()V;
	  if(!ARGBUF[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = ARGBUF[0].O->cls->instance;
	  Object *mth = cls->vtable[m_130471865_11];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, ARGBUF);
	  if(vm->exception) goto __EXCEPTION;
	}
BB48:
	{
	  frame->pc=48;
	  AOTMETHOD(m_130471865_16,52,68,2); //java/lang/System:gc:()V;
	  ((VM_CALL)(MTH(((Object*)m_130471865_16),entry)))(vm,m_130471865_16,NULL);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;vm->SP -= 4;return;
__EXCEPTION: {
	caughtException = vm->exception;
	vm->exception = NULL;
	if(frame->pc >= 24 && frame->pc < 40) {
		AOTCLASS(c_130471865_10,62);
		if(check_cast(vm,caughtException->cls,c_130471865_10))
			goto BB43;
	}
	vm->exception = caughtException;
	vm->FP--; vm->SP -= 4; return;
}
}
void digiplay_Platform__clinit____V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	VAR* ARGBUF = &vm->stack[vm->SP];
	vm->SP += 2;
	JLONG T0;
BB0:
	{
	  frame->pc=0;
	  AOTMETHOD(m_130471865_3,52,53,54); //java/lang/System:currentTimeMillis:()J;
	  ((VM_CALL)(MTH(((Object*)m_130471865_3),entry)))(vm,m_130471865_3,NULL);
	  if(vm->exception) goto __EXCEPTION;
	  T0=frame->ret.J;
	}
	
	AOTFIELD(f_130471865_13,41,65,56); //digiplay/Platform:lastTime:J;
	*((JLONG*)(f_130471865_13->offset)) = T0;
	vm->FP--;vm->SP -= 2;return;
__EXCEPTION: {
	vm->FP--; vm->SP -= 2; return;
}
}
void aot_init(VM *vm) {
	static  int i=0; if(i) return; i=1;
	aot_strings = (Object**)malloc(sizeof(Object*)*69);
	aot_strings[65] = alloc_string_java(vm,(JCHAR[]){108,97,115,116,84,105,109,101},8,1);
	aot_strings[46] = alloc_string_java(vm,(JCHAR[]){115,101,116,89},4,1);
	aot_strings[43] = alloc_string_java(vm,(JCHAR[]){115,101,116,88},4,1);
	aot_strings[10] = alloc_string_java(vm,(JCHAR[]){109,97,114,107,67,111,110,116,101,110,116,73,110,118,97,108,105,100},18,1);
	aot_strings[47] = alloc_string_java(vm,(JCHAR[]){103,101,116,82,111,116,97,116,105,111,110},11,1);
	aot_strings[57] = alloc_string_java(vm,(JCHAR[]){114,117,110},3,1);
	aot_strings[38] = alloc_string_java(vm,(JCHAR[]){40,76,100,105,103,105,112,108,97,121,47,81,117,97,100,77,101,115,104,59,76,100,105,103,105,112,108,97,121,47,77,97,116,50,68,59,76,100,105,103,105,112,108,97,121,47,71,76,83,104,97,100,101,114,50,68,59,76,100,105,103,105,112,108,97,121,47,71,76,84,101,120,116,117,114,101,59,73,73,70,73,41,86},83,1);
	aot_strings[7] = alloc_string_java(vm,(JCHAR[]){100,120},2,1);
	aot_strings[55] = alloc_string_java(vm,(JCHAR[]){103,97,109,101,83,116,97,114,116,84,105,109,101},13,1);
	aot_strings[9] = alloc_string_java(vm,(JCHAR[]){100,121},2,1);
	aot_strings[62] = alloc_string_java(vm,(JCHAR[]){106,97,118,97,47,108,97,110,103,47,84,104,114,111,119,97,98,108,101},19,1);
	aot_strings[29] = alloc_string_java(vm,(JCHAR[]){68,101,102,97,117,108,116,83,104,97,100,101,114},13,1);
	aot_strings[21] = alloc_string_java(vm,(JCHAR[]){40,73,70,70,70,70,70,70,70,70,70,70,70,70,41,86},16,1);
	aot_strings[14] = alloc_string_java(vm,(JCHAR[]){76,100,105,103,105,112,108,97,121,47,81,117,97,100,77,101,115,104,59},19,1);
	aot_strings[63] = alloc_string_java(vm,(JCHAR[]){112,114,105,110,116,83,116,97,99,107,84,114,97,99,101},15,1);
	aot_strings[24] = alloc_string_java(vm,(JCHAR[]){76,100,105,103,105,112,108,97,121,47,71,76,81,117,97,100,66,97,116,99,104,59},22,1);
	aot_strings[48] = alloc_string_java(vm,(JCHAR[]){115,101,116,82,111,116,97,116,105,111,110},11,1);
	aot_strings[1] = alloc_string_java(vm,(JCHAR[]){60,105,110,105,116,62},6,1);
	aot_strings[19] = alloc_string_java(vm,(JCHAR[]){115,101,116,72,101,105,103,104,116},9,1);
	aot_strings[6] = alloc_string_java(vm,(JCHAR[]){100,105,103,105,112,108,97,121,47,73,109,97,103,101},14,1);
	aot_strings[12] = alloc_string_java(vm,(JCHAR[]){76,106,97,118,97,47,108,97,110,103,47,83,116,114,105,110,103,59},18,1);
	aot_strings[49] = alloc_string_java(vm,(JCHAR[]){106,97,118,97,47,108,97,110,103,47,79,98,106,101,99,116},16,1);
	aot_strings[22] = alloc_string_java(vm,(JCHAR[]){100,105,103,105,112,108,97,121,47,83,116,97,103,101,50,68},16,1);
	aot_strings[30] = alloc_string_java(vm,(JCHAR[]){76,100,105,103,105,112,108,97,121,47,71,76,83,104,97,100,101,114,50,68,59},21,1);
	aot_strings[51] = alloc_string_java(vm,(JCHAR[]){76,100,105,103,105,112,108,97,121,47,71,97,109,101,59},15,1);
	aot_strings[37] = alloc_string_java(vm,(JCHAR[]){100,114,97,119,81,117,97,100,77,101,115,104},12,1);
	aot_strings[61] = alloc_string_java(vm,(JCHAR[]){98,101,103,105,110},5,1);
	aot_strings[16] = alloc_string_java(vm,(JCHAR[]){40,73,41,86},4,1);
	aot_strings[52] = alloc_string_java(vm,(JCHAR[]){106,97,118,97,47,108,97,110,103,47,83,121,115,116,101,109},16,1);
	aot_strings[50] = alloc_string_java(vm,(JCHAR[]){103,97,109,101},4,1);
	aot_strings[42] = alloc_string_java(vm,(JCHAR[]){115,99,114,101,101,110,87,105,100,116,104},11,1);
	aot_strings[33] = alloc_string_java(vm,(JCHAR[]){99,111,108,111,114},5,1);
	aot_strings[8] = alloc_string_java(vm,(JCHAR[]){70},1,1);
	aot_strings[0] = alloc_string_java(vm,(JCHAR[]){100,105,103,105,112,108,97,121,47,83,112,114,105,116,101,50,68},17,1);
	aot_strings[66] = alloc_string_java(vm,(JCHAR[]){117,112,100,97,116,101},6,1);
	aot_strings[26] = alloc_string_java(vm,(JCHAR[]){73},1,1);
	aot_strings[56] = alloc_string_java(vm,(JCHAR[]){74},1,1);
	aot_strings[60] = alloc_string_java(vm,(JCHAR[]){100,105,103,105,112,108,97,121,47,71,97,109,101},13,1);
	aot_strings[25] = alloc_string_java(vm,(JCHAR[]){71,76,79,66,65,76,95,70,82,65,77,69,95,86,69,82,83,73,79,78},20,1);
	aot_strings[34] = alloc_string_java(vm,(JCHAR[]){119,111,114,108,100,65,108,112,104,97},10,1);
	aot_strings[4] = alloc_string_java(vm,(JCHAR[]){114,97,110,100,111,109},6,1);
	aot_strings[23] = alloc_string_java(vm,(JCHAR[]){81,117,97,100,66,97,116,99,104},9,1);
	aot_strings[64] = alloc_string_java(vm,(JCHAR[]){103,97,109,101,84,105,109,101},8,1);
	aot_strings[58] = alloc_string_java(vm,(JCHAR[]){105,110,105,116,105,97,108,105,122,101,100},11,1);
	aot_strings[59] = alloc_string_java(vm,(JCHAR[]){90},1,1);
	aot_strings[68] = alloc_string_java(vm,(JCHAR[]){103,99},2,1);
	aot_strings[67] = alloc_string_java(vm,(JCHAR[]){114,101,110,100,101,114},6,1);
	aot_strings[28] = alloc_string_java(vm,(JCHAR[]){40,73,41,76,100,105,103,105,112,108,97,121,47,77,97,116,50,68,59},19,1);
	aot_strings[3] = alloc_string_java(vm,(JCHAR[]){106,97,118,97,47,108,97,110,103,47,77,97,116,104},14,1);
	aot_strings[20] = alloc_string_java(vm,(JCHAR[]){115,101,116},3,1);
	aot_strings[5] = alloc_string_java(vm,(JCHAR[]){40,41,68},3,1);
	aot_strings[40] = alloc_string_java(vm,(JCHAR[]){40,41,70},3,1);
	aot_strings[11] = alloc_string_java(vm,(JCHAR[]){115,114,99},3,1);
	aot_strings[32] = alloc_string_java(vm,(JCHAR[]){76,100,105,103,105,112,108,97,121,47,71,76,84,101,120,116,117,114,101,59},20,1);
	aot_strings[31] = alloc_string_java(vm,(JCHAR[]){116,101,120,116,117,114,101},7,1);
	aot_strings[45] = alloc_string_java(vm,(JCHAR[]){115,99,114,101,101,110,72,101,105,103,104,116},12,1);
	aot_strings[54] = alloc_string_java(vm,(JCHAR[]){40,41,74},3,1);
	aot_strings[27] = alloc_string_java(vm,(JCHAR[]){103,101,116,87,111,114,108,100,77,97,116,114,105,120},14,1);
	aot_strings[17] = alloc_string_java(vm,(JCHAR[]){115,101,116,87,105,100,116,104},8,1);
	aot_strings[15] = alloc_string_java(vm,(JCHAR[]){100,105,103,105,112,108,97,121,47,81,117,97,100,77,101,115,104},17,1);
	aot_strings[36] = alloc_string_java(vm,(JCHAR[]){100,105,103,105,112,108,97,121,47,71,76,81,117,97,100,66,97,116,99,104},20,1);
	aot_strings[39] = alloc_string_java(vm,(JCHAR[]){103,101,116,88},4,1);
	aot_strings[13] = alloc_string_java(vm,(JCHAR[]){113,117,97,100},4,1);
	aot_strings[44] = alloc_string_java(vm,(JCHAR[]){103,101,116,89},4,1);
	aot_strings[35] = alloc_string_java(vm,(JCHAR[]){98,108,101,110,100,77,111,100,101},9,1);
	aot_strings[2] = alloc_string_java(vm,(JCHAR[]){40,41,86},3,1);
	aot_strings[53] = alloc_string_java(vm,(JCHAR[]){99,117,114,114,101,110,116,84,105,109,101,77,105,108,108,105,115},17,1);
	aot_strings[18] = alloc_string_java(vm,(JCHAR[]){40,70,41,86},4,1);
	aot_strings[41] = alloc_string_java(vm,(JCHAR[]){100,105,103,105,112,108,97,121,47,80,108,97,116,102,111,114,109},17,1);
}
NativeMethodInfo aot_native_methods[] = {
	{"digiplay/Image:<init>:()V",&digiplay_Image__init____V}
	,{"digiplay/Image:getSrc:()Ljava/lang/String;",&digiplay_Image_getSrc___Ljava_lang_String_}
	,{"digiplay/Image:setSrc:(Ljava/lang/String;)V",&digiplay_Image_setSrc__Ljava_lang_String__V}
	,{"digiplay/Image:invalidateContent:()V",&digiplay_Image_invalidateContent___V}
	,{"digiplay/Image:draw:()V",&digiplay_Image_draw___V}
	,{"digiplay/Platform:<init>:()V",&digiplay_Platform__init____V}
	,{"digiplay/Platform:run:(Ldigiplay/Game;)V",&digiplay_Platform_run__Ldigiplay_Game__V}
	,{"digiplay/Platform:resize:(II)V",&digiplay_Platform_resize__II_V}
	,{"digiplay/Platform:step:()V",&digiplay_Platform_step___V}
	,{"digiplay/Platform:<clinit>:()V",&digiplay_Platform__clinit____V}
	,NULL
};
