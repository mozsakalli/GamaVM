#include "vm.h"
#include <math.h>
Object **aot_strings;

//MyGame
static Field *f_1976564770_2=NULL,*f_1976564770_4=NULL,*f_1976564770_5=NULL,*f_1976564770_15=NULL,*f_1976564770_25=NULL,*f_1976564770_28=NULL,*f_1976564770_38=NULL,*f_1976564770_41=NULL,*f_1976564770_43=NULL;
static JLONG m_1976564770_1=0,m_1976564770_6=0,m_1976564770_7=0,m_1976564770_9=0,m_1976564770_10=0,m_1976564770_12=0,m_1976564770_14=0,m_1976564770_16=0,m_1976564770_20=0,m_1976564770_22=0,m_1976564770_27=0,m_1976564770_30=0,m_1976564770_32=0,m_1976564770_33=0,m_1976564770_34=0,m_1976564770_35=0,m_1976564770_36=0,m_1976564770_37=0,m_1976564770_48=0,m_1976564770_49=0,m_1976564770_50=0;
static Object *c_1976564770_3=NULL,*c_1976564770_8=NULL,*c_1976564770_29=NULL,*c_1976564770_47=NULL,*c_1976564770_51=NULL,*c_1976564770_52=NULL,*c_1976564770_53=NULL,*c_1976564770_82=NULL,*c_1976564770_85=NULL,*c_1976564770_95=NULL,*c_1976564770_101=NULL,*c_1976564770_103=NULL,*c_1976564770_110=NULL,*c_1976564770_121=NULL,*c_1976564770_166=NULL;
void MyGame__init____V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	Object *L0;
	L0=args[0].O;
BB0:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=1;
	  AOTMETHOD(m_1976564770_1,0,1,2); //java/lang/Object:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m_1976564770_1),entry)))(vm,m_1976564770_1,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void MyGame_begin___V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JDOUBLE T5,T6;
	JFLOAT T3,T4;
	JINT L0,T2,T7,T8;
	Object *L1,*L2,*T0,*T1;
BB0:
	AOTFIELD(f_1976564770_2,3,4,5); //digiplay/Stage2D:I:Ldigiplay/Stage2D;
	T0 = *((Object**)(CLS(f_1976564770_2->declaringClass,global) + f_1976564770_2->offset));
	AOTCLASS(c_1976564770_3,6);
	T1=alloc_object(vm,c_1976564770_3,0);
	AOTFIELD(f_1976564770_4,7,8,4); //digiplay/Platform:screenWidth:I;
	T2 = *((JINT*)(CLS(f_1976564770_4->declaringClass,global) + f_1976564770_4->offset));
	T3=(JFLOAT)T2;
	AOTFIELD(f_1976564770_5,7,9,4); //digiplay/Platform:screenHeight:I;
	T2 = *((JINT*)(CLS(f_1976564770_5->declaringClass,global) + f_1976564770_5->offset));
	T4=(JFLOAT)T2;
	{
	  VAR cargs[]={{.O=T1},{.F=T3},{.F=T4}};
	  frame->pc=15;
	  AOTMETHOD(m_1976564770_6,6,1,10); //digiplay/Point2D:<init>:(FF)V;
	  ((VM_CALL)(MTH(((Object*)m_1976564770_6),entry)))(vm,m_1976564770_6,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	{
	  VAR cargs[]={{.O=T0},{.O=T1}};
	  frame->pc=18;
	  AOTVMETHOD(m_1976564770_7,3,11,12,vTableIndex); //digiplay/Stage2D:setup:(Ldigiplay/Point2D;)V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_1976564770_7];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	L0=0;
BB23:
	if(L0>=5000) goto BB130;
BB30:
	AOTCLASS(c_1976564770_8,13);
	T0=alloc_object(vm,c_1976564770_8,0);
	{
	  VAR cargs[]={{.O=T0}};
	  frame->pc=34;
	  AOTMETHOD(m_1976564770_9,13,1,2); //digiplay/Image:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m_1976564770_9),entry)))(vm,m_1976564770_9,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	L1=T0;
	AOTFIELD(f_1976564770_2,3,4,5); //digiplay/Stage2D:I:Ldigiplay/Stage2D;
	T0 = *((Object**)(CLS(f_1976564770_2->declaringClass,global) + f_1976564770_2->offset));
	{
	  VAR cargs[]={{.O=T0},{.O=L1}};
	  frame->pc=42;
	  AOTVMETHOD(m_1976564770_10,3,14,15,vTableIndex); //digiplay/Stage2D:addChild:(Ldigiplay/Sprite2D;)V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_1976564770_10];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	{
	  VAR cargs[]={{.O=L1},{.F=480.0}};
	  frame->pc=48;
	  AOTVMETHOD(m_1976564770_12,13,16,17,vTableIndex); //digiplay/Image:x:(F)V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_1976564770_12];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	{
	  VAR cargs[]={{.O=L1},{.F=320.0}};
	  frame->pc=54;
	  AOTVMETHOD(m_1976564770_14,13,18,17,vTableIndex); //digiplay/Image:y:(F)V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_1976564770_14];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	if(!f_1976564770_15) { //blendMode;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,15);
	  f_1976564770_15=fld->instance;
	}
	*FIELD_PTR_I(L1,f_1976564770_15->offset) = 0;
	{
	  frame->pc=63;
	  AOTMETHOD(m_1976564770_16,19,20,21); //java/lang/Math:random:()D;
	  ((VM_CALL)(MTH(((Object*)m_1976564770_16),entry)))(vm,m_1976564770_16,NULL);
	  if(vm->exception) goto __EXCEPTION;
	  T5=frame->ret.D;
	}
	
	T6 = T5 * 0.5;
	T3=(JFLOAT)T6;
	T4 = T3 + 0.5;
	{
	  VAR cargs[]={{.O=L1},{.F=T4}};
	  frame->pc=74;
	  AOTVMETHOD(m_1976564770_20,13,22,17,vTableIndex); //digiplay/Image:setAlpha:(F)V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_1976564770_20];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	{
	  frame->pc=78;
	  AOTMETHOD(m_1976564770_16,19,20,21); //java/lang/Math:random:()D;
	  ((VM_CALL)(MTH(((Object*)m_1976564770_16),entry)))(vm,m_1976564770_16,NULL);
	  if(vm->exception) goto __EXCEPTION;
	  T5=frame->ret.D;
	}
	
	T3=(JFLOAT)T5;
	T4 = T3 * 360.0;
	{
	  VAR cargs[]={{.O=L1},{.F=T4}};
	  frame->pc=85;
	  AOTVMETHOD(m_1976564770_22,13,23,17,vTableIndex); //digiplay/Image:rotation:(F)V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_1976564770_22];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	{
	  frame->pc=89;
	  AOTMETHOD(m_1976564770_16,19,20,21); //java/lang/Math:random:()D;
	  ((VM_CALL)(MTH(((Object*)m_1976564770_16),entry)))(vm,m_1976564770_16,NULL);
	  if(vm->exception) goto __EXCEPTION;
	  T5=frame->ret.D;
	}
	
	T6 = T5 * 255.0;
	T2=(JINT)T6;
	T7 = T2 << 16;
	{
	  frame->pc=100;
	  AOTMETHOD(m_1976564770_16,19,20,21); //java/lang/Math:random:()D;
	  ((VM_CALL)(MTH(((Object*)m_1976564770_16),entry)))(vm,m_1976564770_16,NULL);
	  if(vm->exception) goto __EXCEPTION;
	  T5=frame->ret.D;
	}
	
	T6 = T5 * 255.0;
	T2=(JINT)T6;
	T8 = T2 << 8;
	T2 = T7 | T8;
	{
	  frame->pc=112;
	  AOTMETHOD(m_1976564770_16,19,20,21); //java/lang/Math:random:()D;
	  ((VM_CALL)(MTH(((Object*)m_1976564770_16),entry)))(vm,m_1976564770_16,NULL);
	  if(vm->exception) goto __EXCEPTION;
	  T5=frame->ret.D;
	}
	
	T6 = T5 * 255.0;
	T7=(JINT)T6;
	T8 = T2 | T7;
	if(!f_1976564770_25) { //color;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,25);
	  f_1976564770_25=fld->instance;
	}
	*FIELD_PTR_I(L1,f_1976564770_25->offset) = T8;
	L0+=1;
	goto BB23;
BB130:
	{
	  VAR cargs[]={{.O=aot_strings[24]}};
	  frame->pc=132;
	  AOTMETHOD(m_1976564770_27,25,26,27); //digiplay/MainActivity:readFile:(Ljava/lang/String;)[B;
	  ((VM_CALL)(MTH(((Object*)m_1976564770_27),entry)))(vm,m_1976564770_27,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T0=frame->ret.O;
	}
	
	L2=T0;
	AOTFIELD(f_1976564770_28,28,29,30); //java/lang/System:out:Ljava/io/PrintStream;
	T0 = *((Object**)(CLS(f_1976564770_28->declaringClass,global) + f_1976564770_28->offset));
	AOTCLASS(c_1976564770_29,31);
	T1=alloc_object(vm,c_1976564770_29,0);
	{
	  VAR cargs[]={{.O=T1}};
	  frame->pc=143;
	  AOTMETHOD(m_1976564770_30,31,1,2); //java/lang/StringBuilder:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m_1976564770_30),entry)))(vm,m_1976564770_30,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	{
	  VAR cargs[]={{.O=T1},{.O=aot_strings[32]}};
	  frame->pc=148;
	  AOTVMETHOD(m_1976564770_32,31,33,34,vTableIndex); //java/lang/StringBuilder:append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_1976564770_32];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T1=frame->ret.O;
	}
	
	if(!L2) {throw_null(vm);} T2=L2->length;
	{
	  VAR cargs[]={{.O=T1},{.I=T2}};
	  frame->pc=153;
	  AOTVMETHOD(m_1976564770_33,31,33,35,vTableIndex); //java/lang/StringBuilder:append:(I)Ljava/lang/StringBuilder;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_1976564770_33];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T1=frame->ret.O;
	}
	
	{
	  VAR cargs[]={{.O=T1}};
	  frame->pc=156;
	  AOTVMETHOD(m_1976564770_34,31,36,37,vTableIndex); //java/lang/StringBuilder:toString:()Ljava/lang/String;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_1976564770_34];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T1=frame->ret.O;
	}
	
	{
	  VAR cargs[]={{.O=T0},{.O=T1}};
	  frame->pc=159;
	  AOTVMETHOD(m_1976564770_35,38,39,40,vTableIndex); //java/io/PrintStream:println:(Ljava/lang/String;)V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_1976564770_35];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void MyGame_update___V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JINT T4,T5;
	JLONG L0,T1,T2,T3;
	Object *L1,*T0,*T6;
	L1=args[0].O;
BB0:
	AOTFIELD(f_1976564770_2,3,4,5); //digiplay/Stage2D:I:Ldigiplay/Stage2D;
	T0 = *((Object**)(CLS(f_1976564770_2->declaringClass,global) + f_1976564770_2->offset));
	{
	  VAR cargs[]={{.O=T0}};
	  frame->pc=3;
	  AOTVMETHOD(m_1976564770_36,3,41,2,vTableIndex); //digiplay/Stage2D:update:()V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_1976564770_36];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	{
	  frame->pc=6;
	  AOTMETHOD(m_1976564770_37,28,42,43); //java/lang/System:currentTimeMillis:()J;
	  ((VM_CALL)(MTH(((Object*)m_1976564770_37),entry)))(vm,m_1976564770_37,NULL);
	  if(vm->exception) goto __EXCEPTION;
	  T1=frame->ret.J;
	}
	
	L0=T1;
	{
	  frame->pc=10;
	  AOTMETHOD(m_1976564770_37,28,42,43); //java/lang/System:currentTimeMillis:()J;
	  ((VM_CALL)(MTH(((Object*)m_1976564770_37),entry)))(vm,m_1976564770_37,NULL);
	  if(vm->exception) goto __EXCEPTION;
	  T1=frame->ret.J;
	}
	
	AOTFIELD(f_1976564770_38,44,45,46); //MyGame:fpsTimer:J;
	if(!L1) { frame->pc = 14; throw_null(vm); goto __EXCEPTION; }
	T2 = *FIELD_PTR_J(L1,f_1976564770_38->offset);
	T3 = T1 - T2;
	T1 = T3 == 1000 ? 0 : (T3 > 1000 ? 1 : -1);
	if(T1>0) goto BB38;
BB25:
	AOTFIELD(f_1976564770_41,44,47,4); //MyGame:fps:I;
	if(!L1) { frame->pc = 27; throw_null(vm); goto __EXCEPTION; }
	T4 = *FIELD_PTR_I(L1,f_1976564770_41->offset);
	T5 = T4 + 1;
	if(!f_1976564770_41) { //fps;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,41);
	  f_1976564770_41=fld->instance;
	}
	*FIELD_PTR_I(L1,f_1976564770_41->offset) = T5;
	goto BB78;
BB38:
	AOTFIELD(f_1976564770_28,28,29,30); //java/lang/System:out:Ljava/io/PrintStream;
	T0 = *((Object**)(CLS(f_1976564770_28->declaringClass,global) + f_1976564770_28->offset));
	AOTCLASS(c_1976564770_29,31);
	T6=alloc_object(vm,c_1976564770_29,0);
	{
	  VAR cargs[]={{.O=T6}};
	  frame->pc=45;
	  AOTMETHOD(m_1976564770_30,31,1,2); //java/lang/StringBuilder:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m_1976564770_30),entry)))(vm,m_1976564770_30,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	{
	  VAR cargs[]={{.O=T6},{.O=aot_strings[48]}};
	  frame->pc=50;
	  AOTVMETHOD(m_1976564770_32,31,33,34,vTableIndex); //java/lang/StringBuilder:append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_1976564770_32];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T6=frame->ret.O;
	}
	
	AOTFIELD(f_1976564770_41,44,47,4); //MyGame:fps:I;
	if(!L1) { frame->pc = 54; throw_null(vm); goto __EXCEPTION; }
	T4 = *FIELD_PTR_I(L1,f_1976564770_41->offset);
	{
	  VAR cargs[]={{.O=T6},{.I=T4}};
	  frame->pc=57;
	  AOTVMETHOD(m_1976564770_33,31,33,35,vTableIndex); //java/lang/StringBuilder:append:(I)Ljava/lang/StringBuilder;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_1976564770_33];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T6=frame->ret.O;
	}
	
	{
	  VAR cargs[]={{.O=T6}};
	  frame->pc=60;
	  AOTVMETHOD(m_1976564770_34,31,36,37,vTableIndex); //java/lang/StringBuilder:toString:()Ljava/lang/String;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_1976564770_34];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T6=frame->ret.O;
	}
	
	{
	  VAR cargs[]={{.O=T0},{.O=T6}};
	  frame->pc=63;
	  AOTVMETHOD(m_1976564770_35,38,39,40,vTableIndex); //java/io/PrintStream:println:(Ljava/lang/String;)V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_1976564770_35];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	if(!f_1976564770_41) { //fps;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,41);
	  f_1976564770_41=fld->instance;
	}
	*FIELD_PTR_I(L1,f_1976564770_41->offset) = 0;
	{
	  frame->pc=72;
	  AOTMETHOD(m_1976564770_37,28,42,43); //java/lang/System:currentTimeMillis:()J;
	  ((VM_CALL)(MTH(((Object*)m_1976564770_37),entry)))(vm,m_1976564770_37,NULL);
	  if(vm->exception) goto __EXCEPTION;
	  T1=frame->ret.J;
	}
	
	if(!f_1976564770_38) { //fpsTimer;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,38);
	  f_1976564770_38=fld->instance;
	}
	*FIELD_PTR_J(L1,f_1976564770_38->offset) = T1;
BB78:
	AOTFIELD(f_1976564770_43,44,49,46); //MyGame:httpTimer:J;
	if(!L1) { frame->pc = 80; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_J(L1,f_1976564770_43->offset);
	T2 = L0 - T1;
	T1 = T2 == 5000 ? 0 : (T2 > 5000 ? 1 : -1);
	if(T1<0) goto BB110;
BB91:
	AOTCLASS(c_1976564770_47,51);
	T0=alloc_object(vm,c_1976564770_47,0);
	{
	  VAR cargs[]={{.O=T0},{.O=L1}};
	  frame->pc=99;
	  AOTMETHOD(m_1976564770_48,51,1,52); //MyGame$1:<init>:(LMyGame;)V;
	  ((VM_CALL)(MTH(((Object*)m_1976564770_48),entry)))(vm,m_1976564770_48,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	{
	  VAR cargs[]={{.O=aot_strings[50]},{.O=NULL},{.O=T0}};
	  frame->pc=102;
	  AOTMETHOD(m_1976564770_49,53,54,55); //digiplay/Net:http:(Ljava/lang/String;Ljava/lang/String;Ldigiplay/Net$HttpListener;)V;
	  ((VM_CALL)(MTH(((Object*)m_1976564770_49),entry)))(vm,m_1976564770_49,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	if(!f_1976564770_43) { //httpTimer;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,43);
	  f_1976564770_43=fld->instance;
	}
	*FIELD_PTR_J(L1,f_1976564770_43->offset) = L0;
BB110:
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void MyGame_render___V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	Object *T0;
BB0:
	AOTFIELD(f_1976564770_2,3,4,5); //digiplay/Stage2D:I:Ldigiplay/Stage2D;
	T0 = *((Object**)(CLS(f_1976564770_2->declaringClass,global) + f_1976564770_2->offset));
	{
	  VAR cargs[]={{.O=T0}};
	  frame->pc=3;
	  AOTVMETHOD(m_1976564770_50,3,56,2,vTableIndex); //digiplay/Stage2D:render:()V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_1976564770_50];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
//Tmp
static JLONG m84215_1=0,m84215_7=0,m84215_13=0,m84215_17=0,m84215_25=0,m84215_30=0,m84215_36=0,m84215_39=0,m84215_45=0,m84215_49=0,m84215_53=0,m84215_59=0,m84215_62=0,m84215_66=0,m84215_75=0,m84215_78=0,m84215_82=0;
static Object *c84215_2=NULL,*c84215_8=NULL,*c84215_18=NULL,*c84215_23=NULL,*c84215_34=NULL,*c84215_54=NULL,*c84215_73=NULL,*c84215_83=NULL,*c84215_118=NULL,*c84215_120=NULL,*c84215_121=NULL,*c84215_123=NULL;
void Tmp__init____V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	Object *L0;
	L0=args[0].O;
BB0:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=1;
	  AOTMETHOD(m84215_1,0,1,2); //java/lang/Object:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m84215_1),entry)))(vm,m84215_1,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void Tmp_work__Ljava_net_Socket__V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JINT L4,L7,L10,L12,L13,T1,T2;
	Object *L0,*L1,*L2,*L3,*L5,*L6,*L8,*L9,*L11,*L14,*L15,*T0,*T3;
	L0=args[0].O;
BB0:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=1;
	  AOTVMETHOD(m84215_7,57,58,59,vTableIndex); //java/net/Socket:getInputStream:()Ljava/io/InputStream;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m84215_7];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T0=frame->ret.O;
	}
	
	L1=T0;
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=6;
	  AOTVMETHOD(m84215_13,57,60,61,vTableIndex); //java/net/Socket:getOutputStream:()Ljava/io/OutputStream;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m84215_13];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T0=frame->ret.O;
	}
	
	L2=T0;
	T0 = alloc_array_B(vm,8192,0);
	L3=T0;
	{
	  VAR cargs[]={{.O=L1},{.O=L3}};
	  frame->pc=18;
	  AOTVMETHOD(m84215_17,62,63,64,vTableIndex); //java/io/InputStream:read:([B)I;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m84215_17];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T1=frame->ret.I;
	}
	
	L4=T1;
	L5=NULL;
	L6=NULL;
	L7=0;
BB32:
	if(L7>=L4) goto BB264;
BB39:
	if(!L3) { throw_null(vm); goto __EXCEPTION;}
	if(L7 < 0 || L7 >= L3->length) { throw_arrayounds(vm,L7,L3->length); goto __EXCEPTION; }
	T1 = ARRAY_DATA_B(L3)[L7];
	if(T1!=10) goto BB258;
BB48:
	T1 = L7 + 2;
	if(!L3) { throw_null(vm); goto __EXCEPTION;}
	if(T1 < 0 || T1 >= L3->length) { throw_arrayounds(vm,T1,L3->length); goto __EXCEPTION; }
	T1 = ARRAY_DATA_B(L3)[T1];
	if(T1!=10) goto BB258;
BB59:
	AOTCLASS(c84215_23,65);
	T0=alloc_object(vm,c84215_23,0);
	{
	  VAR cargs[]={{.O=T0},{.O=L3},{.I=0},{.I=L7}};
	  frame->pc=67;
	  AOTMETHOD(m84215_25,65,1,66); //java/lang/String:<init>:([BII)V;
	  ((VM_CALL)(MTH(((Object*)m84215_25),entry)))(vm,m84215_25,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	L5=T0;
	{
	  VAR cargs[]={{.O=L5},{.O=aot_strings[67]}};
	  frame->pc=76;
	  AOTVMETHOD(m84215_30,65,68,69,vTableIndex); //java/lang/String:startsWith:(Ljava/lang/String;)Z;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m84215_30];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T1=frame->ret.I;
	}
	
	if(T1==0) goto BB264;
BB82:
	AOTCLASS(c84215_34,70);
	T0=alloc_object(vm,c84215_34,0);
	{
	  VAR cargs[]={{.O=T0}};
	  frame->pc=86;
	  AOTMETHOD(m84215_36,70,1,2); //java/io/ByteArrayOutputStream:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m84215_36),entry)))(vm,m84215_36,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	L8=T0;
	{
	  VAR cargs[]={{.O=L5},{.O=aot_strings[71]}};
	  frame->pc=95;
	  AOTVMETHOD(m84215_39,65,72,73,vTableIndex); //java/lang/String:split:(Ljava/lang/String;)[Ljava/lang/String;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m84215_39];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T0=frame->ret.O;
	}
	
	L9=T0;
	L10=0;
	L11=L9;
	if(!L11) {throw_null(vm);} T1=L11->length;
	L12=T1;
	L13=0;
BB115:
	if(L13>=L12) goto BB163;
BB122:
	if(!L11) { throw_null(vm); goto __EXCEPTION;}
	if(L13 < 0 || L13 >= L11->length) { throw_arrayounds(vm,L13,L11->length); goto __EXCEPTION; }
	T0 = ARRAY_DATA_O(L11)[L13];
	L14=T0;
	{
	  VAR cargs[]={{.O=L14},{.O=aot_strings[74]}};
	  frame->pc=133;
	  AOTVMETHOD(m84215_30,65,68,69,vTableIndex); //java/lang/String:startsWith:(Ljava/lang/String;)Z;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m84215_30];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T1=frame->ret.I;
	}
	
	if(T1==0) goto BB157;
BB139:
	{
	  VAR cargs[]={{.O=L14},{.I=15}};
	  frame->pc=143;
	  AOTVMETHOD(m84215_45,65,75,76,vTableIndex); //java/lang/String:substring:(I)Ljava/lang/String;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m84215_45];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T0=frame->ret.O;
	}
	
	{
	  VAR cargs[]={{.O=T0}};
	  frame->pc=146;
	  AOTVMETHOD(m84215_49,65,77,37,vTableIndex); //java/lang/String:trim:()Ljava/lang/String;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m84215_49];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T0=frame->ret.O;
	}
	
	{
	  VAR cargs[]={{.O=T0}};
	  frame->pc=149;
	  AOTMETHOD(m84215_53,78,79,80); //java/lang/Integer:parseInt:(Ljava/lang/String;)I;
	  ((VM_CALL)(MTH(((Object*)m84215_53),entry)))(vm,m84215_53,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T1=frame->ret.I;
	}
	
	L10=T1;
	goto BB163;
BB157:
	L13+=1;
	goto BB115;
BB163:
	AOTCLASS(c84215_34,70);
	T0=alloc_object(vm,c84215_34,0);
	{
	  VAR cargs[]={{.O=T0}};
	  frame->pc=167;
	  AOTMETHOD(m84215_36,70,1,2); //java/io/ByteArrayOutputStream:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m84215_36),entry)))(vm,m84215_36,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	L11=T0;
	T1 = L4 - L7;
	T2 = T1 - 3;
	L12=T2;
	if(L12<=0) goto BB205;
BB186:
	T1 = L7 + 3;
	{
	  VAR cargs[]={{.O=L11},{.O=L3},{.I=T1},{.I=L12}};
	  frame->pc=195;
	  AOTVMETHOD(m84215_59,70,81,66,vTableIndex); //java/io/ByteArrayOutputStream:write:([BII)V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m84215_59];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	T1 = L10 - L12;
	L10=T1;
BB205:
	if(L10<=0) goto BB241;
BB210:
	{
	  VAR cargs[]={{.O=L1},{.O=L3}};
	  frame->pc=212;
	  AOTVMETHOD(m84215_17,62,63,64,vTableIndex); //java/io/InputStream:read:([B)I;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m84215_17];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T1=frame->ret.I;
	}
	
	L4=T1;
	if(L4<=0) goto BB241;
BB222:
	{
	  VAR cargs[]={{.O=L11},{.O=L3},{.I=0},{.I=L4}};
	  frame->pc=228;
	  AOTVMETHOD(m84215_59,70,81,66,vTableIndex); //java/io/ByteArrayOutputStream:write:([BII)V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m84215_59];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	T1 = L10 - L4;
	L10=T1;
	goto BB205;
BB241:
	AOTCLASS(c84215_23,65);
	T0=alloc_object(vm,c84215_23,0);
	{
	  VAR cargs[]={{.O=L11}};
	  frame->pc=247;
	  AOTVMETHOD(m84215_62,70,82,83,vTableIndex); //java/io/ByteArrayOutputStream:toByteArray:()[B;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m84215_62];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T3=frame->ret.O;
	}
	
	{
	  VAR cargs[]={{.O=T0},{.O=T3}};
	  frame->pc=250;
	  AOTMETHOD(m84215_66,65,1,84); //java/lang/String:<init>:([B)V;
	  ((VM_CALL)(MTH(((Object*)m84215_66),entry)))(vm,m84215_66,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	L6=T0;
	goto BB264;
BB258:
	L7+=1;
	goto BB32;
BB264:
	L15=NULL;
	{
	  VAR cargs[]={{.O=L5},{.O=aot_strings[71]}};
	  frame->pc=271;
	  AOTVMETHOD(m84215_39,65,72,73,vTableIndex); //java/lang/String:split:(Ljava/lang/String;)[Ljava/lang/String;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m84215_39];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T0=frame->ret.O;
	}
	
	L8=T0;
	if(!L8) { throw_null(vm); goto __EXCEPTION;}
	if(0 < 0 || 0 >= L8->length) { throw_arrayounds(vm,0,L8->length); goto __EXCEPTION; }
	T0 = ARRAY_DATA_O(L8)[0];
	{
	  VAR cargs[]={{.O=T0},{.O=aot_strings[85]}};
	  frame->pc=282;
	  AOTVMETHOD(m84215_39,65,72,73,vTableIndex); //java/lang/String:split:(Ljava/lang/String;)[Ljava/lang/String;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m84215_39];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T0=frame->ret.O;
	}
	
	if(!T0) { throw_null(vm); goto __EXCEPTION;}
	if(1 < 0 || 1 >= T0->length) { throw_arrayounds(vm,1,T0->length); goto __EXCEPTION; }
	T0 = ARRAY_DATA_O(T0)[1];
	{
	  VAR cargs[]={{.O=T0},{.O=aot_strings[86]}};
	  frame->pc=289;
	  AOTVMETHOD(m84215_39,65,72,73,vTableIndex); //java/lang/String:split:(Ljava/lang/String;)[Ljava/lang/String;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m84215_39];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T0=frame->ret.O;
	}
	
	L9=T0;
	if(!L9) { throw_null(vm); goto __EXCEPTION;}
	if(0 < 0 || 0 >= L9->length) { throw_arrayounds(vm,0,L9->length); goto __EXCEPTION; }
	T0 = ARRAY_DATA_O(L9)[0];
	L15=T0;
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void Tmp_main___Ljava_lang_String__V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	Object *L0,*L1,*T0;
BB0:
	AOTCLASS(c84215_73,87);
	T0=alloc_object(vm,c84215_73,0);
	{
	  VAR cargs[]={{.O=T0},{.I=7777}};
	  frame->pc=7;
	  AOTMETHOD(m84215_75,87,1,88); //java/net/ServerSocket:<init>:(I)V;
	  ((VM_CALL)(MTH(((Object*)m84215_75),entry)))(vm,m84215_75,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	L0=T0;
BB11:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=12;
	  AOTVMETHOD(m84215_78,87,89,90,vTableIndex); //java/net/ServerSocket:accept:()Ljava/net/Socket;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m84215_78];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T0=frame->ret.O;
	}
	
	L1=T0;
	{
	  VAR cargs[]={{.O=L1}};
	  frame->pc=17;
	  AOTMETHOD(m84215_82,91,92,93); //Tmp:work:(Ljava/net/Socket;)V;
	  ((VM_CALL)(MTH(((Object*)m84215_82),entry)))(vm,m84215_82,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	goto BB11;
__EXCEPTION: {
	vm->FP--; return;
}
}
//MyGame$1
static Field *f_1103197973_1=NULL,*f_1103197973_3=NULL;
static JLONG m_1103197973_2=0,m_1103197973_5=0,m_1103197973_7=0,m_1103197973_9=0,m_1103197973_10=0,m_1103197973_11=0;
static Object *c_1103197973_4=NULL,*c_1103197973_8=NULL,*c_1103197973_13=NULL,*c_1103197973_14=NULL,*c_1103197973_15=NULL,*c_1103197973_37=NULL,*c_1103197973_41=NULL,*c_1103197973_49=NULL,*c_1103197973_54=NULL;
void MyGame$1__init___LMyGame__V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	Object *L0,*L1;
	L0=args[0].O;
	L1=args[1].O;
BB0:
	if(!f_1103197973_1) { //this$0;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,1);
	  f_1103197973_1=fld->instance;
	}
	*FIELD_PTR_O(L0,f_1103197973_1->offset) = L1;
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=6;
	  AOTMETHOD(m_1103197973_2,0,1,2); //java/lang/Object:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m_1103197973_2),entry)))(vm,m_1103197973_2,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void MyGame$1_onHttpSuccess___B_V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	Object *L0,*T0,*T1,*T2;
BB0:
	AOTFIELD(f_1103197973_3,28,29,30); //java/lang/System:out:Ljava/io/PrintStream;
	T0 = *((Object**)(CLS(f_1103197973_3->declaringClass,global) + f_1103197973_3->offset));
	AOTCLASS(c_1103197973_4,31);
	T1=alloc_object(vm,c_1103197973_4,0);
	{
	  VAR cargs[]={{.O=T1}};
	  frame->pc=7;
	  AOTMETHOD(m_1103197973_5,31,1,2); //java/lang/StringBuilder:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m_1103197973_5),entry)))(vm,m_1103197973_5,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	{
	  VAR cargs[]={{.O=T1},{.O=aot_strings[94]}};
	  frame->pc=12;
	  AOTVMETHOD(m_1103197973_7,31,33,34,vTableIndex); //java/lang/StringBuilder:append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_1103197973_7];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T1=frame->ret.O;
	}
	
	AOTCLASS(c_1103197973_8,65);
	T2=alloc_object(vm,c_1103197973_8,0);
	{
	  VAR cargs[]={{.O=T2},{.O=L0}};
	  frame->pc=20;
	  AOTMETHOD(m_1103197973_9,65,1,84); //java/lang/String:<init>:([B)V;
	  ((VM_CALL)(MTH(((Object*)m_1103197973_9),entry)))(vm,m_1103197973_9,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	{
	  VAR cargs[]={{.O=T1},{.O=T2}};
	  frame->pc=23;
	  AOTVMETHOD(m_1103197973_7,31,33,34,vTableIndex); //java/lang/StringBuilder:append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_1103197973_7];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T1=frame->ret.O;
	}
	
	{
	  VAR cargs[]={{.O=T1}};
	  frame->pc=26;
	  AOTVMETHOD(m_1103197973_10,31,36,37,vTableIndex); //java/lang/StringBuilder:toString:()Ljava/lang/String;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_1103197973_10];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T1=frame->ret.O;
	}
	
	{
	  VAR cargs[]={{.O=T0},{.O=T1}};
	  frame->pc=29;
	  AOTVMETHOD(m_1103197973_11,38,39,40,vTableIndex); //java/io/PrintStream:println:(Ljava/lang/String;)V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_1103197973_11];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void MyGame$1_onHttpFail___V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	Object *T0;
BB0:
	AOTFIELD(f_1103197973_3,28,29,30); //java/lang/System:out:Ljava/io/PrintStream;
	T0 = *((Object**)(CLS(f_1103197973_3->declaringClass,global) + f_1103197973_3->offset));
	{
	  VAR cargs[]={{.O=T0},{.O=aot_strings[95]}};
	  frame->pc=5;
	  AOTVMETHOD(m_1103197973_11,38,39,40,vTableIndex); //java/io/PrintStream:println:(Ljava/lang/String;)V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_1103197973_11];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
//Main
static JLONG m2390489_1=0,m2390489_9=0,m2390489_10=0;
static Object *c2390489_2=NULL,*c2390489_7=NULL,*c2390489_11=NULL,*c2390489_16=NULL;
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
	Object *T0;
BB0:
	AOTCLASS(c2390489_7,44);
	T0=alloc_object(vm,c2390489_7,0);
	{
	  VAR cargs[]={{.O=T0}};
	  frame->pc=4;
	  AOTMETHOD(m2390489_9,44,1,2); //MyGame:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m2390489_9),entry)))(vm,m2390489_9,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	{
	  VAR cargs[]={{.O=T0}};
	  frame->pc=7;
	  AOTMETHOD(m2390489_10,7,96,97); //digiplay/Platform:run:(Ldigiplay/Game;)V;
	  ((VM_CALL)(MTH(((Object*)m2390489_10),entry)))(vm,m2390489_10,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;return;
__EXCEPTION: {
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
//gamavm/External
static Object *c_1459729515_1=NULL,*c_1459729515_2=NULL,*c_1459729515_3=NULL;
//digiplay/MainActivity
static JLONG m_1675081284_1=0;
static Object *c_1675081284_2=NULL,*c_1675081284_3=NULL;
void digiplay_MainActivity__init____V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	Object *L0;
	L0=args[0].O;
BB0:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=1;
	  AOTMETHOD(m_1675081284_1,0,1,2); //java/lang/Object:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m_1675081284_1),entry)))(vm,m_1675081284_1,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
//digiplay/Mat2D
static Field *f1466582110_13=NULL;
static JLONG m1466582110_1=0,m1466582110_7=0,m1466582110_17=0;
static Object *c1466582110_2=NULL,*c1466582110_8=NULL,*c1466582110_18=NULL,*c1466582110_36=NULL;
void digiplay_Mat2D__init____V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JLONG T0;
	Object *L0;
	L0=args[0].O;
BB0:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=1;
	  AOTMETHOD(m1466582110_1,0,1,2); //java/lang/Object:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m1466582110_1),entry)))(vm,m1466582110_1,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	{
	  frame->pc=5;
	  AOTMETHOD(m1466582110_7,98,99,43); //digiplay/Mat2D:create:()J;
	  ((VM_CALL)(MTH(((Object*)m1466582110_7),entry)))(vm,m1466582110_7,NULL);
	  if(vm->exception) goto __EXCEPTION;
	  T0=frame->ret.J;
	}
	
	if(!f1466582110_13) { //handle;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,13);
	  f1466582110_13=fld->instance;
	}
	*FIELD_PTR_J(L0,f1466582110_13->offset) = T0;
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Mat2D_finalize___V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JLONG T0;
	Object *L0;
	L0=args[0].O;
BB0:
	AOTFIELD(f1466582110_13,98,100,46); //digiplay/Mat2D:handle:J;
	if(!L0) { frame->pc = 1; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_J(L0,f1466582110_13->offset);
	if(T0==0) goto BB16;
BB9:
	AOTFIELD(f1466582110_13,98,100,46); //digiplay/Mat2D:handle:J;
	if(!L0) { frame->pc = 10; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_J(L0,f1466582110_13->offset);
	{
	  VAR cargs[]={{.J=T0}};
	  frame->pc=13;
	  AOTMETHOD(m1466582110_17,101,102,103); //gamavm/VM:freeMem:(J)V;
	  ((VM_CALL)(MTH(((Object*)m1466582110_17),entry)))(vm,m1466582110_17,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
BB16:
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
//digiplay/Net$Http
static Field *f_769500381_7=NULL,*f_769500381_13=NULL;
static JLONG m_769500381_1=0;
static Object *c_769500381_2=NULL,*c_769500381_8=NULL,*c_769500381_26=NULL;
void digiplay_Net$Http__init___Ljava_lang_String_Ljava_lang_String__V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	Object *L0,*L1,*L2;
	L0=args[0].O;
	L1=args[1].O;
	L2=args[2].O;
BB0:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=1;
	  AOTMETHOD(m_769500381_1,104,1,2); //digiplay/ByteArrayCompletable:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m_769500381_1),entry)))(vm,m_769500381_1,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	if(!f_769500381_7) { //url;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,7);
	  f_769500381_7=fld->instance;
	}
	*FIELD_PTR_O(L0,f_769500381_7->offset) = L1;
	if(!f_769500381_13) { //postData;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,13);
	  f_769500381_13=fld->instance;
	}
	*FIELD_PTR_O(L0,f_769500381_13->offset) = L2;
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
//digiplay/GLShader2D
static Field *f2099842992_16=NULL;
static JLONG m2099842992_1=0,m2099842992_9=0,m2099842992_10=0,m2099842992_24=0;
static Object *c2099842992_2=NULL,*c2099842992_7=NULL,*c2099842992_11=NULL,*c2099842992_20=NULL,*c2099842992_35=NULL,*c2099842992_39=NULL;
void digiplay_GLShader2D__init___Ljava_lang_String__V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JLONG T1;
	Object *L0,*L1,*T0;
	L0=args[0].O;
	L1=args[1].O;
BB0:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=1;
	  AOTMETHOD(m2099842992_1,0,1,2); //java/lang/Object:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m2099842992_1),entry)))(vm,m2099842992_1,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	if(L1!=NULL) goto BB16;
BB8:
	AOTCLASS(c2099842992_7,105);
	T0=alloc_object(vm,c2099842992_7,0);
	{
	  VAR cargs[]={{.O=T0}};
	  frame->pc=12;
	  AOTMETHOD(m2099842992_9,105,1,2); //java/lang/NullPointerException:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m2099842992_9),entry)))(vm,m2099842992_9,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	throw_exception(vm,T0);
BB16:
	{
	  VAR cargs[]={{.O=L1}};
	  frame->pc=18;
	  AOTMETHOD(m2099842992_10,106,107,108); //digiplay/GLShader2D:compile:(Ljava/lang/String;)J;
	  ((VM_CALL)(MTH(((Object*)m2099842992_10),entry)))(vm,m2099842992_10,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T1=frame->ret.J;
	}
	
	if(!f2099842992_16) { //handle;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,16);
	  f2099842992_16=fld->instance;
	}
	*FIELD_PTR_J(L0,f2099842992_16->offset) = T1;
	AOTFIELD(f2099842992_16,106,100,46); //digiplay/GLShader2D:handle:J;
	if(!L0) { frame->pc = 25; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_J(L0,f2099842992_16->offset);
	T1 = T1 == 0 ? 0 : (T1 > 0 ? 1 : -1);
	if(T1>0) goto BB43;
BB33:
	AOTCLASS(c2099842992_20,109);
	T0=alloc_object(vm,c2099842992_20,0);
	{
	  VAR cargs[]={{.O=T0},{.O=aot_strings[110]}};
	  frame->pc=39;
	  AOTMETHOD(m2099842992_24,109,1,40); //java/lang/RuntimeException:<init>:(Ljava/lang/String;)V;
	  ((VM_CALL)(MTH(((Object*)m2099842992_24),entry)))(vm,m2099842992_24,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	throw_exception(vm,T0);
BB43:
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
//digiplay/Sprite2D
static Field *f534981547_9=NULL,*f534981547_13=NULL,*f534981547_17=NULL,*f534981547_20=NULL,*f534981547_23=NULL,*f534981547_27=NULL,*f534981547_30=NULL,*f534981547_34=NULL,*f534981547_37=NULL,*f534981547_43=NULL,*f534981547_47=NULL,*f534981547_50=NULL,*f534981547_53=NULL,*f534981547_56=NULL,*f534981547_59=NULL,*f534981547_62=NULL,*f534981547_65=NULL,*f534981547_68=NULL,*f534981547_71=NULL,*f534981547_74=NULL,*f534981547_77=NULL,*f534981547_80=NULL,*f534981547_83=NULL,*f534981547_86=NULL,*f534981547_89=NULL,*f534981547_92=NULL,*f534981547_95=NULL,*f534981547_98=NULL,*f534981547_104=NULL,*f534981547_108=NULL,*f534981547_111=NULL,*f534981547_114=NULL,*f534981547_117=NULL,*f534981547_120=NULL,*f534981547_127=NULL,*f534981547_139=NULL,*f534981547_148=NULL;
static JLONG m534981547_1=0,m534981547_42=0,m534981547_101=0,m534981547_123=0,m534981547_130=0,m534981547_133=0,m534981547_136=0,m534981547_142=0,m534981547_145=0,m534981547_153=0;
static Object *c534981547_2=NULL,*c534981547_7=NULL,*c534981547_40=NULL,*c534981547_149=NULL;
void digiplay_Sprite2D__init____V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	Object *L0,*T0;
	L0=args[0].O;
BB0:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=1;
	  AOTMETHOD(m534981547_1,0,1,2); //java/lang/Object:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m534981547_1),entry)))(vm,m534981547_1,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	if(!f534981547_9) { //flags;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,9);
	  f534981547_9=fld->instance;
	}
	*FIELD_PTR_I(L0,f534981547_9->offset) = 13;
	if(!f534981547_13) { //scaleX;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,13);
	  f534981547_13=fld->instance;
	}
	*FIELD_PTR_F(L0,f534981547_13->offset) = 1;
	if(!f534981547_17) { //scaleY;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,17);
	  f534981547_17=fld->instance;
	}
	*FIELD_PTR_F(L0,f534981547_17->offset) = 1;
	if(!f534981547_20) { //alpha;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,20);
	  f534981547_20=fld->instance;
	}
	*FIELD_PTR_F(L0,f534981547_20->offset) = 1;
	if(!f534981547_23) { //worldAlpha;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,23);
	  f534981547_23=fld->instance;
	}
	*FIELD_PTR_F(L0,f534981547_23->offset) = 1;
	if(!f534981547_27) { //pivotX;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,27);
	  f534981547_27=fld->instance;
	}
	*FIELD_PTR_F(L0,f534981547_27->offset) = 0.5;
	if(!f534981547_30) { //pivotY;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,30);
	  f534981547_30=fld->instance;
	}
	*FIELD_PTR_F(L0,f534981547_30->offset) = 0.5;
	if(!f534981547_34) { //color;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,34);
	  f534981547_34=fld->instance;
	}
	*FIELD_PTR_I(L0,f534981547_34->offset) = 16777215;
	if(!f534981547_37) { //blendMode;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,37);
	  f534981547_37=fld->instance;
	}
	*FIELD_PTR_I(L0,f534981547_37->offset) = 1;
	AOTCLASS(c534981547_40,98);
	T0=alloc_object(vm,c534981547_40,0);
	{
	  VAR cargs[]={{.O=T0}};
	  frame->pc=58;
	  AOTMETHOD(m534981547_42,98,1,2); //digiplay/Mat2D:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m534981547_42),entry)))(vm,m534981547_42,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	if(!f534981547_43) { //localMatrix;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,43);
	  f534981547_43=fld->instance;
	}
	*FIELD_PTR_O(L0,f534981547_43->offset) = T0;
	AOTCLASS(c534981547_40,98);
	T0=alloc_object(vm,c534981547_40,0);
	{
	  VAR cargs[]={{.O=T0}};
	  frame->pc=69;
	  AOTMETHOD(m534981547_42,98,1,2); //digiplay/Mat2D:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m534981547_42),entry)))(vm,m534981547_42,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	if(!f534981547_47) { //worldMatrix;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,47);
	  f534981547_47=fld->instance;
	}
	*FIELD_PTR_O(L0,f534981547_47->offset) = T0;
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Sprite2D_x___F(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JFLOAT T0,T1,T2;
	Object *L0;
	L0=args[0].O;
BB0:
	AOTFIELD(f534981547_50,111,16,112); //digiplay/Sprite2D:x:F;
	if(!L0) { frame->pc = 1; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_F(L0,f534981547_50->offset);
	AOTFIELD(f534981547_53,111,113,112); //digiplay/Sprite2D:animX:F;
	if(!L0) { frame->pc = 5; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_F(L0,f534981547_53->offset);
	T2 = T0 + T1;
	vm->FP--;vm->frames[vm->FP].ret.F=T2;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Sprite2D_x__F_V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JFLOAT L0,T0;
	JINT T1,T2;
	Object *L1;
	L1=args[0].O;
	L0=args[1].F;
BB0:
	AOTFIELD(f534981547_50,111,16,112); //digiplay/Sprite2D:x:F;
	if(!L1) { frame->pc = 2; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_F(L1,f534981547_50->offset);
	if(L0==T0) goto BB25;
BB9:
	if(!f534981547_50) { //x;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,50);
	  f534981547_50=fld->instance;
	}
	*FIELD_PTR_F(L1,f534981547_50->offset) = L0;
	AOTFIELD(f534981547_9,111,114,4); //digiplay/Sprite2D:flags:I;
	if(!L1) { frame->pc = 16; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_I(L1,f534981547_9->offset);
	T2 = T1 | 12;
	if(!f534981547_9) { //flags;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,9);
	  f534981547_9=fld->instance;
	}
	*FIELD_PTR_I(L1,f534981547_9->offset) = T2;
BB25:
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Sprite2D_y___F(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JFLOAT T0,T1,T2;
	Object *L0;
	L0=args[0].O;
BB0:
	AOTFIELD(f534981547_56,111,18,112); //digiplay/Sprite2D:y:F;
	if(!L0) { frame->pc = 1; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_F(L0,f534981547_56->offset);
	AOTFIELD(f534981547_59,111,115,112); //digiplay/Sprite2D:animY:F;
	if(!L0) { frame->pc = 5; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_F(L0,f534981547_59->offset);
	T2 = T0 + T1;
	vm->FP--;vm->frames[vm->FP].ret.F=T2;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Sprite2D_y__F_V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JFLOAT L0,T0;
	JINT T1,T2;
	Object *L1;
	L1=args[0].O;
	L0=args[1].F;
BB0:
	AOTFIELD(f534981547_56,111,18,112); //digiplay/Sprite2D:y:F;
	if(!L1) { frame->pc = 2; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_F(L1,f534981547_56->offset);
	if(L0==T0) goto BB25;
BB9:
	if(!f534981547_56) { //y;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,56);
	  f534981547_56=fld->instance;
	}
	*FIELD_PTR_F(L1,f534981547_56->offset) = L0;
	AOTFIELD(f534981547_9,111,114,4); //digiplay/Sprite2D:flags:I;
	if(!L1) { frame->pc = 16; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_I(L1,f534981547_9->offset);
	T2 = T1 | 12;
	if(!f534981547_9) { //flags;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,9);
	  f534981547_9=fld->instance;
	}
	*FIELD_PTR_I(L1,f534981547_9->offset) = T2;
BB25:
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Sprite2D_scaleX___F(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JFLOAT T0,T1,T2;
	Object *L0;
	L0=args[0].O;
BB0:
	AOTFIELD(f534981547_13,111,116,112); //digiplay/Sprite2D:scaleX:F;
	if(!L0) { frame->pc = 1; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_F(L0,f534981547_13->offset);
	AOTFIELD(f534981547_62,111,117,112); //digiplay/Sprite2D:animScaleX:F;
	if(!L0) { frame->pc = 5; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_F(L0,f534981547_62->offset);
	T2 = T0 + T1;
	vm->FP--;vm->frames[vm->FP].ret.F=T2;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Sprite2D_scaleX__F_V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JFLOAT L0,T0;
	JINT T1,T2;
	Object *L1;
	L1=args[0].O;
	L0=args[1].F;
BB0:
	AOTFIELD(f534981547_13,111,116,112); //digiplay/Sprite2D:scaleX:F;
	if(!L1) { frame->pc = 2; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_F(L1,f534981547_13->offset);
	if(L0==T0) goto BB25;
BB9:
	if(!f534981547_13) { //scaleX;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,13);
	  f534981547_13=fld->instance;
	}
	*FIELD_PTR_F(L1,f534981547_13->offset) = L0;
	AOTFIELD(f534981547_9,111,114,4); //digiplay/Sprite2D:flags:I;
	if(!L1) { frame->pc = 16; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_I(L1,f534981547_9->offset);
	T2 = T1 | 12;
	if(!f534981547_9) { //flags;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,9);
	  f534981547_9=fld->instance;
	}
	*FIELD_PTR_I(L1,f534981547_9->offset) = T2;
BB25:
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Sprite2D_getScaleY___F(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JFLOAT T0,T1,T2;
	Object *L0;
	L0=args[0].O;
BB0:
	AOTFIELD(f534981547_17,111,118,112); //digiplay/Sprite2D:scaleY:F;
	if(!L0) { frame->pc = 1; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_F(L0,f534981547_17->offset);
	AOTFIELD(f534981547_65,111,119,112); //digiplay/Sprite2D:animScaleY:F;
	if(!L0) { frame->pc = 5; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_F(L0,f534981547_65->offset);
	T2 = T0 + T1;
	vm->FP--;vm->frames[vm->FP].ret.F=T2;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Sprite2D_setScaleY__F_V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JFLOAT L0,T0;
	JINT T1,T2;
	Object *L1;
	L1=args[0].O;
	L0=args[1].F;
BB0:
	AOTFIELD(f534981547_17,111,118,112); //digiplay/Sprite2D:scaleY:F;
	if(!L1) { frame->pc = 2; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_F(L1,f534981547_17->offset);
	if(L0==T0) goto BB25;
BB9:
	if(!f534981547_17) { //scaleY;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,17);
	  f534981547_17=fld->instance;
	}
	*FIELD_PTR_F(L1,f534981547_17->offset) = L0;
	AOTFIELD(f534981547_9,111,114,4); //digiplay/Sprite2D:flags:I;
	if(!L1) { frame->pc = 16; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_I(L1,f534981547_9->offset);
	T2 = T1 | 12;
	if(!f534981547_9) { //flags;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,9);
	  f534981547_9=fld->instance;
	}
	*FIELD_PTR_I(L1,f534981547_9->offset) = T2;
BB25:
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Sprite2D_rotation___F(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JFLOAT T0,T1,T2;
	Object *L0;
	L0=args[0].O;
BB0:
	AOTFIELD(f534981547_68,111,23,112); //digiplay/Sprite2D:rotation:F;
	if(!L0) { frame->pc = 1; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_F(L0,f534981547_68->offset);
	AOTFIELD(f534981547_71,111,120,112); //digiplay/Sprite2D:animRotation:F;
	if(!L0) { frame->pc = 5; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_F(L0,f534981547_71->offset);
	T2 = T0 + T1;
	vm->FP--;vm->frames[vm->FP].ret.F=T2;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Sprite2D_rotation__F_V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JFLOAT L0,T0;
	JINT T1,T2;
	Object *L1;
	L1=args[0].O;
	L0=args[1].F;
BB0:
	AOTFIELD(f534981547_68,111,23,112); //digiplay/Sprite2D:rotation:F;
	if(!L1) { frame->pc = 2; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_F(L1,f534981547_68->offset);
	if(L0==T0) goto BB25;
BB9:
	if(!f534981547_68) { //rotation;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,68);
	  f534981547_68=fld->instance;
	}
	*FIELD_PTR_F(L1,f534981547_68->offset) = L0;
	AOTFIELD(f534981547_9,111,114,4); //digiplay/Sprite2D:flags:I;
	if(!L1) { frame->pc = 16; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_I(L1,f534981547_9->offset);
	T2 = T1 | 44;
	if(!f534981547_9) { //flags;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,9);
	  f534981547_9=fld->instance;
	}
	*FIELD_PTR_I(L1,f534981547_9->offset) = T2;
BB25:
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Sprite2D_width___F(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JFLOAT T0;
	Object *L0;
	L0=args[0].O;
BB0:
	AOTFIELD(f534981547_74,111,121,112); //digiplay/Sprite2D:width:F;
	if(!L0) { frame->pc = 1; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_F(L0,f534981547_74->offset);
	vm->FP--;vm->frames[vm->FP].ret.F=T0;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Sprite2D_width__F_V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JFLOAT L0,T0,T1;
	JINT T2,T3;
	Object *L1;
	L1=args[0].O;
	L0=args[1].F;
BB0:
	AOTFIELD(f534981547_74,111,121,112); //digiplay/Sprite2D:width:F;
	if(!L1) { frame->pc = 2; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_F(L1,f534981547_74->offset);
	if(L0==T0) goto BB35;
BB9:
	if(!f534981547_74) { //width;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,74);
	  f534981547_74=fld->instance;
	}
	*FIELD_PTR_F(L1,f534981547_74->offset) = L0;
	AOTFIELD(f534981547_27,111,122,112); //digiplay/Sprite2D:pivotX:F;
	if(!L1) { frame->pc = 17; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_F(L1,f534981547_27->offset);
	T1 = L0 * T0;
	if(!f534981547_77) { //midX;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,77);
	  f534981547_77=fld->instance;
	}
	*FIELD_PTR_F(L1,f534981547_77->offset) = T1;
	AOTFIELD(f534981547_9,111,114,4); //digiplay/Sprite2D:flags:I;
	if(!L1) { frame->pc = 26; throw_null(vm); goto __EXCEPTION; }
	T2 = *FIELD_PTR_I(L1,f534981547_9->offset);
	T3 = T2 | 12;
	if(!f534981547_9) { //flags;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,9);
	  f534981547_9=fld->instance;
	}
	*FIELD_PTR_I(L1,f534981547_9->offset) = T3;
BB35:
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Sprite2D_height___F(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JFLOAT T0;
	Object *L0;
	L0=args[0].O;
BB0:
	AOTFIELD(f534981547_80,111,123,112); //digiplay/Sprite2D:height:F;
	if(!L0) { frame->pc = 1; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_F(L0,f534981547_80->offset);
	vm->FP--;vm->frames[vm->FP].ret.F=T0;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Sprite2D_height__F_V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JFLOAT L0,T0,T1;
	JINT T2,T3;
	Object *L1;
	L1=args[0].O;
	L0=args[1].F;
BB0:
	AOTFIELD(f534981547_80,111,123,112); //digiplay/Sprite2D:height:F;
	if(!L1) { frame->pc = 2; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_F(L1,f534981547_80->offset);
	if(L0==T0) goto BB35;
BB9:
	if(!f534981547_80) { //height;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,80);
	  f534981547_80=fld->instance;
	}
	*FIELD_PTR_F(L1,f534981547_80->offset) = L0;
	AOTFIELD(f534981547_30,111,124,112); //digiplay/Sprite2D:pivotY:F;
	if(!L1) { frame->pc = 17; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_F(L1,f534981547_30->offset);
	T1 = L0 * T0;
	if(!f534981547_83) { //midY;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,83);
	  f534981547_83=fld->instance;
	}
	*FIELD_PTR_F(L1,f534981547_83->offset) = T1;
	AOTFIELD(f534981547_9,111,114,4); //digiplay/Sprite2D:flags:I;
	if(!L1) { frame->pc = 26; throw_null(vm); goto __EXCEPTION; }
	T2 = *FIELD_PTR_I(L1,f534981547_9->offset);
	T3 = T2 | 12;
	if(!f534981547_9) { //flags;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,9);
	  f534981547_9=fld->instance;
	}
	*FIELD_PTR_I(L1,f534981547_9->offset) = T3;
BB35:
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Sprite2D_getSkewX___F(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JFLOAT T0,T1,T2;
	Object *L0;
	L0=args[0].O;
BB0:
	AOTFIELD(f534981547_86,111,125,112); //digiplay/Sprite2D:skewX:F;
	if(!L0) { frame->pc = 1; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_F(L0,f534981547_86->offset);
	AOTFIELD(f534981547_89,111,126,112); //digiplay/Sprite2D:animSkewX:F;
	if(!L0) { frame->pc = 5; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_F(L0,f534981547_89->offset);
	T2 = T0 + T1;
	vm->FP--;vm->frames[vm->FP].ret.F=T2;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Sprite2D_setSkewX__F_V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JFLOAT L0,T0;
	JINT T1,T2;
	Object *L1;
	L1=args[0].O;
	L0=args[1].F;
BB0:
	AOTFIELD(f534981547_86,111,125,112); //digiplay/Sprite2D:skewX:F;
	if(!L1) { frame->pc = 2; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_F(L1,f534981547_86->offset);
	if(L0==T0) goto BB25;
BB9:
	if(!f534981547_86) { //skewX;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,86);
	  f534981547_86=fld->instance;
	}
	*FIELD_PTR_F(L1,f534981547_86->offset) = L0;
	AOTFIELD(f534981547_9,111,114,4); //digiplay/Sprite2D:flags:I;
	if(!L1) { frame->pc = 16; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_I(L1,f534981547_9->offset);
	T2 = T1 | 44;
	if(!f534981547_9) { //flags;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,9);
	  f534981547_9=fld->instance;
	}
	*FIELD_PTR_I(L1,f534981547_9->offset) = T2;
BB25:
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Sprite2D_getSkewY___F(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JFLOAT T0,T1,T2;
	Object *L0;
	L0=args[0].O;
BB0:
	AOTFIELD(f534981547_92,111,127,112); //digiplay/Sprite2D:skewY:F;
	if(!L0) { frame->pc = 1; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_F(L0,f534981547_92->offset);
	AOTFIELD(f534981547_95,111,128,112); //digiplay/Sprite2D:animSkewY:F;
	if(!L0) { frame->pc = 5; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_F(L0,f534981547_95->offset);
	T2 = T0 + T1;
	vm->FP--;vm->frames[vm->FP].ret.F=T2;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Sprite2D_setSkewY__F_V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JFLOAT L0,T0;
	JINT T1,T2;
	Object *L1;
	L1=args[0].O;
	L0=args[1].F;
BB0:
	AOTFIELD(f534981547_92,111,127,112); //digiplay/Sprite2D:skewY:F;
	if(!L1) { frame->pc = 2; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_F(L1,f534981547_92->offset);
	if(L0==T0) goto BB25;
BB9:
	if(!f534981547_92) { //skewY;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,92);
	  f534981547_92=fld->instance;
	}
	*FIELD_PTR_F(L1,f534981547_92->offset) = L0;
	AOTFIELD(f534981547_9,111,114,4); //digiplay/Sprite2D:flags:I;
	if(!L1) { frame->pc = 16; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_I(L1,f534981547_9->offset);
	T2 = T1 | 44;
	if(!f534981547_9) { //flags;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,9);
	  f534981547_9=fld->instance;
	}
	*FIELD_PTR_I(L1,f534981547_9->offset) = T2;
BB25:
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Sprite2D_getAnimX___F(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JFLOAT T0;
	Object *L0;
	L0=args[0].O;
BB0:
	AOTFIELD(f534981547_53,111,113,112); //digiplay/Sprite2D:animX:F;
	if(!L0) { frame->pc = 1; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_F(L0,f534981547_53->offset);
	vm->FP--;vm->frames[vm->FP].ret.F=T0;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Sprite2D_setAnimX__F_V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JFLOAT L0,T0;
	JINT T1,T2;
	Object *L1;
	L1=args[0].O;
	L0=args[1].F;
BB0:
	AOTFIELD(f534981547_53,111,113,112); //digiplay/Sprite2D:animX:F;
	if(!L1) { frame->pc = 2; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_F(L1,f534981547_53->offset);
	if(L0==T0) goto BB25;
BB9:
	if(!f534981547_53) { //animX;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,53);
	  f534981547_53=fld->instance;
	}
	*FIELD_PTR_F(L1,f534981547_53->offset) = L0;
	AOTFIELD(f534981547_9,111,114,4); //digiplay/Sprite2D:flags:I;
	if(!L1) { frame->pc = 16; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_I(L1,f534981547_9->offset);
	T2 = T1 | 12;
	if(!f534981547_9) { //flags;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,9);
	  f534981547_9=fld->instance;
	}
	*FIELD_PTR_I(L1,f534981547_9->offset) = T2;
BB25:
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Sprite2D_getAnimY___F(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JFLOAT T0;
	Object *L0;
	L0=args[0].O;
BB0:
	AOTFIELD(f534981547_59,111,115,112); //digiplay/Sprite2D:animY:F;
	if(!L0) { frame->pc = 1; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_F(L0,f534981547_59->offset);
	vm->FP--;vm->frames[vm->FP].ret.F=T0;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Sprite2D_setAnimY__F_V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JFLOAT L0,T0;
	JINT T1,T2;
	Object *L1;
	L1=args[0].O;
	L0=args[1].F;
BB0:
	AOTFIELD(f534981547_59,111,115,112); //digiplay/Sprite2D:animY:F;
	if(!L1) { frame->pc = 2; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_F(L1,f534981547_59->offset);
	if(L0==T0) goto BB25;
BB9:
	if(!f534981547_59) { //animY;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,59);
	  f534981547_59=fld->instance;
	}
	*FIELD_PTR_F(L1,f534981547_59->offset) = L0;
	AOTFIELD(f534981547_9,111,114,4); //digiplay/Sprite2D:flags:I;
	if(!L1) { frame->pc = 16; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_I(L1,f534981547_9->offset);
	T2 = T1 | 12;
	if(!f534981547_9) { //flags;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,9);
	  f534981547_9=fld->instance;
	}
	*FIELD_PTR_I(L1,f534981547_9->offset) = T2;
BB25:
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Sprite2D_getAnimScaleX___F(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JFLOAT T0;
	Object *L0;
	L0=args[0].O;
BB0:
	AOTFIELD(f534981547_62,111,117,112); //digiplay/Sprite2D:animScaleX:F;
	if(!L0) { frame->pc = 1; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_F(L0,f534981547_62->offset);
	vm->FP--;vm->frames[vm->FP].ret.F=T0;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Sprite2D_setAnimScaleX__F_V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JFLOAT L0,T0;
	JINT T1,T2;
	Object *L1;
	L1=args[0].O;
	L0=args[1].F;
BB0:
	AOTFIELD(f534981547_62,111,117,112); //digiplay/Sprite2D:animScaleX:F;
	if(!L1) { frame->pc = 2; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_F(L1,f534981547_62->offset);
	if(L0==T0) goto BB25;
BB9:
	if(!f534981547_62) { //animScaleX;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,62);
	  f534981547_62=fld->instance;
	}
	*FIELD_PTR_F(L1,f534981547_62->offset) = L0;
	AOTFIELD(f534981547_9,111,114,4); //digiplay/Sprite2D:flags:I;
	if(!L1) { frame->pc = 16; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_I(L1,f534981547_9->offset);
	T2 = T1 | 12;
	if(!f534981547_9) { //flags;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,9);
	  f534981547_9=fld->instance;
	}
	*FIELD_PTR_I(L1,f534981547_9->offset) = T2;
BB25:
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Sprite2D_getAnimScaleY___F(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JFLOAT T0;
	Object *L0;
	L0=args[0].O;
BB0:
	AOTFIELD(f534981547_65,111,119,112); //digiplay/Sprite2D:animScaleY:F;
	if(!L0) { frame->pc = 1; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_F(L0,f534981547_65->offset);
	vm->FP--;vm->frames[vm->FP].ret.F=T0;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Sprite2D_setAnimScaleY__F_V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JFLOAT L0,T0;
	JINT T1,T2;
	Object *L1;
	L1=args[0].O;
	L0=args[1].F;
BB0:
	AOTFIELD(f534981547_65,111,119,112); //digiplay/Sprite2D:animScaleY:F;
	if(!L1) { frame->pc = 2; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_F(L1,f534981547_65->offset);
	if(L0==T0) goto BB25;
BB9:
	if(!f534981547_65) { //animScaleY;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,65);
	  f534981547_65=fld->instance;
	}
	*FIELD_PTR_F(L1,f534981547_65->offset) = L0;
	AOTFIELD(f534981547_9,111,114,4); //digiplay/Sprite2D:flags:I;
	if(!L1) { frame->pc = 16; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_I(L1,f534981547_9->offset);
	T2 = T1 | 12;
	if(!f534981547_9) { //flags;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,9);
	  f534981547_9=fld->instance;
	}
	*FIELD_PTR_I(L1,f534981547_9->offset) = T2;
BB25:
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Sprite2D_getAnimRotation___F(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JFLOAT T0;
	Object *L0;
	L0=args[0].O;
BB0:
	AOTFIELD(f534981547_71,111,120,112); //digiplay/Sprite2D:animRotation:F;
	if(!L0) { frame->pc = 1; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_F(L0,f534981547_71->offset);
	vm->FP--;vm->frames[vm->FP].ret.F=T0;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Sprite2D_setAnimRotation__F_V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JFLOAT L0,T0;
	JINT T1,T2;
	Object *L1;
	L1=args[0].O;
	L0=args[1].F;
BB0:
	AOTFIELD(f534981547_71,111,120,112); //digiplay/Sprite2D:animRotation:F;
	if(!L1) { frame->pc = 2; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_F(L1,f534981547_71->offset);
	if(L0==T0) goto BB25;
BB9:
	if(!f534981547_71) { //animRotation;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,71);
	  f534981547_71=fld->instance;
	}
	*FIELD_PTR_F(L1,f534981547_71->offset) = L0;
	AOTFIELD(f534981547_9,111,114,4); //digiplay/Sprite2D:flags:I;
	if(!L1) { frame->pc = 16; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_I(L1,f534981547_9->offset);
	T2 = T1 | 44;
	if(!f534981547_9) { //flags;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,9);
	  f534981547_9=fld->instance;
	}
	*FIELD_PTR_I(L1,f534981547_9->offset) = T2;
BB25:
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Sprite2D_getAlpha___F(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JFLOAT T0,T1,T2;
	Object *L0;
	L0=args[0].O;
BB0:
	AOTFIELD(f534981547_20,111,129,112); //digiplay/Sprite2D:alpha:F;
	if(!L0) { frame->pc = 1; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_F(L0,f534981547_20->offset);
	AOTFIELD(f534981547_98,111,130,112); //digiplay/Sprite2D:animAlpha:F;
	if(!L0) { frame->pc = 5; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_F(L0,f534981547_98->offset);
	T2 = T0 + T1;
	vm->FP--;vm->frames[vm->FP].ret.F=T2;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Sprite2D_setAlpha__F_V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JFLOAT L0,T0;
	JINT T1,T2;
	Object *L1;
	L1=args[0].O;
	L0=args[1].F;
BB0:
	AOTFIELD(f534981547_20,111,129,112); //digiplay/Sprite2D:alpha:F;
	if(!L1) { frame->pc = 2; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_F(L1,f534981547_20->offset);
	if(L0==T0) goto BB28;
BB9:
	if(!f534981547_20) { //alpha;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,20);
	  f534981547_20=fld->instance;
	}
	*FIELD_PTR_F(L1,f534981547_20->offset) = L0;
	AOTFIELD(f534981547_9,111,114,4); //digiplay/Sprite2D:flags:I;
	if(!L1) { frame->pc = 15; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_I(L1,f534981547_9->offset);
	T2 = T1 & 64;
	if(T2==0) goto BB28;
BB24:
	{
	  VAR cargs[]={{.O=L1}};
	  frame->pc=25;
	  AOTVMETHOD(m534981547_101,111,131,2,vTableIndex); //digiplay/Sprite2D:updateWorldAlpha:()V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m534981547_101];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
BB28:
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Sprite2D_getAnimAlpha___F(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JFLOAT T0;
	Object *L0;
	L0=args[0].O;
BB0:
	AOTFIELD(f534981547_98,111,130,112); //digiplay/Sprite2D:animAlpha:F;
	if(!L0) { frame->pc = 1; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_F(L0,f534981547_98->offset);
	vm->FP--;vm->frames[vm->FP].ret.F=T0;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Sprite2D_setAnimAlpha__F_V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JFLOAT L0,T0;
	JINT T1,T2;
	Object *L1;
	L1=args[0].O;
	L0=args[1].F;
BB0:
	AOTFIELD(f534981547_98,111,130,112); //digiplay/Sprite2D:animAlpha:F;
	if(!L1) { frame->pc = 2; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_F(L1,f534981547_98->offset);
	if(L0==T0) goto BB28;
BB9:
	if(!f534981547_98) { //animAlpha;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,98);
	  f534981547_98=fld->instance;
	}
	*FIELD_PTR_F(L1,f534981547_98->offset) = L0;
	AOTFIELD(f534981547_9,111,114,4); //digiplay/Sprite2D:flags:I;
	if(!L1) { frame->pc = 15; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_I(L1,f534981547_9->offset);
	T2 = T1 & 64;
	if(T2==0) goto BB28;
BB24:
	{
	  VAR cargs[]={{.O=L1}};
	  frame->pc=25;
	  AOTVMETHOD(m534981547_101,111,131,2,vTableIndex); //digiplay/Sprite2D:updateWorldAlpha:()V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m534981547_101];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
BB28:
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Sprite2D_getPivotX___F(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JFLOAT T0;
	Object *L0;
	L0=args[0].O;
BB0:
	AOTFIELD(f534981547_27,111,122,112); //digiplay/Sprite2D:pivotX:F;
	if(!L0) { frame->pc = 1; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_F(L0,f534981547_27->offset);
	vm->FP--;vm->frames[vm->FP].ret.F=T0;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Sprite2D_setPivotX__F_V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JFLOAT L0,T0,T1;
	JINT T2,T3;
	Object *L1;
	L1=args[0].O;
	L0=args[1].F;
BB0:
	AOTFIELD(f534981547_27,111,122,112); //digiplay/Sprite2D:pivotX:F;
	if(!L1) { frame->pc = 2; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_F(L1,f534981547_27->offset);
	if(L0==T0) goto BB35;
BB9:
	if(!f534981547_27) { //pivotX;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,27);
	  f534981547_27=fld->instance;
	}
	*FIELD_PTR_F(L1,f534981547_27->offset) = L0;
	AOTFIELD(f534981547_74,111,121,112); //digiplay/Sprite2D:width:F;
	if(!L1) { frame->pc = 17; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_F(L1,f534981547_74->offset);
	T1 = L0 * T0;
	if(!f534981547_77) { //midX;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,77);
	  f534981547_77=fld->instance;
	}
	*FIELD_PTR_F(L1,f534981547_77->offset) = T1;
	AOTFIELD(f534981547_9,111,114,4); //digiplay/Sprite2D:flags:I;
	if(!L1) { frame->pc = 26; throw_null(vm); goto __EXCEPTION; }
	T2 = *FIELD_PTR_I(L1,f534981547_9->offset);
	T3 = T2 | 12;
	if(!f534981547_9) { //flags;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,9);
	  f534981547_9=fld->instance;
	}
	*FIELD_PTR_I(L1,f534981547_9->offset) = T3;
BB35:
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Sprite2D_getPivotY___F(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JFLOAT T0;
	Object *L0;
	L0=args[0].O;
BB0:
	AOTFIELD(f534981547_30,111,124,112); //digiplay/Sprite2D:pivotY:F;
	if(!L0) { frame->pc = 1; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_F(L0,f534981547_30->offset);
	vm->FP--;vm->frames[vm->FP].ret.F=T0;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Sprite2D_setPivotY__F_V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JFLOAT L0,T0,T1;
	JINT T2,T3;
	Object *L1;
	L1=args[0].O;
	L0=args[1].F;
BB0:
	AOTFIELD(f534981547_30,111,124,112); //digiplay/Sprite2D:pivotY:F;
	if(!L1) { frame->pc = 2; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_F(L1,f534981547_30->offset);
	if(L0==T0) goto BB35;
BB9:
	if(!f534981547_30) { //pivotY;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,30);
	  f534981547_30=fld->instance;
	}
	*FIELD_PTR_F(L1,f534981547_30->offset) = L0;
	AOTFIELD(f534981547_80,111,123,112); //digiplay/Sprite2D:height:F;
	if(!L1) { frame->pc = 17; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_F(L1,f534981547_80->offset);
	T1 = L0 * T0;
	if(!f534981547_83) { //midY;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,83);
	  f534981547_83=fld->instance;
	}
	*FIELD_PTR_F(L1,f534981547_83->offset) = T1;
	AOTFIELD(f534981547_9,111,114,4); //digiplay/Sprite2D:flags:I;
	if(!L1) { frame->pc = 26; throw_null(vm); goto __EXCEPTION; }
	T2 = *FIELD_PTR_I(L1,f534981547_9->offset);
	T3 = T2 | 12;
	if(!f534981547_9) { //flags;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,9);
	  f534981547_9=fld->instance;
	}
	*FIELD_PTR_I(L1,f534981547_9->offset) = T3;
BB35:
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Sprite2D_updateWorldAlpha___V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JFLOAT T1,T2,T3,T4;
	Object *L0,*L1,*T0;
	L0=args[0].O;
BB0:
	AOTFIELD(f534981547_104,111,132,133); //digiplay/Sprite2D:parent:Ldigiplay/Sprite2D;
	if(!L0) { frame->pc = 1; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f534981547_104->offset);
	if(T0!=NULL) goto BB8;
BB7:
	vm->FP--;return;
BB8:
	AOTFIELD(f534981547_104,111,132,133); //digiplay/Sprite2D:parent:Ldigiplay/Sprite2D;
	if(!L0) { frame->pc = 10; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f534981547_104->offset);
	AOTFIELD(f534981547_23,111,134,112); //digiplay/Sprite2D:worldAlpha:F;
	if(!T0) { frame->pc = 13; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_F(T0,f534981547_23->offset);
	AOTFIELD(f534981547_20,111,129,112); //digiplay/Sprite2D:alpha:F;
	if(!L0) { frame->pc = 17; throw_null(vm); goto __EXCEPTION; }
	T2 = *FIELD_PTR_F(L0,f534981547_20->offset);
	AOTFIELD(f534981547_98,111,130,112); //digiplay/Sprite2D:animAlpha:F;
	if(!L0) { frame->pc = 21; throw_null(vm); goto __EXCEPTION; }
	T3 = *FIELD_PTR_F(L0,f534981547_98->offset);
	T4 = T2 + T3;
	T2 = T1 * T4;
	if(!f534981547_23) { //worldAlpha;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,23);
	  f534981547_23=fld->instance;
	}
	*FIELD_PTR_F(L0,f534981547_23->offset) = T2;
	AOTFIELD(f534981547_108,111,135,133); //digiplay/Sprite2D:firstChild:Ldigiplay/Sprite2D;
	if(!L0) { frame->pc = 30; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f534981547_108->offset);
	L1=T0;
BB34:
	if(L1==NULL) goto BB50;
BB38:
	{
	  VAR cargs[]={{.O=L1}};
	  frame->pc=39;
	  AOTVMETHOD(m534981547_101,111,131,2,vTableIndex); //digiplay/Sprite2D:updateWorldAlpha:()V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m534981547_101];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	AOTFIELD(f534981547_111,111,136,133); //digiplay/Sprite2D:next:Ldigiplay/Sprite2D;
	if(!L1) { frame->pc = 43; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L1,f534981547_111->offset);
	L1=T0;
	goto BB34;
BB50:
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Sprite2D_getFlags___I(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JINT T0;
	Object *L0;
	L0=args[0].O;
BB0:
	AOTFIELD(f534981547_9,111,114,4); //digiplay/Sprite2D:flags:I;
	if(!L0) { frame->pc = 1; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_I(L0,f534981547_9->offset);
	vm->FP--;vm->frames[vm->FP].ret.I=T0;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Sprite2D_setFlags__I_V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JINT L1,T0,T1;
	Object *L0;
	L0=args[0].O;
	L1=args[1].I;
BB0:
	AOTFIELD(f534981547_9,111,114,4); //digiplay/Sprite2D:flags:I;
	if(!L0) { frame->pc = 2; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_I(L0,f534981547_9->offset);
	T1 = T0 | L1;
	if(!f534981547_9) { //flags;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,9);
	  f534981547_9=fld->instance;
	}
	*FIELD_PTR_I(L0,f534981547_9->offset) = T1;
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Sprite2D_cleatFlags__I_V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JINT L1,T0,T1,T2;
	Object *L0;
	L0=args[0].O;
	L1=args[1].I;
BB0:
	AOTFIELD(f534981547_9,111,114,4); //digiplay/Sprite2D:flags:I;
	if(!L0) { frame->pc = 2; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_I(L0,f534981547_9->offset);
	T1 = L1 ^ -1;
	T2 = T0 & T1;
	if(!f534981547_9) { //flags;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,9);
	  f534981547_9=fld->instance;
	}
	*FIELD_PTR_I(L0,f534981547_9->offset) = T2;
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Sprite2D_dispose___V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
BB0:
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Sprite2D_unlinkChild__Ldigiplay_Sprite2D__V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	Object *L0,*L1,*T0,*T1;
	L1=args[0].O;
	L0=args[1].O;
BB0:
	AOTFIELD(f534981547_114,111,137,133); //digiplay/Sprite2D:prev:Ldigiplay/Sprite2D;
	if(!L0) { frame->pc = 1; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f534981547_114->offset);
	if(T0!=NULL) goto BB18;
BB7:
	AOTFIELD(f534981547_108,111,135,133); //digiplay/Sprite2D:firstChild:Ldigiplay/Sprite2D;
	if(!L1) { frame->pc = 9; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L1,f534981547_108->offset);
	AOTFIELD(f534981547_111,111,136,133); //digiplay/Sprite2D:next:Ldigiplay/Sprite2D;
	if(!T0) { frame->pc = 12; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_O(T0,f534981547_111->offset);
	if(!f534981547_108) { //firstChild;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,108);
	  f534981547_108=fld->instance;
	}
	*FIELD_PTR_O(L1,f534981547_108->offset) = T1;
BB18:
	AOTFIELD(f534981547_111,111,136,133); //digiplay/Sprite2D:next:Ldigiplay/Sprite2D;
	if(!L0) { frame->pc = 19; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f534981547_111->offset);
	if(T0!=NULL) goto BB36;
BB25:
	AOTFIELD(f534981547_117,111,138,133); //digiplay/Sprite2D:lastChild:Ldigiplay/Sprite2D;
	if(!L1) { frame->pc = 27; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L1,f534981547_117->offset);
	AOTFIELD(f534981547_114,111,137,133); //digiplay/Sprite2D:prev:Ldigiplay/Sprite2D;
	if(!T0) { frame->pc = 30; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_O(T0,f534981547_114->offset);
	if(!f534981547_117) { //lastChild;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,117);
	  f534981547_117=fld->instance;
	}
	*FIELD_PTR_O(L1,f534981547_117->offset) = T1;
BB36:
	AOTFIELD(f534981547_114,111,137,133); //digiplay/Sprite2D:prev:Ldigiplay/Sprite2D;
	if(!L0) { frame->pc = 37; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f534981547_114->offset);
	if(T0==NULL) goto BB54;
BB43:
	AOTFIELD(f534981547_114,111,137,133); //digiplay/Sprite2D:prev:Ldigiplay/Sprite2D;
	if(!L0) { frame->pc = 44; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f534981547_114->offset);
	AOTFIELD(f534981547_111,111,136,133); //digiplay/Sprite2D:next:Ldigiplay/Sprite2D;
	if(!L0) { frame->pc = 48; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_O(L0,f534981547_111->offset);
	if(!f534981547_111) { //next;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,111);
	  f534981547_111=fld->instance;
	}
	*FIELD_PTR_O(T0,f534981547_111->offset) = T1;
BB54:
	AOTFIELD(f534981547_111,111,136,133); //digiplay/Sprite2D:next:Ldigiplay/Sprite2D;
	if(!L0) { frame->pc = 55; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f534981547_111->offset);
	if(T0==NULL) goto BB72;
BB61:
	AOTFIELD(f534981547_111,111,136,133); //digiplay/Sprite2D:next:Ldigiplay/Sprite2D;
	if(!L0) { frame->pc = 62; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f534981547_111->offset);
	AOTFIELD(f534981547_114,111,137,133); //digiplay/Sprite2D:prev:Ldigiplay/Sprite2D;
	if(!L0) { frame->pc = 66; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_O(L0,f534981547_114->offset);
	if(!f534981547_114) { //prev;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,114);
	  f534981547_114=fld->instance;
	}
	*FIELD_PTR_O(T0,f534981547_114->offset) = T1;
BB72:
	if(!f534981547_114) { //prev;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,114);
	  f534981547_114=fld->instance;
	}
	*FIELD_PTR_O(L0,f534981547_114->offset) = NULL;
	if(!f534981547_111) { //next;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,111);
	  f534981547_111=fld->instance;
	}
	*FIELD_PTR_O(L0,f534981547_111->offset) = NULL;
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Sprite2D_linkChild__Ldigiplay_Sprite2D__V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JINT T1,T2;
	Object *L0,*L1,*L2,*L3,*T0;
	L0=args[0].O;
	L1=args[1].O;
BB0:
	AOTFIELD(f534981547_108,111,135,133); //digiplay/Sprite2D:firstChild:Ldigiplay/Sprite2D;
	if(!L0) { frame->pc = 1; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f534981547_108->offset);
	if(T0!=NULL) goto BB30;
BB7:
	if(!f534981547_117) { //lastChild;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,117);
	  f534981547_117=fld->instance;
	}
	*FIELD_PTR_O(L0,f534981547_117->offset) = L1;
	if(!f534981547_108) { //firstChild;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,108);
	  f534981547_108=fld->instance;
	}
	*FIELD_PTR_O(L0,f534981547_108->offset) = L1;
	if(!f534981547_111) { //next;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,111);
	  f534981547_111=fld->instance;
	}
	*FIELD_PTR_O(L1,f534981547_111->offset) = NULL;
	if(!f534981547_114) { //prev;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,114);
	  f534981547_114=fld->instance;
	}
	*FIELD_PTR_O(L1,f534981547_114->offset) = NULL;
	goto BB179;
BB30:
	AOTFIELD(f534981547_120,111,139,4); //digiplay/Sprite2D:depth:I;
	if(!L1) { frame->pc = 31; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_I(L1,f534981547_120->offset);
	AOTFIELD(f534981547_108,111,135,133); //digiplay/Sprite2D:firstChild:Ldigiplay/Sprite2D;
	if(!L0) { frame->pc = 35; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f534981547_108->offset);
	AOTFIELD(f534981547_120,111,139,4); //digiplay/Sprite2D:depth:I;
	if(!T0) { frame->pc = 38; throw_null(vm); goto __EXCEPTION; }
	T2 = *FIELD_PTR_I(T0,f534981547_120->offset);
	if(T1>=T2) goto BB76;
BB44:
	AOTFIELD(f534981547_108,111,135,133); //digiplay/Sprite2D:firstChild:Ldigiplay/Sprite2D;
	if(!L0) { frame->pc = 46; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f534981547_108->offset);
	if(!f534981547_111) { //next;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,111);
	  f534981547_111=fld->instance;
	}
	*FIELD_PTR_O(L1,f534981547_111->offset) = T0;
	AOTFIELD(f534981547_108,111,135,133); //digiplay/Sprite2D:firstChild:Ldigiplay/Sprite2D;
	if(!L0) { frame->pc = 53; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f534981547_108->offset);
	if(!f534981547_114) { //prev;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,114);
	  f534981547_114=fld->instance;
	}
	*FIELD_PTR_O(T0,f534981547_114->offset) = L1;
	if(!f534981547_108) { //firstChild;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,108);
	  f534981547_108=fld->instance;
	}
	*FIELD_PTR_O(L0,f534981547_108->offset) = L1;
	AOTFIELD(f534981547_108,111,135,133); //digiplay/Sprite2D:firstChild:Ldigiplay/Sprite2D;
	if(!L0) { frame->pc = 66; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f534981547_108->offset);
	if(!f534981547_114) { //prev;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,114);
	  f534981547_114=fld->instance;
	}
	*FIELD_PTR_O(T0,f534981547_114->offset) = NULL;
	goto BB179;
BB76:
	AOTFIELD(f534981547_120,111,139,4); //digiplay/Sprite2D:depth:I;
	if(!L1) { frame->pc = 77; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_I(L1,f534981547_120->offset);
	AOTFIELD(f534981547_117,111,138,133); //digiplay/Sprite2D:lastChild:Ldigiplay/Sprite2D;
	if(!L0) { frame->pc = 81; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f534981547_117->offset);
	AOTFIELD(f534981547_120,111,139,4); //digiplay/Sprite2D:depth:I;
	if(!T0) { frame->pc = 84; throw_null(vm); goto __EXCEPTION; }
	T2 = *FIELD_PTR_I(T0,f534981547_120->offset);
	if(T1<T2) goto BB122;
BB90:
	AOTFIELD(f534981547_117,111,138,133); //digiplay/Sprite2D:lastChild:Ldigiplay/Sprite2D;
	if(!L0) { frame->pc = 91; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f534981547_117->offset);
	if(!f534981547_111) { //next;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,111);
	  f534981547_111=fld->instance;
	}
	*FIELD_PTR_O(T0,f534981547_111->offset) = L1;
	AOTFIELD(f534981547_117,111,138,133); //digiplay/Sprite2D:lastChild:Ldigiplay/Sprite2D;
	if(!L0) { frame->pc = 100; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f534981547_117->offset);
	if(!f534981547_114) { //prev;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,114);
	  f534981547_114=fld->instance;
	}
	*FIELD_PTR_O(L1,f534981547_114->offset) = T0;
	if(!f534981547_117) { //lastChild;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,117);
	  f534981547_117=fld->instance;
	}
	*FIELD_PTR_O(L0,f534981547_117->offset) = L1;
	AOTFIELD(f534981547_117,111,138,133); //digiplay/Sprite2D:lastChild:Ldigiplay/Sprite2D;
	if(!L0) { frame->pc = 112; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f534981547_117->offset);
	if(!f534981547_111) { //next;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,111);
	  f534981547_111=fld->instance;
	}
	*FIELD_PTR_O(T0,f534981547_111->offset) = NULL;
	goto BB179;
BB122:
	AOTFIELD(f534981547_108,111,135,133); //digiplay/Sprite2D:firstChild:Ldigiplay/Sprite2D;
	if(!L0) { frame->pc = 123; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f534981547_108->offset);
	L2=T0;
BB127:
	if(L2==NULL) goto BB150;
BB131:
	AOTFIELD(f534981547_120,111,139,4); //digiplay/Sprite2D:depth:I;
	if(!L2) { frame->pc = 132; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_I(L2,f534981547_120->offset);
	AOTFIELD(f534981547_120,111,139,4); //digiplay/Sprite2D:depth:I;
	if(!L1) { frame->pc = 136; throw_null(vm); goto __EXCEPTION; }
	T2 = *FIELD_PTR_I(L1,f534981547_120->offset);
	if(T1>T2) goto BB150;
BB142:
	AOTFIELD(f534981547_111,111,136,133); //digiplay/Sprite2D:next:Ldigiplay/Sprite2D;
	if(!L2) { frame->pc = 143; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L2,f534981547_111->offset);
	L2=T0;
	goto BB127;
BB150:
	AOTFIELD(f534981547_114,111,137,133); //digiplay/Sprite2D:prev:Ldigiplay/Sprite2D;
	if(!L2) { frame->pc = 151; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L2,f534981547_114->offset);
	L3=T0;
	if(L3==NULL) goto BB164;
BB159:
	if(!f534981547_111) { //next;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,111);
	  f534981547_111=fld->instance;
	}
	*FIELD_PTR_O(L3,f534981547_111->offset) = L1;
BB164:
	if(!f534981547_114) { //prev;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,114);
	  f534981547_114=fld->instance;
	}
	*FIELD_PTR_O(L1,f534981547_114->offset) = L3;
	if(!f534981547_111) { //next;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,111);
	  f534981547_111=fld->instance;
	}
	*FIELD_PTR_O(L1,f534981547_111->offset) = L2;
	if(!f534981547_114) { //prev;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,114);
	  f534981547_114=fld->instance;
	}
	*FIELD_PTR_O(L2,f534981547_114->offset) = L1;
BB179:
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Sprite2D_removeChild__Ldigiplay_Sprite2D__V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JINT T1,T2;
	Object *L0,*L1,*T0,*S0O;
	L1=args[0].O;
	L0=args[1].O;
BB0:
	if(L0==NULL) goto BB31;
BB4:
	AOTFIELD(f534981547_104,111,132,133); //digiplay/Sprite2D:parent:Ldigiplay/Sprite2D;
	if(!L0) { frame->pc = 5; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f534981547_104->offset);
	/*spill*/S0O=T0;
	if(L1!=NULL) goto BB31;
BB12:
	{
	  VAR cargs[]={{.O=L1},{.O=L0}};
	  frame->pc=14;
	  AOTVMETHOD(m534981547_123,111,140,15,vTableIndex); //digiplay/Sprite2D:unlinkChild:(Ldigiplay/Sprite2D;)V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m534981547_123];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	AOTFIELD(f534981547_127,111,141,4); //digiplay/Sprite2D:numChildren:I;
	if(!L1) { frame->pc = 19; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_I(L1,f534981547_127->offset);
	T2 = T1 - 1;
	if(!f534981547_127) { //numChildren;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,127);
	  f534981547_127=fld->instance;
	}
	*FIELD_PTR_I(L1,f534981547_127->offset) = T2;
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=28;
	  AOTVMETHOD(m534981547_130,111,142,2,vTableIndex); //digiplay/Sprite2D:dispose:()V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m534981547_130];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
BB31:
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Sprite2D_addChild__Ldigiplay_Sprite2D__V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JINT T1,T2;
	Object *L0,*L1,*T0,*S0O;
	L1=args[0].O;
	L0=args[1].O;
BB0:
	if(L0==NULL) goto BB12;
BB4:
	AOTFIELD(f534981547_104,111,132,133); //digiplay/Sprite2D:parent:Ldigiplay/Sprite2D;
	if(!L0) { frame->pc = 5; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f534981547_104->offset);
	/*spill*/S0O=T0;
	if(L1!=NULL) goto BB13;
BB12:
	vm->FP--;return;
BB13:
	AOTFIELD(f534981547_104,111,132,133); //digiplay/Sprite2D:parent:Ldigiplay/Sprite2D;
	if(!L0) { frame->pc = 14; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f534981547_104->offset);
	if(T0==NULL) goto BB28;
BB20:
	AOTFIELD(f534981547_104,111,132,133); //digiplay/Sprite2D:parent:Ldigiplay/Sprite2D;
	if(!L0) { frame->pc = 21; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f534981547_104->offset);
	{
	  VAR cargs[]={{.O=T0},{.O=L0}};
	  frame->pc=25;
	  AOTVMETHOD(m534981547_123,111,140,15,vTableIndex); //digiplay/Sprite2D:unlinkChild:(Ldigiplay/Sprite2D;)V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m534981547_123];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
BB28:
	if(!f534981547_111) { //next;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,111);
	  f534981547_111=fld->instance;
	}
	*FIELD_PTR_O(L0,f534981547_111->offset) = NULL;
	if(!f534981547_104) { //parent;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,104);
	  f534981547_104=fld->instance;
	}
	*FIELD_PTR_O(L0,f534981547_104->offset) = L1;
	{
	  VAR cargs[]={{.O=L1},{.O=L0}};
	  frame->pc=40;
	  AOTVMETHOD(m534981547_133,111,143,15,vTableIndex); //digiplay/Sprite2D:linkChild:(Ldigiplay/Sprite2D;)V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m534981547_133];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	AOTFIELD(f534981547_127,111,141,4); //digiplay/Sprite2D:numChildren:I;
	if(!L1) { frame->pc = 45; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_I(L1,f534981547_127->offset);
	T2 = T1 + 1;
	if(!f534981547_127) { //numChildren;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,127);
	  f534981547_127=fld->instance;
	}
	*FIELD_PTR_I(L1,f534981547_127->offset) = T2;
	AOTFIELD(f534981547_9,111,114,4); //digiplay/Sprite2D:flags:I;
	if(!L1) { frame->pc = 54; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_I(L1,f534981547_9->offset);
	T2 = T1 & 64;
	if(T2==0) goto BB71;
BB63:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=64;
	  AOTVMETHOD(m534981547_101,111,131,2,vTableIndex); //digiplay/Sprite2D:updateWorldAlpha:()V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m534981547_101];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=68;
	  AOTVMETHOD(m534981547_136,111,144,2,vTableIndex); //digiplay/Sprite2D:setInStage:()V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m534981547_136];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
BB71:
	AOTFIELD(f534981547_9,111,114,4); //digiplay/Sprite2D:flags:I;
	if(!L0) { frame->pc = 73; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_I(L0,f534981547_9->offset);
	T2 = T1 | 12;
	if(!f534981547_9) { //flags;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,9);
	  f534981547_9=fld->instance;
	}
	*FIELD_PTR_I(L0,f534981547_9->offset) = T2;
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Sprite2D_markContentInvalid___V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JINT T0,T1;
	Object *L0;
	L0=args[0].O;
BB0:
	AOTFIELD(f534981547_9,111,114,4); //digiplay/Sprite2D:flags:I;
	if(!L0) { frame->pc = 1; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_I(L0,f534981547_9->offset);
	T1 = T0 & 128;
	if(T1!=0) goto BB31;
BB11:
	AOTFIELD(f534981547_9,111,114,4); //digiplay/Sprite2D:flags:I;
	if(!L0) { frame->pc = 13; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_I(L0,f534981547_9->offset);
	T1 = T0 | 128;
	if(!f534981547_9) { //flags;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,9);
	  f534981547_9=fld->instance;
	}
	*FIELD_PTR_I(L0,f534981547_9->offset) = T1;
	AOTFIELD(f534981547_139,111,145,4); //digiplay/Sprite2D:InvalidationCounter:I;
	T0 = *((JINT*)(CLS(f534981547_139->declaringClass,global) + f534981547_139->offset));
	T1 = T0 + 1;
	if(!f534981547_139) { //InvalidationCounter;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,139);
	  f534981547_139=fld->instance;
	}
	*((JINT*)((CLS(f534981547_139->declaringClass,global))+f534981547_139->offset)) = T1;
BB31:
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Sprite2D_invalidateContent___V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
BB0:
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Sprite2D_invalidateContentIfRequired___V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JINT T0,T1;
	Object *L0;
	L0=args[0].O;
BB0:
	AOTFIELD(f534981547_9,111,114,4); //digiplay/Sprite2D:flags:I;
	if(!L0) { frame->pc = 1; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_I(L0,f534981547_9->offset);
	T1 = T0 & 128;
	if(T1==0) goto BB27;
BB11:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=12;
	  AOTVMETHOD(m534981547_142,111,146,2,vTableIndex); //digiplay/Sprite2D:invalidateContent:()V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m534981547_142];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	AOTFIELD(f534981547_9,111,114,4); //digiplay/Sprite2D:flags:I;
	if(!L0) { frame->pc = 17; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_I(L0,f534981547_9->offset);
	T1 = T0 & -129;
	if(!f534981547_9) { //flags;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,9);
	  f534981547_9=fld->instance;
	}
	*FIELD_PTR_I(L0,f534981547_9->offset) = T1;
BB27:
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Sprite2D_init___V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
BB0:
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Sprite2D_setInStage___V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JINT T0,T1;
	Object *L0,*L1,*T2,*T3,*S0O;
	L0=args[0].O;
BB0:
	AOTFIELD(f534981547_9,111,114,4); //digiplay/Sprite2D:flags:I;
	if(!L0) { frame->pc = 1; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_I(L0,f534981547_9->offset);
	T1 = T0 & 64;
	if(T1==0) goto BB11;
BB10:
	vm->FP--;return;
BB11:
	AOTFIELD(f534981547_9,111,114,4); //digiplay/Sprite2D:flags:I;
	if(!L0) { frame->pc = 13; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_I(L0,f534981547_9->offset);
	T1 = T0 | 64;
	if(!f534981547_9) { //flags;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,9);
	  f534981547_9=fld->instance;
	}
	*FIELD_PTR_I(L0,f534981547_9->offset) = T1;
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=23;
	  AOTVMETHOD(m534981547_145,111,147,2,vTableIndex); //digiplay/Sprite2D:markContentInvalid:()V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m534981547_145];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	AOTFIELD(f534981547_108,111,135,133); //digiplay/Sprite2D:firstChild:Ldigiplay/Sprite2D;
	if(!L0) { frame->pc = 27; throw_null(vm); goto __EXCEPTION; }
	T2 = *FIELD_PTR_O(L0,f534981547_108->offset);
	L1=T2;
BB31:
	if(L1==NULL) goto BB47;
BB35:
	{
	  VAR cargs[]={{.O=L1}};
	  frame->pc=36;
	  AOTVMETHOD(m534981547_136,111,144,2,vTableIndex); //digiplay/Sprite2D:setInStage:()V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m534981547_136];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	AOTFIELD(f534981547_111,111,136,133); //digiplay/Sprite2D:next:Ldigiplay/Sprite2D;
	if(!L1) { frame->pc = 40; throw_null(vm); goto __EXCEPTION; }
	T2 = *FIELD_PTR_O(L1,f534981547_111->offset);
	L1=T2;
	goto BB31;
BB47:
	AOTFIELD(f534981547_104,111,132,133); //digiplay/Sprite2D:parent:Ldigiplay/Sprite2D;
	if(!L0) { frame->pc = 48; throw_null(vm); goto __EXCEPTION; }
	T2 = *FIELD_PTR_O(L0,f534981547_104->offset);
	AOTFIELD(f534981547_148,3,4,5); //digiplay/Stage2D:I:Ldigiplay/Stage2D;
	T3 = *((Object**)(CLS(f534981547_148->declaringClass,global) + f534981547_148->offset));
	/*spill*/S0O=T2;
	if(T3!=NULL) goto BB61;
BB57:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=58;
	  AOTVMETHOD(m534981547_142,111,146,2,vTableIndex); //digiplay/Sprite2D:invalidateContent:()V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m534981547_142];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
BB61:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=62;
	  AOTVMETHOD(m534981547_153,111,148,2,vTableIndex); //digiplay/Sprite2D:init:()V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m534981547_153];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Sprite2D_draw___V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
BB0:
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
//digiplay/Game
static Object *c_91417146_1=NULL,*c_91417146_3=NULL;
//digiplay/Texture2D
static JLONG m1247361881_1=0;
static Object *c1247361881_2=NULL,*c1247361881_7=NULL;
void digiplay_Texture2D__init____V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	Object *L0;
	L0=args[0].O;
BB0:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=1;
	  AOTMETHOD(m1247361881_1,0,1,2); //java/lang/Object:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m1247361881_1),entry)))(vm,m1247361881_1,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Texture2D_create__Ldigiplay_GLTexture__Ldigiplay_Texture2D_(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
BB0:
	vm->FP--;vm->frames[vm->FP].ret.O=NULL;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
//digiplay/Matrix2D
static Field *f_1694338649_12=NULL,*f_1694338649_16=NULL,*f_1694338649_19=NULL,*f_1694338649_22=NULL,*f_1694338649_25=NULL,*f_1694338649_28=NULL,*f_1694338649_35=NULL,*f_1694338649_38=NULL,*f_1694338649_41=NULL,*f_1694338649_44=NULL,*f_1694338649_47=NULL;
static JLONG m_1694338649_1=0,m_1694338649_7=0,m_1694338649_31=0,m_1694338649_56=0,m_1694338649_60=0;
static Object *c_1694338649_2=NULL,*c_1694338649_8=NULL,*c_1694338649_52=NULL;
void digiplay_Matrix2D__init____V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	Object *L0;
	L0=args[0].O;
BB0:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=1;
	  AOTMETHOD(m_1694338649_1,0,1,2); //java/lang/Object:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m_1694338649_1),entry)))(vm,m_1694338649_1,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=5;
	  AOTVMETHOD(m_1694338649_7,149,150,2,vTableIndex); //digiplay/Matrix2D:identity:()V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_1694338649_7];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Matrix2D_set__FFFFFF_V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JFLOAT L1,L2,L3,L4,L5,L6;
	Object *L0;
	L0=args[0].O;
	L1=args[1].F;
	L4=args[2].F;
	L2=args[3].F;
	L5=args[4].F;
	L3=args[5].F;
	L6=args[6].F;
BB0:
	if(!f_1694338649_12) { //m00;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,12);
	  f_1694338649_12=fld->instance;
	}
	*FIELD_PTR_F(L0,f_1694338649_12->offset) = L1;
	if(!f_1694338649_16) { //m01;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,16);
	  f_1694338649_16=fld->instance;
	}
	*FIELD_PTR_F(L0,f_1694338649_16->offset) = L2;
	if(!f_1694338649_19) { //m02;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,19);
	  f_1694338649_19=fld->instance;
	}
	*FIELD_PTR_F(L0,f_1694338649_19->offset) = L3;
	if(!f_1694338649_22) { //m10;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,22);
	  f_1694338649_22=fld->instance;
	}
	*FIELD_PTR_F(L0,f_1694338649_22->offset) = L4;
	if(!f_1694338649_25) { //m11;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,25);
	  f_1694338649_25=fld->instance;
	}
	*FIELD_PTR_F(L0,f_1694338649_25->offset) = L5;
	if(!f_1694338649_28) { //m12;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,28);
	  f_1694338649_28=fld->instance;
	}
	*FIELD_PTR_F(L0,f_1694338649_28->offset) = L6;
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Matrix2D_copyFrom__Ldigiplay_Matrix2D__V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JFLOAT T0;
	Object *L0,*L1;
	L0=args[0].O;
	L1=args[1].O;
BB0:
	AOTFIELD(f_1694338649_12,149,151,112); //digiplay/Matrix2D:m00:F;
	if(!L1) { frame->pc = 2; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_F(L1,f_1694338649_12->offset);
	if(!f_1694338649_12) { //m00;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,12);
	  f_1694338649_12=fld->instance;
	}
	*FIELD_PTR_F(L0,f_1694338649_12->offset) = T0;
	AOTFIELD(f_1694338649_16,149,152,112); //digiplay/Matrix2D:m01:F;
	if(!L1) { frame->pc = 10; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_F(L1,f_1694338649_16->offset);
	if(!f_1694338649_16) { //m01;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,16);
	  f_1694338649_16=fld->instance;
	}
	*FIELD_PTR_F(L0,f_1694338649_16->offset) = T0;
	AOTFIELD(f_1694338649_19,149,153,112); //digiplay/Matrix2D:m02:F;
	if(!L1) { frame->pc = 18; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_F(L1,f_1694338649_19->offset);
	if(!f_1694338649_19) { //m02;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,19);
	  f_1694338649_19=fld->instance;
	}
	*FIELD_PTR_F(L0,f_1694338649_19->offset) = T0;
	AOTFIELD(f_1694338649_22,149,154,112); //digiplay/Matrix2D:m10:F;
	if(!L1) { frame->pc = 26; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_F(L1,f_1694338649_22->offset);
	if(!f_1694338649_22) { //m10;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,22);
	  f_1694338649_22=fld->instance;
	}
	*FIELD_PTR_F(L0,f_1694338649_22->offset) = T0;
	AOTFIELD(f_1694338649_25,149,155,112); //digiplay/Matrix2D:m11:F;
	if(!L1) { frame->pc = 34; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_F(L1,f_1694338649_25->offset);
	if(!f_1694338649_25) { //m11;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,25);
	  f_1694338649_25=fld->instance;
	}
	*FIELD_PTR_F(L0,f_1694338649_25->offset) = T0;
	AOTFIELD(f_1694338649_28,149,156,112); //digiplay/Matrix2D:m12:F;
	if(!L1) { frame->pc = 42; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_F(L1,f_1694338649_28->offset);
	if(!f_1694338649_28) { //m12;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,28);
	  f_1694338649_28=fld->instance;
	}
	*FIELD_PTR_F(L0,f_1694338649_28->offset) = T0;
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Matrix2D_identity___V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JINT T0,T1;
	Object *L0;
	L0=args[0].O;
BB0:
	{
	  VAR cargs[]={{.O=L0},{.F=1},{.F=0},{.F=0},{.F=1},{.F=0},{.F=0}};
	  frame->pc=7;
	  AOTVMETHOD(m_1694338649_31,149,157,158,vTableIndex); //digiplay/Matrix2D:set:(FFFFFF)V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_1694338649_31];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	if(!f_1694338649_35) { //_cx;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,35);
	  f_1694338649_35=fld->instance;
	}
	*FIELD_PTR_F(L0,f_1694338649_35->offset) = 1;
	if(!f_1694338649_38) { //_sx;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,38);
	  f_1694338649_38=fld->instance;
	}
	*FIELD_PTR_F(L0,f_1694338649_38->offset) = 0;
	if(!f_1694338649_41) { //_cy;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,41);
	  f_1694338649_41=fld->instance;
	}
	*FIELD_PTR_F(L0,f_1694338649_41->offset) = 0;
	if(!f_1694338649_44) { //_sy;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,44);
	  f_1694338649_44=fld->instance;
	}
	*FIELD_PTR_F(L0,f_1694338649_44->offset) = 1;
	AOTFIELD(f_1694338649_47,149,159,4); //digiplay/Matrix2D:modifyCounter:I;
	if(!L0) { frame->pc = 32; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_I(L0,f_1694338649_47->offset);
	T1 = T0 + 1;
	if(!f_1694338649_47) { //modifyCounter;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,47);
	  f_1694338649_47=fld->instance;
	}
	*FIELD_PTR_I(L0,f_1694338649_47->offset) = T1;
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Matrix2D_updateRotAndSkew__FFF_V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JDOUBLE T1,T2;
	JFLOAT L0,L1,L2,T0;
	Object *L3;
	L3=args[0].O;
	L0=args[1].F;
	L1=args[2].F;
	L2=args[3].F;
BB0:
	T0 = L0 / 180.0;
	T1=(JDOUBLE)T0;
	T2 = T1 * 3.141592653589793;
	T0=(JFLOAT)T2;
	L0=T0;
	T0 = L1 / 180.0;
	T1=(JDOUBLE)T0;
	T2 = T1 * 3.141592653589793;
	T0=(JFLOAT)T2;
	L1=T0;
	T0 = L2 / 180.0;
	T1=(JDOUBLE)T0;
	T2 = T1 * 3.141592653589793;
	T0=(JFLOAT)T2;
	L2=T0;
	T0 = L0 + L2;
	T1=(JDOUBLE)T0;
	{
	  VAR cargs[]={{.D=T1}};
	  frame->pc=38;
	  AOTMETHOD(m_1694338649_56,19,160,161); //java/lang/Math:cos:(D)D;
	  ((VM_CALL)(MTH(((Object*)m_1694338649_56),entry)))(vm,m_1694338649_56,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T1=frame->ret.D;
	}
	
	T0=(JFLOAT)T1;
	if(!f_1694338649_35) { //_cx;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,35);
	  f_1694338649_35=fld->instance;
	}
	*FIELD_PTR_F(L3,f_1694338649_35->offset) = T0;
	T0 = L0 + L2;
	T1=(JDOUBLE)T0;
	{
	  VAR cargs[]={{.D=T1}};
	  frame->pc=50;
	  AOTMETHOD(m_1694338649_60,19,162,161); //java/lang/Math:sin:(D)D;
	  ((VM_CALL)(MTH(((Object*)m_1694338649_60),entry)))(vm,m_1694338649_60,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T1=frame->ret.D;
	}
	
	T0=(JFLOAT)T1;
	if(!f_1694338649_38) { //_sx;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,38);
	  f_1694338649_38=fld->instance;
	}
	*FIELD_PTR_F(L3,f_1694338649_38->offset) = T0;
	T0 = L0 - L1;
	T1=(JDOUBLE)T0;
	{
	  VAR cargs[]={{.D=T1}};
	  frame->pc=62;
	  AOTMETHOD(m_1694338649_60,19,162,161); //java/lang/Math:sin:(D)D;
	  ((VM_CALL)(MTH(((Object*)m_1694338649_60),entry)))(vm,m_1694338649_60,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T1=frame->ret.D;
	}
	
	T2=-T1;
	T0=(JFLOAT)T2;
	if(!f_1694338649_41) { //_cy;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,41);
	  f_1694338649_41=fld->instance;
	}
	*FIELD_PTR_F(L3,f_1694338649_41->offset) = T0;
	T0 = L0 - L1;
	T1=(JDOUBLE)T0;
	{
	  VAR cargs[]={{.D=T1}};
	  frame->pc=75;
	  AOTMETHOD(m_1694338649_56,19,160,161); //java/lang/Math:cos:(D)D;
	  ((VM_CALL)(MTH(((Object*)m_1694338649_56),entry)))(vm,m_1694338649_56,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T1=frame->ret.D;
	}
	
	T0=(JFLOAT)T1;
	if(!f_1694338649_44) { //_sy;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,44);
	  f_1694338649_44=fld->instance;
	}
	*FIELD_PTR_F(L3,f_1694338649_44->offset) = T0;
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Matrix2D_compose__FFFFFF_V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JFLOAT L1,L2,L3,L4,L5,L6,L7,L8,L9,L10,T0,T1,T2;
	Object *L0;
	L0=args[0].O;
	L7=args[1].F;
	L10=args[2].F;
	L1=args[3].F;
	L4=args[4].F;
	L8=args[5].F;
	L9=args[6].F;
BB0:
	AOTFIELD(f_1694338649_35,149,163,112); //digiplay/Matrix2D:_cx:F;
	if(!L0) { frame->pc = 1; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_F(L0,f_1694338649_35->offset);
	T1 = T0 * L1;
	L2=T1;
	AOTFIELD(f_1694338649_38,149,164,112); //digiplay/Matrix2D:_sx:F;
	if(!L0) { frame->pc = 9; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_F(L0,f_1694338649_38->offset);
	T1 = T0 * L1;
	L3=T1;
	AOTFIELD(f_1694338649_41,149,165,112); //digiplay/Matrix2D:_cy:F;
	if(!L0) { frame->pc = 17; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_F(L0,f_1694338649_41->offset);
	T1 = T0 * L4;
	L5=T1;
	AOTFIELD(f_1694338649_44,149,166,112); //digiplay/Matrix2D:_sy:F;
	if(!L0) { frame->pc = 26; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_F(L0,f_1694338649_44->offset);
	T1 = T0 * L4;
	L6=T1;
	T0 = L8 * L2;
	T1 = L9 * L5;
	T2 = T0 + T1;
	T0 = L7 - T2;
	if(!f_1694338649_19) { //m02;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,19);
	  f_1694338649_19=fld->instance;
	}
	*FIELD_PTR_F(L0,f_1694338649_19->offset) = T0;
	T0 = L8 * L3;
	T1 = L9 * L6;
	T2 = T0 + T1;
	T0 = L10 - T2;
	if(!f_1694338649_28) { //m12;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,28);
	  f_1694338649_28=fld->instance;
	}
	*FIELD_PTR_F(L0,f_1694338649_28->offset) = T0;
	if(!f_1694338649_12) { //m00;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,12);
	  f_1694338649_12=fld->instance;
	}
	*FIELD_PTR_F(L0,f_1694338649_12->offset) = L2;
	if(!f_1694338649_22) { //m10;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,22);
	  f_1694338649_22=fld->instance;
	}
	*FIELD_PTR_F(L0,f_1694338649_22->offset) = L3;
	if(!f_1694338649_16) { //m01;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,16);
	  f_1694338649_16=fld->instance;
	}
	*FIELD_PTR_F(L0,f_1694338649_16->offset) = L5;
	if(!f_1694338649_25) { //m11;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,25);
	  f_1694338649_25=fld->instance;
	}
	*FIELD_PTR_F(L0,f_1694338649_25->offset) = L6;
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Matrix2D_multiply__Ldigiplay_Matrix2D_Ldigiplay_Matrix2D_Ldigiplay_Matrix2D__V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JFLOAT L1,L2,L3,L4,L6,L7,L8,L9,L10,L11,T0,T1,T2;
	Object *L0,*L5,*L12;
	L0=args[0].O;
	L5=args[1].O;
	L12=args[2].O;
BB0:
	AOTFIELD(f_1694338649_12,149,151,112); //digiplay/Matrix2D:m00:F;
	if(!L0) { frame->pc = 1; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_F(L0,f_1694338649_12->offset);
	L1=T0;
	AOTFIELD(f_1694338649_16,149,152,112); //digiplay/Matrix2D:m01:F;
	if(!L0) { frame->pc = 6; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_F(L0,f_1694338649_16->offset);
	L2=T0;
	AOTFIELD(f_1694338649_22,149,154,112); //digiplay/Matrix2D:m10:F;
	if(!L0) { frame->pc = 12; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_F(L0,f_1694338649_22->offset);
	L3=T0;
	AOTFIELD(f_1694338649_25,149,155,112); //digiplay/Matrix2D:m11:F;
	if(!L0) { frame->pc = 18; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_F(L0,f_1694338649_25->offset);
	L4=T0;
	AOTFIELD(f_1694338649_12,149,151,112); //digiplay/Matrix2D:m00:F;
	if(!L5) { frame->pc = 24; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_F(L5,f_1694338649_12->offset);
	L6=T0;
	AOTFIELD(f_1694338649_16,149,152,112); //digiplay/Matrix2D:m01:F;
	if(!L5) { frame->pc = 30; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_F(L5,f_1694338649_16->offset);
	L7=T0;
	AOTFIELD(f_1694338649_19,149,153,112); //digiplay/Matrix2D:m02:F;
	if(!L5) { frame->pc = 36; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_F(L5,f_1694338649_19->offset);
	L8=T0;
	AOTFIELD(f_1694338649_22,149,154,112); //digiplay/Matrix2D:m10:F;
	if(!L5) { frame->pc = 42; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_F(L5,f_1694338649_22->offset);
	L9=T0;
	AOTFIELD(f_1694338649_25,149,155,112); //digiplay/Matrix2D:m11:F;
	if(!L5) { frame->pc = 48; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_F(L5,f_1694338649_25->offset);
	L10=T0;
	AOTFIELD(f_1694338649_28,149,156,112); //digiplay/Matrix2D:m12:F;
	if(!L5) { frame->pc = 54; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_F(L5,f_1694338649_28->offset);
	L11=T0;
	T0 = L1 * L6;
	T1 = L2 * L9;
	T2 = T0 + T1;
	if(!f_1694338649_12) { //m00;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,12);
	  f_1694338649_12=fld->instance;
	}
	*FIELD_PTR_F(L12,f_1694338649_12->offset) = T2;
	T0 = L1 * L7;
	T1 = L2 * L10;
	T2 = T0 + T1;
	if(!f_1694338649_16) { //m01;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,16);
	  f_1694338649_16=fld->instance;
	}
	*FIELD_PTR_F(L12,f_1694338649_16->offset) = T2;
	T0 = L1 * L8;
	T1 = L2 * L11;
	T2 = T0 + T1;
	AOTFIELD(f_1694338649_19,149,153,112); //digiplay/Matrix2D:m02:F;
	if(!L0) { frame->pc = 99; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_F(L0,f_1694338649_19->offset);
	T1 = T2 + T0;
	if(!f_1694338649_19) { //m02;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,19);
	  f_1694338649_19=fld->instance;
	}
	*FIELD_PTR_F(L12,f_1694338649_19->offset) = T1;
	T0 = L3 * L6;
	T1 = L4 * L9;
	T2 = T0 + T1;
	if(!f_1694338649_22) { //m10;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,22);
	  f_1694338649_22=fld->instance;
	}
	*FIELD_PTR_F(L12,f_1694338649_22->offset) = T2;
	T0 = L3 * L7;
	T1 = L4 * L10;
	T2 = T0 + T1;
	if(!f_1694338649_25) { //m11;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,25);
	  f_1694338649_25=fld->instance;
	}
	*FIELD_PTR_F(L12,f_1694338649_25->offset) = T2;
	T0 = L3 * L8;
	T1 = L4 * L11;
	T2 = T0 + T1;
	AOTFIELD(f_1694338649_28,149,156,112); //digiplay/Matrix2D:m12:F;
	if(!L0) { frame->pc = 149; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_F(L0,f_1694338649_28->offset);
	T1 = T2 + T0;
	if(!f_1694338649_28) { //m12;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,28);
	  f_1694338649_28=fld->instance;
	}
	*FIELD_PTR_F(L12,f_1694338649_28->offset) = T1;
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
//digiplay/Completable
static Object *c_791477326_1=NULL,*c_791477326_3=NULL;
//digiplay/Point2D
static Field *f_603837042_7=NULL,*f_603837042_13=NULL;
static JLONG m_603837042_1=0;
static Object *c_603837042_2=NULL,*c_603837042_8=NULL;
void digiplay_Point2D__init____V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	Object *L0;
	L0=args[0].O;
BB0:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=1;
	  AOTMETHOD(m_603837042_1,0,1,2); //java/lang/Object:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m_603837042_1),entry)))(vm,m_603837042_1,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Point2D__init___FF_V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JFLOAT L1,L2;
	Object *L0;
	L0=args[0].O;
	L1=args[1].F;
	L2=args[2].F;
BB0:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=1;
	  AOTMETHOD(m_603837042_1,0,1,2); //java/lang/Object:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m_603837042_1),entry)))(vm,m_603837042_1,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	if(!f_603837042_7) { //x;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,7);
	  f_603837042_7=fld->instance;
	}
	*FIELD_PTR_F(L0,f_603837042_7->offset) = L1;
	if(!f_603837042_13) { //y;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,13);
	  f_603837042_13=fld->instance;
	}
	*FIELD_PTR_F(L0,f_603837042_13->offset) = L2;
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
//digiplay/Image
static Field *f1463228935_17=NULL,*f1463228935_23=NULL,*f1463228935_30=NULL,*f1463228935_44=NULL,*f1463228935_57=NULL,*f1463228935_63=NULL,*f1463228935_71=NULL,*f1463228935_75=NULL,*f1463228935_78=NULL,*f1463228935_81=NULL,*f1463228935_99=NULL,*f1463228935_109=NULL;
static JLONG m1463228935_1=0,m1463228935_9=0,m1463228935_33=0,m1463228935_37=0,m1463228935_41=0,m1463228935_50=0,m1463228935_53=0,m1463228935_67=0,m1463228935_84=0,m1463228935_90=0,m1463228935_94=0,m1463228935_96=0,m1463228935_104=0,m1463228935_106=0,m1463228935_112=0;
static Object *c1463228935_2=NULL,*c1463228935_10=NULL,*c1463228935_18=NULL,*c1463228935_48=NULL,*c1463228935_58=NULL,*c1463228935_85=NULL,*c1463228935_100=NULL;
void digiplay_Image__init____V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JDOUBLE T0,T1;
	JFLOAT T2;
	Object *L0;
	L0=args[0].O;
BB0:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=1;
	  AOTMETHOD(m1463228935_1,111,1,2); //digiplay/Sprite2D:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m1463228935_1),entry)))(vm,m1463228935_1,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	{
	  frame->pc=8;
	  AOTMETHOD(m1463228935_9,19,20,21); //java/lang/Math:random:()D;
	  ((VM_CALL)(MTH(((Object*)m1463228935_9),entry)))(vm,m1463228935_9,NULL);
	  if(vm->exception) goto __EXCEPTION;
	  T0=frame->ret.D;
	}
	
	T1 = T0 * 6.0;
	T0 = -3.0 + T1;
	T2=(JFLOAT)T0;
	if(!f1463228935_17) { //dx;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,17);
	  f1463228935_17=fld->instance;
	}
	*FIELD_PTR_F(L0,f1463228935_17->offset) = T2;
	{
	  frame->pc=24;
	  AOTMETHOD(m1463228935_9,19,20,21); //java/lang/Math:random:()D;
	  ((VM_CALL)(MTH(((Object*)m1463228935_9),entry)))(vm,m1463228935_9,NULL);
	  if(vm->exception) goto __EXCEPTION;
	  T0=frame->ret.D;
	}
	
	T1 = T0 * 6.0;
	T0 = -3.0 + T1;
	T2=(JFLOAT)T0;
	if(!f1463228935_23) { //dy;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,23);
	  f1463228935_23=fld->instance;
	}
	*FIELD_PTR_F(L0,f1463228935_23->offset) = T2;
	{
	  frame->pc=40;
	  AOTMETHOD(m1463228935_9,19,20,21); //java/lang/Math:random:()D;
	  ((VM_CALL)(MTH(((Object*)m1463228935_9),entry)))(vm,m1463228935_9,NULL);
	  if(vm->exception) goto __EXCEPTION;
	  T0=frame->ret.D;
	}
	
	T1 = T0 * 10.0;
	T0 = -5.0 + T1;
	T2=(JFLOAT)T0;
	if(!f1463228935_30) { //r;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,30);
	  f1463228935_30=fld->instance;
	}
	*FIELD_PTR_F(L0,f1463228935_30->offset) = T2;
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=53;
	  AOTVMETHOD(m1463228935_33,13,147,2,vTableIndex); //digiplay/Image:markContentInvalid:()V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m1463228935_33];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	{
	  VAR cargs[]={{.O=L0},{.F=50.0}};
	  frame->pc=59;
	  AOTVMETHOD(m1463228935_37,13,121,17,vTableIndex); //digiplay/Image:width:(F)V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m1463228935_37];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	{
	  VAR cargs[]={{.O=L0},{.F=50.0}};
	  frame->pc=65;
	  AOTVMETHOD(m1463228935_41,13,123,17,vTableIndex); //digiplay/Image:height:(F)V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m1463228935_41];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
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
	AOTFIELD(f1463228935_44,13,167,168); //digiplay/Image:quad:Ldigiplay/QuadMesh;
	if(!L0) { frame->pc = 1; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f1463228935_44->offset);
	if(T0!=NULL) goto BB19;
BB7:
	AOTCLASS(c1463228935_48,169);
	T0=alloc_object(vm,c1463228935_48,0);
	{
	  VAR cargs[]={{.O=T0},{.I=1}};
	  frame->pc=13;
	  AOTMETHOD(m1463228935_50,169,1,88); //digiplay/QuadMesh:<init>:(I)V;
	  ((VM_CALL)(MTH(((Object*)m1463228935_50),entry)))(vm,m1463228935_50,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	if(!f1463228935_44) { //quad;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,44);
	  f1463228935_44=fld->instance;
	}
	*FIELD_PTR_O(L0,f1463228935_44->offset) = T0;
BB19:
	AOTFIELD(f1463228935_44,13,167,168); //digiplay/Image:quad:Ldigiplay/QuadMesh;
	if(!L0) { frame->pc = 20; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f1463228935_44->offset);
	{
	  VAR cargs[]={{.O=T0},{.I=0},{.F=0},{.F=0},{.F=50.0},{.F=50.0},{.F=0},{.F=0},{.F=0},{.F=0},{.F=0},{.F=0},{.F=0},{.F=0}};
	  frame->pc=38;
	  AOTVMETHOD(m1463228935_53,169,157,170,vTableIndex); //digiplay/QuadMesh:set:(IFFFFFFFFFFFF)V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m1463228935_53];
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
	JFLOAT L1,L2,T5,T7,T8;
	JINT T2,T6;
	Object *L0,*T0,*T1,*T3,*T4;
	L0=args[0].O;
BB0:
	AOTFIELD(f1463228935_44,13,167,168); //digiplay/Image:quad:Ldigiplay/QuadMesh;
	if(!L0) { frame->pc = 1; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f1463228935_44->offset);
	if(T0==NULL) goto BB39;
BB7:
	AOTFIELD(f1463228935_57,3,171,172); //digiplay/Stage2D:QuadBatch:Ldigiplay/GLQuadBatch;
	T0 = *((Object**)(CLS(f1463228935_57->declaringClass,global) + f1463228935_57->offset));
	AOTFIELD(f1463228935_44,13,167,168); //digiplay/Image:quad:Ldigiplay/QuadMesh;
	if(!L0) { frame->pc = 11; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_O(L0,f1463228935_44->offset);
	AOTFIELD(f1463228935_63,13,173,4); //digiplay/Image:GLOBAL_FRAME_VERSION:I;
	T2 = *((JINT*)(CLS(f1463228935_63->declaringClass,global) + f1463228935_63->offset));
	{
	  VAR cargs[]={{.O=L0},{.I=T2}};
	  frame->pc=18;
	  AOTVMETHOD(m1463228935_67,13,174,175,vTableIndex); //digiplay/Image:getWorldMatrix:(I)Ldigiplay/Mat2D;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m1463228935_67];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T3=frame->ret.O;
	}
	
	AOTFIELD(f1463228935_71,3,176,177); //digiplay/Stage2D:DefaultShader:Ldigiplay/GLShader2D;
	T4 = *((Object**)(CLS(f1463228935_71->declaringClass,global) + f1463228935_71->offset));
	AOTFIELD(f1463228935_75,13,178,4); //digiplay/Image:color:I;
	if(!L0) { frame->pc = 25; throw_null(vm); goto __EXCEPTION; }
	T2 = *FIELD_PTR_I(L0,f1463228935_75->offset);
	AOTFIELD(f1463228935_78,13,134,112); //digiplay/Image:worldAlpha:F;
	if(!L0) { frame->pc = 29; throw_null(vm); goto __EXCEPTION; }
	T5 = *FIELD_PTR_F(L0,f1463228935_78->offset);
	AOTFIELD(f1463228935_81,13,179,4); //digiplay/Image:blendMode:I;
	if(!L0) { frame->pc = 33; throw_null(vm); goto __EXCEPTION; }
	T6 = *FIELD_PTR_I(L0,f1463228935_81->offset);
	{
	  VAR cargs[]={{.O=T0},{.O=T1},{.O=T3},{.O=T4},{.I=T2},{.F=T5},{.I=T6}};
	  frame->pc=36;
	  AOTVMETHOD(m1463228935_84,180,181,182,vTableIndex); //digiplay/GLQuadBatch:drawQuadMesh:(Ldigiplay/QuadMesh;Ldigiplay/Mat2D;Ldigiplay/GLShader2D;IFI)V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m1463228935_84];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
BB39:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=41;
	  AOTVMETHOD(m1463228935_90,13,23,183,vTableIndex); //digiplay/Image:rotation:()F;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m1463228935_90];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T5=frame->ret.F;
	}
	
	AOTFIELD(f1463228935_30,13,184,112); //digiplay/Image:r:F;
	if(!L0) { frame->pc = 45; throw_null(vm); goto __EXCEPTION; }
	T7 = *FIELD_PTR_F(L0,f1463228935_30->offset);
	T8 = T5 + T7;
	{
	  VAR cargs[]={{.O=L0},{.F=T8}};
	  frame->pc=49;
	  AOTVMETHOD(m1463228935_94,13,23,17,vTableIndex); //digiplay/Image:rotation:(F)V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m1463228935_94];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=53;
	  AOTVMETHOD(m1463228935_96,13,16,183,vTableIndex); //digiplay/Image:x:()F;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m1463228935_96];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T5=frame->ret.F;
	}
	
	L1=T5;
	AOTFIELD(f1463228935_17,13,185,112); //digiplay/Image:dx:F;
	if(!L0) { frame->pc = 59; throw_null(vm); goto __EXCEPTION; }
	T5 = *FIELD_PTR_F(L0,f1463228935_17->offset);
	T7 = L1 + T5;
	L1=T7;
	T5 = L1 == 0 ? 0 : (L1 > 0 ? 1 : -1);
	if(T5>0) goto BB84;
BB70:
	L1=0;
	AOTFIELD(f1463228935_17,13,185,112); //digiplay/Image:dx:F;
	if(!L0) { frame->pc = 74; throw_null(vm); goto __EXCEPTION; }
	T5 = *FIELD_PTR_F(L0,f1463228935_17->offset);
	T7=-T5;
	if(!f1463228935_17) { //dx;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,17);
	  f1463228935_17=fld->instance;
	}
	*FIELD_PTR_F(L0,f1463228935_17->offset) = T7;
	goto BB107;
BB84:
	AOTFIELD(f1463228935_99,7,8,4); //digiplay/Platform:screenWidth:I;
	T2 = *((JINT*)(CLS(f1463228935_99->declaringClass,global) + f1463228935_99->offset));
	T5=(JFLOAT)T2;
	T5 = L1 == T5 ? 0 : (L1 > T5 ? 1 : -1);
	if(T5<0) goto BB107;
BB93:
	AOTFIELD(f1463228935_99,7,8,4); //digiplay/Platform:screenWidth:I;
	T2 = *((JINT*)(CLS(f1463228935_99->declaringClass,global) + f1463228935_99->offset));
	T5=(JFLOAT)T2;
	L1=T5;
	AOTFIELD(f1463228935_17,13,185,112); //digiplay/Image:dx:F;
	if(!L0) { frame->pc = 100; throw_null(vm); goto __EXCEPTION; }
	T5 = *FIELD_PTR_F(L0,f1463228935_17->offset);
	T7=-T5;
	if(!f1463228935_17) { //dx;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,17);
	  f1463228935_17=fld->instance;
	}
	*FIELD_PTR_F(L0,f1463228935_17->offset) = T7;
BB107:
	{
	  VAR cargs[]={{.O=L0},{.F=L1}};
	  frame->pc=109;
	  AOTVMETHOD(m1463228935_104,13,16,17,vTableIndex); //digiplay/Image:x:(F)V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m1463228935_104];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=113;
	  AOTVMETHOD(m1463228935_106,13,18,183,vTableIndex); //digiplay/Image:y:()F;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m1463228935_106];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T5=frame->ret.F;
	}
	
	L2=T5;
	AOTFIELD(f1463228935_23,13,186,112); //digiplay/Image:dy:F;
	if(!L0) { frame->pc = 119; throw_null(vm); goto __EXCEPTION; }
	T5 = *FIELD_PTR_F(L0,f1463228935_23->offset);
	T7 = L2 + T5;
	L2=T7;
	T5 = L2 == 0 ? 0 : (L2 > 0 ? 1 : -1);
	if(T5>0) goto BB144;
BB130:
	L2=0;
	AOTFIELD(f1463228935_23,13,186,112); //digiplay/Image:dy:F;
	if(!L0) { frame->pc = 134; throw_null(vm); goto __EXCEPTION; }
	T5 = *FIELD_PTR_F(L0,f1463228935_23->offset);
	T7=-T5;
	if(!f1463228935_23) { //dy;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,23);
	  f1463228935_23=fld->instance;
	}
	*FIELD_PTR_F(L0,f1463228935_23->offset) = T7;
	goto BB167;
BB144:
	AOTFIELD(f1463228935_109,7,9,4); //digiplay/Platform:screenHeight:I;
	T2 = *((JINT*)(CLS(f1463228935_109->declaringClass,global) + f1463228935_109->offset));
	T5=(JFLOAT)T2;
	T5 = L2 == T5 ? 0 : (L2 > T5 ? 1 : -1);
	if(T5<0) goto BB167;
BB153:
	AOTFIELD(f1463228935_109,7,9,4); //digiplay/Platform:screenHeight:I;
	T2 = *((JINT*)(CLS(f1463228935_109->declaringClass,global) + f1463228935_109->offset));
	T5=(JFLOAT)T2;
	L2=T5;
	AOTFIELD(f1463228935_23,13,186,112); //digiplay/Image:dy:F;
	if(!L0) { frame->pc = 160; throw_null(vm); goto __EXCEPTION; }
	T5 = *FIELD_PTR_F(L0,f1463228935_23->offset);
	T7=-T5;
	if(!f1463228935_23) { //dy;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,23);
	  f1463228935_23=fld->instance;
	}
	*FIELD_PTR_F(L0,f1463228935_23->offset) = T7;
BB167:
	{
	  VAR cargs[]={{.O=L0},{.F=L2}};
	  frame->pc=169;
	  AOTVMETHOD(m1463228935_112,13,18,17,vTableIndex); //digiplay/Image:y:(F)V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m1463228935_112];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
//digiplay/QuadMesh
static Field *f994406312_13=NULL,*f994406312_17=NULL,*f994406312_23=NULL,*f994406312_26=NULL,*f994406312_29=NULL;
static JLONG m994406312_1=0,m994406312_7=0,m994406312_32=0;
static Object *c994406312_2=NULL,*c994406312_8=NULL,*c994406312_18=NULL,*c994406312_45=NULL;
void digiplay_QuadMesh__init___I_V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JINT L1;
	JLONG T0;
	Object *L0;
	L0=args[0].O;
	L1=args[1].I;
BB0:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=1;
	  AOTMETHOD(m994406312_1,0,1,2); //java/lang/Object:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m994406312_1),entry)))(vm,m994406312_1,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	{
	  VAR cargs[]={{.I=L1}};
	  frame->pc=6;
	  AOTMETHOD(m994406312_7,169,99,187); //digiplay/QuadMesh:create:(I)J;
	  ((VM_CALL)(MTH(((Object*)m994406312_7),entry)))(vm,m994406312_7,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T0=frame->ret.J;
	}
	
	if(!f994406312_13) { //handle;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,13);
	  f994406312_13=fld->instance;
	}
	*FIELD_PTR_J(L0,f994406312_13->offset) = T0;
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_QuadMesh_set__IFFLdigiplay_GLTexture__V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JFLOAT L1,L2,L3,L4,L5,L6,L7,L8,T1,T2;
	JINT L10,T0;
	Object *L0,*L9;
	L9=args[0].O;
	L10=args[1].I;
	L5=args[2].F;
	L7=args[3].F;
	L0=args[4].O;
BB0:
	AOTFIELD(f994406312_17,188,189,4); //digiplay/GLTexture:hwWidth:I;
	if(!L0) { frame->pc = 2; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_I(L0,f994406312_17->offset);
	T1=(JFLOAT)T0;
	L1=T1;
	AOTFIELD(f994406312_23,188,190,4); //digiplay/GLTexture:hwHeight:I;
	if(!L0) { frame->pc = 10; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_I(L0,f994406312_23->offset);
	T1=(JFLOAT)T0;
	L2=T1;
	AOTFIELD(f994406312_26,188,121,4); //digiplay/GLTexture:width:I;
	if(!L0) { frame->pc = 18; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_I(L0,f994406312_26->offset);
	T1=(JFLOAT)T0;
	T2 = T1 / L1;
	L3=T2;
	AOTFIELD(f994406312_29,188,123,4); //digiplay/GLTexture:height:I;
	if(!L0) { frame->pc = 29; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_I(L0,f994406312_29->offset);
	T1=(JFLOAT)T0;
	T2 = T1 / L2;
	L4=T2;
	AOTFIELD(f994406312_26,188,121,4); //digiplay/GLTexture:width:I;
	if(!L0) { frame->pc = 41; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_I(L0,f994406312_26->offset);
	T1=(JFLOAT)T0;
	T2 = L5 + T1;
	L6=T2;
	AOTFIELD(f994406312_29,188,123,4); //digiplay/GLTexture:height:I;
	if(!L0) { frame->pc = 51; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_I(L0,f994406312_29->offset);
	T1=(JFLOAT)T0;
	T2 = L7 + T1;
	L8=T2;
	{
	  VAR cargs[]={{.O=L9},{.I=L10},{.F=L5},{.F=L7},{.F=L6},{.F=L8},{.F=0},{.F=0},{.F=L3},{.F=0},{.F=L3},{.F=L4},{.F=0},{.F=L4}};
	  frame->pc=78;
	  AOTVMETHOD(m994406312_32,169,157,170,vTableIndex); //digiplay/QuadMesh:set:(IFFFFFFFFFFFF)V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m994406312_32];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
//digiplay/GLQuadBatch
static Field *f1139497626_13=NULL;
static JLONG m1139497626_1=0,m1139497626_7=0;
static Object *c1139497626_2=NULL,*c1139497626_8=NULL,*c1139497626_32=NULL;
void digiplay_GLQuadBatch__init___I_V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JINT L1;
	JLONG T0;
	Object *L0;
	L0=args[0].O;
	L1=args[1].I;
BB0:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=1;
	  AOTMETHOD(m1139497626_1,0,1,2); //java/lang/Object:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m1139497626_1),entry)))(vm,m1139497626_1,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	{
	  VAR cargs[]={{.I=L1}};
	  frame->pc=6;
	  AOTMETHOD(m1139497626_7,180,99,187); //digiplay/GLQuadBatch:create:(I)J;
	  ((VM_CALL)(MTH(((Object*)m1139497626_7),entry)))(vm,m1139497626_7,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T0=frame->ret.J;
	}
	
	if(!f1139497626_13) { //handle;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,13);
	  f1139497626_13=fld->instance;
	}
	*FIELD_PTR_J(L0,f1139497626_13->offset) = T0;
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
//digiplay/Bag
static Field *f_1665521740_12=NULL,*f_1665521740_16=NULL;
static JLONG m_1665521740_1=0,m_1665521740_7=0;
static Object *c_1665521740_2=NULL,*c_1665521740_8=NULL;
void digiplay_Bag__init____V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	Object *L0;
	L0=args[0].O;
BB0:
	{
	  VAR cargs[]={{.O=L0},{.I=16}};
	  frame->pc=3;
	  AOTMETHOD(m_1665521740_1,191,1,88); //digiplay/Bag:<init>:(I)V;
	  ((VM_CALL)(MTH(((Object*)m_1665521740_1),entry)))(vm,m_1665521740_1,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Bag__init___I_V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JINT L1;
	Object *L0,*T0;
	L0=args[0].O;
	L1=args[1].I;
BB0:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=1;
	  AOTMETHOD(m_1665521740_7,0,1,2); //java/lang/Object:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m_1665521740_7),entry)))(vm,m_1665521740_7,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	if(!c_1665521740_8) c_1665521740_8=resolve_class_by_index(vm,method->declaringClass,8);
	T0 = alloc_array_O(vm,c_1665521740_8,L1,0);
	
	if(!f_1665521740_12) { //items;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,12);
	  f_1665521740_12=fld->instance;
	}
	*FIELD_PTR_O(L0,f_1665521740_12->offset) = T0;
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Bag_getSize___I(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JINT T0;
	Object *L0;
	L0=args[0].O;
BB0:
	AOTFIELD(f_1665521740_16,191,192,4); //digiplay/Bag:size:I;
	if(!L0) { frame->pc = 1; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_I(L0,f_1665521740_16->offset);
	vm->FP--;vm->frames[vm->FP].ret.I=T0;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
//digiplay/Stage2D
static Field *f_2100758660_7=NULL,*f_2100758660_20=NULL,*f_2100758660_26=NULL,*f_2100758660_29=NULL,*f_2100758660_35=NULL,*f_2100758660_38=NULL,*f_2100758660_48=NULL,*f_2100758660_92=NULL,*f_2100758660_100=NULL,*f_2100758660_103=NULL,*f_2100758660_106=NULL,*f_2100758660_109=NULL,*f_2100758660_127=NULL,*f_2100758660_138=NULL;
static JLONG m_2100758660_1=0,m_2100758660_13=0,m_2100758660_17=0,m_2100758660_41=0,m_2100758660_45=0,m_2100758660_56=0,m_2100758660_59=0,m_2100758660_63=0,m_2100758660_69=0,m_2100758660_73=0,m_2100758660_79=0,m_2100758660_81=0,m_2100758660_83=0,m_2100758660_86=0,m_2100758660_89=0,m_2100758660_96=0,m_2100758660_114=0,m_2100758660_120=0,m_2100758660_123=0,m_2100758660_126=0,m_2100758660_130=0,m_2100758660_136=0;
static Object *c_2100758660_2=NULL,*c_2100758660_8=NULL,*c_2100758660_21=NULL,*c_2100758660_30=NULL,*c_2100758660_49=NULL,*c_2100758660_54=NULL,*c_2100758660_74=NULL,*c_2100758660_115=NULL,*c_2100758660_132=NULL;
void digiplay_Stage2D__init____V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	Object *L0;
	L0=args[0].O;
BB0:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=1;
	  AOTMETHOD(m_2100758660_1,111,1,2); //digiplay/Sprite2D:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m_2100758660_1),entry)))(vm,m_2100758660_1,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Stage2D_setup__Ldigiplay_Point2D__V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	Object *L0,*L1;
	L0=args[0].O;
	L1=args[1].O;
BB0:
	if(!f_2100758660_7) { //designSize;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,7);
	  f_2100758660_7=fld->instance;
	}
	*FIELD_PTR_O(L0,f_2100758660_7->offset) = L1;
	{
	  VAR cargs[]={{.O=L0},{.I=82}};
	  frame->pc=8;
	  AOTVMETHOD(m_2100758660_13,3,193,88,vTableIndex); //digiplay/Stage2D:setFlags:(I)V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_2100758660_13];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=12;
	  AOTVMETHOD(m_2100758660_17,3,194,2,vTableIndex); //digiplay/Stage2D:resize:()V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_2100758660_17];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Stage2D_resize___V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JFLOAT L1,L2,L3,L4,L5,L6,L7,T1,T3,T4;
	JINT T2;
	Object *L0,*T0,*T5;
	L0=args[0].O;
BB0:
	AOTFIELD(f_2100758660_7,3,195,196); //digiplay/Stage2D:designSize:Ldigiplay/Point2D;
	if(!L0) { frame->pc = 1; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_2100758660_7->offset);
	AOTFIELD(f_2100758660_20,6,16,112); //digiplay/Point2D:x:F;
	if(!T0) { frame->pc = 4; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_F(T0,f_2100758660_20->offset);
	L1=T1;
	AOTFIELD(f_2100758660_7,3,195,196); //digiplay/Stage2D:designSize:Ldigiplay/Point2D;
	if(!L0) { frame->pc = 9; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_2100758660_7->offset);
	AOTFIELD(f_2100758660_26,6,18,112); //digiplay/Point2D:y:F;
	if(!T0) { frame->pc = 12; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_F(T0,f_2100758660_26->offset);
	L2=T1;
	T1 = L2 / L1;
	L3=T1;
	AOTFIELD(f_2100758660_29,7,8,4); //digiplay/Platform:screenWidth:I;
	T2 = *((JINT*)(CLS(f_2100758660_29->declaringClass,global) + f_2100758660_29->offset));
	T1=(JFLOAT)T2;
	L4=T1;
	AOTFIELD(f_2100758660_35,7,9,4); //digiplay/Platform:screenHeight:I;
	T2 = *((JINT*)(CLS(f_2100758660_35->declaringClass,global) + f_2100758660_35->offset));
	T1=(JFLOAT)T2;
	L5=T1;
	L6=L4;
	T1 = L6 * L3;
	T2=(JINT)T1;
	T1=(JFLOAT)T2;
	L7=T1;
	T1 = L7 - 2;
	T1 = T1 == L5 ? 0 : (T1 > L5 ? 1 : -1);
	if(T1<=0) goto BB77;
BB54:
	L7=L5;
	T1 = L7 / L3;
	T2=(JINT)T1;
	T1=(JFLOAT)T2;
	L6=T1;
	T1 = L7 / L2;
	if(!f_2100758660_38) { //scaleFactor;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,38);
	  f_2100758660_38=fld->instance;
	}
	*FIELD_PTR_F(L0,f_2100758660_38->offset) = T1;
	goto BB85;
BB77:
	T1 = L6 / L1;
	if(!f_2100758660_38) { //scaleFactor;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,38);
	  f_2100758660_38=fld->instance;
	}
	*FIELD_PTR_F(L0,f_2100758660_38->offset) = T1;
BB85:
	AOTFIELD(f_2100758660_38,3,197,112); //digiplay/Stage2D:scaleFactor:F;
	if(!L0) { frame->pc = 86; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_F(L0,f_2100758660_38->offset);
	AOTFIELD(f_2100758660_7,3,195,196); //digiplay/Stage2D:designSize:Ldigiplay/Point2D;
	if(!L0) { frame->pc = 90; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_2100758660_7->offset);
	AOTFIELD(f_2100758660_20,6,16,112); //digiplay/Point2D:x:F;
	if(!T0) { frame->pc = 93; throw_null(vm); goto __EXCEPTION; }
	T3 = *FIELD_PTR_F(T0,f_2100758660_20->offset);
	T4 = T1 * T3;
	L6=T4;
	AOTFIELD(f_2100758660_38,3,197,112); //digiplay/Stage2D:scaleFactor:F;
	if(!L0) { frame->pc = 100; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_F(L0,f_2100758660_38->offset);
	AOTFIELD(f_2100758660_7,3,195,196); //digiplay/Stage2D:designSize:Ldigiplay/Point2D;
	if(!L0) { frame->pc = 104; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_2100758660_7->offset);
	AOTFIELD(f_2100758660_26,6,18,112); //digiplay/Point2D:y:F;
	if(!T0) { frame->pc = 107; throw_null(vm); goto __EXCEPTION; }
	T3 = *FIELD_PTR_F(T0,f_2100758660_26->offset);
	T4 = T1 * T3;
	L7=T4;
	T1 = L6 / L1;
	{
	  VAR cargs[]={{.O=L0},{.F=T1}};
	  frame->pc=118;
	  AOTVMETHOD(m_2100758660_41,3,116,17,vTableIndex); //digiplay/Stage2D:scaleX:(F)V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_2100758660_41];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	T1 = L7 / L2;
	{
	  VAR cargs[]={{.O=L0},{.F=T1}};
	  frame->pc=126;
	  AOTVMETHOD(m_2100758660_45,3,198,17,vTableIndex); //digiplay/Stage2D:setScaleY:(F)V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_2100758660_45];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	AOTFIELD(f_2100758660_48,28,29,30); //java/lang/System:out:Ljava/io/PrintStream;
	T0 = *((Object**)(CLS(f_2100758660_48->declaringClass,global) + f_2100758660_48->offset));
	AOTCLASS(c_2100758660_54,31);
	T5=alloc_object(vm,c_2100758660_54,0);
	{
	  VAR cargs[]={{.O=T5}};
	  frame->pc=136;
	  AOTMETHOD(m_2100758660_56,31,1,2); //java/lang/StringBuilder:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m_2100758660_56),entry)))(vm,m_2100758660_56,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	{
	  VAR cargs[]={{.O=T5},{.O=aot_strings[199]}};
	  frame->pc=141;
	  AOTVMETHOD(m_2100758660_59,31,33,34,vTableIndex); //java/lang/StringBuilder:append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_2100758660_59];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T5=frame->ret.O;
	}
	
	AOTFIELD(f_2100758660_38,3,197,112); //digiplay/Stage2D:scaleFactor:F;
	if(!L0) { frame->pc = 145; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_F(L0,f_2100758660_38->offset);
	{
	  VAR cargs[]={{.O=T5},{.F=T1}};
	  frame->pc=148;
	  AOTVMETHOD(m_2100758660_63,31,33,200,vTableIndex); //java/lang/StringBuilder:append:(F)Ljava/lang/StringBuilder;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_2100758660_63];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T5=frame->ret.O;
	}
	
	{
	  VAR cargs[]={{.O=T5},{.O=aot_strings[201]}};
	  frame->pc=153;
	  AOTVMETHOD(m_2100758660_59,31,33,34,vTableIndex); //java/lang/StringBuilder:append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_2100758660_59];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T5=frame->ret.O;
	}
	
	{
	  VAR cargs[]={{.O=T5},{.F=L4}};
	  frame->pc=158;
	  AOTVMETHOD(m_2100758660_63,31,33,200,vTableIndex); //java/lang/StringBuilder:append:(F)Ljava/lang/StringBuilder;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_2100758660_63];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T5=frame->ret.O;
	}
	
	{
	  VAR cargs[]={{.O=T5},{.O=aot_strings[16]}};
	  frame->pc=163;
	  AOTVMETHOD(m_2100758660_59,31,33,34,vTableIndex); //java/lang/StringBuilder:append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_2100758660_59];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T5=frame->ret.O;
	}
	
	{
	  VAR cargs[]={{.O=T5},{.F=L5}};
	  frame->pc=168;
	  AOTVMETHOD(m_2100758660_63,31,33,200,vTableIndex); //java/lang/StringBuilder:append:(F)Ljava/lang/StringBuilder;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_2100758660_63];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T5=frame->ret.O;
	}
	
	{
	  VAR cargs[]={{.O=T5}};
	  frame->pc=171;
	  AOTVMETHOD(m_2100758660_69,31,36,37,vTableIndex); //java/lang/StringBuilder:toString:()Ljava/lang/String;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_2100758660_69];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T5=frame->ret.O;
	}
	
	{
	  VAR cargs[]={{.O=T0},{.O=T5}};
	  frame->pc=174;
	  AOTVMETHOD(m_2100758660_73,38,39,40,vTableIndex); //java/io/PrintStream:println:(Ljava/lang/String;)V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_2100758660_73];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	T1 = L4 - L6;
	T3 = T1 / 2;
	{
	  VAR cargs[]={{.O=L0},{.F=T3}};
	  frame->pc=185;
	  AOTVMETHOD(m_2100758660_79,3,16,17,vTableIndex); //digiplay/Stage2D:x:(F)V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_2100758660_79];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	T1 = L5 - L7;
	T3 = T1 / 2;
	{
	  VAR cargs[]={{.O=L0},{.F=T3}};
	  frame->pc=196;
	  AOTVMETHOD(m_2100758660_81,3,18,17,vTableIndex); //digiplay/Stage2D:y:(F)V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_2100758660_81];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	{
	  VAR cargs[]={{.O=L0},{.F=0}};
	  frame->pc=201;
	  AOTVMETHOD(m_2100758660_83,3,202,17,vTableIndex); //digiplay/Stage2D:setPivotX:(F)V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_2100758660_83];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	{
	  VAR cargs[]={{.O=L0},{.F=0}};
	  frame->pc=206;
	  AOTVMETHOD(m_2100758660_86,3,203,17,vTableIndex); //digiplay/Stage2D:setPivotY:(F)V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_2100758660_86];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Stage2D_invalidateSprite__Ldigiplay_Sprite2D__V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	Object *L0,*L1,*L2,*T0;
	L2=args[0].O;
	L0=args[1].O;
BB0:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=1;
	  AOTVMETHOD(m_2100758660_89,111,204,2,vTableIndex); //digiplay/Sprite2D:invalidateContentIfRequired:()V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_2100758660_89];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	AOTFIELD(f_2100758660_92,111,135,133); //digiplay/Sprite2D:firstChild:Ldigiplay/Sprite2D;
	if(!L0) { frame->pc = 5; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_2100758660_92->offset);
	L1=T0;
BB9:
	if(L1==NULL) goto BB26;
BB13:
	{
	  VAR cargs[]={{.O=L2},{.O=L1}};
	  frame->pc=15;
	  AOTVMETHOD(m_2100758660_96,3,205,15,vTableIndex); //digiplay/Stage2D:invalidateSprite:(Ldigiplay/Sprite2D;)V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_2100758660_96];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	AOTFIELD(f_2100758660_100,111,136,133); //digiplay/Sprite2D:next:Ldigiplay/Sprite2D;
	if(!L1) { frame->pc = 19; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L1,f_2100758660_100->offset);
	L1=T0;
	goto BB9;
BB26:
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Stage2D_update___V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JINT L0,T0;
	Object *L1;
	L1=args[0].O;
BB0:
	L0=0;
	AOTFIELD(f_2100758660_103,3,145,4); //digiplay/Stage2D:InvalidationCounter:I;
	T0 = *((JINT*)(CLS(f_2100758660_103->declaringClass,global) + f_2100758660_103->offset));
	if(T0==0) goto BB30;
BB8:
	if(!f_2100758660_103) { //InvalidationCounter;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,103);
	  f_2100758660_103=fld->instance;
	}
	*((JINT*)((CLS(f_2100758660_103->declaringClass,global))+f_2100758660_103->offset)) = 0;
	{
	  VAR cargs[]={{.O=L1},{.O=L1}};
	  frame->pc=14;
	  AOTVMETHOD(m_2100758660_96,3,205,15,vTableIndex); //digiplay/Stage2D:invalidateSprite:(Ldigiplay/Sprite2D;)V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_2100758660_96];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	AOTFIELD(f_2100758660_103,3,145,4); //digiplay/Stage2D:InvalidationCounter:I;
	T0 = *((JINT*)(CLS(f_2100758660_103->declaringClass,global) + f_2100758660_103->offset));
	if(T0==0) goto BB28;
BB23:
	{
	  VAR cargs[]={{.O=L1},{.O=L1}};
	  frame->pc=25;
	  AOTVMETHOD(m_2100758660_96,3,205,15,vTableIndex); //digiplay/Stage2D:invalidateSprite:(Ldigiplay/Sprite2D;)V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_2100758660_96];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
BB28:
	L0=1;
BB30:
	AOTFIELD(f_2100758660_103,3,145,4); //digiplay/Stage2D:InvalidationCounter:I;
	T0 = *((JINT*)(CLS(f_2100758660_103->declaringClass,global) + f_2100758660_103->offset));
	if(T0==0) goto BB58;
BB36:
	if(!f_2100758660_103) { //InvalidationCounter;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,103);
	  f_2100758660_103=fld->instance;
	}
	*((JINT*)((CLS(f_2100758660_103->declaringClass,global))+f_2100758660_103->offset)) = 0;
	{
	  VAR cargs[]={{.O=L1},{.O=L1}};
	  frame->pc=42;
	  AOTVMETHOD(m_2100758660_96,3,205,15,vTableIndex); //digiplay/Stage2D:invalidateSprite:(Ldigiplay/Sprite2D;)V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_2100758660_96];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	AOTFIELD(f_2100758660_103,3,145,4); //digiplay/Stage2D:InvalidationCounter:I;
	T0 = *((JINT*)(CLS(f_2100758660_103->declaringClass,global) + f_2100758660_103->offset));
	if(T0==0) goto BB56;
BB51:
	{
	  VAR cargs[]={{.O=L1},{.O=L1}};
	  frame->pc=53;
	  AOTVMETHOD(m_2100758660_96,3,205,15,vTableIndex); //digiplay/Stage2D:invalidateSprite:(Ldigiplay/Sprite2D;)V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_2100758660_96];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
BB56:
	L0=1;
BB58:
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Stage2D_render___V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JINT T0,T1;
	Object *L0,*T2;
	L0=args[0].O;
BB0:
	AOTFIELD(f_2100758660_106,3,173,4); //digiplay/Stage2D:GLOBAL_FRAME_VERSION:I;
	T0 = *((JINT*)(CLS(f_2100758660_106->declaringClass,global) + f_2100758660_106->offset));
	T1 = T0 + 1;
	if(!f_2100758660_106) { //GLOBAL_FRAME_VERSION;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,106);
	  f_2100758660_106=fld->instance;
	}
	*((JINT*)((CLS(f_2100758660_106->declaringClass,global))+f_2100758660_106->offset)) = T1;
	AOTFIELD(f_2100758660_109,3,171,172); //digiplay/Stage2D:QuadBatch:Ldigiplay/GLQuadBatch;
	T2 = *((Object**)(CLS(f_2100758660_109->declaringClass,global) + f_2100758660_109->offset));
	AOTFIELD(f_2100758660_29,7,8,4); //digiplay/Platform:screenWidth:I;
	T0 = *((JINT*)(CLS(f_2100758660_29->declaringClass,global) + f_2100758660_29->offset));
	AOTFIELD(f_2100758660_35,7,9,4); //digiplay/Platform:screenHeight:I;
	T1 = *((JINT*)(CLS(f_2100758660_35->declaringClass,global) + f_2100758660_35->offset));
	{
	  VAR cargs[]={{.O=T2},{.I=T0},{.I=T1},{.I=1},{.I=-16777216}};
	  frame->pc=20;
	  AOTVMETHOD(m_2100758660_114,180,206,207,vTableIndex); //digiplay/GLQuadBatch:begin:(IIZI)V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_2100758660_114];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=24;
	  AOTVMETHOD(m_2100758660_120,3,208,2,vTableIndex); //digiplay/Stage2D:drawChildren:()V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_2100758660_120];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	AOTFIELD(f_2100758660_109,3,171,172); //digiplay/Stage2D:QuadBatch:Ldigiplay/GLQuadBatch;
	T2 = *((Object**)(CLS(f_2100758660_109->declaringClass,global) + f_2100758660_109->offset));
	{
	  VAR cargs[]={{.O=T2}};
	  frame->pc=30;
	  AOTVMETHOD(m_2100758660_123,180,209,2,vTableIndex); //digiplay/GLQuadBatch:end:()V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_2100758660_123];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Stage2D__clinit____V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	Object *T0;
BB0:
	AOTCLASS(c_2100758660_8,3);
	T0=alloc_object(vm,c_2100758660_8,0);
	{
	  VAR cargs[]={{.O=T0}};
	  frame->pc=4;
	  AOTMETHOD(m_2100758660_126,3,1,2); //digiplay/Stage2D:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m_2100758660_126),entry)))(vm,m_2100758660_126,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	if(!f_2100758660_127) { //I;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,127);
	  f_2100758660_127=fld->instance;
	}
	*((Object**)((CLS(f_2100758660_127->declaringClass,global))+f_2100758660_127->offset)) = T0;
	AOTCLASS(c_2100758660_115,180);
	T0=alloc_object(vm,c_2100758660_115,0);
	{
	  VAR cargs[]={{.O=T0},{.I=4096}};
	  frame->pc=17;
	  AOTMETHOD(m_2100758660_130,180,1,88); //digiplay/GLQuadBatch:<init>:(I)V;
	  ((VM_CALL)(MTH(((Object*)m_2100758660_130),entry)))(vm,m_2100758660_130,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	if(!f_2100758660_109) { //QuadBatch;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,109);
	  f_2100758660_109=fld->instance;
	}
	*((Object**)((CLS(f_2100758660_109->declaringClass,global))+f_2100758660_109->offset)) = T0;
	AOTCLASS(c_2100758660_132,106);
	T0=alloc_object(vm,c_2100758660_132,0);
	{
	  VAR cargs[]={{.O=T0},{.O=aot_strings[210]}};
	  frame->pc=29;
	  AOTMETHOD(m_2100758660_136,106,1,40); //digiplay/GLShader2D:<init>:(Ljava/lang/String;)V;
	  ((VM_CALL)(MTH(((Object*)m_2100758660_136),entry)))(vm,m_2100758660_136,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	if(!f_2100758660_138) { //DefaultShader;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,138);
	  f_2100758660_138=fld->instance;
	}
	*((Object**)((CLS(f_2100758660_138->declaringClass,global))+f_2100758660_138->offset)) = T0;
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
//digiplay/Platform
static Field *f_130471865_7=NULL,*f_130471865_16=NULL,*f_130471865_20=NULL,*f_130471865_23=NULL,*f_130471865_43=NULL;
static JLONG m_130471865_1=0,m_130471865_13=0,m_130471865_27=0,m_130471865_34=0,m_130471865_37=0,m_130471865_47=0,m_130471865_50=0,m_130471865_53=0;
static Object *c_130471865_2=NULL,*c_130471865_8=NULL,*c_130471865_28=NULL,*c_130471865_32=NULL,*c_130471865_38=NULL;
void digiplay_Platform__init____V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	Object *L0;
	L0=args[0].O;
BB0:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=1;
	  AOTMETHOD(m_130471865_1,0,1,2); //java/lang/Object:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m_130471865_1),entry)))(vm,m_130471865_1,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Platform_run__Ldigiplay_Game__V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	Object *L0;
	L0=args[0].O;
BB0:
	if(!f_130471865_7) { //game;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,7);
	  f_130471865_7=fld->instance;
	}
	*((Object**)((CLS(f_130471865_7->declaringClass,global))+f_130471865_7->offset)) = L0;
	{
	  frame->pc=4;
	  AOTMETHOD(m_130471865_13,7,96,2); //digiplay/Platform:run:()V;
	  ((VM_CALL)(MTH(((Object*)m_130471865_13),entry)))(vm,m_130471865_13,NULL);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Platform_resize__II_V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JINT L0,L1,T0;
	Object *L2,*T1;
	Object *caughtException;
	L0=args[0].I;
	L1=args[1].I;
BB0:
	if(!f_130471865_16) { //screenWidth;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,16);
	  f_130471865_16=fld->instance;
	}
	*((JINT*)((CLS(f_130471865_16->declaringClass,global))+f_130471865_16->offset)) = L0;
	if(!f_130471865_20) { //screenHeight;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,20);
	  f_130471865_20=fld->instance;
	}
	*((JINT*)((CLS(f_130471865_20->declaringClass,global))+f_130471865_20->offset)) = L1;
	AOTFIELD(f_130471865_23,7,211,212); //digiplay/Platform:initialized:Z;
	T0 = *((JBOOL*)(CLS(f_130471865_23->declaringClass,global) + f_130471865_23->offset));
	if(T0!=0) goto BB26;
BB14:
	if(!f_130471865_23) { //initialized;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,23);
	  f_130471865_23=fld->instance;
	}
	*((JBOOL*)((CLS(f_130471865_23->declaringClass,global))+f_130471865_23->offset)) = 1;
	AOTFIELD(f_130471865_7,7,213,214); //digiplay/Platform:game:Ldigiplay/Game;
	T1 = *((Object**)(CLS(f_130471865_7->declaringClass,global) + f_130471865_7->offset));
	{
	  VAR cargs[]={{.O=T1}};
	  frame->pc=21;
	  AOTVMETHOD(m_130471865_27,215,206,2,iTableIndex); //digiplay/Game:begin:()V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->itable[m_130471865_27];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
BB26:
	goto BB34;
BB29:
	L2=caughtException;
	{
	  VAR cargs[]={{.O=L2}};
	  frame->pc=31;
	  AOTVMETHOD(m_130471865_34,216,217,2,vTableIndex); //java/lang/Throwable:printStackTrace:()V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_130471865_34];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
BB34:
	vm->FP--;return;
__EXCEPTION: {
	caughtException = vm->exception;
	vm->exception = NULL;
	if(frame->pc >= 0 && frame->pc < 26) {
		AOTCLASS(c_130471865_32,216);
		if(check_cast(vm,caughtException->cls,c_130471865_32))
			goto BB29;
	}
	vm->exception = caughtException;
	vm->FP--; return;
}
}
void digiplay_Platform_step___V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JINT L1,T2;
	JLONG L0,T0,T1;
	Object *L2,*T3;
	Object *caughtException;
BB0:
	{
	  frame->pc=0;
	  AOTMETHOD(m_130471865_37,28,42,43); //java/lang/System:currentTimeMillis:()J;
	  ((VM_CALL)(MTH(((Object*)m_130471865_37),entry)))(vm,m_130471865_37,NULL);
	  if(vm->exception) goto __EXCEPTION;
	  T0=frame->ret.J;
	}
	
	L0=T0;
	AOTFIELD(f_130471865_43,7,218,46); //digiplay/Platform:lastTime:J;
	T0 = *((JLONG*)(CLS(f_130471865_43->declaringClass,global) + f_130471865_43->offset));
	T1 = L0 - T0;
	T2=(JINT)T1;
	L1=T2;
	if(!f_130471865_43) { //lastTime;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,43);
	  f_130471865_43=fld->instance;
	}
	*((JLONG*)((CLS(f_130471865_43->declaringClass,global))+f_130471865_43->offset)) = L0;
	AOTFIELD(f_130471865_7,7,213,214); //digiplay/Platform:game:Ldigiplay/Game;
	T3 = *((Object**)(CLS(f_130471865_7->declaringClass,global) + f_130471865_7->offset));
	{
	  VAR cargs[]={{.O=T3}};
	  frame->pc=18;
	  AOTVMETHOD(m_130471865_47,215,41,2,iTableIndex); //digiplay/Game:update:()V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->itable[m_130471865_47];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	AOTFIELD(f_130471865_7,7,213,214); //digiplay/Platform:game:Ldigiplay/Game;
	T3 = *((Object**)(CLS(f_130471865_7->declaringClass,global) + f_130471865_7->offset));
	{
	  VAR cargs[]={{.O=T3}};
	  frame->pc=26;
	  AOTVMETHOD(m_130471865_50,215,56,2,iTableIndex); //digiplay/Game:render:()V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->itable[m_130471865_50];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	goto BB39;
BB34:
	L2=caughtException;
	{
	  VAR cargs[]={{.O=L2}};
	  frame->pc=36;
	  AOTVMETHOD(m_130471865_34,216,217,2,vTableIndex); //java/lang/Throwable:printStackTrace:()V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_130471865_34];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
BB39:
	{
	  frame->pc=39;
	  AOTMETHOD(m_130471865_53,28,219,2); //java/lang/System:gc:()V;
	  ((VM_CALL)(MTH(((Object*)m_130471865_53),entry)))(vm,m_130471865_53,NULL);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;return;
__EXCEPTION: {
	caughtException = vm->exception;
	vm->exception = NULL;
	if(frame->pc >= 15 && frame->pc < 31) {
		AOTCLASS(c_130471865_32,216);
		if(check_cast(vm,caughtException->cls,c_130471865_32))
			goto BB34;
	}
	vm->exception = caughtException;
	vm->FP--; return;
}
}
void digiplay_Platform__clinit____V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JLONG T0;
BB0:
	{
	  frame->pc=0;
	  AOTMETHOD(m_130471865_37,28,42,43); //java/lang/System:currentTimeMillis:()J;
	  ((VM_CALL)(MTH(((Object*)m_130471865_37),entry)))(vm,m_130471865_37,NULL);
	  if(vm->exception) goto __EXCEPTION;
	  T0=frame->ret.J;
	}
	
	if(!f_130471865_43) { //lastTime;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,43);
	  f_130471865_43=fld->instance;
	}
	*((JLONG*)((CLS(f_130471865_43->declaringClass,global))+f_130471865_43->offset)) = T0;
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
//digiplay/Metal
static JLONG m1466702771_1=0;
static Object *c1466702771_2=NULL,*c1466702771_7=NULL;
void digiplay_Metal__init____V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	Object *L0;
	L0=args[0].O;
BB0:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=1;
	  AOTMETHOD(m1466702771_1,0,1,2); //java/lang/Object:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m1466702771_1),entry)))(vm,m1466702771_1,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
//digiplay/Mat3D
static JLONG m1466582141_1=0;
static Object *c1466582141_2=NULL,*c1466582141_7=NULL;
void digiplay_Mat3D__init____V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	Object *L0;
	L0=args[0].O;
BB0:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=1;
	  AOTMETHOD(m1466582141_1,0,1,2); //java/lang/Object:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m1466582141_1),entry)))(vm,m1466582141_1,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
//digiplay/Asset
static Field *f1456036764_19=NULL;
static JLONG m1456036764_1=0,m1456036764_7=0,m1456036764_13=0;
static Object *c1456036764_2=NULL,*c1456036764_8=NULL,*c1456036764_14=NULL,*c1456036764_23=NULL;
void digiplay_Asset__init____V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	Object *L0;
	L0=args[0].O;
BB0:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=1;
	  AOTMETHOD(m1456036764_1,0,1,2); //java/lang/Object:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m1456036764_1),entry)))(vm,m1456036764_1,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Asset_load__Ljava_lang_String__V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JLONG T0;
	Object *L0,*L1;
	L0=args[0].O;
	L1=args[1].O;
BB0:
	{
	  VAR cargs[]={{.O=L0},{.O=L1}};
	  frame->pc=2;
	  AOTMETHOD(m1456036764_7,220,221,108); //digiplay/Asset:loadBytes:(Ljava/lang/String;)J;
	  ((VM_CALL)(MTH(((Object*)m1456036764_7),entry)))(vm,m1456036764_7,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T0=frame->ret.J;
	}
	
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Asset_complete__JI_V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
BB0:
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Asset_loaded__JI_V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JINT L0;
	JLONG L2;
	Object *L1,*T0;
	L1=args[0].O;
	L2=args[1].J;
	L0=args[2].I;
BB0:
	if(L0<=0) goto BB13;
BB4:
	{
	  VAR cargs[]={{.J=L2},{.I=L0}};
	  frame->pc=7;
	  AOTMETHOD(m1456036764_13,101,222,223); //gamavm/VM:wrapBytes:(JI)[B;
	  ((VM_CALL)(MTH(((Object*)m1456036764_13),entry)))(vm,m1456036764_13,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T0=frame->ret.O;
	}
	
	if(!f1456036764_19) { //data;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,19);
	  f1456036764_19=fld->instance;
	}
	*FIELD_PTR_O(L1,f1456036764_19->offset) = T0;
BB13:
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
//digiplay/GLTexture
static JLONG m336896834_1=0;
static Object *c336896834_2=NULL,*c336896834_7=NULL;
void digiplay_GLTexture__init____V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	Object *L0;
	L0=args[0].O;
BB0:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=1;
	  AOTMETHOD(m336896834_1,0,1,2); //java/lang/Object:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m336896834_1),entry)))(vm,m336896834_1,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
//digiplay/Action1
static Object *c_1365033369_1=NULL,*c_1365033369_3=NULL;
//digiplay/Matrix3D
static Field *f_1694338618_7=NULL,*f_1694338618_32=NULL,*f_1694338618_45=NULL,*f_1694338618_53=NULL,*f_1694338618_58=NULL,*f_1694338618_61=NULL,*f_1694338618_64=NULL,*f_1694338618_67=NULL,*f_1694338618_70=NULL,*f_1694338618_73=NULL,*f_1694338618_81=NULL,*f_1694338618_94=NULL,*f_1694338618_106=NULL,*f_1694338618_137=NULL;
static JLONG m_1694338618_1=0,m_1694338618_13=0,m_1694338618_22=0,m_1694338618_28=0,m_1694338618_37=0,m_1694338618_41=0,m_1694338618_49=0,m_1694338618_77=0,m_1694338618_84=0,m_1694338618_87=0,m_1694338618_90=0,m_1694338618_100=0,m_1694338618_103=0,m_1694338618_114=0,m_1694338618_115=0,m_1694338618_121=0,m_1694338618_126=0,m_1694338618_130=0,m_1694338618_136=0,m_1694338618_143=0;
static Object *c_1694338618_2=NULL,*c_1694338618_8=NULL,*c_1694338618_16=NULL,*c_1694338618_54=NULL,*c_1694338618_107=NULL,*c_1694338618_112=NULL,*c_1694338618_131=NULL,*c_1694338618_231=NULL;
void digiplay_Matrix3D__init____V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	Object *L0,*T0;
	L0=args[0].O;
BB0:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=1;
	  AOTMETHOD(m_1694338618_1,0,1,2); //java/lang/Object:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m_1694338618_1),entry)))(vm,m_1694338618_1,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	T0 = alloc_array_F(vm,16,0);
	if(!f_1694338618_7) { //raw;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,7);
	  f_1694338618_7=fld->instance;
	}
	*FIELD_PTR_O(L0,f_1694338618_7->offset) = T0;
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=13;
	  AOTVMETHOD(m_1694338618_13,224,150,2,vTableIndex); //digiplay/Matrix3D:identity:()V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_1694338618_13];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Matrix3D_identity___V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	Object *L0,*T0;
	L0=args[0].O;
BB0:
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 1; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T0) { throw_null(vm); goto __EXCEPTION;}
	if(0 < 0 || 0 >= T0->length) { throw_arrayounds(vm,0,T0->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T0)[0] = 1;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 8; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T0) { throw_null(vm); goto __EXCEPTION;}
	if(4 < 0 || 4 >= T0->length) { throw_arrayounds(vm,4,T0->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T0)[4] = 0;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 15; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T0) { throw_null(vm); goto __EXCEPTION;}
	if(8 < 0 || 8 >= T0->length) { throw_arrayounds(vm,8,T0->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T0)[8] = 0;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 23; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T0) { throw_null(vm); goto __EXCEPTION;}
	if(12 < 0 || 12 >= T0->length) { throw_arrayounds(vm,12,T0->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T0)[12] = 0;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 31; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T0) { throw_null(vm); goto __EXCEPTION;}
	if(1 < 0 || 1 >= T0->length) { throw_arrayounds(vm,1,T0->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T0)[1] = 0;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 38; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T0) { throw_null(vm); goto __EXCEPTION;}
	if(5 < 0 || 5 >= T0->length) { throw_arrayounds(vm,5,T0->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T0)[5] = 1;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 45; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T0) { throw_null(vm); goto __EXCEPTION;}
	if(9 < 0 || 9 >= T0->length) { throw_arrayounds(vm,9,T0->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T0)[9] = 0;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 53; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T0) { throw_null(vm); goto __EXCEPTION;}
	if(13 < 0 || 13 >= T0->length) { throw_arrayounds(vm,13,T0->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T0)[13] = 0;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 61; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T0) { throw_null(vm); goto __EXCEPTION;}
	if(2 < 0 || 2 >= T0->length) { throw_arrayounds(vm,2,T0->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T0)[2] = 0;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 68; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T0) { throw_null(vm); goto __EXCEPTION;}
	if(6 < 0 || 6 >= T0->length) { throw_arrayounds(vm,6,T0->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T0)[6] = 0;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 76; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T0) { throw_null(vm); goto __EXCEPTION;}
	if(10 < 0 || 10 >= T0->length) { throw_arrayounds(vm,10,T0->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T0)[10] = 1;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 84; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T0) { throw_null(vm); goto __EXCEPTION;}
	if(14 < 0 || 14 >= T0->length) { throw_arrayounds(vm,14,T0->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T0)[14] = 0;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 92; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T0) { throw_null(vm); goto __EXCEPTION;}
	if(3 < 0 || 3 >= T0->length) { throw_arrayounds(vm,3,T0->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T0)[3] = 0;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 99; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T0) { throw_null(vm); goto __EXCEPTION;}
	if(7 < 0 || 7 >= T0->length) { throw_arrayounds(vm,7,T0->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T0)[7] = 0;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 107; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T0) { throw_null(vm); goto __EXCEPTION;}
	if(11 < 0 || 11 >= T0->length) { throw_arrayounds(vm,11,T0->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T0)[11] = 0;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 115; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T0) { throw_null(vm); goto __EXCEPTION;}
	if(15 < 0 || 15 >= T0->length) { throw_arrayounds(vm,15,T0->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T0)[15] = 1;
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Matrix3D_set__FFFFFFFFFFFFFFFF_V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JFLOAT L1,L2,L3,L4,L5,L6,L7,L8,L9,L10,L11,L12,L13,L14,L15,L16;
	Object *L0,*T0;
	L0=args[0].O;
	L1=args[1].F;
	L2=args[2].F;
	L3=args[3].F;
	L4=args[4].F;
	L5=args[5].F;
	L6=args[6].F;
	L7=args[7].F;
	L8=args[8].F;
	L9=args[9].F;
	L10=args[10].F;
	L11=args[11].F;
	L12=args[12].F;
	L13=args[13].F;
	L14=args[14].F;
	L15=args[15].F;
	L16=args[16].F;
BB0:
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 1; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T0) { throw_null(vm); goto __EXCEPTION;}
	if(0 < 0 || 0 >= T0->length) { throw_arrayounds(vm,0,T0->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T0)[0] = L1;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 8; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T0) { throw_null(vm); goto __EXCEPTION;}
	if(4 < 0 || 4 >= T0->length) { throw_arrayounds(vm,4,T0->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T0)[4] = L2;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 15; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T0) { throw_null(vm); goto __EXCEPTION;}
	if(8 < 0 || 8 >= T0->length) { throw_arrayounds(vm,8,T0->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T0)[8] = L3;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 23; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T0) { throw_null(vm); goto __EXCEPTION;}
	if(12 < 0 || 12 >= T0->length) { throw_arrayounds(vm,12,T0->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T0)[12] = L4;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 32; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T0) { throw_null(vm); goto __EXCEPTION;}
	if(1 < 0 || 1 >= T0->length) { throw_arrayounds(vm,1,T0->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T0)[1] = L5;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 40; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T0) { throw_null(vm); goto __EXCEPTION;}
	if(5 < 0 || 5 >= T0->length) { throw_arrayounds(vm,5,T0->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T0)[5] = L6;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 48; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T0) { throw_null(vm); goto __EXCEPTION;}
	if(9 < 0 || 9 >= T0->length) { throw_arrayounds(vm,9,T0->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T0)[9] = L7;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 57; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T0) { throw_null(vm); goto __EXCEPTION;}
	if(13 < 0 || 13 >= T0->length) { throw_arrayounds(vm,13,T0->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T0)[13] = L8;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 66; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T0) { throw_null(vm); goto __EXCEPTION;}
	if(2 < 0 || 2 >= T0->length) { throw_arrayounds(vm,2,T0->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T0)[2] = L9;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 74; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T0) { throw_null(vm); goto __EXCEPTION;}
	if(6 < 0 || 6 >= T0->length) { throw_arrayounds(vm,6,T0->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T0)[6] = L10;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 83; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T0) { throw_null(vm); goto __EXCEPTION;}
	if(10 < 0 || 10 >= T0->length) { throw_arrayounds(vm,10,T0->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T0)[10] = L11;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 92; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T0) { throw_null(vm); goto __EXCEPTION;}
	if(14 < 0 || 14 >= T0->length) { throw_arrayounds(vm,14,T0->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T0)[14] = L12;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 101; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T0) { throw_null(vm); goto __EXCEPTION;}
	if(3 < 0 || 3 >= T0->length) { throw_arrayounds(vm,3,T0->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T0)[3] = L13;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 109; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T0) { throw_null(vm); goto __EXCEPTION;}
	if(7 < 0 || 7 >= T0->length) { throw_arrayounds(vm,7,T0->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T0)[7] = L14;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 118; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T0) { throw_null(vm); goto __EXCEPTION;}
	if(11 < 0 || 11 >= T0->length) { throw_arrayounds(vm,11,T0->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T0)[11] = L15;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 127; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T0) { throw_null(vm); goto __EXCEPTION;}
	if(15 < 0 || 15 >= T0->length) { throw_arrayounds(vm,15,T0->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T0)[15] = L16;
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Matrix3D_set2__FFFFFFFFFFFFFFFF_V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JFLOAT L1,L2,L3,L4,L5,L6,L7,L8,L9,L10,L11,L12,L13,L14,L15,L16;
	Object *L0,*T0;
	L0=args[0].O;
	L1=args[1].F;
	L2=args[2].F;
	L3=args[3].F;
	L4=args[4].F;
	L5=args[5].F;
	L6=args[6].F;
	L7=args[7].F;
	L8=args[8].F;
	L9=args[9].F;
	L10=args[10].F;
	L11=args[11].F;
	L12=args[12].F;
	L13=args[13].F;
	L14=args[14].F;
	L15=args[15].F;
	L16=args[16].F;
BB0:
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 1; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T0) { throw_null(vm); goto __EXCEPTION;}
	if(0 < 0 || 0 >= T0->length) { throw_arrayounds(vm,0,T0->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T0)[0] = L1;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 8; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T0) { throw_null(vm); goto __EXCEPTION;}
	if(1 < 0 || 1 >= T0->length) { throw_arrayounds(vm,1,T0->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T0)[1] = L2;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 15; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T0) { throw_null(vm); goto __EXCEPTION;}
	if(2 < 0 || 2 >= T0->length) { throw_arrayounds(vm,2,T0->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T0)[2] = L3;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 22; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T0) { throw_null(vm); goto __EXCEPTION;}
	if(3 < 0 || 3 >= T0->length) { throw_arrayounds(vm,3,T0->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T0)[3] = L4;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 30; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T0) { throw_null(vm); goto __EXCEPTION;}
	if(4 < 0 || 4 >= T0->length) { throw_arrayounds(vm,4,T0->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T0)[4] = L5;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 38; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T0) { throw_null(vm); goto __EXCEPTION;}
	if(5 < 0 || 5 >= T0->length) { throw_arrayounds(vm,5,T0->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T0)[5] = L6;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 46; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T0) { throw_null(vm); goto __EXCEPTION;}
	if(6 < 0 || 6 >= T0->length) { throw_arrayounds(vm,6,T0->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T0)[6] = L7;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 55; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T0) { throw_null(vm); goto __EXCEPTION;}
	if(7 < 0 || 7 >= T0->length) { throw_arrayounds(vm,7,T0->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T0)[7] = L8;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 64; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T0) { throw_null(vm); goto __EXCEPTION;}
	if(8 < 0 || 8 >= T0->length) { throw_arrayounds(vm,8,T0->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T0)[8] = L9;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 73; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T0) { throw_null(vm); goto __EXCEPTION;}
	if(9 < 0 || 9 >= T0->length) { throw_arrayounds(vm,9,T0->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T0)[9] = L10;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 82; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T0) { throw_null(vm); goto __EXCEPTION;}
	if(10 < 0 || 10 >= T0->length) { throw_arrayounds(vm,10,T0->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T0)[10] = L11;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 91; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T0) { throw_null(vm); goto __EXCEPTION;}
	if(11 < 0 || 11 >= T0->length) { throw_arrayounds(vm,11,T0->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T0)[11] = L12;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 100; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T0) { throw_null(vm); goto __EXCEPTION;}
	if(12 < 0 || 12 >= T0->length) { throw_arrayounds(vm,12,T0->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T0)[12] = L13;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 109; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T0) { throw_null(vm); goto __EXCEPTION;}
	if(13 < 0 || 13 >= T0->length) { throw_arrayounds(vm,13,T0->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T0)[13] = L14;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 118; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T0) { throw_null(vm); goto __EXCEPTION;}
	if(14 < 0 || 14 >= T0->length) { throw_arrayounds(vm,14,T0->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T0)[14] = L15;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 127; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T0) { throw_null(vm); goto __EXCEPTION;}
	if(15 < 0 || 15 >= T0->length) { throw_arrayounds(vm,15,T0->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T0)[15] = L16;
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Matrix3D_perspective__FFFF_V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JDOUBLE T0,T1;
	JFLOAT L1,L2,L3,L4,L5,L6,L7,T2,T3,T4;
	Object *L0,*T5;
	L0=args[0].O;
	L4=args[1].F;
	L3=args[2].F;
	L1=args[3].F;
	L7=args[4].F;
BB0:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=1;
	  AOTVMETHOD(m_1694338618_13,224,150,2,vTableIndex); //digiplay/Matrix3D:identity:()V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_1694338618_13];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	T0=(JDOUBLE)L1;
	T1 = T0 * 0.017453292519943295;
	T0 = T1 / 2.0;
	{
	  VAR cargs[]={{.D=T0}};
	  frame->pc=15;
	  AOTMETHOD(m_1694338618_22,19,227,161); //java/lang/Math:tan:(D)D;
	  ((VM_CALL)(MTH(((Object*)m_1694338618_22),entry)))(vm,m_1694338618_22,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T0=frame->ret.D;
	}
	
	T1 = 1 / T0;
	T2=(JFLOAT)T1;
	L2=T2;
	T2 = L3 + L4;
	T3 = L4 - L3;
	T4 = T2 / T3;
	L5=T4;
	T2 = 2 * L3;
	T3 = T2 * L4;
	T2 = L4 - L3;
	T4 = T3 / T2;
	L6=T4;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 43; throw_null(vm); goto __EXCEPTION; }
	T5 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	T2 = L2 / L7;
	if(!T5) { throw_null(vm); goto __EXCEPTION;}
	if(0 < 0 || 0 >= T5->length) { throw_arrayounds(vm,0,T5->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T5)[0] = T2;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 54; throw_null(vm); goto __EXCEPTION; }
	T5 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T5) { throw_null(vm); goto __EXCEPTION;}
	if(1 < 0 || 1 >= T5->length) { throw_arrayounds(vm,1,T5->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T5)[1] = 0;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 61; throw_null(vm); goto __EXCEPTION; }
	T5 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T5) { throw_null(vm); goto __EXCEPTION;}
	if(2 < 0 || 2 >= T5->length) { throw_arrayounds(vm,2,T5->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T5)[2] = 0;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 68; throw_null(vm); goto __EXCEPTION; }
	T5 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T5) { throw_null(vm); goto __EXCEPTION;}
	if(3 < 0 || 3 >= T5->length) { throw_arrayounds(vm,3,T5->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T5)[3] = 0;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 75; throw_null(vm); goto __EXCEPTION; }
	T5 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T5) { throw_null(vm); goto __EXCEPTION;}
	if(4 < 0 || 4 >= T5->length) { throw_arrayounds(vm,4,T5->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T5)[4] = 0;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 82; throw_null(vm); goto __EXCEPTION; }
	T5 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T5) { throw_null(vm); goto __EXCEPTION;}
	if(5 < 0 || 5 >= T5->length) { throw_arrayounds(vm,5,T5->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T5)[5] = L2;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 90; throw_null(vm); goto __EXCEPTION; }
	T5 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T5) { throw_null(vm); goto __EXCEPTION;}
	if(6 < 0 || 6 >= T5->length) { throw_arrayounds(vm,6,T5->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T5)[6] = 0;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 98; throw_null(vm); goto __EXCEPTION; }
	T5 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T5) { throw_null(vm); goto __EXCEPTION;}
	if(7 < 0 || 7 >= T5->length) { throw_arrayounds(vm,7,T5->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T5)[7] = 0;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 106; throw_null(vm); goto __EXCEPTION; }
	T5 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T5) { throw_null(vm); goto __EXCEPTION;}
	if(8 < 0 || 8 >= T5->length) { throw_arrayounds(vm,8,T5->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T5)[8] = 0;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 114; throw_null(vm); goto __EXCEPTION; }
	T5 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T5) { throw_null(vm); goto __EXCEPTION;}
	if(9 < 0 || 9 >= T5->length) { throw_arrayounds(vm,9,T5->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T5)[9] = 0;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 122; throw_null(vm); goto __EXCEPTION; }
	T5 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T5) { throw_null(vm); goto __EXCEPTION;}
	if(10 < 0 || 10 >= T5->length) { throw_arrayounds(vm,10,T5->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T5)[10] = L5;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 131; throw_null(vm); goto __EXCEPTION; }
	T5 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T5) { throw_null(vm); goto __EXCEPTION;}
	if(11 < 0 || 11 >= T5->length) { throw_arrayounds(vm,11,T5->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T5)[11] = -1.0;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 140; throw_null(vm); goto __EXCEPTION; }
	T5 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T5) { throw_null(vm); goto __EXCEPTION;}
	if(12 < 0 || 12 >= T5->length) { throw_arrayounds(vm,12,T5->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T5)[12] = 0;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 148; throw_null(vm); goto __EXCEPTION; }
	T5 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T5) { throw_null(vm); goto __EXCEPTION;}
	if(13 < 0 || 13 >= T5->length) { throw_arrayounds(vm,13,T5->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T5)[13] = 0;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 156; throw_null(vm); goto __EXCEPTION; }
	T5 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T5) { throw_null(vm); goto __EXCEPTION;}
	if(14 < 0 || 14 >= T5->length) { throw_arrayounds(vm,14,T5->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T5)[14] = L6;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 165; throw_null(vm); goto __EXCEPTION; }
	T5 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T5) { throw_null(vm); goto __EXCEPTION;}
	if(15 < 0 || 15 >= T5->length) { throw_arrayounds(vm,15,T5->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T5)[15] = 0;
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Matrix3D_orthographic__FFFFFF_V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JFLOAT L1,L2,L3,L4,L5,L6,L7,L8,L9,L10,L11,L12,T0,T1,T2;
	Object *L0,*T3;
	L0=args[0].O;
	L2=args[1].F;
	L1=args[2].F;
	L5=args[3].F;
	L4=args[4].F;
	L8=args[5].F;
	L7=args[6].F;
BB0:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=1;
	  AOTVMETHOD(m_1694338618_13,224,150,2,vTableIndex); //digiplay/Matrix3D:identity:()V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_1694338618_13];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	T0 = L1 - L2;
	T1 = 2 / T0;
	L3=T1;
	T0 = L4 - L5;
	T1 = 2 / T0;
	L6=T1;
	T0 = L7 - L8;
	T1 = -2.0 / T0;
	L9=T1;
	T0 = L1 + L2;
	T1=-T0;
	T0 = L1 - L2;
	T2 = T1 / T0;
	L10=T2;
	T0 = L4 + L5;
	T1=-T0;
	T0 = L4 - L5;
	T2 = T1 / T0;
	L11=T2;
	T0 = L7 + L8;
	T1=-T0;
	T0 = L7 - L8;
	T2 = T1 / T0;
	L12=T2;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 66; throw_null(vm); goto __EXCEPTION; }
	T3 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T3) { throw_null(vm); goto __EXCEPTION;}
	if(0 < 0 || 0 >= T3->length) { throw_arrayounds(vm,0,T3->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T3)[0] = L3;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 74; throw_null(vm); goto __EXCEPTION; }
	T3 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T3) { throw_null(vm); goto __EXCEPTION;}
	if(1 < 0 || 1 >= T3->length) { throw_arrayounds(vm,1,T3->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T3)[1] = 0;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 81; throw_null(vm); goto __EXCEPTION; }
	T3 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T3) { throw_null(vm); goto __EXCEPTION;}
	if(2 < 0 || 2 >= T3->length) { throw_arrayounds(vm,2,T3->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T3)[2] = 0;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 88; throw_null(vm); goto __EXCEPTION; }
	T3 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T3) { throw_null(vm); goto __EXCEPTION;}
	if(3 < 0 || 3 >= T3->length) { throw_arrayounds(vm,3,T3->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T3)[3] = 0;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 95; throw_null(vm); goto __EXCEPTION; }
	T3 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T3) { throw_null(vm); goto __EXCEPTION;}
	if(4 < 0 || 4 >= T3->length) { throw_arrayounds(vm,4,T3->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T3)[4] = 0;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 102; throw_null(vm); goto __EXCEPTION; }
	T3 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T3) { throw_null(vm); goto __EXCEPTION;}
	if(5 < 0 || 5 >= T3->length) { throw_arrayounds(vm,5,T3->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T3)[5] = L6;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 110; throw_null(vm); goto __EXCEPTION; }
	T3 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T3) { throw_null(vm); goto __EXCEPTION;}
	if(6 < 0 || 6 >= T3->length) { throw_arrayounds(vm,6,T3->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T3)[6] = 0;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 118; throw_null(vm); goto __EXCEPTION; }
	T3 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T3) { throw_null(vm); goto __EXCEPTION;}
	if(7 < 0 || 7 >= T3->length) { throw_arrayounds(vm,7,T3->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T3)[7] = 0;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 126; throw_null(vm); goto __EXCEPTION; }
	T3 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T3) { throw_null(vm); goto __EXCEPTION;}
	if(8 < 0 || 8 >= T3->length) { throw_arrayounds(vm,8,T3->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T3)[8] = 0;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 134; throw_null(vm); goto __EXCEPTION; }
	T3 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T3) { throw_null(vm); goto __EXCEPTION;}
	if(9 < 0 || 9 >= T3->length) { throw_arrayounds(vm,9,T3->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T3)[9] = 0;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 142; throw_null(vm); goto __EXCEPTION; }
	T3 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T3) { throw_null(vm); goto __EXCEPTION;}
	if(10 < 0 || 10 >= T3->length) { throw_arrayounds(vm,10,T3->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T3)[10] = L9;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 151; throw_null(vm); goto __EXCEPTION; }
	T3 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T3) { throw_null(vm); goto __EXCEPTION;}
	if(11 < 0 || 11 >= T3->length) { throw_arrayounds(vm,11,T3->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T3)[11] = 0;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 159; throw_null(vm); goto __EXCEPTION; }
	T3 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T3) { throw_null(vm); goto __EXCEPTION;}
	if(12 < 0 || 12 >= T3->length) { throw_arrayounds(vm,12,T3->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T3)[12] = L10;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 168; throw_null(vm); goto __EXCEPTION; }
	T3 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T3) { throw_null(vm); goto __EXCEPTION;}
	if(13 < 0 || 13 >= T3->length) { throw_arrayounds(vm,13,T3->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T3)[13] = L11;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 177; throw_null(vm); goto __EXCEPTION; }
	T3 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T3) { throw_null(vm); goto __EXCEPTION;}
	if(14 < 0 || 14 >= T3->length) { throw_arrayounds(vm,14,T3->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T3)[14] = L12;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 186; throw_null(vm); goto __EXCEPTION; }
	T3 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T3) { throw_null(vm); goto __EXCEPTION;}
	if(15 < 0 || 15 >= T3->length) { throw_arrayounds(vm,15,T3->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T3)[15] = 1;
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Matrix3D_setup__FFFFFF_V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JFLOAT L1,L2,L3,L4,L5,L6;
	Object *L0;
	L0=args[0].O;
	L1=args[1].F;
	L2=args[2].F;
	L3=args[3].F;
	L4=args[4].F;
	L5=args[5].F;
	L6=args[6].F;
BB0:
	{
	  VAR cargs[]={{.O=L0},{.F=L1},{.F=L2},{.F=L3},{.F=L4},{.F=L5},{.F=L6},{.I=0}};
	  frame->pc=11;
	  AOTVMETHOD(m_1694338618_28,224,11,228,vTableIndex); //digiplay/Matrix3D:setup:(FFFFFFZ)V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_1694338618_28];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Matrix3D_setup__FFFFFFZ_V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JFLOAT L1,L2,L3,L4,L5,L6,L7,L8,L9,L10,L11,L12,L13,L14,L16,L17,T0,T1,T3,T4,S0F;
	JINT L15,S1I,S3I;
	Object *L0,*T2,*S2O;
	L0=args[0].O;
	L16=args[1].F;
	L17=args[2].F;
	L1=args[3].F;
	L3=args[4].F;
	L7=args[5].F;
	L9=args[6].F;
	L15=args[7].I;
BB0:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=1;
	  AOTVMETHOD(m_1694338618_13,224,150,2,vTableIndex); //digiplay/Matrix3D:identity:()V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_1694338618_13];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	L2=L1;
	L4=L3;
	AOTFIELD(f_1694338618_32,224,229,112); //digiplay/Matrix3D:TAN05:F;
	T0 = *((JFLOAT*)(CLS(f_1694338618_32->declaringClass,global) + f_1694338618_32->offset));
	T1 = L2 / T0;
	L5=T1;
	T0 = L5 == 0 ? 0 : (L5 > 0 ? 1 : -1);
	if(T0>=0) goto BB32;
BB26:
	T0=-L5;
	/*spill*/S0F=T0;
	goto BB34;
BB32:
	/*spill*/S0F=L5;
BB34:
	L6=S0F;
	T0 = L2 / 2;
	T1 = L7 - T0;
	L8=T1;
	T0 = L4 / 2;
	T1 = L9 - T0;
	L10=T1;
	T0 = L6 * 20.0;
	L11=T0;
	L12=1;
	T0 = L2 / L1;
	L13=T0;
	T0 = L4 / L3;
	L14=T0;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 78; throw_null(vm); goto __EXCEPTION; }
	T2 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	T0 = 2 * L6;
	T1 = T0 / L2;
	if(!T2) { throw_null(vm); goto __EXCEPTION;}
	if(0 < 0 || 0 >= T2->length) { throw_arrayounds(vm,0,T2->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T2)[0] = T1;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 91; throw_null(vm); goto __EXCEPTION; }
	T2 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	T0 = 2 * L6;
	T1 = T0 / L4;
	/*spill*/S0F=T1;
	/*spill*/S1I=5;
	/*spill*/S2O=T2;
	if(L15==0) goto BB111;
BB107:
	/*spill*/S3I=1;
	goto BB112;
BB111:
	/*spill*/S3I=-1;
BB112:
	T0=(JFLOAT)S3I;
	T1 = S0F * T0;
	if(!S2O) { throw_null(vm); goto __EXCEPTION;}
	if(S1I < 0 || S1I >= S2O->length) { throw_arrayounds(vm,S1I,S2O->length); goto __EXCEPTION; }
	ARRAY_DATA_F(S2O)[S1I] = T1;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 116; throw_null(vm); goto __EXCEPTION; }
	T2 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	T0 = L11 - L12;
	T1 = L11 / T0;
	if(!T2) { throw_null(vm); goto __EXCEPTION;}
	if(10 < 0 || 10 >= T2->length) { throw_arrayounds(vm,10,T2->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T2)[10] = T1;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 131; throw_null(vm); goto __EXCEPTION; }
	T2 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	T0=-L11;
	T1 = T0 * L12;
	T0 = L11 - L12;
	T3 = T1 / T0;
	if(!T2) { throw_null(vm); goto __EXCEPTION;}
	if(14 < 0 || 14 >= T2->length) { throw_arrayounds(vm,14,T2->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T2)[14] = T3;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 150; throw_null(vm); goto __EXCEPTION; }
	T2 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T2) { throw_null(vm); goto __EXCEPTION;}
	if(11 < 0 || 11 >= T2->length) { throw_arrayounds(vm,11,T2->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T2)[11] = 1;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 158; throw_null(vm); goto __EXCEPTION; }
	T2 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T2) { throw_null(vm); goto __EXCEPTION;}
	if(0 < 0 || 0 >= T2->length) { throw_arrayounds(vm,0,T2->length); goto __EXCEPTION; }
	T0 = ARRAY_DATA_F(T2)[0];
	T1 = T0 * L13;
	if(!T2) { throw_null(vm); goto __EXCEPTION;}
	if(0 < 0 || 0 >= T2->length) { throw_arrayounds(vm,0,T2->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T2)[0] = T1;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 169; throw_null(vm); goto __EXCEPTION; }
	T2 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	if(!T2) { throw_null(vm); goto __EXCEPTION;}
	if(5 < 0 || 5 >= T2->length) { throw_arrayounds(vm,5,T2->length); goto __EXCEPTION; }
	T0 = ARRAY_DATA_F(T2)[5];
	T1 = T0 * L14;
	if(!T2) { throw_null(vm); goto __EXCEPTION;}
	if(5 < 0 || 5 >= T2->length) { throw_arrayounds(vm,5,T2->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T2)[5] = T1;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 180; throw_null(vm); goto __EXCEPTION; }
	T2 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	T0 = L13 - 1;
	T1 = 2 * L13;
	T3 = L16 - L8;
	T4 = T1 * T3;
	T1 = T4 / L2;
	T3 = T0 - T1;
	if(!T2) { throw_null(vm); goto __EXCEPTION;}
	if(8 < 0 || 8 >= T2->length) { throw_arrayounds(vm,8,T2->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T2)[8] = T3;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 204; throw_null(vm); goto __EXCEPTION; }
	T2 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	T0=-L14;
	T1 = T0 + 1;
	T0 = 2 * L14;
	T3 = L17 - L10;
	T4 = T0 * T3;
	T0 = T4 / L4;
	T3 = T1 + T0;
	if(!T2) { throw_null(vm); goto __EXCEPTION;}
	if(9 < 0 || 9 >= T2->length) { throw_arrayounds(vm,9,T2->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T2)[9] = T3;
	T0=-L2;
	T1 = T0 / 2;
	T0 = T1 - L8;
	T1=-L4;
	T3 = T1 / 2;
	T1 = T3 - L10;
	{
	  VAR cargs[]={{.O=L0},{.F=T0},{.F=T1},{.F=L6}};
	  frame->pc=247;
	  AOTVMETHOD(m_1694338618_37,224,230,231,vTableIndex); //digiplay/Matrix3D:prependTranslation:(FFF)V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_1694338618_37];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Matrix3D_prepend__Ldigiplay_Matrix3D__V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	Object *L0,*L1;
	L0=args[0].O;
	L1=args[1].O;
BB0:
	{
	  VAR cargs[]={{.O=L0},{.O=L1},{.O=L0}};
	  frame->pc=3;
	  AOTMETHOD(m_1694338618_41,224,232,233); //digiplay/Matrix3D:multiply:(Ldigiplay/Matrix3D;Ldigiplay/Matrix3D;Ldigiplay/Matrix3D;)V;
	  ((VM_CALL)(MTH(((Object*)m_1694338618_41),entry)))(vm,m_1694338618_41,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Matrix3D_prependTranslation__FFF_V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JFLOAT L0,L1,L2;
	Object *L3,*T0,*T1;
	L3=args[0].O;
	L0=args[1].F;
	L1=args[2].F;
	L2=args[3].F;
BB0:
	AOTFIELD(f_1694338618_45,224,234,235); //digiplay/Matrix3D:TRAMAT:Ldigiplay/Matrix3D;
	T0 = *((Object**)(CLS(f_1694338618_45->declaringClass,global) + f_1694338618_45->offset));
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!T0) { frame->pc = 3; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_O(T0,f_1694338618_7->offset);
	if(!T1) { throw_null(vm); goto __EXCEPTION;}
	if(12 < 0 || 12 >= T1->length) { throw_arrayounds(vm,12,T1->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T1)[12] = L0;
	AOTFIELD(f_1694338618_45,224,234,235); //digiplay/Matrix3D:TRAMAT:Ldigiplay/Matrix3D;
	T0 = *((Object**)(CLS(f_1694338618_45->declaringClass,global) + f_1694338618_45->offset));
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!T0) { frame->pc = 13; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_O(T0,f_1694338618_7->offset);
	if(!T1) { throw_null(vm); goto __EXCEPTION;}
	if(13 < 0 || 13 >= T1->length) { throw_arrayounds(vm,13,T1->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T1)[13] = L1;
	AOTFIELD(f_1694338618_45,224,234,235); //digiplay/Matrix3D:TRAMAT:Ldigiplay/Matrix3D;
	T0 = *((Object**)(CLS(f_1694338618_45->declaringClass,global) + f_1694338618_45->offset));
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!T0) { frame->pc = 23; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_O(T0,f_1694338618_7->offset);
	if(!T1) { throw_null(vm); goto __EXCEPTION;}
	if(14 < 0 || 14 >= T1->length) { throw_arrayounds(vm,14,T1->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T1)[14] = L2;
	AOTFIELD(f_1694338618_45,224,234,235); //digiplay/Matrix3D:TRAMAT:Ldigiplay/Matrix3D;
	T0 = *((Object**)(CLS(f_1694338618_45->declaringClass,global) + f_1694338618_45->offset));
	{
	  VAR cargs[]={{.O=L3},{.O=T0}};
	  frame->pc=34;
	  AOTVMETHOD(m_1694338618_49,224,236,237,vTableIndex); //digiplay/Matrix3D:prepend:(Ldigiplay/Matrix3D;)V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_1694338618_49];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Matrix3D_copyFrom2D__Ldigiplay_Matrix2D__V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JFLOAT T1;
	Object *L0,*L1,*T0;
	L0=args[0].O;
	L1=args[1].O;
BB0:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=1;
	  AOTVMETHOD(m_1694338618_13,224,150,2,vTableIndex); //digiplay/Matrix3D:identity:()V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_1694338618_13];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 5; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	AOTFIELD(f_1694338618_53,149,151,112); //digiplay/Matrix2D:m00:F;
	if(!L1) { frame->pc = 10; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_F(L1,f_1694338618_53->offset);
	if(!T0) { throw_null(vm); goto __EXCEPTION;}
	if(0 < 0 || 0 >= T0->length) { throw_arrayounds(vm,0,T0->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T0)[0] = T1;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 15; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	AOTFIELD(f_1694338618_58,149,154,112); //digiplay/Matrix2D:m10:F;
	if(!L1) { frame->pc = 20; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_F(L1,f_1694338618_58->offset);
	if(!T0) { throw_null(vm); goto __EXCEPTION;}
	if(1 < 0 || 1 >= T0->length) { throw_arrayounds(vm,1,T0->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T0)[1] = T1;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 25; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	AOTFIELD(f_1694338618_61,149,152,112); //digiplay/Matrix2D:m01:F;
	if(!L1) { frame->pc = 30; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_F(L1,f_1694338618_61->offset);
	if(!T0) { throw_null(vm); goto __EXCEPTION;}
	if(4 < 0 || 4 >= T0->length) { throw_arrayounds(vm,4,T0->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T0)[4] = T1;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 35; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	AOTFIELD(f_1694338618_64,149,155,112); //digiplay/Matrix2D:m11:F;
	if(!L1) { frame->pc = 40; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_F(L1,f_1694338618_64->offset);
	if(!T0) { throw_null(vm); goto __EXCEPTION;}
	if(5 < 0 || 5 >= T0->length) { throw_arrayounds(vm,5,T0->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T0)[5] = T1;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 45; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	AOTFIELD(f_1694338618_67,149,153,112); //digiplay/Matrix2D:m02:F;
	if(!L1) { frame->pc = 51; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_F(L1,f_1694338618_67->offset);
	if(!T0) { throw_null(vm); goto __EXCEPTION;}
	if(12 < 0 || 12 >= T0->length) { throw_arrayounds(vm,12,T0->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T0)[12] = T1;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 56; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	AOTFIELD(f_1694338618_70,149,156,112); //digiplay/Matrix2D:m12:F;
	if(!L1) { frame->pc = 62; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_F(L1,f_1694338618_70->offset);
	if(!T0) { throw_null(vm); goto __EXCEPTION;}
	if(13 < 0 || 13 >= T0->length) { throw_arrayounds(vm,13,T0->length); goto __EXCEPTION; }
	ARRAY_DATA_F(T0)[13] = T1;
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Matrix3D_copyTo2D__Ldigiplay_Matrix2D__V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JFLOAT T1;
	Object *L0,*L1,*T0;
	L1=args[0].O;
	L0=args[1].O;
BB0:
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L1) { frame->pc = 2; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L1,f_1694338618_7->offset);
	if(!T0) { throw_null(vm); goto __EXCEPTION;}
	if(0 < 0 || 0 >= T0->length) { throw_arrayounds(vm,0,T0->length); goto __EXCEPTION; }
	T1 = ARRAY_DATA_F(T0)[0];
	if(!f_1694338618_53) { //m00;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,53);
	  f_1694338618_53=fld->instance;
	}
	*FIELD_PTR_F(L0,f_1694338618_53->offset) = T1;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L1) { frame->pc = 12; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L1,f_1694338618_7->offset);
	if(!T0) { throw_null(vm); goto __EXCEPTION;}
	if(1 < 0 || 1 >= T0->length) { throw_arrayounds(vm,1,T0->length); goto __EXCEPTION; }
	T1 = ARRAY_DATA_F(T0)[1];
	if(!f_1694338618_58) { //m10;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,58);
	  f_1694338618_58=fld->instance;
	}
	*FIELD_PTR_F(L0,f_1694338618_58->offset) = T1;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L1) { frame->pc = 22; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L1,f_1694338618_7->offset);
	if(!T0) { throw_null(vm); goto __EXCEPTION;}
	if(4 < 0 || 4 >= T0->length) { throw_arrayounds(vm,4,T0->length); goto __EXCEPTION; }
	T1 = ARRAY_DATA_F(T0)[4];
	if(!f_1694338618_61) { //m01;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,61);
	  f_1694338618_61=fld->instance;
	}
	*FIELD_PTR_F(L0,f_1694338618_61->offset) = T1;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L1) { frame->pc = 32; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L1,f_1694338618_7->offset);
	if(!T0) { throw_null(vm); goto __EXCEPTION;}
	if(5 < 0 || 5 >= T0->length) { throw_arrayounds(vm,5,T0->length); goto __EXCEPTION; }
	T1 = ARRAY_DATA_F(T0)[5];
	if(!f_1694338618_64) { //m11;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,64);
	  f_1694338618_64=fld->instance;
	}
	*FIELD_PTR_F(L0,f_1694338618_64->offset) = T1;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L1) { frame->pc = 42; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L1,f_1694338618_7->offset);
	if(!T0) { throw_null(vm); goto __EXCEPTION;}
	if(12 < 0 || 12 >= T0->length) { throw_arrayounds(vm,12,T0->length); goto __EXCEPTION; }
	T1 = ARRAY_DATA_F(T0)[12];
	if(!f_1694338618_67) { //m02;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,67);
	  f_1694338618_67=fld->instance;
	}
	*FIELD_PTR_F(L0,f_1694338618_67->offset) = T1;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L1) { frame->pc = 53; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L1,f_1694338618_7->offset);
	if(!T0) { throw_null(vm); goto __EXCEPTION;}
	if(13 < 0 || 13 >= T0->length) { throw_arrayounds(vm,13,T0->length); goto __EXCEPTION; }
	T1 = ARRAY_DATA_F(T0)[13];
	if(!f_1694338618_70) { //m12;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,70);
	  f_1694338618_70=fld->instance;
	}
	*FIELD_PTR_F(L0,f_1694338618_70->offset) = T1;
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Matrix3D_to2D___Ldigiplay_Matrix2D_(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	Object *L0,*T0;
	L0=args[0].O;
BB0:
	AOTFIELD(f_1694338618_73,224,238,239); //digiplay/Matrix3D:TMP2D:Ldigiplay/Matrix2D;
	T0 = *((Object**)(CLS(f_1694338618_73->declaringClass,global) + f_1694338618_73->offset));
	{
	  VAR cargs[]={{.O=L0},{.O=T0}};
	  frame->pc=4;
	  AOTVMETHOD(m_1694338618_77,224,240,241,vTableIndex); //digiplay/Matrix3D:copyTo2D:(Ldigiplay/Matrix2D;)V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_1694338618_77];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	AOTFIELD(f_1694338618_73,224,238,239); //digiplay/Matrix3D:TMP2D:Ldigiplay/Matrix2D;
	T0 = *((Object**)(CLS(f_1694338618_73->declaringClass,global) + f_1694338618_73->offset));
	vm->FP--;vm->frames[vm->FP].ret.O=T0;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Matrix3D_convertTo3D__Ldigiplay_Matrix2D__Ldigiplay_Matrix3D_(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	Object *L0,*T0;
	L0=args[0].O;
BB0:
	AOTFIELD(f_1694338618_81,224,242,235); //digiplay/Matrix3D:TMP3D:Ldigiplay/Matrix3D;
	T0 = *((Object**)(CLS(f_1694338618_81->declaringClass,global) + f_1694338618_81->offset));
	{
	  VAR cargs[]={{.O=T0},{.O=L0}};
	  frame->pc=4;
	  AOTVMETHOD(m_1694338618_84,224,243,241,vTableIndex); //digiplay/Matrix3D:copyFrom2D:(Ldigiplay/Matrix2D;)V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_1694338618_84];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	AOTFIELD(f_1694338618_81,224,242,235); //digiplay/Matrix3D:TMP3D:Ldigiplay/Matrix3D;
	T0 = *((Object**)(CLS(f_1694338618_81->declaringClass,global) + f_1694338618_81->offset));
	vm->FP--;vm->frames[vm->FP].ret.O=T0;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Matrix3D_lookAt__FFFFFFFFF_V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JDOUBLE T3;
	JFLOAT L0,L1,L2,L3,L4,L5,L6,L7,L8,L9,L10,L11,L12,L13,L14,L15,L16,L17,L18,T0,T1,T2;
	Object *L19,*L20,*T4;
	L19=args[0].O;
	L0=args[1].F;
	L3=args[2].F;
	L6=args[3].F;
	L1=args[4].F;
	L4=args[5].F;
	L7=args[6].F;
	L13=args[7].F;
	L10=args[8].F;
	L11=args[9].F;
BB0:
	T0 = L0 - L1;
	L2=T0;
	T0 = L3 - L4;
	L5=T0;
	T0 = L6 - L7;
	L8=T0;
	T0 = L2 * L2;
	T1 = L5 * L5;
	T2 = T0 + T1;
	T0 = L8 * L8;
	T1 = T2 + T0;
	T3=(JDOUBLE)T1;
	{
	  VAR cargs[]={{.D=T3}};
	  frame->pc=37;
	  AOTMETHOD(m_1694338618_87,19,244,161); //java/lang/Math:sqrt:(D)D;
	  ((VM_CALL)(MTH(((Object*)m_1694338618_87),entry)))(vm,m_1694338618_87,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T3=frame->ret.D;
	}
	
	T0=(JFLOAT)T3;
	T1 = 1 / T0;
	L9=T1;
	T0 = L2 * L9;
	L2=T0;
	T0 = L5 * L9;
	L5=T0;
	T0 = L8 * L9;
	L8=T0;
	T0 = L10 * L8;
	T1 = L11 * L5;
	T2 = T0 - T1;
	L12=T2;
	T0 = L11 * L2;
	T1 = L13 * L8;
	T2 = T0 - T1;
	L14=T2;
	T0 = L13 * L5;
	T1 = L10 * L2;
	T2 = T0 - T1;
	L15=T2;
	T0 = L12 * L12;
	T1 = L14 * L14;
	T2 = T0 + T1;
	T0 = L15 * L15;
	T1 = T2 + T0;
	T3=(JDOUBLE)T1;
	{
	  VAR cargs[]={{.D=T3}};
	  frame->pc=122;
	  AOTMETHOD(m_1694338618_87,19,244,161); //java/lang/Math:sqrt:(D)D;
	  ((VM_CALL)(MTH(((Object*)m_1694338618_87),entry)))(vm,m_1694338618_87,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T3=frame->ret.D;
	}
	
	T0=(JFLOAT)T3;
	L9=T0;
	T0 = L9 == 0 ? 0 : (L9 > 0 ? 1 : -1);
	if(T0!=0) goto BB150;
BB135:
	L12=L2;
	L14=L5;
	L15=L8;
	goto BB177;
BB150:
	T0 = 1 / L9;
	L9=T0;
	T0 = L12 * L9;
	L12=T0;
	T0 = L14 * L9;
	L14=T0;
	T0 = L15 * L9;
	L15=T0;
BB177:
	T0 = L5 * L15;
	T1 = L8 * L14;
	T2 = T0 - T1;
	L16=T2;
	T0 = L8 * L12;
	T1 = L2 * L15;
	T2 = T0 - T1;
	L17=T2;
	T0 = L2 * L14;
	T1 = L5 * L12;
	T2 = T0 - T1;
	L18=T2;
	{
	  VAR cargs[]={{.O=L19},{.F=L12},{.F=L16},{.F=L2},{.F=0},{.F=L14},{.F=L17},{.F=L5},{.F=0},{.F=L15},{.F=L18},{.F=L8},{.F=0},{.F=0},{.F=0},{.F=0},{.F=1}};
	  frame->pc=242;
	  AOTVMETHOD(m_1694338618_90,224,245,246,vTableIndex); //digiplay/Matrix3D:set2:(FFFFFFFFFFFFFFFF)V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_1694338618_90];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	AOTFIELD(f_1694338618_94,224,247,235); //digiplay/Matrix3D:TMP:Ldigiplay/Matrix3D;
	T4 = *((Object**)(CLS(f_1694338618_94->declaringClass,global) + f_1694338618_94->offset));
	L20=T4;
	T0=-L0;
	T1=-L3;
	T2=-L6;
	{
	  VAR cargs[]={{.O=L20},{.F=1},{.F=0},{.F=0},{.F=0},{.F=0},{.F=1},{.F=0},{.F=0},{.F=0},{.F=0},{.F=1},{.F=0},{.F=T0},{.F=T1},{.F=T2},{.F=1}};
	  frame->pc=271;
	  AOTVMETHOD(m_1694338618_90,224,245,246,vTableIndex); //digiplay/Matrix3D:set2:(FFFFFFFFFFFFFFFF)V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_1694338618_90];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	{
	  VAR cargs[]={{.O=L19},{.O=L20},{.O=L19}};
	  frame->pc=278;
	  AOTMETHOD(m_1694338618_41,224,232,233); //digiplay/Matrix3D:multiply:(Ldigiplay/Matrix3D;Ldigiplay/Matrix3D;Ldigiplay/Matrix3D;)V;
	  ((VM_CALL)(MTH(((Object*)m_1694338618_41),entry)))(vm,m_1694338618_41,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Matrix3D_compose__FFFFFFFFF_V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JDOUBLE T1,T2;
	JFLOAT L0,L1,L2,L3,L4,L5,L6,L7,L8,L11,L12,L13,L14,L15,L16,T0,T4,T5;
	Object *L9,*L10,*T3;
	L9=args[0].O;
	L14=args[1].F;
	L15=args[2].F;
	L16=args[3].F;
	L0=args[4].F;
	L1=args[5].F;
	L2=args[6].F;
	L11=args[7].F;
	L12=args[8].F;
	L13=args[9].F;
BB0:
	T0 = L0 / 180.0;
	T1=(JDOUBLE)T0;
	T2 = T1 * 3.141592653589793;
	T0=(JFLOAT)T2;
	L0=T0;
	T0 = L1 / 180.0;
	T1=(JDOUBLE)T0;
	T2 = T1 * 3.141592653589793;
	T0=(JFLOAT)T2;
	L1=T0;
	T0 = L2 / 180.0;
	T1=(JDOUBLE)T0;
	T2 = T1 * 3.141592653589793;
	T0=(JFLOAT)T2;
	L2=T0;
	T1=(JDOUBLE)L0;
	{
	  VAR cargs[]={{.D=T1}};
	  frame->pc=42;
	  AOTMETHOD(m_1694338618_100,19,160,161); //java/lang/Math:cos:(D)D;
	  ((VM_CALL)(MTH(((Object*)m_1694338618_100),entry)))(vm,m_1694338618_100,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T1=frame->ret.D;
	}
	
	T0=(JFLOAT)T1;
	L3=T0;
	T1=(JDOUBLE)L1;
	{
	  VAR cargs[]={{.D=T1}};
	  frame->pc=51;
	  AOTMETHOD(m_1694338618_100,19,160,161); //java/lang/Math:cos:(D)D;
	  ((VM_CALL)(MTH(((Object*)m_1694338618_100),entry)))(vm,m_1694338618_100,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T1=frame->ret.D;
	}
	
	T0=(JFLOAT)T1;
	L4=T0;
	T1=(JDOUBLE)L2;
	{
	  VAR cargs[]={{.D=T1}};
	  frame->pc=60;
	  AOTMETHOD(m_1694338618_100,19,160,161); //java/lang/Math:cos:(D)D;
	  ((VM_CALL)(MTH(((Object*)m_1694338618_100),entry)))(vm,m_1694338618_100,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T1=frame->ret.D;
	}
	
	T0=(JFLOAT)T1;
	L5=T0;
	T1=(JDOUBLE)L0;
	{
	  VAR cargs[]={{.D=T1}};
	  frame->pc=69;
	  AOTMETHOD(m_1694338618_103,19,162,161); //java/lang/Math:sin:(D)D;
	  ((VM_CALL)(MTH(((Object*)m_1694338618_103),entry)))(vm,m_1694338618_103,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T1=frame->ret.D;
	}
	
	T0=(JFLOAT)T1;
	L6=T0;
	T1=(JDOUBLE)L1;
	{
	  VAR cargs[]={{.D=T1}};
	  frame->pc=78;
	  AOTMETHOD(m_1694338618_103,19,162,161); //java/lang/Math:sin:(D)D;
	  ((VM_CALL)(MTH(((Object*)m_1694338618_103),entry)))(vm,m_1694338618_103,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T1=frame->ret.D;
	}
	
	T0=(JFLOAT)T1;
	L7=T0;
	T1=(JDOUBLE)L2;
	{
	  VAR cargs[]={{.D=T1}};
	  frame->pc=87;
	  AOTMETHOD(m_1694338618_103,19,162,161); //java/lang/Math:sin:(D)D;
	  ((VM_CALL)(MTH(((Object*)m_1694338618_103),entry)))(vm,m_1694338618_103,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T1=frame->ret.D;
	}
	
	T0=(JFLOAT)T1;
	L8=T0;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L9) { frame->pc = 94; throw_null(vm); goto __EXCEPTION; }
	T3 = *FIELD_PTR_O(L9,f_1694338618_7->offset);
	L10=T3;
	T0 = L4 * L5;
	T4 = T0 * L11;
	if(!L10) { throw_null(vm); goto __EXCEPTION;}
	if(0 < 0 || 0 >= L10->length) { throw_arrayounds(vm,0,L10->length); goto __EXCEPTION; }
	ARRAY_DATA_F(L10)[0] = T4;
	T0 = L4 * L8;
	T4 = T0 * L11;
	if(!L10) { throw_null(vm); goto __EXCEPTION;}
	if(1 < 0 || 1 >= L10->length) { throw_arrayounds(vm,1,L10->length); goto __EXCEPTION; }
	ARRAY_DATA_F(L10)[1] = T4;
	T0=-L7;
	T4 = T0 * L11;
	if(!L10) { throw_null(vm); goto __EXCEPTION;}
	if(2 < 0 || 2 >= L10->length) { throw_arrayounds(vm,2,L10->length); goto __EXCEPTION; }
	ARRAY_DATA_F(L10)[2] = T4;
	if(!L10) { throw_null(vm); goto __EXCEPTION;}
	if(3 < 0 || 3 >= L10->length) { throw_arrayounds(vm,3,L10->length); goto __EXCEPTION; }
	ARRAY_DATA_F(L10)[3] = 0;
	T0 = L6 * L7;
	T4 = T0 * L5;
	T0 = L3 * L8;
	T5 = T4 - T0;
	T0 = T5 * L12;
	if(!L10) { throw_null(vm); goto __EXCEPTION;}
	if(4 < 0 || 4 >= L10->length) { throw_arrayounds(vm,4,L10->length); goto __EXCEPTION; }
	ARRAY_DATA_F(L10)[4] = T0;
	T0 = L6 * L7;
	T4 = T0 * L8;
	T0 = L3 * L5;
	T5 = T4 + T0;
	T0 = T5 * L12;
	if(!L10) { throw_null(vm); goto __EXCEPTION;}
	if(5 < 0 || 5 >= L10->length) { throw_arrayounds(vm,5,L10->length); goto __EXCEPTION; }
	ARRAY_DATA_F(L10)[5] = T0;
	T0 = L6 * L4;
	T4 = T0 * L12;
	if(!L10) { throw_null(vm); goto __EXCEPTION;}
	if(6 < 0 || 6 >= L10->length) { throw_arrayounds(vm,6,L10->length); goto __EXCEPTION; }
	ARRAY_DATA_F(L10)[6] = T4;
	if(!L10) { throw_null(vm); goto __EXCEPTION;}
	if(7 < 0 || 7 >= L10->length) { throw_arrayounds(vm,7,L10->length); goto __EXCEPTION; }
	ARRAY_DATA_F(L10)[7] = 0;
	T0 = L3 * L7;
	T4 = T0 * L5;
	T0 = L6 * L8;
	T5 = T4 + T0;
	T0 = T5 * L13;
	if(!L10) { throw_null(vm); goto __EXCEPTION;}
	if(8 < 0 || 8 >= L10->length) { throw_arrayounds(vm,8,L10->length); goto __EXCEPTION; }
	ARRAY_DATA_F(L10)[8] = T0;
	T0 = L3 * L7;
	T4 = T0 * L8;
	T0 = L6 * L5;
	T5 = T4 - T0;
	T0 = T5 * L13;
	if(!L10) { throw_null(vm); goto __EXCEPTION;}
	if(9 < 0 || 9 >= L10->length) { throw_arrayounds(vm,9,L10->length); goto __EXCEPTION; }
	ARRAY_DATA_F(L10)[9] = T0;
	T0 = L3 * L4;
	T4 = T0 * L13;
	if(!L10) { throw_null(vm); goto __EXCEPTION;}
	if(10 < 0 || 10 >= L10->length) { throw_arrayounds(vm,10,L10->length); goto __EXCEPTION; }
	ARRAY_DATA_F(L10)[10] = T4;
	if(!L10) { throw_null(vm); goto __EXCEPTION;}
	if(11 < 0 || 11 >= L10->length) { throw_arrayounds(vm,11,L10->length); goto __EXCEPTION; }
	ARRAY_DATA_F(L10)[11] = 0;
	if(!L10) { throw_null(vm); goto __EXCEPTION;}
	if(12 < 0 || 12 >= L10->length) { throw_arrayounds(vm,12,L10->length); goto __EXCEPTION; }
	ARRAY_DATA_F(L10)[12] = L14;
	if(!L10) { throw_null(vm); goto __EXCEPTION;}
	if(13 < 0 || 13 >= L10->length) { throw_arrayounds(vm,13,L10->length); goto __EXCEPTION; }
	ARRAY_DATA_F(L10)[13] = L15;
	if(!L10) { throw_null(vm); goto __EXCEPTION;}
	if(14 < 0 || 14 >= L10->length) { throw_arrayounds(vm,14,L10->length); goto __EXCEPTION; }
	ARRAY_DATA_F(L10)[14] = L16;
	if(!L10) { throw_null(vm); goto __EXCEPTION;}
	if(15 < 0 || 15 >= L10->length) { throw_arrayounds(vm,15,L10->length); goto __EXCEPTION; }
	ARRAY_DATA_F(L10)[15] = 1;
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Matrix3D_multiply__Ldigiplay_Matrix3D_Ldigiplay_Matrix3D_Ldigiplay_Matrix3D__V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JFLOAT L2,L3,L4,L5,L6,L7,L8,L9,L10,L11,L12,L13,L14,L15,L16,L17,L19,L20,L21,L22,L23,L24,L25,L26,L27,L28,L29,L30,L31,L32,L33,L34,T1,T2,T3;
	Object *L0,*L1,*L18,*L35,*L36,*T0;
	L18=args[0].O;
	L0=args[1].O;
	L35=args[2].O;
BB0:
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 1; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	L1=T0;
	if(!L1) { throw_null(vm); goto __EXCEPTION;}
	if(0 < 0 || 0 >= L1->length) { throw_arrayounds(vm,0,L1->length); goto __EXCEPTION; }
	T1 = ARRAY_DATA_F(L1)[0];
	L2=T1;
	if(!L1) { throw_null(vm); goto __EXCEPTION;}
	if(4 < 0 || 4 >= L1->length) { throw_arrayounds(vm,4,L1->length); goto __EXCEPTION; }
	T1 = ARRAY_DATA_F(L1)[4];
	L3=T1;
	if(!L1) { throw_null(vm); goto __EXCEPTION;}
	if(8 < 0 || 8 >= L1->length) { throw_arrayounds(vm,8,L1->length); goto __EXCEPTION; }
	T1 = ARRAY_DATA_F(L1)[8];
	L4=T1;
	if(!L1) { throw_null(vm); goto __EXCEPTION;}
	if(12 < 0 || 12 >= L1->length) { throw_arrayounds(vm,12,L1->length); goto __EXCEPTION; }
	T1 = ARRAY_DATA_F(L1)[12];
	L5=T1;
	if(!L1) { throw_null(vm); goto __EXCEPTION;}
	if(1 < 0 || 1 >= L1->length) { throw_arrayounds(vm,1,L1->length); goto __EXCEPTION; }
	T1 = ARRAY_DATA_F(L1)[1];
	L6=T1;
	if(!L1) { throw_null(vm); goto __EXCEPTION;}
	if(5 < 0 || 5 >= L1->length) { throw_arrayounds(vm,5,L1->length); goto __EXCEPTION; }
	T1 = ARRAY_DATA_F(L1)[5];
	L7=T1;
	if(!L1) { throw_null(vm); goto __EXCEPTION;}
	if(9 < 0 || 9 >= L1->length) { throw_arrayounds(vm,9,L1->length); goto __EXCEPTION; }
	T1 = ARRAY_DATA_F(L1)[9];
	L8=T1;
	if(!L1) { throw_null(vm); goto __EXCEPTION;}
	if(13 < 0 || 13 >= L1->length) { throw_arrayounds(vm,13,L1->length); goto __EXCEPTION; }
	T1 = ARRAY_DATA_F(L1)[13];
	L9=T1;
	if(!L1) { throw_null(vm); goto __EXCEPTION;}
	if(2 < 0 || 2 >= L1->length) { throw_arrayounds(vm,2,L1->length); goto __EXCEPTION; }
	T1 = ARRAY_DATA_F(L1)[2];
	L10=T1;
	if(!L1) { throw_null(vm); goto __EXCEPTION;}
	if(6 < 0 || 6 >= L1->length) { throw_arrayounds(vm,6,L1->length); goto __EXCEPTION; }
	T1 = ARRAY_DATA_F(L1)[6];
	L11=T1;
	if(!L1) { throw_null(vm); goto __EXCEPTION;}
	if(10 < 0 || 10 >= L1->length) { throw_arrayounds(vm,10,L1->length); goto __EXCEPTION; }
	T1 = ARRAY_DATA_F(L1)[10];
	L12=T1;
	if(!L1) { throw_null(vm); goto __EXCEPTION;}
	if(14 < 0 || 14 >= L1->length) { throw_arrayounds(vm,14,L1->length); goto __EXCEPTION; }
	T1 = ARRAY_DATA_F(L1)[14];
	L13=T1;
	if(!L1) { throw_null(vm); goto __EXCEPTION;}
	if(3 < 0 || 3 >= L1->length) { throw_arrayounds(vm,3,L1->length); goto __EXCEPTION; }
	T1 = ARRAY_DATA_F(L1)[3];
	L14=T1;
	if(!L1) { throw_null(vm); goto __EXCEPTION;}
	if(7 < 0 || 7 >= L1->length) { throw_arrayounds(vm,7,L1->length); goto __EXCEPTION; }
	T1 = ARRAY_DATA_F(L1)[7];
	L15=T1;
	if(!L1) { throw_null(vm); goto __EXCEPTION;}
	if(11 < 0 || 11 >= L1->length) { throw_arrayounds(vm,11,L1->length); goto __EXCEPTION; }
	T1 = ARRAY_DATA_F(L1)[11];
	L16=T1;
	if(!L1) { throw_null(vm); goto __EXCEPTION;}
	if(15 < 0 || 15 >= L1->length) { throw_arrayounds(vm,15,L1->length); goto __EXCEPTION; }
	T1 = ARRAY_DATA_F(L1)[15];
	L17=T1;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L18) { frame->pc = 112; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L18,f_1694338618_7->offset);
	L1=T0;
	if(!L1) { throw_null(vm); goto __EXCEPTION;}
	if(0 < 0 || 0 >= L1->length) { throw_arrayounds(vm,0,L1->length); goto __EXCEPTION; }
	T1 = ARRAY_DATA_F(L1)[0];
	L19=T1;
	if(!L1) { throw_null(vm); goto __EXCEPTION;}
	if(4 < 0 || 4 >= L1->length) { throw_arrayounds(vm,4,L1->length); goto __EXCEPTION; }
	T1 = ARRAY_DATA_F(L1)[4];
	L20=T1;
	if(!L1) { throw_null(vm); goto __EXCEPTION;}
	if(8 < 0 || 8 >= L1->length) { throw_arrayounds(vm,8,L1->length); goto __EXCEPTION; }
	T1 = ARRAY_DATA_F(L1)[8];
	L21=T1;
	if(!L1) { throw_null(vm); goto __EXCEPTION;}
	if(12 < 0 || 12 >= L1->length) { throw_arrayounds(vm,12,L1->length); goto __EXCEPTION; }
	T1 = ARRAY_DATA_F(L1)[12];
	L22=T1;
	if(!L1) { throw_null(vm); goto __EXCEPTION;}
	if(1 < 0 || 1 >= L1->length) { throw_arrayounds(vm,1,L1->length); goto __EXCEPTION; }
	T1 = ARRAY_DATA_F(L1)[1];
	L23=T1;
	if(!L1) { throw_null(vm); goto __EXCEPTION;}
	if(5 < 0 || 5 >= L1->length) { throw_arrayounds(vm,5,L1->length); goto __EXCEPTION; }
	T1 = ARRAY_DATA_F(L1)[5];
	L24=T1;
	if(!L1) { throw_null(vm); goto __EXCEPTION;}
	if(9 < 0 || 9 >= L1->length) { throw_arrayounds(vm,9,L1->length); goto __EXCEPTION; }
	T1 = ARRAY_DATA_F(L1)[9];
	L25=T1;
	if(!L1) { throw_null(vm); goto __EXCEPTION;}
	if(13 < 0 || 13 >= L1->length) { throw_arrayounds(vm,13,L1->length); goto __EXCEPTION; }
	T1 = ARRAY_DATA_F(L1)[13];
	L26=T1;
	if(!L1) { throw_null(vm); goto __EXCEPTION;}
	if(2 < 0 || 2 >= L1->length) { throw_arrayounds(vm,2,L1->length); goto __EXCEPTION; }
	T1 = ARRAY_DATA_F(L1)[2];
	L27=T1;
	if(!L1) { throw_null(vm); goto __EXCEPTION;}
	if(6 < 0 || 6 >= L1->length) { throw_arrayounds(vm,6,L1->length); goto __EXCEPTION; }
	T1 = ARRAY_DATA_F(L1)[6];
	L28=T1;
	if(!L1) { throw_null(vm); goto __EXCEPTION;}
	if(10 < 0 || 10 >= L1->length) { throw_arrayounds(vm,10,L1->length); goto __EXCEPTION; }
	T1 = ARRAY_DATA_F(L1)[10];
	L29=T1;
	if(!L1) { throw_null(vm); goto __EXCEPTION;}
	if(14 < 0 || 14 >= L1->length) { throw_arrayounds(vm,14,L1->length); goto __EXCEPTION; }
	T1 = ARRAY_DATA_F(L1)[14];
	L30=T1;
	if(!L1) { throw_null(vm); goto __EXCEPTION;}
	if(3 < 0 || 3 >= L1->length) { throw_arrayounds(vm,3,L1->length); goto __EXCEPTION; }
	T1 = ARRAY_DATA_F(L1)[3];
	L31=T1;
	if(!L1) { throw_null(vm); goto __EXCEPTION;}
	if(7 < 0 || 7 >= L1->length) { throw_arrayounds(vm,7,L1->length); goto __EXCEPTION; }
	T1 = ARRAY_DATA_F(L1)[7];
	L32=T1;
	if(!L1) { throw_null(vm); goto __EXCEPTION;}
	if(11 < 0 || 11 >= L1->length) { throw_arrayounds(vm,11,L1->length); goto __EXCEPTION; }
	T1 = ARRAY_DATA_F(L1)[11];
	L33=T1;
	if(!L1) { throw_null(vm); goto __EXCEPTION;}
	if(15 < 0 || 15 >= L1->length) { throw_arrayounds(vm,15,L1->length); goto __EXCEPTION; }
	T1 = ARRAY_DATA_F(L1)[15];
	L34=T1;
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L35) { frame->pc = 224; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L35,f_1694338618_7->offset);
	L36=T0;
	T1 = L2 * L19;
	T2 = L6 * L20;
	T3 = T1 + T2;
	T1 = L10 * L21;
	T2 = T3 + T1;
	T1 = L14 * L22;
	T3 = T2 + T1;
	if(!L36) { throw_null(vm); goto __EXCEPTION;}
	if(0 < 0 || 0 >= L36->length) { throw_arrayounds(vm,0,L36->length); goto __EXCEPTION; }
	ARRAY_DATA_F(L36)[0] = T3;
	T1 = L2 * L23;
	T2 = L6 * L24;
	T3 = T1 + T2;
	T1 = L10 * L25;
	T2 = T3 + T1;
	T1 = L14 * L26;
	T3 = T2 + T1;
	if(!L36) { throw_null(vm); goto __EXCEPTION;}
	if(1 < 0 || 1 >= L36->length) { throw_arrayounds(vm,1,L36->length); goto __EXCEPTION; }
	ARRAY_DATA_F(L36)[1] = T3;
	T1 = L2 * L27;
	T2 = L6 * L28;
	T3 = T1 + T2;
	T1 = L10 * L29;
	T2 = T3 + T1;
	T1 = L14 * L30;
	T3 = T2 + T1;
	if(!L36) { throw_null(vm); goto __EXCEPTION;}
	if(2 < 0 || 2 >= L36->length) { throw_arrayounds(vm,2,L36->length); goto __EXCEPTION; }
	ARRAY_DATA_F(L36)[2] = T3;
	T1 = L2 * L31;
	T2 = L6 * L32;
	T3 = T1 + T2;
	T1 = L10 * L33;
	T2 = T3 + T1;
	T1 = L14 * L34;
	T3 = T2 + T1;
	if(!L36) { throw_null(vm); goto __EXCEPTION;}
	if(3 < 0 || 3 >= L36->length) { throw_arrayounds(vm,3,L36->length); goto __EXCEPTION; }
	ARRAY_DATA_F(L36)[3] = T3;
	T1 = L3 * L19;
	T2 = L7 * L20;
	T3 = T1 + T2;
	T1 = L11 * L21;
	T2 = T3 + T1;
	T1 = L15 * L22;
	T3 = T2 + T1;
	if(!L36) { throw_null(vm); goto __EXCEPTION;}
	if(4 < 0 || 4 >= L36->length) { throw_arrayounds(vm,4,L36->length); goto __EXCEPTION; }
	ARRAY_DATA_F(L36)[4] = T3;
	T1 = L3 * L23;
	T2 = L7 * L24;
	T3 = T1 + T2;
	T1 = L11 * L25;
	T2 = T3 + T1;
	T1 = L15 * L26;
	T3 = T2 + T1;
	if(!L36) { throw_null(vm); goto __EXCEPTION;}
	if(5 < 0 || 5 >= L36->length) { throw_arrayounds(vm,5,L36->length); goto __EXCEPTION; }
	ARRAY_DATA_F(L36)[5] = T3;
	T1 = L3 * L27;
	T2 = L7 * L28;
	T3 = T1 + T2;
	T1 = L11 * L29;
	T2 = T3 + T1;
	T1 = L15 * L30;
	T3 = T2 + T1;
	if(!L36) { throw_null(vm); goto __EXCEPTION;}
	if(6 < 0 || 6 >= L36->length) { throw_arrayounds(vm,6,L36->length); goto __EXCEPTION; }
	ARRAY_DATA_F(L36)[6] = T3;
	T1 = L3 * L31;
	T2 = L7 * L32;
	T3 = T1 + T2;
	T1 = L11 * L33;
	T2 = T3 + T1;
	T1 = L15 * L34;
	T3 = T2 + T1;
	if(!L36) { throw_null(vm); goto __EXCEPTION;}
	if(7 < 0 || 7 >= L36->length) { throw_arrayounds(vm,7,L36->length); goto __EXCEPTION; }
	ARRAY_DATA_F(L36)[7] = T3;
	T1 = L4 * L19;
	T2 = L8 * L20;
	T3 = T1 + T2;
	T1 = L12 * L21;
	T2 = T3 + T1;
	T1 = L16 * L22;
	T3 = T2 + T1;
	if(!L36) { throw_null(vm); goto __EXCEPTION;}
	if(8 < 0 || 8 >= L36->length) { throw_arrayounds(vm,8,L36->length); goto __EXCEPTION; }
	ARRAY_DATA_F(L36)[8] = T3;
	T1 = L4 * L23;
	T2 = L8 * L24;
	T3 = T1 + T2;
	T1 = L12 * L25;
	T2 = T3 + T1;
	T1 = L16 * L26;
	T3 = T2 + T1;
	if(!L36) { throw_null(vm); goto __EXCEPTION;}
	if(9 < 0 || 9 >= L36->length) { throw_arrayounds(vm,9,L36->length); goto __EXCEPTION; }
	ARRAY_DATA_F(L36)[9] = T3;
	T1 = L4 * L27;
	T2 = L8 * L28;
	T3 = T1 + T2;
	T1 = L12 * L29;
	T2 = T3 + T1;
	T1 = L16 * L30;
	T3 = T2 + T1;
	if(!L36) { throw_null(vm); goto __EXCEPTION;}
	if(10 < 0 || 10 >= L36->length) { throw_arrayounds(vm,10,L36->length); goto __EXCEPTION; }
	ARRAY_DATA_F(L36)[10] = T3;
	T1 = L4 * L31;
	T2 = L8 * L32;
	T3 = T1 + T2;
	T1 = L12 * L33;
	T2 = T3 + T1;
	T1 = L16 * L34;
	T3 = T2 + T1;
	if(!L36) { throw_null(vm); goto __EXCEPTION;}
	if(11 < 0 || 11 >= L36->length) { throw_arrayounds(vm,11,L36->length); goto __EXCEPTION; }
	ARRAY_DATA_F(L36)[11] = T3;
	T1 = L5 * L19;
	T2 = L9 * L20;
	T3 = T1 + T2;
	T1 = L13 * L21;
	T2 = T3 + T1;
	T1 = L17 * L22;
	T3 = T2 + T1;
	if(!L36) { throw_null(vm); goto __EXCEPTION;}
	if(12 < 0 || 12 >= L36->length) { throw_arrayounds(vm,12,L36->length); goto __EXCEPTION; }
	ARRAY_DATA_F(L36)[12] = T3;
	T1 = L5 * L23;
	T2 = L9 * L24;
	T3 = T1 + T2;
	T1 = L13 * L25;
	T2 = T3 + T1;
	T1 = L17 * L26;
	T3 = T2 + T1;
	if(!L36) { throw_null(vm); goto __EXCEPTION;}
	if(13 < 0 || 13 >= L36->length) { throw_arrayounds(vm,13,L36->length); goto __EXCEPTION; }
	ARRAY_DATA_F(L36)[13] = T3;
	T1 = L5 * L27;
	T2 = L9 * L28;
	T3 = T1 + T2;
	T1 = L13 * L29;
	T2 = T3 + T1;
	T1 = L17 * L30;
	T3 = T2 + T1;
	if(!L36) { throw_null(vm); goto __EXCEPTION;}
	if(14 < 0 || 14 >= L36->length) { throw_arrayounds(vm,14,L36->length); goto __EXCEPTION; }
	ARRAY_DATA_F(L36)[14] = T3;
	T1 = L5 * L31;
	T2 = L9 * L32;
	T3 = T1 + T2;
	T1 = L13 * L33;
	T2 = T3 + T1;
	T1 = L17 * L34;
	T3 = T2 + T1;
	if(!L36) { throw_null(vm); goto __EXCEPTION;}
	if(15 < 0 || 15 >= L36->length) { throw_arrayounds(vm,15,L36->length); goto __EXCEPTION; }
	ARRAY_DATA_F(L36)[15] = T3;
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Matrix3D_t__FFF_V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JFLOAT L2,L3,L4,L5,L6,L7,T1,T2,T3;
	Object *L0,*L1,*T0,*T4;
	L0=args[0].O;
	L2=args[1].F;
	L3=args[2].F;
	L4=args[3].F;
BB0:
	AOTFIELD(f_1694338618_7,224,225,226); //digiplay/Matrix3D:raw:[F;
	if(!L0) { frame->pc = 1; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1694338618_7->offset);
	L1=T0;
	if(!L1) { throw_null(vm); goto __EXCEPTION;}
	if(0 < 0 || 0 >= L1->length) { throw_arrayounds(vm,0,L1->length); goto __EXCEPTION; }
	T1 = ARRAY_DATA_F(L1)[0];
	T2 = L2 * T1;
	if(!L1) { throw_null(vm); goto __EXCEPTION;}
	if(4 < 0 || 4 >= L1->length) { throw_arrayounds(vm,4,L1->length); goto __EXCEPTION; }
	T1 = ARRAY_DATA_F(L1)[4];
	T3 = L3 * T1;
	T1 = T2 + T3;
	if(!L1) { throw_null(vm); goto __EXCEPTION;}
	if(8 < 0 || 8 >= L1->length) { throw_arrayounds(vm,8,L1->length); goto __EXCEPTION; }
	T2 = ARRAY_DATA_F(L1)[8];
	T3 = L4 * T2;
	T2 = T1 + T3;
	if(!L1) { throw_null(vm); goto __EXCEPTION;}
	if(12 < 0 || 12 >= L1->length) { throw_arrayounds(vm,12,L1->length); goto __EXCEPTION; }
	T1 = ARRAY_DATA_F(L1)[12];
	T3 = T2 + T1;
	L5=T3;
	if(!L1) { throw_null(vm); goto __EXCEPTION;}
	if(1 < 0 || 1 >= L1->length) { throw_arrayounds(vm,1,L1->length); goto __EXCEPTION; }
	T1 = ARRAY_DATA_F(L1)[1];
	T2 = L2 * T1;
	if(!L1) { throw_null(vm); goto __EXCEPTION;}
	if(5 < 0 || 5 >= L1->length) { throw_arrayounds(vm,5,L1->length); goto __EXCEPTION; }
	T1 = ARRAY_DATA_F(L1)[5];
	T3 = L3 * T1;
	T1 = T2 + T3;
	if(!L1) { throw_null(vm); goto __EXCEPTION;}
	if(9 < 0 || 9 >= L1->length) { throw_arrayounds(vm,9,L1->length); goto __EXCEPTION; }
	T2 = ARRAY_DATA_F(L1)[9];
	T3 = L4 * T2;
	T2 = T1 + T3;
	if(!L1) { throw_null(vm); goto __EXCEPTION;}
	if(13 < 0 || 13 >= L1->length) { throw_arrayounds(vm,13,L1->length); goto __EXCEPTION; }
	T1 = ARRAY_DATA_F(L1)[13];
	T3 = T2 + T1;
	L6=T3;
	if(!L1) { throw_null(vm); goto __EXCEPTION;}
	if(2 < 0 || 2 >= L1->length) { throw_arrayounds(vm,2,L1->length); goto __EXCEPTION; }
	T1 = ARRAY_DATA_F(L1)[2];
	T2 = L2 * T1;
	if(!L1) { throw_null(vm); goto __EXCEPTION;}
	if(6 < 0 || 6 >= L1->length) { throw_arrayounds(vm,6,L1->length); goto __EXCEPTION; }
	T1 = ARRAY_DATA_F(L1)[6];
	T3 = L3 * T1;
	T1 = T2 + T3;
	if(!L1) { throw_null(vm); goto __EXCEPTION;}
	if(10 < 0 || 10 >= L1->length) { throw_arrayounds(vm,10,L1->length); goto __EXCEPTION; }
	T2 = ARRAY_DATA_F(L1)[10];
	T3 = L4 * T2;
	T2 = T1 + T3;
	if(!L1) { throw_null(vm); goto __EXCEPTION;}
	if(14 < 0 || 14 >= L1->length) { throw_arrayounds(vm,14,L1->length); goto __EXCEPTION; }
	T1 = ARRAY_DATA_F(L1)[14];
	T3 = T2 + T1;
	L7=T3;
	AOTFIELD(f_1694338618_106,28,29,30); //java/lang/System:out:Ljava/io/PrintStream;
	T0 = *((Object**)(CLS(f_1694338618_106->declaringClass,global) + f_1694338618_106->offset));
	AOTCLASS(c_1694338618_112,31);
	T4=alloc_object(vm,c_1694338618_112,0);
	{
	  VAR cargs[]={{.O=T4}};
	  frame->pc=101;
	  AOTMETHOD(m_1694338618_114,31,1,2); //java/lang/StringBuilder:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m_1694338618_114),entry)))(vm,m_1694338618_114,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	{
	  VAR cargs[]={{.O=T4},{.F=L2}};
	  frame->pc=105;
	  AOTVMETHOD(m_1694338618_115,31,33,200,vTableIndex); //java/lang/StringBuilder:append:(F)Ljava/lang/StringBuilder;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_1694338618_115];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T4=frame->ret.O;
	}
	
	{
	  VAR cargs[]={{.O=T4},{.O=aot_strings[248]}};
	  frame->pc=110;
	  AOTVMETHOD(m_1694338618_121,31,33,34,vTableIndex); //java/lang/StringBuilder:append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_1694338618_121];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T4=frame->ret.O;
	}
	
	{
	  VAR cargs[]={{.O=T4},{.F=L3}};
	  frame->pc=114;
	  AOTVMETHOD(m_1694338618_115,31,33,200,vTableIndex); //java/lang/StringBuilder:append:(F)Ljava/lang/StringBuilder;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_1694338618_115];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T4=frame->ret.O;
	}
	
	{
	  VAR cargs[]={{.O=T4},{.O=aot_strings[248]}};
	  frame->pc=119;
	  AOTVMETHOD(m_1694338618_121,31,33,34,vTableIndex); //java/lang/StringBuilder:append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_1694338618_121];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T4=frame->ret.O;
	}
	
	{
	  VAR cargs[]={{.O=T4},{.F=L4}};
	  frame->pc=123;
	  AOTVMETHOD(m_1694338618_115,31,33,200,vTableIndex); //java/lang/StringBuilder:append:(F)Ljava/lang/StringBuilder;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_1694338618_115];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T4=frame->ret.O;
	}
	
	{
	  VAR cargs[]={{.O=T4},{.O=aot_strings[249]}};
	  frame->pc=128;
	  AOTVMETHOD(m_1694338618_121,31,33,34,vTableIndex); //java/lang/StringBuilder:append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_1694338618_121];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T4=frame->ret.O;
	}
	
	{
	  VAR cargs[]={{.O=T4},{.F=L5}};
	  frame->pc=133;
	  AOTVMETHOD(m_1694338618_115,31,33,200,vTableIndex); //java/lang/StringBuilder:append:(F)Ljava/lang/StringBuilder;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_1694338618_115];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T4=frame->ret.O;
	}
	
	{
	  VAR cargs[]={{.O=T4},{.O=aot_strings[248]}};
	  frame->pc=138;
	  AOTVMETHOD(m_1694338618_121,31,33,34,vTableIndex); //java/lang/StringBuilder:append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_1694338618_121];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T4=frame->ret.O;
	}
	
	{
	  VAR cargs[]={{.O=T4},{.F=L6}};
	  frame->pc=143;
	  AOTVMETHOD(m_1694338618_115,31,33,200,vTableIndex); //java/lang/StringBuilder:append:(F)Ljava/lang/StringBuilder;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_1694338618_115];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T4=frame->ret.O;
	}
	
	{
	  VAR cargs[]={{.O=T4},{.O=aot_strings[248]}};
	  frame->pc=148;
	  AOTVMETHOD(m_1694338618_121,31,33,34,vTableIndex); //java/lang/StringBuilder:append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_1694338618_121];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T4=frame->ret.O;
	}
	
	{
	  VAR cargs[]={{.O=T4},{.F=L7}};
	  frame->pc=153;
	  AOTVMETHOD(m_1694338618_115,31,33,200,vTableIndex); //java/lang/StringBuilder:append:(F)Ljava/lang/StringBuilder;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_1694338618_115];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T4=frame->ret.O;
	}
	
	{
	  VAR cargs[]={{.O=T4}};
	  frame->pc=156;
	  AOTVMETHOD(m_1694338618_126,31,36,37,vTableIndex); //java/lang/StringBuilder:toString:()Ljava/lang/String;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_1694338618_126];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T4=frame->ret.O;
	}
	
	{
	  VAR cargs[]={{.O=T0},{.O=T4}};
	  frame->pc=159;
	  AOTVMETHOD(m_1694338618_130,38,39,40,vTableIndex); //java/io/PrintStream:println:(Ljava/lang/String;)V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_1694338618_130];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Matrix3D__clinit____V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JDOUBLE T1;
	JFLOAT T2,T3;
	Object *T0;
BB0:
	AOTCLASS(c_1694338618_8,224);
	T0=alloc_object(vm,c_1694338618_8,0);
	{
	  VAR cargs[]={{.O=T0}};
	  frame->pc=4;
	  AOTMETHOD(m_1694338618_136,224,1,2); //digiplay/Matrix3D:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m_1694338618_136),entry)))(vm,m_1694338618_136,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	if(!f_1694338618_137) { //IDENTITY;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,137);
	  f_1694338618_137=fld->instance;
	}
	*((Object**)((CLS(f_1694338618_137->declaringClass,global))+f_1694338618_137->offset)) = T0;
	AOTCLASS(c_1694338618_8,224);
	T0=alloc_object(vm,c_1694338618_8,0);
	{
	  VAR cargs[]={{.O=T0}};
	  frame->pc=14;
	  AOTMETHOD(m_1694338618_136,224,1,2); //digiplay/Matrix3D:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m_1694338618_136),entry)))(vm,m_1694338618_136,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	if(!f_1694338618_94) { //TMP;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,94);
	  f_1694338618_94=fld->instance;
	}
	*((Object**)((CLS(f_1694338618_94->declaringClass,global))+f_1694338618_94->offset)) = T0;
	{
	  VAR cargs[]={{.D=0.5}};
	  frame->pc=23;
	  AOTMETHOD(m_1694338618_22,19,227,161); //java/lang/Math:tan:(D)D;
	  ((VM_CALL)(MTH(((Object*)m_1694338618_22),entry)))(vm,m_1694338618_22,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T1=frame->ret.D;
	}
	
	T2=(JFLOAT)T1;
	T3 = T2 * 0.5;
	if(!f_1694338618_32) { //TAN05;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,32);
	  f_1694338618_32=fld->instance;
	}
	*((JFLOAT*)((CLS(f_1694338618_32->declaringClass,global))+f_1694338618_32->offset)) = T3;
	AOTCLASS(c_1694338618_8,224);
	T0=alloc_object(vm,c_1694338618_8,0);
	{
	  VAR cargs[]={{.O=T0}};
	  frame->pc=37;
	  AOTMETHOD(m_1694338618_136,224,1,2); //digiplay/Matrix3D:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m_1694338618_136),entry)))(vm,m_1694338618_136,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	if(!f_1694338618_45) { //TRAMAT;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,45);
	  f_1694338618_45=fld->instance;
	}
	*((Object**)((CLS(f_1694338618_45->declaringClass,global))+f_1694338618_45->offset)) = T0;
	AOTCLASS(c_1694338618_54,149);
	T0=alloc_object(vm,c_1694338618_54,0);
	{
	  VAR cargs[]={{.O=T0}};
	  frame->pc=47;
	  AOTMETHOD(m_1694338618_143,149,1,2); //digiplay/Matrix2D:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m_1694338618_143),entry)))(vm,m_1694338618_143,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	if(!f_1694338618_73) { //TMP2D;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,73);
	  f_1694338618_73=fld->instance;
	}
	*((Object**)((CLS(f_1694338618_73->declaringClass,global))+f_1694338618_73->offset)) = T0;
	AOTCLASS(c_1694338618_8,224);
	T0=alloc_object(vm,c_1694338618_8,0);
	{
	  VAR cargs[]={{.O=T0}};
	  frame->pc=57;
	  AOTMETHOD(m_1694338618_136,224,1,2); //digiplay/Matrix3D:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m_1694338618_136),entry)))(vm,m_1694338618_136,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	if(!f_1694338618_81) { //TMP3D;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,81);
	  f_1694338618_81=fld->instance;
	}
	*((Object**)((CLS(f_1694338618_81->declaringClass,global))+f_1694338618_81->offset)) = T0;
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
//digiplay/Graphics
static Field *f_1904448929_7=NULL,*f_1904448929_13=NULL,*f_1904448929_16=NULL,*f_1904448929_19=NULL,*f_1904448929_22=NULL,*f_1904448929_25=NULL;
static JLONG m_1904448929_1=0;
static Object *c_1904448929_2=NULL,*c_1904448929_8=NULL;
void digiplay_Graphics__init____V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	Object *L0;
	L0=args[0].O;
BB0:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=1;
	  AOTMETHOD(m_1904448929_1,0,1,2); //java/lang/Object:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m_1904448929_1),entry)))(vm,m_1904448929_1,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Graphics_resize__IIIIII_V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JINT L1,L2,L3,L4,L5,L6;
	Object *L0;
	L0=args[0].O;
	L1=args[1].I;
	L2=args[2].I;
	L3=args[3].I;
	L4=args[4].I;
	L5=args[5].I;
	L6=args[6].I;
BB0:
	if(!f_1904448929_7) { //screenWidth;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,7);
	  f_1904448929_7=fld->instance;
	}
	*FIELD_PTR_I(L0,f_1904448929_7->offset) = L1;
	if(!f_1904448929_13) { //screenHeight;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,13);
	  f_1904448929_13=fld->instance;
	}
	*FIELD_PTR_I(L0,f_1904448929_13->offset) = L2;
	if(!f_1904448929_16) { //safeLeft;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,16);
	  f_1904448929_16=fld->instance;
	}
	*FIELD_PTR_I(L0,f_1904448929_16->offset) = L3;
	if(!f_1904448929_19) { //safeTop;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,19);
	  f_1904448929_19=fld->instance;
	}
	*FIELD_PTR_I(L0,f_1904448929_19->offset) = L4;
	if(!f_1904448929_22) { //safeRight;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,22);
	  f_1904448929_22=fld->instance;
	}
	*FIELD_PTR_I(L0,f_1904448929_22->offset) = L5;
	if(!f_1904448929_25) { //safeBottom;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,25);
	  f_1904448929_25=fld->instance;
	}
	*FIELD_PTR_I(L0,f_1904448929_25->offset) = L6;
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Graphics_getScreenWidth___I(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JINT T0;
	Object *L0;
	L0=args[0].O;
BB0:
	AOTFIELD(f_1904448929_7,250,8,4); //digiplay/Graphics:screenWidth:I;
	if(!L0) { frame->pc = 1; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_I(L0,f_1904448929_7->offset);
	vm->FP--;vm->frames[vm->FP].ret.I=T0;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Graphics_getScreenHeight___I(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JINT T0;
	Object *L0;
	L0=args[0].O;
BB0:
	AOTFIELD(f_1904448929_13,250,9,4); //digiplay/Graphics:screenHeight:I;
	if(!L0) { frame->pc = 1; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_I(L0,f_1904448929_13->offset);
	vm->FP--;vm->frames[vm->FP].ret.I=T0;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Graphics_getSafeLeft___I(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JINT T0;
	Object *L0;
	L0=args[0].O;
BB0:
	AOTFIELD(f_1904448929_16,250,251,4); //digiplay/Graphics:safeLeft:I;
	if(!L0) { frame->pc = 1; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_I(L0,f_1904448929_16->offset);
	vm->FP--;vm->frames[vm->FP].ret.I=T0;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Graphics_getSafeRight___I(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JINT T0;
	Object *L0;
	L0=args[0].O;
BB0:
	AOTFIELD(f_1904448929_22,250,252,4); //digiplay/Graphics:safeRight:I;
	if(!L0) { frame->pc = 1; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_I(L0,f_1904448929_22->offset);
	vm->FP--;vm->frames[vm->FP].ret.I=T0;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Graphics_getSafeTop___I(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JINT T0;
	Object *L0;
	L0=args[0].O;
BB0:
	AOTFIELD(f_1904448929_19,250,253,4); //digiplay/Graphics:safeTop:I;
	if(!L0) { frame->pc = 1; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_I(L0,f_1904448929_19->offset);
	vm->FP--;vm->frames[vm->FP].ret.I=T0;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Graphics_getSafeBottom___I(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JINT T0;
	Object *L0;
	L0=args[0].O;
BB0:
	AOTFIELD(f_1904448929_25,250,254,4); //digiplay/Graphics:safeBottom:I;
	if(!L0) { frame->pc = 1; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_I(L0,f_1904448929_25->offset);
	vm->FP--;vm->frames[vm->FP].ret.I=T0;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
//digiplay/Camera
static Field *f_2067044359_10=NULL,*f_2067044359_16=NULL,*f_2067044359_19=NULL,*f_2067044359_22=NULL,*f_2067044359_25=NULL,*f_2067044359_30=NULL,*f_2067044359_34=NULL,*f_2067044359_37=NULL,*f_2067044359_40=NULL,*f_2067044359_44=NULL,*f_2067044359_47=NULL,*f_2067044359_50=NULL,*f_2067044359_53=NULL,*f_2067044359_56=NULL,*f_2067044359_59=NULL,*f_2067044359_62=NULL,*f_2067044359_65=NULL,*f_2067044359_68=NULL,*f_2067044359_71=NULL,*f_2067044359_74=NULL,*f_2067044359_77=NULL,*f_2067044359_80=NULL,*f_2067044359_83=NULL,*f_2067044359_86=NULL,*f_2067044359_112=NULL;
static JLONG m_2067044359_1=0,m_2067044359_9=0,m_2067044359_89=0,m_2067044359_95=0,m_2067044359_99=0,m_2067044359_102=0,m_2067044359_106=0,m_2067044359_115=0,m_2067044359_125=0;
static Object *c_2067044359_2=NULL,*c_2067044359_7=NULL,*c_2067044359_11=NULL,*c_2067044359_121=NULL;
void digiplay_Camera__init____V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	Object *L0,*T0;
	L0=args[0].O;
BB0:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=1;
	  AOTMETHOD(m_2067044359_1,0,1,2); //java/lang/Object:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m_2067044359_1),entry)))(vm,m_2067044359_1,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	AOTCLASS(c_2067044359_7,224);
	T0=alloc_object(vm,c_2067044359_7,0);
	{
	  VAR cargs[]={{.O=T0}};
	  frame->pc=9;
	  AOTMETHOD(m_2067044359_9,224,1,2); //digiplay/Matrix3D:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m_2067044359_9),entry)))(vm,m_2067044359_9,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	if(!f_2067044359_10) { //projectionMatrix;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,10);
	  f_2067044359_10=fld->instance;
	}
	*FIELD_PTR_O(L0,f_2067044359_10->offset) = T0;
	AOTCLASS(c_2067044359_7,224);
	T0=alloc_object(vm,c_2067044359_7,0);
	{
	  VAR cargs[]={{.O=T0}};
	  frame->pc=20;
	  AOTMETHOD(m_2067044359_9,224,1,2); //digiplay/Matrix3D:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m_2067044359_9),entry)))(vm,m_2067044359_9,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	if(!f_2067044359_16) { //invertMatrix;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,16);
	  f_2067044359_16=fld->instance;
	}
	*FIELD_PTR_O(L0,f_2067044359_16->offset) = T0;
	AOTCLASS(c_2067044359_7,224);
	T0=alloc_object(vm,c_2067044359_7,0);
	{
	  VAR cargs[]={{.O=T0}};
	  frame->pc=31;
	  AOTMETHOD(m_2067044359_9,224,1,2); //digiplay/Matrix3D:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m_2067044359_9),entry)))(vm,m_2067044359_9,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	if(!f_2067044359_19) { //combinedMatrix;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,19);
	  f_2067044359_19=fld->instance;
	}
	*FIELD_PTR_O(L0,f_2067044359_19->offset) = T0;
	AOTCLASS(c_2067044359_7,224);
	T0=alloc_object(vm,c_2067044359_7,0);
	{
	  VAR cargs[]={{.O=T0}};
	  frame->pc=42;
	  AOTMETHOD(m_2067044359_9,224,1,2); //digiplay/Matrix3D:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m_2067044359_9),entry)))(vm,m_2067044359_9,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	if(!f_2067044359_22) { //localMatrix;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,22);
	  f_2067044359_22=fld->instance;
	}
	*FIELD_PTR_O(L0,f_2067044359_22->offset) = T0;
	if(!f_2067044359_25) { //near;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,25);
	  f_2067044359_25=fld->instance;
	}
	*FIELD_PTR_F(L0,f_2067044359_25->offset) = 1;
	if(!f_2067044359_30) { //far;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,30);
	  f_2067044359_30=fld->instance;
	}
	*FIELD_PTR_F(L0,f_2067044359_30->offset) = 2000.0;
	if(!f_2067044359_34) { //fov;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,34);
	  f_2067044359_34=fld->instance;
	}
	*FIELD_PTR_F(L0,f_2067044359_34->offset) = 20.0;
	if(!f_2067044359_37) { //YUp;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,37);
	  f_2067044359_37=fld->instance;
	}
	*FIELD_PTR_F(L0,f_2067044359_37->offset) = 1;
	if(!f_2067044359_40) { //dirty;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,40);
	  f_2067044359_40=fld->instance;
	}
	*FIELD_PTR_Z(L0,f_2067044359_40->offset) = 1;
	if(!f_2067044359_44) { //scaleX;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,44);
	  f_2067044359_44=fld->instance;
	}
	*FIELD_PTR_F(L0,f_2067044359_44->offset) = 1;
	if(!f_2067044359_47) { //scaleY;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,47);
	  f_2067044359_47=fld->instance;
	}
	*FIELD_PTR_F(L0,f_2067044359_47->offset) = 1;
	if(!f_2067044359_50) { //scaleZ;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,50);
	  f_2067044359_50=fld->instance;
	}
	*FIELD_PTR_F(L0,f_2067044359_50->offset) = 1;
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Camera_setTarget__FFF_V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JFLOAT L1,L2,L3;
	Object *L0;
	L0=args[0].O;
	L1=args[1].F;
	L2=args[2].F;
	L3=args[3].F;
BB0:
	if(!f_2067044359_53) { //targetX;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,53);
	  f_2067044359_53=fld->instance;
	}
	*FIELD_PTR_F(L0,f_2067044359_53->offset) = L1;
	if(!f_2067044359_56) { //targetY;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,56);
	  f_2067044359_56=fld->instance;
	}
	*FIELD_PTR_F(L0,f_2067044359_56->offset) = L2;
	if(!f_2067044359_59) { //targetZ;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,59);
	  f_2067044359_59=fld->instance;
	}
	*FIELD_PTR_F(L0,f_2067044359_59->offset) = L3;
	if(!f_2067044359_40) { //dirty;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,40);
	  f_2067044359_40=fld->instance;
	}
	*FIELD_PTR_Z(L0,f_2067044359_40->offset) = 1;
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Camera_getCombinedMatrix___Ldigiplay_Matrix3D_(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JFLOAT L1,L2,L3,L4,L5,T1,T2,T3,T5,T6,T7,T8;
	JINT T0;
	Object *L0,*T4,*T9,*T10;
	L0=args[0].O;
BB0:
	AOTFIELD(f_2067044359_40,255,256,212); //digiplay/Camera:dirty:Z;
	if(!L0) { frame->pc = 1; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_Z(L0,f_2067044359_40->offset);
	if(T0==0) goto BB195;
BB7:
	AOTFIELD(f_2067044359_62,255,16,112); //digiplay/Camera:x:F;
	if(!L0) { frame->pc = 8; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_F(L0,f_2067044359_62->offset);
	L1=T1;
	AOTFIELD(f_2067044359_65,255,18,112); //digiplay/Camera:y:F;
	if(!L0) { frame->pc = 13; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_F(L0,f_2067044359_65->offset);
	L2=T1;
	AOTFIELD(f_2067044359_68,255,257,112); //digiplay/Camera:z:F;
	if(!L0) { frame->pc = 18; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_F(L0,f_2067044359_68->offset);
	L3=T1;
	AOTFIELD(f_2067044359_71,255,121,112); //digiplay/Camera:width:F;
	if(!L0) { frame->pc = 23; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_F(L0,f_2067044359_71->offset);
	L4=T1;
	AOTFIELD(f_2067044359_74,255,123,112); //digiplay/Camera:height:F;
	if(!L0) { frame->pc = 29; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_F(L0,f_2067044359_74->offset);
	L5=T1;
	AOTFIELD(f_2067044359_77,255,258,212); //digiplay/Camera:isOrtho:Z;
	if(!L0) { frame->pc = 35; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_Z(L0,f_2067044359_77->offset);
	if(T0==0) goto BB114;
BB41:
	T1=-L1;
	T2 = L4 / 2;
	T3 = T1 + T2;
	L1=T3;
	T1=-L2;
	T2 = L5 / 2;
	T3 = T1 + T2;
	L2=T3;
	T1=-L3;
	L3=T1;
	AOTFIELD(f_2067044359_22,255,259,235); //digiplay/Camera:localMatrix:Ldigiplay/Matrix3D;
	if(!L0) { frame->pc = 61; throw_null(vm); goto __EXCEPTION; }
	T4 = *FIELD_PTR_O(L0,f_2067044359_22->offset);
	AOTFIELD(f_2067044359_80,255,260,112); //digiplay/Camera:rotationX:F;
	if(!L0) { frame->pc = 68; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_F(L0,f_2067044359_80->offset);
	AOTFIELD(f_2067044359_83,255,261,112); //digiplay/Camera:rotationY:F;
	if(!L0) { frame->pc = 72; throw_null(vm); goto __EXCEPTION; }
	T2 = *FIELD_PTR_F(L0,f_2067044359_83->offset);
	AOTFIELD(f_2067044359_86,255,262,112); //digiplay/Camera:rotationZ:F;
	if(!L0) { frame->pc = 76; throw_null(vm); goto __EXCEPTION; }
	T3 = *FIELD_PTR_F(L0,f_2067044359_86->offset);
	AOTFIELD(f_2067044359_44,255,116,112); //digiplay/Camera:scaleX:F;
	if(!L0) { frame->pc = 80; throw_null(vm); goto __EXCEPTION; }
	T5 = *FIELD_PTR_F(L0,f_2067044359_44->offset);
	AOTFIELD(f_2067044359_47,255,118,112); //digiplay/Camera:scaleY:F;
	if(!L0) { frame->pc = 84; throw_null(vm); goto __EXCEPTION; }
	T6 = *FIELD_PTR_F(L0,f_2067044359_47->offset);
	AOTFIELD(f_2067044359_50,255,263,112); //digiplay/Camera:scaleZ:F;
	if(!L0) { frame->pc = 88; throw_null(vm); goto __EXCEPTION; }
	T7 = *FIELD_PTR_F(L0,f_2067044359_50->offset);
	{
	  VAR cargs[]={{.O=T4},{.F=L1},{.F=L2},{.F=L3},{.F=T1},{.F=T2},{.F=T3},{.F=T5},{.F=T6},{.F=T7}};
	  frame->pc=91;
	  AOTVMETHOD(m_2067044359_89,224,264,265,vTableIndex); //digiplay/Matrix3D:compose:(FFFFFFFFF)V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_2067044359_89];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	AOTFIELD(f_2067044359_10,255,266,235); //digiplay/Camera:projectionMatrix:Ldigiplay/Matrix3D;
	if(!L0) { frame->pc = 95; throw_null(vm); goto __EXCEPTION; }
	T4 = *FIELD_PTR_O(L0,f_2067044359_10->offset);
	{
	  VAR cargs[]={{.O=T4},{.F=0},{.F=L4},{.F=L5},{.F=0},{.F=-999999.0},{.F=999999.0}};
	  frame->pc=108;
	  AOTVMETHOD(m_2067044359_95,224,267,158,vTableIndex); //digiplay/Matrix3D:orthographic:(FFFFFF)V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_2067044359_95];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	goto BB175;
BB114:
	AOTFIELD(f_2067044359_22,255,259,235); //digiplay/Camera:localMatrix:Ldigiplay/Matrix3D;
	if(!L0) { frame->pc = 115; throw_null(vm); goto __EXCEPTION; }
	T4 = *FIELD_PTR_O(L0,f_2067044359_22->offset);
	AOTFIELD(f_2067044359_62,255,16,112); //digiplay/Camera:x:F;
	if(!L0) { frame->pc = 119; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_F(L0,f_2067044359_62->offset);
	AOTFIELD(f_2067044359_65,255,18,112); //digiplay/Camera:y:F;
	if(!L0) { frame->pc = 123; throw_null(vm); goto __EXCEPTION; }
	T2 = *FIELD_PTR_F(L0,f_2067044359_65->offset);
	AOTFIELD(f_2067044359_68,255,257,112); //digiplay/Camera:z:F;
	if(!L0) { frame->pc = 127; throw_null(vm); goto __EXCEPTION; }
	T3 = *FIELD_PTR_F(L0,f_2067044359_68->offset);
	AOTFIELD(f_2067044359_53,255,268,112); //digiplay/Camera:targetX:F;
	if(!L0) { frame->pc = 131; throw_null(vm); goto __EXCEPTION; }
	T5 = *FIELD_PTR_F(L0,f_2067044359_53->offset);
	AOTFIELD(f_2067044359_56,255,269,112); //digiplay/Camera:targetY:F;
	if(!L0) { frame->pc = 135; throw_null(vm); goto __EXCEPTION; }
	T6 = *FIELD_PTR_F(L0,f_2067044359_56->offset);
	AOTFIELD(f_2067044359_59,255,270,112); //digiplay/Camera:targetZ:F;
	if(!L0) { frame->pc = 139; throw_null(vm); goto __EXCEPTION; }
	T7 = *FIELD_PTR_F(L0,f_2067044359_59->offset);
	AOTFIELD(f_2067044359_37,255,271,112); //digiplay/Camera:YUp:F;
	if(!L0) { frame->pc = 144; throw_null(vm); goto __EXCEPTION; }
	T8 = *FIELD_PTR_F(L0,f_2067044359_37->offset);
	{
	  VAR cargs[]={{.O=T4},{.F=T1},{.F=T2},{.F=T3},{.F=T5},{.F=T6},{.F=T7},{.F=0},{.F=T8},{.F=0}};
	  frame->pc=148;
	  AOTVMETHOD(m_2067044359_99,224,272,265,vTableIndex); //digiplay/Matrix3D:lookAt:(FFFFFFFFF)V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_2067044359_99];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	AOTFIELD(f_2067044359_10,255,266,235); //digiplay/Camera:projectionMatrix:Ldigiplay/Matrix3D;
	if(!L0) { frame->pc = 152; throw_null(vm); goto __EXCEPTION; }
	T4 = *FIELD_PTR_O(L0,f_2067044359_10->offset);
	AOTFIELD(f_2067044359_25,255,273,112); //digiplay/Camera:near:F;
	if(!L0) { frame->pc = 156; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_F(L0,f_2067044359_25->offset);
	AOTFIELD(f_2067044359_30,255,274,112); //digiplay/Camera:far:F;
	if(!L0) { frame->pc = 160; throw_null(vm); goto __EXCEPTION; }
	T2 = *FIELD_PTR_F(L0,f_2067044359_30->offset);
	AOTFIELD(f_2067044359_34,255,275,112); //digiplay/Camera:fov:F;
	if(!L0) { frame->pc = 164; throw_null(vm); goto __EXCEPTION; }
	T3 = *FIELD_PTR_F(L0,f_2067044359_34->offset);
	T5 = L4 / L5;
	{
	  VAR cargs[]={{.O=T4},{.F=T1},{.F=T2},{.F=T3},{.F=T5}};
	  frame->pc=172;
	  AOTVMETHOD(m_2067044359_102,224,276,277,vTableIndex); //digiplay/Matrix3D:perspective:(FFFF)V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_2067044359_102];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
BB175:
	if(!f_2067044359_40) { //dirty;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,40);
	  f_2067044359_40=fld->instance;
	}
	*FIELD_PTR_Z(L0,f_2067044359_40->offset) = 0;
	AOTFIELD(f_2067044359_10,255,266,235); //digiplay/Camera:projectionMatrix:Ldigiplay/Matrix3D;
	if(!L0) { frame->pc = 181; throw_null(vm); goto __EXCEPTION; }
	T4 = *FIELD_PTR_O(L0,f_2067044359_10->offset);
	AOTFIELD(f_2067044359_22,255,259,235); //digiplay/Camera:localMatrix:Ldigiplay/Matrix3D;
	if(!L0) { frame->pc = 185; throw_null(vm); goto __EXCEPTION; }
	T9 = *FIELD_PTR_O(L0,f_2067044359_22->offset);
	AOTFIELD(f_2067044359_19,255,278,235); //digiplay/Camera:combinedMatrix:Ldigiplay/Matrix3D;
	if(!L0) { frame->pc = 189; throw_null(vm); goto __EXCEPTION; }
	T10 = *FIELD_PTR_O(L0,f_2067044359_19->offset);
	{
	  VAR cargs[]={{.O=T4},{.O=T9},{.O=T10}};
	  frame->pc=192;
	  AOTMETHOD(m_2067044359_106,224,232,233); //digiplay/Matrix3D:multiply:(Ldigiplay/Matrix3D;Ldigiplay/Matrix3D;Ldigiplay/Matrix3D;)V;
	  ((VM_CALL)(MTH(((Object*)m_2067044359_106),entry)))(vm,m_2067044359_106,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
BB195:
	AOTFIELD(f_2067044359_19,255,278,235); //digiplay/Camera:combinedMatrix:Ldigiplay/Matrix3D;
	if(!L0) { frame->pc = 196; throw_null(vm); goto __EXCEPTION; }
	T4 = *FIELD_PTR_O(L0,f_2067044359_19->offset);
	vm->FP--;vm->frames[vm->FP].ret.O=T4;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Camera_setupFor2D__FF_Ldigiplay_Matrix3D_(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JFLOAT L1,L2,T0,T1,T2;
	Object *L0,*T3;
	L0=args[0].O;
	L1=args[1].F;
	L2=args[2].F;
BB0:
	T0 = L1 / 2;
	if(!f_2067044359_62) { //x;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,62);
	  f_2067044359_62=fld->instance;
	}
	*FIELD_PTR_F(L0,f_2067044359_62->offset) = T0;
	if(!f_2067044359_53) { //targetX;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,53);
	  f_2067044359_53=fld->instance;
	}
	*FIELD_PTR_F(L0,f_2067044359_53->offset) = T0;
	T0 = L2 / 2;
	if(!f_2067044359_65) { //y;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,65);
	  f_2067044359_65=fld->instance;
	}
	*FIELD_PTR_F(L0,f_2067044359_65->offset) = T0;
	if(!f_2067044359_56) { //targetY;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,56);
	  f_2067044359_56=fld->instance;
	}
	*FIELD_PTR_F(L0,f_2067044359_56->offset) = T0;
	if(!f_2067044359_37) { //YUp;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,37);
	  f_2067044359_37=fld->instance;
	}
	*FIELD_PTR_F(L0,f_2067044359_37->offset) = -1.0;
	if(!f_2067044359_34) { //fov;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,34);
	  f_2067044359_34=fld->instance;
	}
	*FIELD_PTR_F(L0,f_2067044359_34->offset) = 20.0;
	if(!f_2067044359_30) { //far;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,30);
	  f_2067044359_30=fld->instance;
	}
	*FIELD_PTR_F(L0,f_2067044359_30->offset) = 100000.0;
	T0=-L2;
	AOTFIELD(f_2067044359_112,255,279,112); //digiplay/Camera:ZDIVISOR:F;
	T1 = *((JFLOAT*)(CLS(f_2067044359_112->declaringClass,global) + f_2067044359_112->offset));
	T2 = T0 / T1;
	if(!f_2067044359_68) { //z;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,68);
	  f_2067044359_68=fld->instance;
	}
	*FIELD_PTR_F(L0,f_2067044359_68->offset) = T2;
	if(!f_2067044359_59) { //targetZ;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,59);
	  f_2067044359_59=fld->instance;
	}
	*FIELD_PTR_F(L0,f_2067044359_59->offset) = 0;
	if(!f_2067044359_71) { //width;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,71);
	  f_2067044359_71=fld->instance;
	}
	*FIELD_PTR_F(L0,f_2067044359_71->offset) = L1;
	if(!f_2067044359_74) { //height;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,74);
	  f_2067044359_74=fld->instance;
	}
	*FIELD_PTR_F(L0,f_2067044359_74->offset) = L2;
	if(!f_2067044359_40) { //dirty;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,40);
	  f_2067044359_40=fld->instance;
	}
	*FIELD_PTR_Z(L0,f_2067044359_40->offset) = 1;
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=73;
	  AOTVMETHOD(m_2067044359_115,255,280,281,vTableIndex); //digiplay/Camera:getCombinedMatrix:()Ldigiplay/Matrix3D;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_2067044359_115];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T3=frame->ret.O;
	}
	
	vm->FP--;vm->frames[vm->FP].ret.O=T3;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_Camera__clinit____V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JDOUBLE T0,T1;
	JFLOAT T2;
BB0:
	{
	  VAR cargs[]={{.D=0.17453292649980456}};
	  frame->pc=6;
	  AOTMETHOD(m_2067044359_125,19,227,161); //java/lang/Math:tan:(D)D;
	  ((VM_CALL)(MTH(((Object*)m_2067044359_125),entry)))(vm,m_2067044359_125,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T0=frame->ret.D;
	}
	
	T1 = 2.0 * T0;
	T2=(JFLOAT)T1;
	if(!f_2067044359_112) { //ZDIVISOR;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,112);
	  f_2067044359_112=fld->instance;
	}
	*((JFLOAT*)((CLS(f_2067044359_112->declaringClass,global))+f_2067044359_112->offset)) = T2;
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
//digiplay/Net
static JLONG m_1665510071_1=0;
static Object *c_1665510071_2=NULL,*c_1665510071_7=NULL,*c_1665510071_19=NULL,*c_1665510071_22=NULL;
void digiplay_Net__init____V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	Object *L0;
	L0=args[0].O;
BB0:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=1;
	  AOTMETHOD(m_1665510071_1,0,1,2); //java/lang/Object:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m_1665510071_1),entry)))(vm,m_1665510071_1,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
//digiplay/Net$HttpListener
static Object *c2097787127_1=NULL,*c2097787127_3=NULL,*c2097787127_12=NULL;
//digiplay/ByteArrayCompletable
static Field *f292908777_13=NULL;
static JLONG m292908777_1=0,m292908777_7=0,m292908777_19=0;
static Object *c292908777_2=NULL,*c292908777_8=NULL,*c292908777_14=NULL,*c292908777_22=NULL;
void digiplay_ByteArrayCompletable__init____V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	Object *L0;
	L0=args[0].O;
BB0:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=1;
	  AOTMETHOD(m292908777_1,0,1,2); //java/lang/Object:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m292908777_1),entry)))(vm,m292908777_1,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_ByteArrayCompletable_complete__JI_V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JINT L0;
	JLONG L2;
	Object *L1,*T0;
	L1=args[0].O;
	L2=args[1].J;
	L0=args[2].I;
BB0:
	if(L0<=0) goto BB13;
BB4:
	{
	  VAR cargs[]={{.J=L2},{.I=L0}};
	  frame->pc=7;
	  AOTMETHOD(m292908777_7,101,222,223); //gamavm/VM:wrapBytes:(JI)[B;
	  ((VM_CALL)(MTH(((Object*)m292908777_7),entry)))(vm,m292908777_7,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T0=frame->ret.O;
	}
	
	if(!f292908777_13) { //bytes;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,13);
	  f292908777_13=fld->instance;
	}
	*FIELD_PTR_O(L1,f292908777_13->offset) = T0;
BB13:
	{
	  VAR cargs[]={{.O=L1}};
	  frame->pc=14;
	  AOTVMETHOD(m292908777_19,104,282,2,vTableIndex); //digiplay/ByteArrayCompletable:onComplete:()V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m292908777_19];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_ByteArrayCompletable_onComplete___V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
BB0:
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
//gamavm/apple/Bridge
static Object *c278786728_1=NULL,*c278786728_3=NULL,*c278786728_5=NULL;
//gamavm/apple/NSDictionary
static JLONG m_523793414_1=0;
static Object *c_523793414_2=NULL,*c_523793414_7=NULL;
void gamavm_apple_NSDictionary__init____V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	Object *L0;
	L0=args[0].O;
BB0:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=1;
	  AOTMETHOD(m_523793414_1,283,1,2); //gamavm/apple/NSObject:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m_523793414_1),entry)))(vm,m_523793414_1,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
//gamavm/apple/ObjC
static JLONG m831945995_1=0;
static Object *c831945995_2=NULL,*c831945995_3=NULL;
void gamavm_apple_ObjC__init____V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	Object *L0;
	L0=args[0].O;
BB0:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=1;
	  AOTMETHOD(m831945995_1,0,1,2); //java/lang/Object:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m831945995_1),entry)))(vm,m831945995_1,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
//gamavm/apple/NSProtocol
static Object *c587477756_1=NULL,*c587477756_3=NULL;
//gamavm/apple/ObjCClass
static Field *f_1063802067_2=NULL,*f_1063802067_14=NULL;
static JLONG m_1063802067_1=0,m_1063802067_3=0,m_1063802067_5=0,m_1063802067_8=0,m_1063802067_10=0,m_1063802067_11=0,m_1063802067_12=0,m_1063802067_13=0,m_1063802067_15=0,m_1063802067_17=0;
static Object *c_1063802067_4=NULL,*c_1063802067_6=NULL,*c_1063802067_7=NULL,*c_1063802067_16=NULL,*c_1063802067_18=NULL,*c_1063802067_46=NULL,*c_1063802067_49=NULL;
void gamavm_apple_ObjCClass__init____V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	Object *L0;
	L0=args[0].O;
BB0:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=1;
	  AOTMETHOD(m_1063802067_1,283,1,2); //gamavm/apple/NSObject:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m_1063802067_1),entry)))(vm,m_1063802067_1,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void gamavm_apple_ObjCClass_get__Ljava_lang_String__Lgamavm_apple_ObjCClass_(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JLONG L2,T1;
	Object *L0,*L1,*T0,*T2;
	L0=args[0].O;
BB0:
	AOTFIELD(f_1063802067_2,284,285,286); //gamavm/apple/ObjCClass:classes:Ljava/util/Map;
	T0 = *((Object**)(CLS(f_1063802067_2->declaringClass,global) + f_1063802067_2->offset));
	{
	  VAR cargs[]={{.O=T0},{.O=L0}};
	  frame->pc=4;
	  AOTVMETHOD(m_1063802067_3,287,288,289,iTableIndex); //java/util/Map:get:(Ljava/lang/Object;)Ljava/lang/Object;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->itable[m_1063802067_3];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T0=frame->ret.O;
	}
	
	check_cast(vm,T0,4);
	L1=T0;
	if(L1!=NULL) goto BB79;
BB17:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=18;
	  AOTMETHOD(m_1063802067_5,290,291,108); //gamavm/apple/ObjC:objc_getClass:(Ljava/lang/String;)J;
	  ((VM_CALL)(MTH(((Object*)m_1063802067_5),entry)))(vm,m_1063802067_5,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T1=frame->ret.J;
	}
	
	L2=T1;
	T1 = L2 == 0 ? 0 : (L2 > 0 ? 1 : -1);
	if(T1!=0) goto BB55;
BB28:
	AOTCLASS(c_1063802067_6,109);
	T0=alloc_object(vm,c_1063802067_6,0);
	AOTCLASS(c_1063802067_7,31);
	T2=alloc_object(vm,c_1063802067_7,0);
	{
	  VAR cargs[]={{.O=T2}};
	  frame->pc=36;
	  AOTMETHOD(m_1063802067_8,31,1,2); //java/lang/StringBuilder:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m_1063802067_8),entry)))(vm,m_1063802067_8,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	{
	  VAR cargs[]={{.O=T2},{.O=aot_strings[292]}};
	  frame->pc=41;
	  AOTVMETHOD(m_1063802067_10,31,33,34,vTableIndex); //java/lang/StringBuilder:append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_1063802067_10];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T2=frame->ret.O;
	}
	
	{
	  VAR cargs[]={{.O=T2},{.O=L0}};
	  frame->pc=45;
	  AOTVMETHOD(m_1063802067_10,31,33,34,vTableIndex); //java/lang/StringBuilder:append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_1063802067_10];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T2=frame->ret.O;
	}
	
	{
	  VAR cargs[]={{.O=T2}};
	  frame->pc=48;
	  AOTVMETHOD(m_1063802067_11,31,36,37,vTableIndex); //java/lang/StringBuilder:toString:()Ljava/lang/String;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_1063802067_11];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T2=frame->ret.O;
	}
	
	{
	  VAR cargs[]={{.O=T0},{.O=T2}};
	  frame->pc=51;
	  AOTMETHOD(m_1063802067_12,109,1,40); //java/lang/RuntimeException:<init>:(Ljava/lang/String;)V;
	  ((VM_CALL)(MTH(((Object*)m_1063802067_12),entry)))(vm,m_1063802067_12,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	throw_exception(vm,T0);
BB55:
	AOTCLASS(c_1063802067_4,284);
	T0=alloc_object(vm,c_1063802067_4,0);
	{
	  VAR cargs[]={{.O=T0}};
	  frame->pc=59;
	  AOTMETHOD(m_1063802067_13,284,1,2); //gamavm/apple/ObjCClass:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m_1063802067_13),entry)))(vm,m_1063802067_13,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	L1=T0;
	if(!f_1063802067_14) { //handle;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,14);
	  f_1063802067_14=fld->instance;
	}
	*FIELD_PTR_J(L1,f_1063802067_14->offset) = L2;
	AOTFIELD(f_1063802067_2,284,285,286); //gamavm/apple/ObjCClass:classes:Ljava/util/Map;
	T0 = *((Object**)(CLS(f_1063802067_2->declaringClass,global) + f_1063802067_2->offset));
	{
	  VAR cargs[]={{.O=T0},{.O=L0},{.O=L1}};
	  frame->pc=73;
	  AOTVMETHOD(m_1063802067_15,287,293,294,iTableIndex); //java/util/Map:put:(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->itable[m_1063802067_15];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T0=frame->ret.O;
	}
BB79:
	vm->FP--;vm->frames[vm->FP].ret.O=L1;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void gamavm_apple_ObjCClass_register__Ljava_lang_Class__Lgamavm_apple_ObjCClass_(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
BB0:
	vm->FP--;vm->frames[vm->FP].ret.O=NULL;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void gamavm_apple_ObjCClass__clinit____V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	Object *T0;
BB0:
	AOTCLASS(c_1063802067_16,295);
	T0=alloc_object(vm,c_1063802067_16,0);
	{
	  VAR cargs[]={{.O=T0}};
	  frame->pc=4;
	  AOTMETHOD(m_1063802067_17,295,1,2); //java/util/HashMap:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m_1063802067_17),entry)))(vm,m_1063802067_17,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	if(!f_1063802067_2) { //classes;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,2);
	  f_1063802067_2=fld->instance;
	}
	*((Object**)((CLS(f_1063802067_2->declaringClass,global))+f_1063802067_2->offset)) = T0;
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
//gamavm/apple/Selector
static Field *f_1671825602_7=NULL,*f_1671825602_26=NULL;
static JLONG m_1671825602_1=0,m_1671825602_13=0,m_1671825602_19=0,m_1671825602_20=0,m_1671825602_34=0,m_1671825602_37=0,m_1671825602_41=0,m_1671825602_45=0,m_1671825602_48=0,m_1671825602_54=0;
static Object *c_1671825602_2=NULL,*c_1671825602_8=NULL,*c_1671825602_14=NULL,*c_1671825602_21=NULL,*c_1671825602_30=NULL,*c_1671825602_32=NULL,*c_1671825602_52=NULL;
void gamavm_apple_Selector__init____V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	Object *L0;
	L0=args[0].O;
BB0:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=1;
	  AOTMETHOD(m_1671825602_1,283,1,2); //gamavm/apple/NSObject:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m_1671825602_1),entry)))(vm,m_1671825602_1,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void gamavm_apple_Selector_register__Ljava_lang_String__Lgamavm_apple_Selector_(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JLONG T1;
	Object *L0,*L1,*T0,*T2;
	L0=args[0].O;
BB0:
	AOTFIELD(f_1671825602_7,296,297,286); //gamavm/apple/Selector:selectors:Ljava/util/Map;
	T0 = *((Object**)(CLS(f_1671825602_7->declaringClass,global) + f_1671825602_7->offset));
	{
	  VAR cargs[]={{.O=T0},{.O=L0}};
	  frame->pc=4;
	  AOTVMETHOD(m_1671825602_13,287,288,289,iTableIndex); //java/util/Map:get:(Ljava/lang/Object;)Ljava/lang/Object;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->itable[m_1671825602_13];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T0=frame->ret.O;
	}
	
	check_cast(vm,T0,8);
	L1=T0;
	if(L1!=NULL) goto BB80;
BB17:
	AOTCLASS(c_1671825602_8,296);
	T0=alloc_object(vm,c_1671825602_8,0);
	{
	  VAR cargs[]={{.O=T0}};
	  frame->pc=21;
	  AOTMETHOD(m_1671825602_19,296,1,2); //gamavm/apple/Selector:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m_1671825602_19),entry)))(vm,m_1671825602_19,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	L1=T0;
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=27;
	  AOTMETHOD(m_1671825602_20,290,298,108); //gamavm/apple/ObjC:sel_registerName:(Ljava/lang/String;)J;
	  ((VM_CALL)(MTH(((Object*)m_1671825602_20),entry)))(vm,m_1671825602_20,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T1=frame->ret.J;
	}
	
	if(!f_1671825602_26) { //handle;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,26);
	  f_1671825602_26=fld->instance;
	}
	*FIELD_PTR_J(L1,f_1671825602_26->offset) = T1;
	AOTFIELD(f_1671825602_26,296,100,46); //gamavm/apple/Selector:handle:J;
	if(!L1) { frame->pc = 34; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_J(L1,f_1671825602_26->offset);
	T1 = T1 == 0 ? 0 : (T1 > 0 ? 1 : -1);
	if(T1!=0) goto BB69;
BB42:
	AOTCLASS(c_1671825602_30,109);
	T0=alloc_object(vm,c_1671825602_30,0);
	AOTCLASS(c_1671825602_32,31);
	T2=alloc_object(vm,c_1671825602_32,0);
	{
	  VAR cargs[]={{.O=T2}};
	  frame->pc=50;
	  AOTMETHOD(m_1671825602_34,31,1,2); //java/lang/StringBuilder:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m_1671825602_34),entry)))(vm,m_1671825602_34,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	{
	  VAR cargs[]={{.O=T2},{.O=aot_strings[299]}};
	  frame->pc=55;
	  AOTVMETHOD(m_1671825602_37,31,33,34,vTableIndex); //java/lang/StringBuilder:append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_1671825602_37];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T2=frame->ret.O;
	}
	
	{
	  VAR cargs[]={{.O=T2},{.O=L0}};
	  frame->pc=59;
	  AOTVMETHOD(m_1671825602_37,31,33,34,vTableIndex); //java/lang/StringBuilder:append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_1671825602_37];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T2=frame->ret.O;
	}
	
	{
	  VAR cargs[]={{.O=T2}};
	  frame->pc=62;
	  AOTVMETHOD(m_1671825602_41,31,36,37,vTableIndex); //java/lang/StringBuilder:toString:()Ljava/lang/String;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_1671825602_41];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T2=frame->ret.O;
	}
	
	{
	  VAR cargs[]={{.O=T0},{.O=T2}};
	  frame->pc=65;
	  AOTMETHOD(m_1671825602_45,109,1,40); //java/lang/RuntimeException:<init>:(Ljava/lang/String;)V;
	  ((VM_CALL)(MTH(((Object*)m_1671825602_45),entry)))(vm,m_1671825602_45,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	throw_exception(vm,T0);
BB69:
	AOTFIELD(f_1671825602_7,296,297,286); //gamavm/apple/Selector:selectors:Ljava/util/Map;
	T0 = *((Object**)(CLS(f_1671825602_7->declaringClass,global) + f_1671825602_7->offset));
	{
	  VAR cargs[]={{.O=T0},{.O=L0},{.O=L1}};
	  frame->pc=74;
	  AOTVMETHOD(m_1671825602_48,287,293,294,iTableIndex); //java/util/Map:put:(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->itable[m_1671825602_48];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T0=frame->ret.O;
	}
BB80:
	vm->FP--;vm->frames[vm->FP].ret.O=L1;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void gamavm_apple_Selector__clinit____V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	Object *T0;
BB0:
	AOTCLASS(c_1671825602_52,295);
	T0=alloc_object(vm,c_1671825602_52,0);
	{
	  VAR cargs[]={{.O=T0}};
	  frame->pc=4;
	  AOTMETHOD(m_1671825602_54,295,1,2); //java/util/HashMap:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m_1671825602_54),entry)))(vm,m_1671825602_54,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	if(!f_1671825602_7) { //selectors;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,7);
	  f_1671825602_7=fld->instance;
	}
	*((Object**)((CLS(f_1671825602_7->declaringClass,global))+f_1671825602_7->offset)) = T0;
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
//gamavm/apple/NSObject
static Field *f_1423961949_7=NULL;
static JLONG m_1423961949_1=0;
static Object *c_1423961949_2=NULL,*c_1423961949_8=NULL,*c_1423961949_22=NULL;
void gamavm_apple_NSObject__init____V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	Object *L0;
	L0=args[0].O;
BB0:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=1;
	  AOTMETHOD(m_1423961949_1,0,1,2); //java/lang/Object:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m_1423961949_1),entry)))(vm,m_1423961949_1,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void gamavm_apple_NSObject_getHandle___J(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JLONG T0;
	Object *L0;
	L0=args[0].O;
BB0:
	AOTFIELD(f_1423961949_7,283,100,46); //gamavm/apple/NSObject:handle:J;
	if(!L0) { frame->pc = 1; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_J(L0,f_1423961949_7->offset);
	vm->FP--;vm->frames[vm->FP].ret.J=T0;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void gamavm_apple_NSObject_finalize___V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
BB0:
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
//gamavm/apple/NSMutableObject
static JLONG m351079457_1=0;
static Object *c351079457_2=NULL,*c351079457_7=NULL,*c351079457_16=NULL;
void gamavm_apple_NSMutableObject__init____V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	Object *L0;
	L0=args[0].O;
BB0:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=1;
	  AOTMETHOD(m351079457_1,283,1,2); //gamavm/apple/NSObject:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m351079457_1),entry)))(vm,m351079457_1,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void gamavm_apple_NSMutableObject_finalize___V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
BB0:
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
//gamavm/jni/JniClass
static Field *f2040770247_2=NULL,*f2040770247_14=NULL;
static JLONG m2040770247_1=0,m2040770247_3=0,m2040770247_5=0,m2040770247_8=0,m2040770247_10=0,m2040770247_11=0,m2040770247_12=0,m2040770247_13=0,m2040770247_15=0,m2040770247_16=0,m2040770247_18=0;
static Object *c2040770247_4=NULL,*c2040770247_6=NULL,*c2040770247_7=NULL,*c2040770247_17=NULL,*c2040770247_19=NULL,*c2040770247_47=NULL,*c2040770247_55=NULL;
void gamavm_jni_JniClass__init____V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	Object *L0;
	L0=args[0].O;
BB0:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=1;
	  AOTMETHOD(m2040770247_1,300,1,2); //gamavm/jni/JniObject:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m2040770247_1),entry)))(vm,m2040770247_1,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void gamavm_jni_JniClass_get__Ljava_lang_String__Lgamavm_jni_JniClass_(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JLONG L2,T1;
	Object *L0,*L1,*T0,*T2;
	L0=args[0].O;
BB0:
	AOTFIELD(f2040770247_2,301,285,286); //gamavm/jni/JniClass:classes:Ljava/util/Map;
	T0 = *((Object**)(CLS(f2040770247_2->declaringClass,global) + f2040770247_2->offset));
	{
	  VAR cargs[]={{.O=T0},{.O=L0}};
	  frame->pc=4;
	  AOTVMETHOD(m2040770247_3,287,288,289,iTableIndex); //java/util/Map:get:(Ljava/lang/Object;)Ljava/lang/Object;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->itable[m2040770247_3];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T0=frame->ret.O;
	}
	
	check_cast(vm,T0,4);
	L1=T0;
	if(L1!=NULL) goto BB79;
BB17:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=18;
	  AOTMETHOD(m2040770247_5,301,302,108); //gamavm/jni/JniClass:nativeGet:(Ljava/lang/String;)J;
	  ((VM_CALL)(MTH(((Object*)m2040770247_5),entry)))(vm,m2040770247_5,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T1=frame->ret.J;
	}
	
	L2=T1;
	T1 = L2 == 0 ? 0 : (L2 > 0 ? 1 : -1);
	if(T1!=0) goto BB55;
BB28:
	AOTCLASS(c2040770247_6,109);
	T0=alloc_object(vm,c2040770247_6,0);
	AOTCLASS(c2040770247_7,31);
	T2=alloc_object(vm,c2040770247_7,0);
	{
	  VAR cargs[]={{.O=T2}};
	  frame->pc=36;
	  AOTMETHOD(m2040770247_8,31,1,2); //java/lang/StringBuilder:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m2040770247_8),entry)))(vm,m2040770247_8,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	{
	  VAR cargs[]={{.O=T2},{.O=aot_strings[303]}};
	  frame->pc=41;
	  AOTVMETHOD(m2040770247_10,31,33,34,vTableIndex); //java/lang/StringBuilder:append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m2040770247_10];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T2=frame->ret.O;
	}
	
	{
	  VAR cargs[]={{.O=T2},{.O=L0}};
	  frame->pc=45;
	  AOTVMETHOD(m2040770247_10,31,33,34,vTableIndex); //java/lang/StringBuilder:append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m2040770247_10];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T2=frame->ret.O;
	}
	
	{
	  VAR cargs[]={{.O=T2}};
	  frame->pc=48;
	  AOTVMETHOD(m2040770247_11,31,36,37,vTableIndex); //java/lang/StringBuilder:toString:()Ljava/lang/String;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m2040770247_11];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T2=frame->ret.O;
	}
	
	{
	  VAR cargs[]={{.O=T0},{.O=T2}};
	  frame->pc=51;
	  AOTMETHOD(m2040770247_12,109,1,40); //java/lang/RuntimeException:<init>:(Ljava/lang/String;)V;
	  ((VM_CALL)(MTH(((Object*)m2040770247_12),entry)))(vm,m2040770247_12,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	throw_exception(vm,T0);
BB55:
	AOTCLASS(c2040770247_4,301);
	T0=alloc_object(vm,c2040770247_4,0);
	{
	  VAR cargs[]={{.O=T0}};
	  frame->pc=59;
	  AOTMETHOD(m2040770247_13,301,1,2); //gamavm/jni/JniClass:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m2040770247_13),entry)))(vm,m2040770247_13,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	L1=T0;
	if(!f2040770247_14) { //handle;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,14);
	  f2040770247_14=fld->instance;
	}
	*FIELD_PTR_J(L1,f2040770247_14->offset) = L2;
	AOTFIELD(f2040770247_2,301,285,286); //gamavm/jni/JniClass:classes:Ljava/util/Map;
	T0 = *((Object**)(CLS(f2040770247_2->declaringClass,global) + f2040770247_2->offset));
	{
	  VAR cargs[]={{.O=T0},{.O=L0},{.O=L1}};
	  frame->pc=73;
	  AOTVMETHOD(m2040770247_15,287,293,294,iTableIndex); //java/util/Map:put:(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->itable[m2040770247_15];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T0=frame->ret.O;
	}
BB79:
	vm->FP--;vm->frames[vm->FP].ret.O=L1;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void gamavm_jni_JniClass_finalize___V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	Object *L0;
	L0=args[0].O;
BB0:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=1;
	  AOTMETHOD(m2040770247_16,300,304,2); //gamavm/jni/JniObject:finalize:()V;
	  ((VM_CALL)(MTH(((Object*)m2040770247_16),entry)))(vm,m2040770247_16,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void gamavm_jni_JniClass__clinit____V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	Object *T0;
BB0:
	AOTCLASS(c2040770247_17,295);
	T0=alloc_object(vm,c2040770247_17,0);
	{
	  VAR cargs[]={{.O=T0}};
	  frame->pc=4;
	  AOTMETHOD(m2040770247_18,295,1,2); //java/util/HashMap:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m2040770247_18),entry)))(vm,m2040770247_18,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	if(!f2040770247_2) { //classes;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,2);
	  f2040770247_2=fld->instance;
	}
	*((Object**)((CLS(f2040770247_2->declaringClass,global))+f2040770247_2->offset)) = T0;
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
//gamavm/jni/JniBridge
static JLONG m_1183496166_1=0;
static Object *c_1183496166_2=NULL,*c_1183496166_3=NULL;
void gamavm_jni_JniBridge__init____V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	Object *L0;
	L0=args[0].O;
BB0:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=1;
	  AOTMETHOD(m_1183496166_1,0,1,2); //java/lang/Object:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m_1183496166_1),entry)))(vm,m_1183496166_1,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
//gamavm/jni/JniObject
static JLONG m_826062896_1=0;
static Object *c_826062896_2=NULL,*c_826062896_3=NULL,*c_826062896_15=NULL;
void gamavm_jni_JniObject__init____V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	Object *L0;
	L0=args[0].O;
BB0:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=1;
	  AOTMETHOD(m_826062896_1,0,1,2); //java/lang/Object:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m_826062896_1),entry)))(vm,m_826062896_1,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
//gamavm/jni/URL
static JLONG m1734952699_1=0;
static Object *c1734952699_2=NULL,*c1734952699_3=NULL;
void gamavm_jni_URL__init___Ljava_lang_String__V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	Object *L0;
	L0=args[0].O;
BB0:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=1;
	  AOTMETHOD(m1734952699_1,300,1,2); //gamavm/jni/JniObject:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m1734952699_1),entry)))(vm,m1734952699_1,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
//gamavm/jni/JniMethod
static JLONG m_880249486_1=0;
static Object *c_880249486_2=NULL,*c_880249486_3=NULL;
void gamavm_jni_JniMethod__init____V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	Object *L0;
	L0=args[0].O;
BB0:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=1;
	  AOTMETHOD(m_880249486_1,300,1,2); //gamavm/jni/JniObject:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m_880249486_1),entry)))(vm,m_880249486_1,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
//digiplay/net/Socket
static Field *f_1266555143_13=NULL,*f_1266555143_17=NULL,*f_1266555143_28=NULL,*f_1266555143_33=NULL;
static JLONG m_1266555143_1=0,m_1266555143_7=0,m_1266555143_22=0,m_1266555143_30=0;
static Object *c_1266555143_2=NULL,*c_1266555143_8=NULL,*c_1266555143_23=NULL,*c_1266555143_54=NULL,*c_1266555143_57=NULL;
void digiplay_net_Socket__init____V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	Object *L0;
	L0=args[0].O;
BB0:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=1;
	  AOTMETHOD(m_1266555143_1,62,1,2); //java/io/InputStream:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m_1266555143_1),entry)))(vm,m_1266555143_1,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_net_Socket_write___B_V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JINT T0;
	Object *L0,*L1;
	L0=args[0].O;
BB0:
	if(!L1) {throw_null(vm);} T0=L1->length;
	{
	  VAR cargs[]={{.O=L0},{.O=L1},{.I=0},{.I=T0}};
	  frame->pc=5;
	  AOTVMETHOD(m_1266555143_7,305,81,66,vTableIndex); //digiplay/net/Socket:write:([BII)V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_1266555143_7];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_net_Socket_append___BII_V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JINT L1,L3,L5,T1,T2,T3,S0I;
	Object *L0,*L2,*L4,*T0,*T4;
	L0=args[0].O;
	L5=args[2].I;
	L1=args[3].I;
BB0:
	AOTFIELD(f_1266555143_13,305,306,307); //digiplay/net/Socket:buffer:[B;
	if(!L0) { frame->pc = 1; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1266555143_13->offset);
	if(T0==NULL) goto BB21;
BB7:
	AOTFIELD(f_1266555143_13,305,306,307); //digiplay/net/Socket:buffer:[B;
	if(!L0) { frame->pc = 8; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1266555143_13->offset);
	if(!T0) {throw_null(vm);} T1=T0->length;
	AOTFIELD(f_1266555143_17,305,192,4); //digiplay/net/Socket:size:I;
	if(!L0) { frame->pc = 13; throw_null(vm); goto __EXCEPTION; }
	T2 = *FIELD_PTR_I(L0,f_1266555143_17->offset);
	T3 = T1 - T2;
	if(T3>=L1) goto BB73;
BB21:
	AOTFIELD(f_1266555143_13,305,306,307); //digiplay/net/Socket:buffer:[B;
	if(!L0) { frame->pc = 22; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1266555143_13->offset);
	if(T0!=NULL) goto BB33;
BB28:
	/*spill*/S0I=32768;
	goto BB40;
BB33:
	AOTFIELD(f_1266555143_13,305,306,307); //digiplay/net/Socket:buffer:[B;
	if(!L0) { frame->pc = 34; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1266555143_13->offset);
	if(!T0) {throw_null(vm);} T1=T0->length;
	T2 = T1 + L1;
	/*spill*/S0I=T2;
BB40:
	T0 = alloc_array_B(vm,S0I,0);
	L2=T0;
	AOTFIELD(f_1266555143_13,305,306,307); //digiplay/net/Socket:buffer:[B;
	if(!L0) { frame->pc = 45; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1266555143_13->offset);
	if(T0==NULL) goto BB67;
BB51:
	AOTFIELD(f_1266555143_13,305,306,307); //digiplay/net/Socket:buffer:[B;
	if(!L0) { frame->pc = 52; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1266555143_13->offset);
	AOTFIELD(f_1266555143_13,305,306,307); //digiplay/net/Socket:buffer:[B;
	if(!L0) { frame->pc = 60; throw_null(vm); goto __EXCEPTION; }
	T4 = *FIELD_PTR_O(L0,f_1266555143_13->offset);
	if(!T4) {throw_null(vm);} T1=T4->length;
	{
	  VAR cargs[]={{.O=T0},{.I=0},{.O=L2},{.I=0},{.I=T1}};
	  frame->pc=64;
	  AOTMETHOD(m_1266555143_22,28,308,309); //java/lang/System:arraycopy:(Ljava/lang/Object;ILjava/lang/Object;II)V;
	  ((VM_CALL)(MTH(((Object*)m_1266555143_22),entry)))(vm,m_1266555143_22,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
BB67:
	if(!f_1266555143_13) { //buffer;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,13);
	  f_1266555143_13=fld->instance;
	}
	*FIELD_PTR_O(L0,f_1266555143_13->offset) = L2;
BB73:
	AOTFIELD(f_1266555143_13,305,306,307); //digiplay/net/Socket:buffer:[B;
	if(!L0) { frame->pc = 74; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1266555143_13->offset);
	if(!T0) {throw_null(vm);} T1=T0->length;
	AOTFIELD(f_1266555143_28,305,81,4); //digiplay/net/Socket:write:I;
	if(!L0) { frame->pc = 79; throw_null(vm); goto __EXCEPTION; }
	T2 = *FIELD_PTR_I(L0,f_1266555143_28->offset);
	T3 = T1 - T2;
	L3=T3;
	if(L3<=L1) goto BB94;
BB91:
	L3=L1;
BB94:
	if(L3<=0) goto BB163;
BB99:
	AOTFIELD(f_1266555143_13,305,306,307); //digiplay/net/Socket:buffer:[B;
	if(!L0) { frame->pc = 102; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1266555143_13->offset);
	AOTFIELD(f_1266555143_28,305,81,4); //digiplay/net/Socket:write:I;
	if(!L0) { frame->pc = 106; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_I(L0,f_1266555143_28->offset);
	{
	  VAR cargs[]={{.O=L4},{.I=L5},{.O=T0},{.I=T1},{.I=L3}};
	  frame->pc=111;
	  AOTMETHOD(m_1266555143_22,28,308,309); //java/lang/System:arraycopy:(Ljava/lang/Object;ILjava/lang/Object;II)V;
	  ((VM_CALL)(MTH(((Object*)m_1266555143_22),entry)))(vm,m_1266555143_22,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	T1 = L5 + L3;
	L5=T1;
	T1 = L1 - L3;
	L1=T1;
	AOTFIELD(f_1266555143_28,305,81,4); //digiplay/net/Socket:write:I;
	if(!L0) { frame->pc = 126; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_I(L0,f_1266555143_28->offset);
	T2 = T1 + L3;
	if(!f_1266555143_28) { //write;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,28);
	  f_1266555143_28=fld->instance;
	}
	*FIELD_PTR_I(L0,f_1266555143_28->offset) = T2;
	AOTFIELD(f_1266555143_28,305,81,4); //digiplay/net/Socket:write:I;
	if(!L0) { frame->pc = 136; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_I(L0,f_1266555143_28->offset);
	AOTFIELD(f_1266555143_13,305,306,307); //digiplay/net/Socket:buffer:[B;
	if(!L0) { frame->pc = 140; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1266555143_13->offset);
	if(!T0) {throw_null(vm);} T2=T0->length;
	if(T1<T2) goto BB152;
BB147:
	if(!f_1266555143_28) { //write;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,28);
	  f_1266555143_28=fld->instance;
	}
	*FIELD_PTR_I(L0,f_1266555143_28->offset) = 0;
BB152:
	AOTFIELD(f_1266555143_17,305,192,4); //digiplay/net/Socket:size:I;
	if(!L0) { frame->pc = 154; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_I(L0,f_1266555143_17->offset);
	T2 = T1 + L3;
	if(!f_1266555143_17) { //size;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,17);
	  f_1266555143_17=fld->instance;
	}
	*FIELD_PTR_I(L0,f_1266555143_17->offset) = T2;
BB163:
	if(L1<=0) goto BB218;
BB167:
	AOTFIELD(f_1266555143_13,305,306,307); //digiplay/net/Socket:buffer:[B;
	if(!L0) { frame->pc = 170; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1266555143_13->offset);
	AOTFIELD(f_1266555143_28,305,81,4); //digiplay/net/Socket:write:I;
	if(!L0) { frame->pc = 174; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_I(L0,f_1266555143_28->offset);
	{
	  VAR cargs[]={{.O=L4},{.I=L5},{.O=T0},{.I=T1},{.I=L1}};
	  frame->pc=178;
	  AOTMETHOD(m_1266555143_22,28,308,309); //java/lang/System:arraycopy:(Ljava/lang/Object;ILjava/lang/Object;II)V;
	  ((VM_CALL)(MTH(((Object*)m_1266555143_22),entry)))(vm,m_1266555143_22,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	AOTFIELD(f_1266555143_28,305,81,4); //digiplay/net/Socket:write:I;
	if(!L0) { frame->pc = 183; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_I(L0,f_1266555143_28->offset);
	T2 = T1 + L1;
	if(!f_1266555143_28) { //write;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,28);
	  f_1266555143_28=fld->instance;
	}
	*FIELD_PTR_I(L0,f_1266555143_28->offset) = T2;
	AOTFIELD(f_1266555143_28,305,81,4); //digiplay/net/Socket:write:I;
	if(!L0) { frame->pc = 192; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_I(L0,f_1266555143_28->offset);
	AOTFIELD(f_1266555143_13,305,306,307); //digiplay/net/Socket:buffer:[B;
	if(!L0) { frame->pc = 196; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1266555143_13->offset);
	if(!T0) {throw_null(vm);} T2=T0->length;
	if(T1<T2) goto BB208;
BB203:
	if(!f_1266555143_28) { //write;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,28);
	  f_1266555143_28=fld->instance;
	}
	*FIELD_PTR_I(L0,f_1266555143_28->offset) = 0;
BB208:
	AOTFIELD(f_1266555143_17,305,192,4); //digiplay/net/Socket:size:I;
	if(!L0) { frame->pc = 210; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_I(L0,f_1266555143_17->offset);
	T2 = T1 + L1;
	if(!f_1266555143_17) { //size;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,17);
	  f_1266555143_17=fld->instance;
	}
	*FIELD_PTR_I(L0,f_1266555143_17->offset) = T2;
BB218:
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_net_Socket_close___V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	Object *L0;
	L0=args[0].O;
BB0:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=1;
	  AOTVMETHOD(m_1266555143_30,305,310,2,vTableIndex); //digiplay/net/Socket:disconnect:()V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m_1266555143_30];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	if(!f_1266555143_17) { //size;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,17);
	  f_1266555143_17=fld->instance;
	}
	*FIELD_PTR_I(L0,f_1266555143_17->offset) = 0;
	if(!f_1266555143_28) { //write;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,28);
	  f_1266555143_28=fld->instance;
	}
	*FIELD_PTR_I(L0,f_1266555143_28->offset) = 0;
	if(!f_1266555143_33) { //read;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,33);
	  f_1266555143_33=fld->instance;
	}
	*FIELD_PTR_I(L0,f_1266555143_33->offset) = 0;
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_net_Socket_available___I(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JINT T0;
	Object *L0;
	L0=args[0].O;
BB0:
	AOTFIELD(f_1266555143_17,305,192,4); //digiplay/net/Socket:size:I;
	if(!L0) { frame->pc = 1; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_I(L0,f_1266555143_17->offset);
	vm->FP--;vm->frames[vm->FP].ret.I=T0;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_net_Socket_read___I(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JINT L1,T0,T2,T3;
	Object *L0,*T1;
	L0=args[0].O;
BB0:
	AOTFIELD(f_1266555143_17,305,192,4); //digiplay/net/Socket:size:I;
	if(!L0) { frame->pc = 1; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_I(L0,f_1266555143_17->offset);
	if(T0<=0) goto BB62;
BB7:
	AOTFIELD(f_1266555143_13,305,306,307); //digiplay/net/Socket:buffer:[B;
	if(!L0) { frame->pc = 8; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_O(L0,f_1266555143_13->offset);
	AOTFIELD(f_1266555143_33,305,63,4); //digiplay/net/Socket:read:I;
	if(!L0) { frame->pc = 12; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_I(L0,f_1266555143_33->offset);
	if(!T1) { throw_null(vm); goto __EXCEPTION;}
	if(T0 < 0 || T0 >= T1->length) { throw_arrayounds(vm,T0,T1->length); goto __EXCEPTION; }
	T0 = ARRAY_DATA_B(T1)[T0];
	L1=T0;
	AOTFIELD(f_1266555143_33,305,63,4); //digiplay/net/Socket:read:I;
	if(!L0) { frame->pc = 19; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_I(L0,f_1266555143_33->offset);
	T2 = T0 + 1;
	AOTFIELD(f_1266555143_13,305,306,307); //digiplay/net/Socket:buffer:[B;
	if(!L0) { frame->pc = 25; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_O(L0,f_1266555143_13->offset);
	if(!T1) {throw_null(vm);} T0=T1->length;
	T3 = T2 % T0;
	if(!f_1266555143_33) { //read;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,33);
	  f_1266555143_33=fld->instance;
	}
	*FIELD_PTR_I(L0,f_1266555143_33->offset) = T3;
	AOTFIELD(f_1266555143_17,305,192,4); //digiplay/net/Socket:size:I;
	if(!L0) { frame->pc = 35; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_I(L0,f_1266555143_17->offset);
	T2 = T0 - 1;
	if(!f_1266555143_17) { //size;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,17);
	  f_1266555143_17=fld->instance;
	}
	*FIELD_PTR_I(L0,f_1266555143_17->offset) = T2;
	AOTFIELD(f_1266555143_17,305,192,4); //digiplay/net/Socket:size:I;
	if(!L0) { frame->pc = 44; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_I(L0,f_1266555143_17->offset);
	if(T0!=0) goto BB60;
BB50:
	if(!f_1266555143_28) { //write;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,28);
	  f_1266555143_28=fld->instance;
	}
	*FIELD_PTR_I(L0,f_1266555143_28->offset) = 0;
	if(!f_1266555143_33) { //read;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,33);
	  f_1266555143_33=fld->instance;
	}
	*FIELD_PTR_I(L0,f_1266555143_33->offset) = 0;
BB60:
	vm->FP--;vm->frames[vm->FP].ret.I=L1;return;
BB62:
	vm->FP--;vm->frames[vm->FP].ret.I=-1;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
//digiplay/render/QuadGeometry
static Field *f_1352308066_1=NULL,*f_1352308066_7=NULL,*f_1352308066_10=NULL,*f_1352308066_14=NULL;
static JLONG m_1352308066_18=0,m_1352308066_22=0;
static Object *c_1352308066_2=NULL,*c_1352308066_23=NULL;
void digiplay_render_QuadGeometry_alloc__I_Ldigiplay_render_QuadGeometry_(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JINT L1,T2;
	Object *L0,*T0,*T1;
	L1=args[0].I;
BB0:
	AOTFIELD(f_1352308066_1,311,312,313); //digiplay/render/QuadGeometry:CACHE:Ldigiplay/render/QuadGeometry;
	T0 = *((Object**)(CLS(f_1352308066_1->declaringClass,global) + f_1352308066_1->offset));
	L0=T0;
	if(L0==NULL) goto BB45;
BB8:
	AOTFIELD(f_1352308066_1,311,312,313); //digiplay/render/QuadGeometry:CACHE:Ldigiplay/render/QuadGeometry;
	T0 = *((Object**)(CLS(f_1352308066_1->declaringClass,global) + f_1352308066_1->offset));
	AOTFIELD(f_1352308066_7,311,136,313); //digiplay/render/QuadGeometry:next:Ldigiplay/render/QuadGeometry;
	if(!T0) { frame->pc = 11; throw_null(vm); goto __EXCEPTION; }
	T1 = *FIELD_PTR_O(T0,f_1352308066_7->offset);
	if(!f_1352308066_1) { //CACHE;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,1);
	  f_1352308066_1=fld->instance;
	}
	*((Object**)((CLS(f_1352308066_1->declaringClass,global))+f_1352308066_1->offset)) = T1;
	if(!f_1352308066_7) { //next;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,7);
	  f_1352308066_7=fld->instance;
	}
	*FIELD_PTR_O(L0,f_1352308066_7->offset) = NULL;
	AOTFIELD(f_1352308066_10,311,192,4); //digiplay/render/QuadGeometry:size:I;
	if(!L0) { frame->pc = 23; throw_null(vm); goto __EXCEPTION; }
	T2 = *FIELD_PTR_I(L0,f_1352308066_10->offset);
	if(T2>=L1) goto BB37;
BB30:
	T0 = alloc_array_F(vm,L1,0);
	if(!f_1352308066_14) { //buffer;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,14);
	  f_1352308066_14=fld->instance;
	}
	*FIELD_PTR_O(L0,f_1352308066_14->offset) = T0;
BB37:
	if(!f_1352308066_10) { //size;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,10);
	  f_1352308066_10=fld->instance;
	}
	*FIELD_PTR_I(L0,f_1352308066_10->offset) = L1;
	goto BB54;
BB45:
	AOTCLASS(c_1352308066_2,311);
	T0=alloc_object(vm,c_1352308066_2,0);
	{
	  VAR cargs[]={{.O=T0},{.I=L1}};
	  frame->pc=50;
	  AOTMETHOD(m_1352308066_18,311,1,88); //digiplay/render/QuadGeometry:<init>:(I)V;
	  ((VM_CALL)(MTH(((Object*)m_1352308066_18),entry)))(vm,m_1352308066_18,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	L0=T0;
BB54:
	vm->FP--;vm->frames[vm->FP].ret.O=L0;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_render_QuadGeometry__init___I_V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JINT L1;
	Object *L0,*T0;
	L0=args[0].O;
	L1=args[1].I;
BB0:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=1;
	  AOTMETHOD(m_1352308066_22,0,1,2); //java/lang/Object:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m_1352308066_22),entry)))(vm,m_1352308066_22,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	T0 = alloc_array_F(vm,L1,0);
	if(!f_1352308066_14) { //buffer;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,14);
	  f_1352308066_14=fld->instance;
	}
	*FIELD_PTR_O(L0,f_1352308066_14->offset) = T0;
	if(!f_1352308066_10) { //size;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,10);
	  f_1352308066_10=fld->instance;
	}
	*FIELD_PTR_I(L0,f_1352308066_10->offset) = L1;
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_render_QuadGeometry_set__IFFFFFFFFFFFFFFFFFFFF_V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
BB0:
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
//digiplay/render/GPU
static Field *f684996423_13=NULL,*f684996423_17=NULL,*f684996423_20=NULL,*f684996423_23=NULL,*f684996423_26=NULL,*f684996423_29=NULL,*f684996423_32=NULL;
static JLONG m684996423_1=0,m684996423_7=0;
static Object *c684996423_2=NULL,*c684996423_8=NULL;
void digiplay_render_GPU__init____V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	Object *L0;
	L0=args[0].O;
BB0:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=1;
	  AOTMETHOD(m684996423_1,0,1,2); //java/lang/Object:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m684996423_1),entry)))(vm,m684996423_1,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_render_GPU_commit___V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
BB0:
	{
	  VAR cargs[]={{.I=-1}};
	  frame->pc=1;
	  AOTMETHOD(m684996423_7,314,315,88); //digiplay/render/GPU:commit:(I)V;
	  ((VM_CALL)(MTH(((Object*)m684996423_7),entry)))(vm,m684996423_7,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_render_GPU_setViewport__IIII_V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JINT L0,L1,L2,L3,T0,T1;
	L0=args[0].I;
	L1=args[1].I;
	L2=args[2].I;
	L3=args[3].I;
BB0:
	if(!f684996423_13) { //vpX;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,13);
	  f684996423_13=fld->instance;
	}
	*((JINT*)((CLS(f684996423_13->declaringClass,global))+f684996423_13->offset)) = L0;
	if(!f684996423_17) { //vpY;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,17);
	  f684996423_17=fld->instance;
	}
	*((JINT*)((CLS(f684996423_17->declaringClass,global))+f684996423_17->offset)) = L1;
	if(!f684996423_20) { //vpW;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,20);
	  f684996423_20=fld->instance;
	}
	*((JINT*)((CLS(f684996423_20->declaringClass,global))+f684996423_20->offset)) = L2;
	if(!f684996423_23) { //vpH;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,23);
	  f684996423_23=fld->instance;
	}
	*((JINT*)((CLS(f684996423_23->declaringClass,global))+f684996423_23->offset)) = L3;
	AOTFIELD(f684996423_26,314,316,4); //digiplay/render/GPU:pendingMask:I;
	T0 = *((JINT*)(CLS(f684996423_26->declaringClass,global) + f684996423_26->offset));
	T1 = T0 | 1;
	if(!f684996423_26) { //pendingMask;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,26);
	  f684996423_26=fld->instance;
	}
	*((JINT*)((CLS(f684996423_26->declaringClass,global))+f684996423_26->offset)) = T1;
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_render_GPU_setBlending__II_V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JINT L0,L1,T0,T1;
	L0=args[0].I;
	L1=args[1].I;
BB0:
	if(!f684996423_29) { //blendSrc;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,29);
	  f684996423_29=fld->instance;
	}
	*((JINT*)((CLS(f684996423_29->declaringClass,global))+f684996423_29->offset)) = L0;
	if(!f684996423_32) { //blendDst;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,32);
	  f684996423_32=fld->instance;
	}
	*((JINT*)((CLS(f684996423_32->declaringClass,global))+f684996423_32->offset)) = L1;
	AOTFIELD(f684996423_26,314,316,4); //digiplay/render/GPU:pendingMask:I;
	T0 = *((JINT*)(CLS(f684996423_26->declaringClass,global) + f684996423_26->offset));
	T1 = T0 | 32;
	if(!f684996423_26) { //pendingMask;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,26);
	  f684996423_26=fld->instance;
	}
	*((JINT*)((CLS(f684996423_26->declaringClass,global))+f684996423_26->offset)) = T1;
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_render_GPU__clinit____V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
BB0:
	if(!f684996423_29) { //blendSrc;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,29);
	  f684996423_29=fld->instance;
	}
	*((JINT*)((CLS(f684996423_29->declaringClass,global))+f684996423_29->offset)) = -1;
	if(!f684996423_32) { //blendDst;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,32);
	  f684996423_32=fld->instance;
	}
	*((JINT*)((CLS(f684996423_32->declaringClass,global))+f684996423_32->offset)) = -1;
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
//digiplay/render/VertexBuffer
static Field *f_774210871_7=NULL,*f_774210871_13=NULL;
static JLONG m_774210871_1=0;
static Object *c_774210871_2=NULL,*c_774210871_8=NULL,*c_774210871_30=NULL;
void digiplay_render_VertexBuffer__init___II_V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JINT L1,L2;
	Object *L0;
	L0=args[0].O;
	L1=args[1].I;
	L2=args[2].I;
BB0:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=1;
	  AOTMETHOD(m_774210871_1,0,1,2); //java/lang/Object:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m_774210871_1),entry)))(vm,m_774210871_1,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	if(!f_774210871_7) { //size;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,7);
	  f_774210871_7=fld->instance;
	}
	*FIELD_PTR_I(L0,f_774210871_7->offset) = L1;
	if(!f_774210871_13) { //stride;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,13);
	  f_774210871_13=fld->instance;
	}
	*FIELD_PTR_I(L0,f_774210871_13->offset) = L2;
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
//digiplay/render/RenderDevice
static Field *f1657886545_13=NULL,*f1657886545_17=NULL,*f1657886545_20=NULL,*f1657886545_23=NULL,*f1657886545_26=NULL,*f1657886545_29=NULL,*f1657886545_32=NULL,*f1657886545_35=NULL,*f1657886545_38=NULL;
static JLONG m1657886545_1=0,m1657886545_7=0;
static Object *c1657886545_2=NULL,*c1657886545_8=NULL;
void digiplay_render_RenderDevice__init____V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	Object *L0;
	L0=args[0].O;
BB0:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=1;
	  AOTMETHOD(m1657886545_1,0,1,2); //java/lang/Object:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m1657886545_1),entry)))(vm,m1657886545_1,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_render_RenderDevice_commit___V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	Object *L0;
	L0=args[0].O;
BB0:
	{
	  VAR cargs[]={{.O=L0},{.I=-1}};
	  frame->pc=2;
	  AOTVMETHOD(m1657886545_7,317,315,88,vTableIndex); //digiplay/render/RenderDevice:commit:(I)V;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m1657886545_7];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_render_RenderDevice_resetStates___V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
BB0:
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_render_RenderDevice_setViewPort__IIII_V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JINT L1,L2,L3,L4,T0,T1;
	Object *L0;
	L0=args[0].O;
	L1=args[1].I;
	L2=args[2].I;
	L3=args[3].I;
	L4=args[4].I;
BB0:
	if(!f1657886545_13) { //vpX;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,13);
	  f1657886545_13=fld->instance;
	}
	*FIELD_PTR_I(L0,f1657886545_13->offset) = L1;
	if(!f1657886545_17) { //vpY;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,17);
	  f1657886545_17=fld->instance;
	}
	*FIELD_PTR_I(L0,f1657886545_17->offset) = L2;
	if(!f1657886545_20) { //vpWidth;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,20);
	  f1657886545_20=fld->instance;
	}
	*FIELD_PTR_I(L0,f1657886545_20->offset) = L3;
	if(!f1657886545_23) { //vpHeight;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,23);
	  f1657886545_23=fld->instance;
	}
	*FIELD_PTR_I(L0,f1657886545_23->offset) = L4;
	AOTFIELD(f1657886545_26,317,316,4); //digiplay/render/RenderDevice:pendingMask:I;
	if(!L0) { frame->pc = 23; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_I(L0,f1657886545_26->offset);
	T1 = T0 | 1;
	if(!f1657886545_26) { //pendingMask;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,26);
	  f1657886545_26=fld->instance;
	}
	*FIELD_PTR_I(L0,f1657886545_26->offset) = T1;
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_render_RenderDevice_setScissor__IIII_V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JINT L1,L2,L3,L4,T0,T1;
	Object *L0;
	L0=args[0].O;
	L1=args[1].I;
	L2=args[2].I;
	L3=args[3].I;
	L4=args[4].I;
BB0:
	if(!f1657886545_29) { //scX;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,29);
	  f1657886545_29=fld->instance;
	}
	*FIELD_PTR_I(L0,f1657886545_29->offset) = L1;
	if(!f1657886545_32) { //scY;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,32);
	  f1657886545_32=fld->instance;
	}
	*FIELD_PTR_I(L0,f1657886545_32->offset) = L2;
	if(!f1657886545_35) { //scWidth;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,35);
	  f1657886545_35=fld->instance;
	}
	*FIELD_PTR_I(L0,f1657886545_35->offset) = L3;
	if(!f1657886545_38) { //scHeight;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,38);
	  f1657886545_38=fld->instance;
	}
	*FIELD_PTR_I(L0,f1657886545_38->offset) = L4;
	AOTFIELD(f1657886545_26,317,316,4); //digiplay/render/RenderDevice:pendingMask:I;
	if(!L0) { frame->pc = 23; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_I(L0,f1657886545_26->offset);
	T1 = T0 | 16;
	if(!f1657886545_26) { //pendingMask;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,26);
	  f1657886545_26=fld->instance;
	}
	*FIELD_PTR_I(L0,f1657886545_26->offset) = T1;
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
//digiplay/render/Shader
static Field *f1704985450_13=NULL;
static JLONG m1704985450_1=0,m1704985450_7=0;
static Object *c1704985450_2=NULL,*c1704985450_8=NULL,*c1704985450_28=NULL;
void digiplay_render_Shader__init___Ljava_lang_String_Ljava_lang_String__V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JLONG T0;
	Object *L0,*L1,*L2;
	L0=args[0].O;
	L1=args[1].O;
	L2=args[2].O;
BB0:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=1;
	  AOTMETHOD(m1704985450_1,0,1,2); //java/lang/Object:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m1704985450_1),entry)))(vm,m1704985450_1,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	{
	  VAR cargs[]={{.O=L0},{.O=L1},{.O=L2}};
	  frame->pc=8;
	  AOTMETHOD(m1704985450_7,318,319,320); //digiplay/render/Shader:internalCreate:(Ljava/lang/String;Ljava/lang/String;)J;
	  ((VM_CALL)(MTH(((Object*)m1704985450_7),entry)))(vm,m1704985450_7,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T0=frame->ret.J;
	}
	
	if(!f1704985450_13) { //deviceHandle;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,13);
	  f1704985450_13=fld->instance;
	}
	*FIELD_PTR_J(L0,f1704985450_13->offset) = T0;
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
//digiplay/render/IndexBuffer
static Field *f_1592646835_7=NULL;
static JLONG m_1592646835_1=0;
static Object *c_1592646835_2=NULL,*c_1592646835_8=NULL,*c_1592646835_35=NULL;
void digiplay_render_IndexBuffer__init___I_V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JINT L1;
	Object *L0,*T0;
	L0=args[0].O;
	L1=args[1].I;
BB0:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=1;
	  AOTMETHOD(m_1592646835_1,0,1,2); //java/lang/Object:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m_1592646835_1),entry)))(vm,m_1592646835_1,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	T0 = alloc_array_S(vm,L1,0);
	if(!f_1592646835_7) { //buffer;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,7);
	  f_1592646835_7=fld->instance;
	}
	*FIELD_PTR_O(L0,f_1592646835_7->offset) = T0;
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_render_IndexBuffer_set__II_V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JINT L1,L2,T1;
	Object *L0,*T0;
	L0=args[0].O;
	L1=args[1].I;
	L2=args[2].I;
BB0:
	AOTFIELD(f_1592646835_7,321,306,322); //digiplay/render/IndexBuffer:buffer:[S;
	if(!L0) { frame->pc = 1; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1592646835_7->offset);
	T1=(JSHORT)L2;
	if(!T0) { throw_null(vm); goto __EXCEPTION;}
	if(L1 < 0 || L1 >= T0->length) { throw_arrayounds(vm,L1,T0->length); goto __EXCEPTION; }
	ARRAY_DATA_S(T0)[L1] = T1;
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void digiplay_render_IndexBuffer_set__IIII_V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JINT L1,L2,L3,L4,T1;
	Object *L0,*T0;
	L0=args[0].O;
	L1=args[1].I;
	L2=args[2].I;
	L3=args[3].I;
	L4=args[4].I;
BB0:
	AOTFIELD(f_1592646835_7,321,306,322); //digiplay/render/IndexBuffer:buffer:[S;
	if(!L0) { frame->pc = 1; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1592646835_7->offset);
	L1+=1;
	T1=(JSHORT)L2;
	if(!T0) { throw_null(vm); goto __EXCEPTION;}
	if(L1 < 0 || L1 >= T0->length) { throw_arrayounds(vm,L1,T0->length); goto __EXCEPTION; }
	ARRAY_DATA_S(T0)[L1] = T1;
	AOTFIELD(f_1592646835_7,321,306,322); //digiplay/render/IndexBuffer:buffer:[S;
	if(!L0) { frame->pc = 12; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1592646835_7->offset);
	L1+=1;
	T1=(JSHORT)L3;
	if(!T0) { throw_null(vm); goto __EXCEPTION;}
	if(L1 < 0 || L1 >= T0->length) { throw_arrayounds(vm,L1,T0->length); goto __EXCEPTION; }
	ARRAY_DATA_S(T0)[L1] = T1;
	AOTFIELD(f_1592646835_7,321,306,322); //digiplay/render/IndexBuffer:buffer:[S;
	if(!L0) { frame->pc = 23; throw_null(vm); goto __EXCEPTION; }
	T0 = *FIELD_PTR_O(L0,f_1592646835_7->offset);
	T1=(JSHORT)L4;
	if(!T0) { throw_null(vm); goto __EXCEPTION;}
	if(L1 < 0 || L1 >= T0->length) { throw_arrayounds(vm,L1,T0->length); goto __EXCEPTION; }
	ARRAY_DATA_S(T0)[L1] = T1;
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
//digiplay/render/Texture
static JLONG m2138290742_1=0;
static Object *c2138290742_2=NULL,*c2138290742_7=NULL;
void digiplay_render_Texture__init____V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	Object *L0;
	L0=args[0].O;
BB0:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=1;
	  AOTMETHOD(m2138290742_1,0,1,2); //java/lang/Object:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m2138290742_1),entry)))(vm,m2138290742_1,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
//gamavm/apple/storekit/SKPaymentQueue
static Field *f_1924104450_2=NULL;
static JLONG m_1924104450_1=0,m_1924104450_4=0,m_1924104450_6=0,m_1924104450_9=0;
static Object *c_1924104450_7=NULL,*c_1924104450_8=NULL,*c_1924104450_10=NULL,*c_1924104450_26=NULL,*c_1924104450_28=NULL,*c_1924104450_32=NULL;
void gamavm_apple_storekit_SKPaymentQueue__init____V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	Object *L0;
	L0=args[0].O;
BB0:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=1;
	  AOTMETHOD(m_1924104450_1,323,1,2); //gamavm/apple/NSMutableObject:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m_1924104450_1),entry)))(vm,m_1924104450_1,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void gamavm_apple_storekit_SKPaymentQueue_defaultQueue___Lgamavm_apple_storekit_SKPaymentQueue_(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	Object *T0;
BB0:
	AOTFIELD(f_1924104450_2,324,325,326); //gamavm/apple/storekit/SKPaymentQueue:defaultQueue:Lgamavm/apple/storekit/SKPaymentQueue;
	T0 = *((Object**)(CLS(f_1924104450_2->declaringClass,global) + f_1924104450_2->offset));
	vm->FP--;vm->frames[vm->FP].ret.O=T0;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void gamavm_apple_storekit_SKPaymentQueue__clinit____V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	Object *T0,*T1,*T2;
BB0:
	{
	  VAR cargs[]={{.O=aot_strings[327]}};
	  frame->pc=2;
	  AOTMETHOD(m_1924104450_4,284,288,328); //gamavm/apple/ObjCClass:get:(Ljava/lang/String;)Lgamavm/apple/ObjCClass;
	  ((VM_CALL)(MTH(((Object*)m_1924104450_4),entry)))(vm,m_1924104450_4,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T0=frame->ret.O;
	}
	
	{
	  VAR cargs[]={{.O=aot_strings[325]}};
	  frame->pc=7;
	  AOTMETHOD(m_1924104450_6,296,329,330); //gamavm/apple/Selector:register:(Ljava/lang/String;)Lgamavm/apple/Selector;
	  ((VM_CALL)(MTH(((Object*)m_1924104450_6),entry)))(vm,m_1924104450_6,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T1=frame->ret.O;
	}
	
	AOTCLASS(c_1924104450_7,7);
	if(!c_1924104450_8) c_1924104450_8=resolve_class_by_index(vm,method->declaringClass,8);
	T2 = alloc_array_O(vm,c_1924104450_8,0,0);
	
	{
	  VAR cargs[]={{.O=T0},{.O=T1},{.O=c_1924104450_7},{.O=T2}};
	  frame->pc=16;
	  AOTMETHOD(m_1924104450_9,290,331,332); //gamavm/apple/ObjC:callObject:(Lgamavm/apple/NSObject;Lgamavm/apple/Selector;Ljava/lang/Class;[Ljava/lang/Object;)Lgamavm/apple/NSObject;
	  ((VM_CALL)(MTH(((Object*)m_1924104450_9),entry)))(vm,m_1924104450_9,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T0=frame->ret.O;
	}
	
	check_cast(vm,T0,7);
	if(!f_1924104450_2) { //defaultQueue;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,2);
	  f_1924104450_2=fld->instance;
	}
	*((Object**)((CLS(f_1924104450_2->declaringClass,global))+f_1924104450_2->offset)) = T0;
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
//gamavm/apple/uikit/UIView
static JLONG m_1890442747_1=0;
static Object *c_1890442747_2=NULL,*c_1890442747_7=NULL;
void gamavm_apple_uikit_UIView__init____V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	Object *L0;
	L0=args[0].O;
BB0:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=1;
	  AOTMETHOD(m_1890442747_1,333,1,2); //gamavm/apple/uikit/UIResponder:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m_1890442747_1),entry)))(vm,m_1890442747_1,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
//gamavm/apple/uikit/UIApplicationDelegate
static Field *f_1469095019_7=NULL;
static JLONG m_1469095019_1=0;
static Object *c_1469095019_2=NULL,*c_1469095019_8=NULL;
void gamavm_apple_uikit_UIApplicationDelegate__init____V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	Object *L0;
	L0=args[0].O;
BB0:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=1;
	  AOTMETHOD(m_1469095019_1,0,1,2); //java/lang/Object:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m_1469095019_1),entry)))(vm,m_1469095019_1,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	if(!f_1469095019_7) { //INSTANCE;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,7);
	  f_1469095019_7=fld->instance;
	}
	*((Object**)((CLS(f_1469095019_7->declaringClass,global))+f_1469095019_7->offset)) = L0;
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void gamavm_apple_uikit_UIApplicationDelegate_didFinishLaunching___V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
BB0:
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
//gamavm/apple/uikit/UIResponder
static JLONG m798617762_1=0;
static Object *c798617762_2=NULL,*c798617762_7=NULL;
void gamavm_apple_uikit_UIResponder__init____V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	Object *L0;
	L0=args[0].O;
BB0:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=1;
	  AOTMETHOD(m798617762_1,283,1,2); //gamavm/apple/NSObject:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m798617762_1),entry)))(vm,m798617762_1,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
//gamavm/apple/uikit/UIViewController
static JLONG m_170434687_1=0;
static Object *c_170434687_2=NULL,*c_170434687_7=NULL;
void gamavm_apple_uikit_UIViewController__init____V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	Object *L0;
	L0=args[0].O;
BB0:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=1;
	  AOTMETHOD(m_170434687_1,333,1,2); //gamavm/apple/uikit/UIResponder:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m_170434687_1),entry)))(vm,m_170434687_1,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
//gamavm/apple/uikit/UIApplication
static Field *f_1606938128_2=NULL;
static JLONG m_1606938128_1=0,m_1606938128_4=0,m_1606938128_6=0,m_1606938128_9=0;
static Object *c_1606938128_7=NULL,*c_1606938128_8=NULL,*c_1606938128_10=NULL,*c_1606938128_30=NULL,*c_1606938128_32=NULL,*c_1606938128_36=NULL;
void gamavm_apple_uikit_UIApplication__init____V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	Object *L0;
	L0=args[0].O;
BB0:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=1;
	  AOTMETHOD(m_1606938128_1,323,1,2); //gamavm/apple/NSMutableObject:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m_1606938128_1),entry)))(vm,m_1606938128_1,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void gamavm_apple_uikit_UIApplication_sharedApplication___Lgamavm_apple_uikit_UIApplication_(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	Object *T0,*T1,*T2;
BB0:
	AOTFIELD(f_1606938128_2,334,335,336); //gamavm/apple/uikit/UIApplication:sharedApplication:Lgamavm/apple/uikit/UIApplication;
	T0 = *((Object**)(CLS(f_1606938128_2->declaringClass,global) + f_1606938128_2->offset));
	if(T0!=NULL) goto BB31;
BB6:
	{
	  VAR cargs[]={{.O=aot_strings[337]}};
	  frame->pc=8;
	  AOTMETHOD(m_1606938128_4,284,288,328); //gamavm/apple/ObjCClass:get:(Ljava/lang/String;)Lgamavm/apple/ObjCClass;
	  ((VM_CALL)(MTH(((Object*)m_1606938128_4),entry)))(vm,m_1606938128_4,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T0=frame->ret.O;
	}
	
	{
	  VAR cargs[]={{.O=aot_strings[335]}};
	  frame->pc=13;
	  AOTMETHOD(m_1606938128_6,296,329,330); //gamavm/apple/Selector:register:(Ljava/lang/String;)Lgamavm/apple/Selector;
	  ((VM_CALL)(MTH(((Object*)m_1606938128_6),entry)))(vm,m_1606938128_6,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T1=frame->ret.O;
	}
	
	AOTCLASS(c_1606938128_7,7);
	if(!c_1606938128_8) c_1606938128_8=resolve_class_by_index(vm,method->declaringClass,8);
	T2 = alloc_array_O(vm,c_1606938128_8,0,0);
	
	{
	  VAR cargs[]={{.O=T0},{.O=T1},{.O=c_1606938128_7},{.O=T2}};
	  frame->pc=22;
	  AOTMETHOD(m_1606938128_9,290,331,332); //gamavm/apple/ObjC:callObject:(Lgamavm/apple/NSObject;Lgamavm/apple/Selector;Ljava/lang/Class;[Ljava/lang/Object;)Lgamavm/apple/NSObject;
	  ((VM_CALL)(MTH(((Object*)m_1606938128_9),entry)))(vm,m_1606938128_9,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T0=frame->ret.O;
	}
	
	check_cast(vm,T0,7);
	if(!f_1606938128_2) { //sharedApplication;
	  Object *fld=resolve_field_by_index(vm,method->declaringClass,2);
	  f_1606938128_2=fld->instance;
	}
	*((Object**)((CLS(f_1606938128_2->declaringClass,global))+f_1606938128_2->offset)) = T0;
BB31:
	AOTFIELD(f_1606938128_2,334,335,336); //gamavm/apple/uikit/UIApplication:sharedApplication:Lgamavm/apple/uikit/UIApplication;
	T0 = *((Object**)(CLS(f_1606938128_2->declaringClass,global) + f_1606938128_2->offset));
	vm->FP--;vm->frames[vm->FP].ret.O=T0;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
//gamavm/apple/uikit/UIWindow
static JLONG m84568912_1=0,m84568912_9=0,m84568912_17=0,m84568912_23=0,m84568912_29=0;
static Object *c84568912_2=NULL,*c84568912_10=NULL,*c84568912_15=NULL,*c84568912_18=NULL,*c84568912_24=NULL,*c84568912_30=NULL,*c84568912_37=NULL;
void gamavm_apple_uikit_UIWindow__init____V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	Object *L0;
	L0=args[0].O;
BB0:
	{
	  VAR cargs[]={{.O=L0}};
	  frame->pc=1;
	  AOTMETHOD(m84568912_1,338,1,2); //gamavm/apple/uikit/UIView:<init>:()V;
	  ((VM_CALL)(MTH(((Object*)m84568912_1),entry)))(vm,m84568912_1,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void gamavm_apple_uikit_UIWindow_setRootViewController__Lgamavm_apple_uikit_UIViewController__V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	JLONG T2;
	Object *L0,*L1,*T0,*T1,*T3;
	L0=args[0].O;
	L1=args[1].O;
BB0:
	{
	  VAR cargs[]={{.O=aot_strings[339]}};
	  frame->pc=3;
	  AOTMETHOD(m84568912_9,296,329,330); //gamavm/apple/Selector:register:(Ljava/lang/String;)Lgamavm/apple/Selector;
	  ((VM_CALL)(MTH(((Object*)m84568912_9),entry)))(vm,m84568912_9,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T0=frame->ret.O;
	}
	
	if(!c84568912_15) c84568912_15=resolve_class_by_index(vm,method->declaringClass,15);
	T1 = alloc_array_O(vm,c84568912_15,1,0);
	
	{
	  VAR cargs[]={{.O=L1}};
	  frame->pc=13;
	  AOTVMETHOD(m84568912_17,340,341,43,vTableIndex); //gamavm/apple/uikit/UIViewController:getHandle:()J;
	  if(!cargs[0].O) { throw_null(vm); goto __EXCEPTION; }
	  Class *cls = cargs[0].O->cls->instance;
	  Object *mth = cls->vtable[m84568912_17];
	  ((VM_CALL)((Method*)mth->instance)->entry)(vm, mth, &cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T2=frame->ret.J;
	}
	
	{
	  VAR cargs[]={{.J=T2}};
	  frame->pc=16;
	  AOTMETHOD(m84568912_23,342,343,344); //java/lang/Long:valueOf:(J)Ljava/lang/Long;
	  ((VM_CALL)(MTH(((Object*)m84568912_23),entry)))(vm,m84568912_23,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T3=frame->ret.O;
	}
	
	if(!T1) { throw_null(vm); goto __EXCEPTION;}
	if(0 < 0 || 0 >= T1->length) { throw_arrayounds(vm,0,T1->length); goto __EXCEPTION; }
	ARRAY_DATA_O(T1)[0] = T3;
	{
	  VAR cargs[]={{.O=L0},{.O=T0},{.O=T1}};
	  frame->pc=20;
	  AOTMETHOD(m84568912_29,290,345,346); //gamavm/apple/ObjC:callVoid:(Lgamavm/apple/NSObject;Lgamavm/apple/Selector;[Ljava/lang/Object;)V;
	  ((VM_CALL)(MTH(((Object*)m84568912_29),entry)))(vm,m84568912_29,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void gamavm_apple_uikit_UIWindow_makeKeyAndVisible___V(VM *vm, Object *omethod, VAR *args) {
	Frame *frame = &vm->frames[++vm->FP];
	frame->method = omethod;
	Method *method = omethod->instance;
	Object *L0,*T0,*T1;
	L0=args[0].O;
BB0:
	{
	  VAR cargs[]={{.O=aot_strings[347]}};
	  frame->pc=3;
	  AOTMETHOD(m84568912_9,296,329,330); //gamavm/apple/Selector:register:(Ljava/lang/String;)Lgamavm/apple/Selector;
	  ((VM_CALL)(MTH(((Object*)m84568912_9),entry)))(vm,m84568912_9,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	  T0=frame->ret.O;
	}
	
	if(!c84568912_15) c84568912_15=resolve_class_by_index(vm,method->declaringClass,15);
	T1 = alloc_array_O(vm,c84568912_15,0,0);
	
	{
	  VAR cargs[]={{.O=L0},{.O=T0},{.O=T1}};
	  frame->pc=10;
	  AOTMETHOD(m84568912_29,290,345,346); //gamavm/apple/ObjC:callVoid:(Lgamavm/apple/NSObject;Lgamavm/apple/Selector;[Ljava/lang/Object;)V;
	  ((VM_CALL)(MTH(((Object*)m84568912_29),entry)))(vm,m84568912_29,&cargs[0]);
	  if(vm->exception) goto __EXCEPTION;
	}
	
	vm->FP--;return;
__EXCEPTION: {
	vm->FP--; return;
}
}
void aot_init(VM *vm) {
	static  int i=0; if(i) return; i=1;
	aot_strings = (Object**)malloc(sizeof(Object*)*348);
	aot_strings[132] = alloc_string_java(vm,(JCHAR[]){112,97,114,101,110,116},6,1);
	aot_strings[31] = alloc_string_java(vm,(JCHAR[]){106,97,118,97,47,108,97,110,103,47,83,116,114,105,110,103,66,117,105,108,100,101,114},23,1);
	aot_strings[37] = alloc_string_java(vm,(JCHAR[]){40,41,76,106,97,118,97,47,108,97,110,103,47,83,116,114,105,110,103,59},20,1);
	aot_strings[243] = alloc_string_java(vm,(JCHAR[]){99,111,112,121,70,114,111,109,50,68},10,1);
	aot_strings[137] = alloc_string_java(vm,(JCHAR[]){112,114,101,118},4,1);
	aot_strings[315] = alloc_string_java(vm,(JCHAR[]){99,111,109,109,105,116},6,1);
	aot_strings[125] = alloc_string_java(vm,(JCHAR[]){115,107,101,119,88},5,1);
	aot_strings[127] = alloc_string_java(vm,(JCHAR[]){115,107,101,119,89},5,1);
	aot_strings[222] = alloc_string_java(vm,(JCHAR[]){119,114,97,112,66,121,116,101,115},9,1);
	aot_strings[71] = alloc_string_java(vm,(JCHAR[]){10},1,1);
	aot_strings[190] = alloc_string_java(vm,(JCHAR[]){104,119,72,101,105,103,104,116},8,1);
	aot_strings[251] = alloc_string_java(vm,(JCHAR[]){115,97,102,101,76,101,102,116},8,1);
	aot_strings[77] = alloc_string_java(vm,(JCHAR[]){116,114,105,109},4,1);
	aot_strings[231] = alloc_string_java(vm,(JCHAR[]){40,70,70,70,41,86},6,1);
	aot_strings[221] = alloc_string_java(vm,(JCHAR[]){108,111,97,100,66,121,116,101,115},9,1);
	aot_strings[141] = alloc_string_java(vm,(JCHAR[]){110,117,109,67,104,105,108,100,114,101,110},11,1);
	aot_strings[83] = alloc_string_java(vm,(JCHAR[]){40,41,91,66},4,1);
	aot_strings[313] = alloc_string_java(vm,(JCHAR[]){76,100,105,103,105,112,108,97,121,47,114,101,110,100,101,114,47,81,117,97,100,71,101,111,109,101,116,114,121,59},30,1);
	aot_strings[273] = alloc_string_java(vm,(JCHAR[]){110,101,97,114},4,1);
	aot_strings[34] = alloc_string_java(vm,(JCHAR[]){40,76,106,97,118,97,47,108,97,110,103,47,83,116,114,105,110,103,59,41,76,106,97,118,97,47,108,97,110,103,47,83,116,114,105,110,103,66,117,105,108,100,101,114,59},45,1);
	aot_strings[223] = alloc_string_java(vm,(JCHAR[]){40,74,73,41,91,66},6,1);
	aot_strings[123] = alloc_string_java(vm,(JCHAR[]){104,101,105,103,104,116},6,1);
	aot_strings[85] = alloc_string_java(vm,(JCHAR[]){32},1,1);
	aot_strings[119] = alloc_string_java(vm,(JCHAR[]){97,110,105,109,83,99,97,108,101,89},10,1);
	aot_strings[259] = alloc_string_java(vm,(JCHAR[]){108,111,99,97,108,77,97,116,114,105,120},11,1);
	aot_strings[250] = alloc_string_java(vm,(JCHAR[]){100,105,103,105,112,108,97,121,47,71,114,97,112,104,105,99,115},17,1);
	aot_strings[217] = alloc_string_java(vm,(JCHAR[]){112,114,105,110,116,83,116,97,99,107,84,114,97,99,101},15,1);
	aot_strings[245] = alloc_string_java(vm,(JCHAR[]){115,101,116,50},4,1);
	aot_strings[225] = alloc_string_java(vm,(JCHAR[]){114,97,119},3,1);
	aot_strings[133] = alloc_string_java(vm,(JCHAR[]){76,100,105,103,105,112,108,97,121,47,83,112,114,105,116,101,50,68,59},19,1);
	aot_strings[248] = alloc_string_java(vm,(JCHAR[]){44},1,1);
	aot_strings[1] = alloc_string_java(vm,(JCHAR[]){60,105,110,105,116,62},6,1);
	aot_strings[89] = alloc_string_java(vm,(JCHAR[]){97,99,99,101,112,116},6,1);
	aot_strings[335] = alloc_string_java(vm,(JCHAR[]){115,104,97,114,101,100,65,112,112,108,105,99,97,116,105,111,110},17,1);
	aot_strings[187] = alloc_string_java(vm,(JCHAR[]){40,73,41,74},4,1);
	aot_strings[202] = alloc_string_java(vm,(JCHAR[]){115,101,116,80,105,118,111,116,88},9,1);
	aot_strings[0] = alloc_string_java(vm,(JCHAR[]){106,97,118,97,47,108,97,110,103,47,79,98,106,101,99,116},16,1);
	aot_strings[203] = alloc_string_java(vm,(JCHAR[]){115,101,116,80,105,118,111,116,89},9,1);
	aot_strings[196] = alloc_string_java(vm,(JCHAR[]){76,100,105,103,105,112,108,97,121,47,80,111,105,110,116,50,68,59},18,1);
	aot_strings[192] = alloc_string_java(vm,(JCHAR[]){115,105,122,101},4,1);
	aot_strings[74] = alloc_string_java(vm,(JCHAR[]){67,111,110,116,101,110,116,45,76,101,110,103,116,104,58},15,1);
	aot_strings[253] = alloc_string_java(vm,(JCHAR[]){115,97,102,101,84,111,112},7,1);
	aot_strings[88] = alloc_string_java(vm,(JCHAR[]){40,73,41,86},4,1);
	aot_strings[14] = alloc_string_java(vm,(JCHAR[]){97,100,100,67,104,105,108,100},8,1);
	aot_strings[144] = alloc_string_java(vm,(JCHAR[]){115,101,116,73,110,83,116,97,103,101},10,1);
	aot_strings[24] = alloc_string_java(vm,(JCHAR[]){115,112,101,99,105,97,108,45,111,102,102,101,114,46,112,110,103},17,1);
	aot_strings[294] = alloc_string_java(vm,(JCHAR[]){40,76,106,97,118,97,47,108,97,110,103,47,79,98,106,101,99,116,59,76,106,97,118,97,47,108,97,110,103,47,79,98,106,101,99,116,59,41,76,106,97,118,97,47,108,97,110,103,47,79,98,106,101,99,116,59},56,1);
	aot_strings[8] = alloc_string_java(vm,(JCHAR[]){115,99,114,101,101,110,87,105,100,116,104},11,1);
	aot_strings[55] = alloc_string_java(vm,(JCHAR[]){40,76,106,97,118,97,47,108,97,110,103,47,83,116,114,105,110,103,59,76,106,97,118,97,47,108,97,110,103,47,83,116,114,105,110,103,59,76,100,105,103,105,112,108,97,121,47,78,101,116,36,72,116,116,112,76,105,115,116,101,110,101,114,59,41,86},66,1);
	aot_strings[112] = alloc_string_java(vm,(JCHAR[]){70},1,1);
	aot_strings[111] = alloc_string_java(vm,(JCHAR[]){100,105,103,105,112,108,97,121,47,83,112,114,105,116,101,50,68},17,1);
	aot_strings[4] = alloc_string_java(vm,(JCHAR[]){73},1,1);
	aot_strings[339] = alloc_string_java(vm,(JCHAR[]){115,101,116,82,111,111,116,86,105,101,119,67,111,110,116,114,111,108,108,101,114,58},22,1);
	aot_strings[46] = alloc_string_java(vm,(JCHAR[]){74},1,1);
	aot_strings[289] = alloc_string_java(vm,(JCHAR[]){40,76,106,97,118,97,47,108,97,110,103,47,79,98,106,101,99,116,59,41,76,106,97,118,97,47,108,97,110,103,47,79,98,106,101,99,116,59},38,1);
	aot_strings[340] = alloc_string_java(vm,(JCHAR[]){103,97,109,97,118,109,47,97,112,112,108,101,47,117,105,107,105,116,47,85,73,86,105,101,119,67,111,110,116,114,111,108,108,101,114},35,1);
	aot_strings[308] = alloc_string_java(vm,(JCHAR[]){97,114,114,97,121,99,111,112,121},9,1);
	aot_strings[138] = alloc_string_java(vm,(JCHAR[]){108,97,115,116,67,104,105,108,100},9,1);
	aot_strings[302] = alloc_string_java(vm,(JCHAR[]){110,97,116,105,118,101,71,101,116},9,1);
	aot_strings[105] = alloc_string_java(vm,(JCHAR[]){106,97,118,97,47,108,97,110,103,47,78,117,108,108,80,111,105,110,116,101,114,69,120,99,101,112,116,105,111,110},30,1);
	aot_strings[276] = alloc_string_java(vm,(JCHAR[]){112,101,114,115,112,101,99,116,105,118,101},11,1);
	aot_strings[246] = alloc_string_java(vm,(JCHAR[]){40,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,41,86},19,1);
	aot_strings[212] = alloc_string_java(vm,(JCHAR[]){90},1,1);
	aot_strings[45] = alloc_string_java(vm,(JCHAR[]){102,112,115,84,105,109,101,114},8,1);
	aot_strings[117] = alloc_string_java(vm,(JCHAR[]){97,110,105,109,83,99,97,108,101,88},10,1);
	aot_strings[321] = alloc_string_java(vm,(JCHAR[]){100,105,103,105,112,108,97,121,47,114,101,110,100,101,114,47,73,110,100,101,120,66,117,102,102,101,114},27,1);
	aot_strings[256] = alloc_string_java(vm,(JCHAR[]){100,105,114,116,121},5,1);
	aot_strings[249] = alloc_string_java(vm,(JCHAR[]){32,45,62,32},4,1);
	aot_strings[175] = alloc_string_java(vm,(JCHAR[]){40,73,41,76,100,105,103,105,112,108,97,121,47,77,97,116,50,68,59},19,1);
	aot_strings[10] = alloc_string_java(vm,(JCHAR[]){40,70,70,41,86},5,1);
	aot_strings[189] = alloc_string_java(vm,(JCHAR[]){104,119,87,105,100,116,104},7,1);
	aot_strings[157] = alloc_string_java(vm,(JCHAR[]){115,101,116},3,1);
	aot_strings[328] = alloc_string_java(vm,(JCHAR[]){40,76,106,97,118,97,47,108,97,110,103,47,83,116,114,105,110,103,59,41,76,103,97,109,97,118,109,47,97,112,112,108,101,47,79,98,106,67,67,108,97,115,115,59},44,1);
	aot_strings[342] = alloc_string_java(vm,(JCHAR[]){106,97,118,97,47,108,97,110,103,47,76,111,110,103},14,1);
	aot_strings[184] = alloc_string_java(vm,(JCHAR[]){114},1,1);
	aot_strings[254] = alloc_string_java(vm,(JCHAR[]){115,97,102,101,66,111,116,116,111,109},10,1);
	aot_strings[201] = alloc_string_java(vm,(JCHAR[]){32,114,101,115,111,108,117,116,105,111,110,58,32},13,1);
	aot_strings[26] = alloc_string_java(vm,(JCHAR[]){114,101,97,100,70,105,108,101},8,1);
	aot_strings[305] = alloc_string_java(vm,(JCHAR[]){100,105,103,105,112,108,97,121,47,110,101,116,47,83,111,99,107,101,116},19,1);
	aot_strings[16] = alloc_string_java(vm,(JCHAR[]){120},1,1);
	aot_strings[18] = alloc_string_java(vm,(JCHAR[]){121},1,1);
	aot_strings[267] = alloc_string_java(vm,(JCHAR[]){111,114,116,104,111,103,114,97,112,104,105,99},12,1);
	aot_strings[257] = alloc_string_java(vm,(JCHAR[]){122},1,1);
	aot_strings[36] = alloc_string_java(vm,(JCHAR[]){116,111,83,116,114,105,110,103},8,1);
	aot_strings[7] = alloc_string_java(vm,(JCHAR[]){100,105,103,105,112,108,97,121,47,80,108,97,116,102,111,114,109},17,1);
	aot_strings[329] = alloc_string_java(vm,(JCHAR[]){114,101,103,105,115,116,101,114},8,1);
	aot_strings[67] = alloc_string_java(vm,(JCHAR[]){80,79,83,84},4,1);
	aot_strings[280] = alloc_string_java(vm,(JCHAR[]){103,101,116,67,111,109,98,105,110,101,100,77,97,116,114,105,120},17,1);
	aot_strings[236] = alloc_string_java(vm,(JCHAR[]){112,114,101,112,101,110,100},7,1);
	aot_strings[96] = alloc_string_java(vm,(JCHAR[]){114,117,110},3,1);
	aot_strings[233] = alloc_string_java(vm,(JCHAR[]){40,76,100,105,103,105,112,108,97,121,47,77,97,116,114,105,120,51,68,59,76,100,105,103,105,112,108,97,121,47,77,97,116,114,105,120,51,68,59,76,100,105,103,105,112,108,97,121,47,77,97,116,114,105,120,51,68,59,41,86},60,1);
	aot_strings[185] = alloc_string_java(vm,(JCHAR[]){100,120},2,1);
	aot_strings[107] = alloc_string_java(vm,(JCHAR[]){99,111,109,112,105,108,101},7,1);
	aot_strings[186] = alloc_string_java(vm,(JCHAR[]){100,121},2,1);
	aot_strings[135] = alloc_string_java(vm,(JCHAR[]){102,105,114,115,116,67,104,105,108,100},10,1);
	aot_strings[106] = alloc_string_java(vm,(JCHAR[]){100,105,103,105,112,108,97,121,47,71,76,83,104,97,100,101,114,50,68},19,1);
	aot_strings[52] = alloc_string_java(vm,(JCHAR[]){40,76,77,121,71,97,109,101,59,41,86},11,1);
	aot_strings[290] = alloc_string_java(vm,(JCHAR[]){103,97,109,97,118,109,47,97,112,112,108,101,47,79,98,106,67},17,1);
	aot_strings[216] = alloc_string_java(vm,(JCHAR[]){106,97,118,97,47,108,97,110,103,47,84,104,114,111,119,97,98,108,101},19,1);
	aot_strings[84] = alloc_string_java(vm,(JCHAR[]){40,91,66,41,86},5,1);
	aot_strings[345] = alloc_string_java(vm,(JCHAR[]){99,97,108,108,86,111,105,100},8,1);
	aot_strings[266] = alloc_string_java(vm,(JCHAR[]){112,114,111,106,101,99,116,105,111,110,77,97,116,114,105,120},16,1);
	aot_strings[149] = alloc_string_java(vm,(JCHAR[]){100,105,103,105,112,108,97,121,47,77,97,116,114,105,120,50,68},17,1);
	aot_strings[270] = alloc_string_java(vm,(JCHAR[]){116,97,114,103,101,116,90},7,1);
	aot_strings[269] = alloc_string_java(vm,(JCHAR[]){116,97,114,103,101,116,89},7,1);
	aot_strings[268] = alloc_string_java(vm,(JCHAR[]){116,97,114,103,101,116,88},7,1);
	aot_strings[22] = alloc_string_java(vm,(JCHAR[]){115,101,116,65,108,112,104,97},8,1);
	aot_strings[312] = alloc_string_java(vm,(JCHAR[]){67,65,67,72,69},5,1);
	aot_strings[64] = alloc_string_java(vm,(JCHAR[]){40,91,66,41,73},5,1);
	aot_strings[200] = alloc_string_java(vm,(JCHAR[]){40,70,41,76,106,97,118,97,47,108,97,110,103,47,83,116,114,105,110,103,66,117,105,108,100,101,114,59},28,1);
	aot_strings[214] = alloc_string_java(vm,(JCHAR[]){76,100,105,103,105,112,108,97,121,47,71,97,109,101,59},15,1);
	aot_strings[54] = alloc_string_java(vm,(JCHAR[]){104,116,116,112},4,1);
	aot_strings[181] = alloc_string_java(vm,(JCHAR[]){100,114,97,119,81,117,97,100,77,101,115,104},12,1);
	aot_strings[207] = alloc_string_java(vm,(JCHAR[]){40,73,73,90,73,41,86},7,1);
	aot_strings[70] = alloc_string_java(vm,(JCHAR[]){106,97,118,97,47,105,111,47,66,121,116,101,65,114,114,97,121,79,117,116,112,117,116,83,116,114,101,97,109},29,1);
	aot_strings[136] = alloc_string_java(vm,(JCHAR[]){110,101,120,116},4,1);
	aot_strings[224] = alloc_string_java(vm,(JCHAR[]){100,105,103,105,112,108,97,121,47,77,97,116,114,105,120,51,68},17,1);
	aot_strings[178] = alloc_string_java(vm,(JCHAR[]){99,111,108,111,114},5,1);
	aot_strings[299] = alloc_string_java(vm,(JCHAR[]){67,97,110,39,116,32,114,101,103,105,115,116,101,114,32,115,101,108,101,99,116,111,114,58,32},25,1);
	aot_strings[285] = alloc_string_java(vm,(JCHAR[]){99,108,97,115,115,101,115},7,1);
	aot_strings[208] = alloc_string_java(vm,(JCHAR[]){100,114,97,119,67,104,105,108,100,114,101,110},12,1);
	aot_strings[41] = alloc_string_java(vm,(JCHAR[]){117,112,100,97,116,101},6,1);
	aot_strings[318] = alloc_string_java(vm,(JCHAR[]){100,105,103,105,112,108,97,121,47,114,101,110,100,101,114,47,83,104,97,100,101,114},22,1);
	aot_strings[323] = alloc_string_java(vm,(JCHAR[]){103,97,109,97,118,109,47,97,112,112,108,101,47,78,83,77,117,116,97,98,108,101,79,98,106,101,99,116},28,1);
	aot_strings[275] = alloc_string_java(vm,(JCHAR[]){102,111,118},3,1);
	aot_strings[69] = alloc_string_java(vm,(JCHAR[]){40,76,106,97,118,97,47,108,97,110,103,47,83,116,114,105,110,103,59,41,90},21,1);
	aot_strings[62] = alloc_string_java(vm,(JCHAR[]){106,97,118,97,47,105,111,47,73,110,112,117,116,83,116,114,101,97,109},19,1);
	aot_strings[20] = alloc_string_java(vm,(JCHAR[]){114,97,110,100,111,109},6,1);
	aot_strings[59] = alloc_string_java(vm,(JCHAR[]){40,41,76,106,97,118,97,47,105,111,47,73,110,112,117,116,83,116,114,101,97,109,59},23,1);
	aot_strings[65] = alloc_string_java(vm,(JCHAR[]){106,97,118,97,47,108,97,110,103,47,83,116,114,105,110,103},16,1);
	aot_strings[271] = alloc_string_java(vm,(JCHAR[]){89,85,112},3,1);
	aot_strings[51] = alloc_string_java(vm,(JCHAR[]){77,121,71,97,109,101,36,49},8,1);
	aot_strings[5] = alloc_string_java(vm,(JCHAR[]){76,100,105,103,105,112,108,97,121,47,83,116,97,103,101,50,68,59},18,1);
	aot_strings[129] = alloc_string_java(vm,(JCHAR[]){97,108,112,104,97},5,1);
	aot_strings[320] = alloc_string_java(vm,(JCHAR[]){40,76,106,97,118,97,47,108,97,110,103,47,83,116,114,105,110,103,59,76,106,97,118,97,47,108,97,110,103,47,83,116,114,105,110,103,59,41,74},39,1);
	aot_strings[205] = alloc_string_java(vm,(JCHAR[]){105,110,118,97,108,105,100,97,116,101,83,112,114,105,116,101},16,1);
	aot_strings[162] = alloc_string_java(vm,(JCHAR[]){115,105,110},3,1);
	aot_strings[209] = alloc_string_java(vm,(JCHAR[]){101,110,100},3,1);
	aot_strings[232] = alloc_string_java(vm,(JCHAR[]){109,117,108,116,105,112,108,121},8,1);
	aot_strings[219] = alloc_string_java(vm,(JCHAR[]){103,99},2,1);
	aot_strings[143] = alloc_string_java(vm,(JCHAR[]){108,105,110,107,67,104,105,108,100},9,1);
	aot_strings[19] = alloc_string_java(vm,(JCHAR[]){106,97,118,97,47,108,97,110,103,47,77,97,116,104},14,1);
	aot_strings[265] = alloc_string_java(vm,(JCHAR[]){40,70,70,70,70,70,70,70,70,70,41,86},12,1);
	aot_strings[195] = alloc_string_java(vm,(JCHAR[]){100,101,115,105,103,110,83,105,122,101},10,1);
	aot_strings[87] = alloc_string_java(vm,(JCHAR[]){106,97,118,97,47,110,101,116,47,83,101,114,118,101,114,83,111,99,107,101,116},21,1);
	aot_strings[343] = alloc_string_java(vm,(JCHAR[]){118,97,108,117,101,79,102},7,1);
	aot_strings[197] = alloc_string_java(vm,(JCHAR[]){115,99,97,108,101,70,97,99,116,111,114},11,1);
	aot_strings[32] = alloc_string_java(vm,(JCHAR[]){112,110,103,45,98,121,116,101,115,58},10,1);
	aot_strings[23] = alloc_string_java(vm,(JCHAR[]){114,111,116,97,116,105,111,110},8,1);
	aot_strings[9] = alloc_string_java(vm,(JCHAR[]){115,99,114,101,101,110,72,101,105,103,104,116},12,1);
	aot_strings[47] = alloc_string_java(vm,(JCHAR[]){102,112,115},3,1);
	aot_strings[174] = alloc_string_java(vm,(JCHAR[]){103,101,116,87,111,114,108,100,77,97,116,114,105,120},14,1);
	aot_strings[35] = alloc_string_java(vm,(JCHAR[]){40,73,41,76,106,97,118,97,47,108,97,110,103,47,83,116,114,105,110,103,66,117,105,108,100,101,114,59},28,1);
	aot_strings[169] = alloc_string_java(vm,(JCHAR[]){100,105,103,105,112,108,97,121,47,81,117,97,100,77,101,115,104},17,1);
	aot_strings[79] = alloc_string_java(vm,(JCHAR[]){112,97,114,115,101,73,110,116},8,1);
	aot_strings[240] = alloc_string_java(vm,(JCHAR[]){99,111,112,121,84,111,50,68},8,1);
	aot_strings[179] = alloc_string_java(vm,(JCHAR[]){98,108,101,110,100,77,111,100,101},9,1);
	aot_strings[247] = alloc_string_java(vm,(JCHAR[]){84,77,80},3,1);
	aot_strings[91] = alloc_string_java(vm,(JCHAR[]){84,109,112},3,1);
	aot_strings[82] = alloc_string_java(vm,(JCHAR[]){116,111,66,121,116,101,65,114,114,97,121},11,1);
	aot_strings[17] = alloc_string_java(vm,(JCHAR[]){40,70,41,86},4,1);
	aot_strings[194] = alloc_string_java(vm,(JCHAR[]){114,101,115,105,122,101},6,1);
	aot_strings[11] = alloc_string_java(vm,(JCHAR[]){115,101,116,117,112},5,1);
	aot_strings[73] = alloc_string_java(vm,(JCHAR[]){40,76,106,97,118,97,47,108,97,110,103,47,83,116,114,105,110,103,59,41,91,76,106,97,118,97,47,108,97,110,103,47,83,116,114,105,110,103,59},39,1);
	aot_strings[33] = alloc_string_java(vm,(JCHAR[]){97,112,112,101,110,100},6,1);
	aot_strings[310] = alloc_string_java(vm,(JCHAR[]){100,105,115,99,111,110,110,101,99,116},10,1);
	aot_strings[78] = alloc_string_java(vm,(JCHAR[]){106,97,118,97,47,108,97,110,103,47,73,110,116,101,103,101,114},17,1);
	aot_strings[210] = alloc_string_java(vm,(JCHAR[]){103,108,95,70,114,97,103,67,111,108,111,114,32,61,32,118,67,111,108,111,114,59},22,1);
	aot_strings[147] = alloc_string_java(vm,(JCHAR[]){109,97,114,107,67,111,110,116,101,110,116,73,110,118,97,108,105,100},18,1);
	aot_strings[166] = alloc_string_java(vm,(JCHAR[]){95,115,121},3,1);
	aot_strings[15] = alloc_string_java(vm,(JCHAR[]){40,76,100,105,103,105,112,108,97,121,47,83,112,114,105,116,101,50,68,59,41,86},22,1);
	aot_strings[164] = alloc_string_java(vm,(JCHAR[]){95,115,120},3,1);
	aot_strings[341] = alloc_string_java(vm,(JCHAR[]){103,101,116,72,97,110,100,108,101},9,1);
	aot_strings[61] = alloc_string_java(vm,(JCHAR[]){40,41,76,106,97,118,97,47,105,111,47,79,117,116,112,117,116,83,116,114,101,97,109,59},24,1);
	aot_strings[293] = alloc_string_java(vm,(JCHAR[]){112,117,116},3,1);
	aot_strings[191] = alloc_string_java(vm,(JCHAR[]){100,105,103,105,112,108,97,121,47,66,97,103},12,1);
	aot_strings[57] = alloc_string_java(vm,(JCHAR[]){106,97,118,97,47,110,101,116,47,83,111,99,107,101,116},15,1);
	aot_strings[38] = alloc_string_java(vm,(JCHAR[]){106,97,118,97,47,105,111,47,80,114,105,110,116,83,116,114,101,97,109},19,1);
	aot_strings[260] = alloc_string_java(vm,(JCHAR[]){114,111,116,97,116,105,111,110,88},9,1);
	aot_strings[300] = alloc_string_java(vm,(JCHAR[]){103,97,109,97,118,109,47,106,110,105,47,74,110,105,79,98,106,101,99,116},20,1);
	aot_strings[261] = alloc_string_java(vm,(JCHAR[]){114,111,116,97,116,105,111,110,89},9,1);
	aot_strings[158] = alloc_string_java(vm,(JCHAR[]){40,70,70,70,70,70,70,41,86},9,1);
	aot_strings[262] = alloc_string_java(vm,(JCHAR[]){114,111,116,97,116,105,111,110,90},9,1);
	aot_strings[165] = alloc_string_java(vm,(JCHAR[]){95,99,121},3,1);
	aot_strings[97] = alloc_string_java(vm,(JCHAR[]){40,76,100,105,103,105,112,108,97,121,47,71,97,109,101,59,41,86},18,1);
	aot_strings[244] = alloc_string_java(vm,(JCHAR[]){115,113,114,116},4,1);
	aot_strings[163] = alloc_string_java(vm,(JCHAR[]){95,99,120},3,1);
	aot_strings[274] = alloc_string_java(vm,(JCHAR[]){102,97,114},3,1);
	aot_strings[330] = alloc_string_java(vm,(JCHAR[]){40,76,106,97,118,97,47,108,97,110,103,47,83,116,114,105,110,103,59,41,76,103,97,109,97,118,109,47,97,112,112,108,101,47,83,101,108,101,99,116,111,114,59},43,1);
	aot_strings[126] = alloc_string_java(vm,(JCHAR[]){97,110,105,109,83,107,101,119,88},9,1);
	aot_strings[27] = alloc_string_java(vm,(JCHAR[]){40,76,106,97,118,97,47,108,97,110,103,47,83,116,114,105,110,103,59,41,91,66},22,1);
	aot_strings[81] = alloc_string_java(vm,(JCHAR[]){119,114,105,116,101},5,1);
	aot_strings[128] = alloc_string_java(vm,(JCHAR[]){97,110,105,109,83,107,101,119,89},9,1);
	aot_strings[239] = alloc_string_java(vm,(JCHAR[]){76,100,105,103,105,112,108,97,121,47,77,97,116,114,105,120,50,68,59},19,1);
	aot_strings[108] = alloc_string_java(vm,(JCHAR[]){40,76,106,97,118,97,47,108,97,110,103,47,83,116,114,105,110,103,59,41,74},21,1);
	aot_strings[50] = alloc_string_java(vm,(JCHAR[]){104,116,116,112,115,58,47,47,119,119,119,46,103,111,111,103,108,101,46,99,111,109},22,1);
	aot_strings[148] = alloc_string_java(vm,(JCHAR[]){105,110,105,116},4,1);
	aot_strings[80] = alloc_string_java(vm,(JCHAR[]){40,76,106,97,118,97,47,108,97,110,103,47,83,116,114,105,110,103,59,41,73},21,1);
	aot_strings[278] = alloc_string_java(vm,(JCHAR[]){99,111,109,98,105,110,101,100,77,97,116,114,105,120},14,1);
	aot_strings[168] = alloc_string_java(vm,(JCHAR[]){76,100,105,103,105,112,108,97,121,47,81,117,97,100,77,101,115,104,59},19,1);
	aot_strings[234] = alloc_string_java(vm,(JCHAR[]){84,82,65,77,65,84},6,1);
	aot_strings[279] = alloc_string_java(vm,(JCHAR[]){90,68,73,86,73,83,79,82},8,1);
	aot_strings[146] = alloc_string_java(vm,(JCHAR[]){105,110,118,97,108,105,100,97,116,101,67,111,110,116,101,110,116},17,1);
	aot_strings[172] = alloc_string_java(vm,(JCHAR[]){76,100,105,103,105,112,108,97,121,47,71,76,81,117,97,100,66,97,116,99,104,59},22,1);
	aot_strings[92] = alloc_string_java(vm,(JCHAR[]){119,111,114,107},4,1);
	aot_strings[325] = alloc_string_java(vm,(JCHAR[]){100,101,102,97,117,108,116,81,117,101,117,101},12,1);
	aot_strings[130] = alloc_string_java(vm,(JCHAR[]){97,110,105,109,65,108,112,104,97},9,1);
	aot_strings[90] = alloc_string_java(vm,(JCHAR[]){40,41,76,106,97,118,97,47,110,101,116,47,83,111,99,107,101,116,59},19,1);
	aot_strings[337] = alloc_string_java(vm,(JCHAR[]){85,73,65,112,112,108,105,99,97,116,105,111,110},13,1);
	aot_strings[100] = alloc_string_java(vm,(JCHAR[]){104,97,110,100,108,101},6,1);
	aot_strings[95] = alloc_string_java(vm,(JCHAR[]){72,116,116,112,32,70,97,105,108},9,1);
	aot_strings[93] = alloc_string_java(vm,(JCHAR[]){40,76,106,97,118,97,47,110,101,116,47,83,111,99,107,101,116,59,41,86},20,1);
	aot_strings[287] = alloc_string_java(vm,(JCHAR[]){106,97,118,97,47,117,116,105,108,47,77,97,112},13,1);
	aot_strings[151] = alloc_string_java(vm,(JCHAR[]){109,48,48},3,1);
	aot_strings[40] = alloc_string_java(vm,(JCHAR[]){40,76,106,97,118,97,47,108,97,110,103,47,83,116,114,105,110,103,59,41,86},21,1);
	aot_strings[58] = alloc_string_java(vm,(JCHAR[]){103,101,116,73,110,112,117,116,83,116,114,101,97,109},14,1);
	aot_strings[153] = alloc_string_java(vm,(JCHAR[]){109,48,50},3,1);
	aot_strings[152] = alloc_string_java(vm,(JCHAR[]){109,48,49},3,1);
	aot_strings[13] = alloc_string_java(vm,(JCHAR[]){100,105,103,105,112,108,97,121,47,73,109,97,103,101},14,1);
	aot_strings[255] = alloc_string_java(vm,(JCHAR[]){100,105,103,105,112,108,97,121,47,67,97,109,101,114,97},15,1);
	aot_strings[110] = alloc_string_java(vm,(JCHAR[]){67,97,110,39,116,32,99,111,109,112,105,108,101,32,71,76,83,104,97,100,101,114,50,68},24,1);
	aot_strings[199] = alloc_string_java(vm,(JCHAR[]){83,116,97,103,101,50,68,58,58,115,99,97,108,101,70,97,99,116,111,114,32,105,115,32},24,1);
	aot_strings[98] = alloc_string_java(vm,(JCHAR[]){100,105,103,105,112,108,97,121,47,77,97,116,50,68},14,1);
	aot_strings[264] = alloc_string_java(vm,(JCHAR[]){99,111,109,112,111,115,101},7,1);
	aot_strings[333] = alloc_string_java(vm,(JCHAR[]){103,97,109,97,118,109,47,97,112,112,108,101,47,117,105,107,105,116,47,85,73,82,101,115,112,111,110,100,101,114},30,1);
	aot_strings[309] = alloc_string_java(vm,(JCHAR[]){40,76,106,97,118,97,47,108,97,110,103,47,79,98,106,101,99,116,59,73,76,106,97,118,97,47,108,97,110,103,47,79,98,106,101,99,116,59,73,73,41,86},42,1);
	aot_strings[206] = alloc_string_java(vm,(JCHAR[]){98,101,103,105,110},5,1);
	aot_strings[332] = alloc_string_java(vm,(JCHAR[]){40,76,103,97,109,97,118,109,47,97,112,112,108,101,47,78,83,79,98,106,101,99,116,59,76,103,97,109,97,118,109,47,97,112,112,108,101,47,83,101,108,101,99,116,111,114,59,76,106,97,118,97,47,108,97,110,103,47,67,108,97,115,115,59,91,76,106,97,118,97,47,108,97,110,103,47,79,98,106,101,99,116,59,41,76,103,97,109,97,118,109,47,97,112,112,108,101,47,78,83,79,98,106,101,99,116,59},107,1);
	aot_strings[28] = alloc_string_java(vm,(JCHAR[]){106,97,118,97,47,108,97,110,103,47,83,121,115,116,101,109},16,1);
	aot_strings[161] = alloc_string_java(vm,(JCHAR[]){40,68,41,68},4,1);
	aot_strings[336] = alloc_string_java(vm,(JCHAR[]){76,103,97,109,97,118,109,47,97,112,112,108,101,47,117,105,107,105,116,47,85,73,65,112,112,108,105,99,97,116,105,111,110,59},34,1);
	aot_strings[307] = alloc_string_java(vm,(JCHAR[]){91,66},2,1);
	aot_strings[114] = alloc_string_java(vm,(JCHAR[]){102,108,97,103,115},5,1);
	aot_strings[238] = alloc_string_java(vm,(JCHAR[]){84,77,80,50,68},5,1);
	aot_strings[124] = alloc_string_java(vm,(JCHAR[]){112,105,118,111,116,89},6,1);
	aot_strings[226] = alloc_string_java(vm,(JCHAR[]){91,70},2,1);
	aot_strings[215] = alloc_string_java(vm,(JCHAR[]){100,105,103,105,112,108,97,121,47,71,97,109,101},13,1);
	aot_strings[122] = alloc_string_java(vm,(JCHAR[]){112,105,118,111,116,88},6,1);
	aot_strings[155] = alloc_string_java(vm,(JCHAR[]){109,49,49},3,1);
	aot_strings[173] = alloc_string_java(vm,(JCHAR[]){71,76,79,66,65,76,95,70,82,65,77,69,95,86,69,82,83,73,79,78},20,1);
	aot_strings[154] = alloc_string_java(vm,(JCHAR[]){109,49,48},3,1);
	aot_strings[319] = alloc_string_java(vm,(JCHAR[]){105,110,116,101,114,110,97,108,67,114,101,97,116,101},14,1);
	aot_strings[134] = alloc_string_java(vm,(JCHAR[]){119,111,114,108,100,65,108,112,104,97},10,1);
	aot_strings[156] = alloc_string_java(vm,(JCHAR[]){109,49,50},3,1);
	aot_strings[29] = alloc_string_java(vm,(JCHAR[]){111,117,116},3,1);
	aot_strings[182] = alloc_string_java(vm,(JCHAR[]){40,76,100,105,103,105,112,108,97,121,47,81,117,97,100,77,101,115,104,59,76,100,105,103,105,112,108,97,121,47,77,97,116,50,68,59,76,100,105,103,105,112,108,97,121,47,71,76,83,104,97,100,101,114,50,68,59,73,70,73,41,86},62,1);
	aot_strings[281] = alloc_string_java(vm,(JCHAR[]){40,41,76,100,105,103,105,112,108,97,121,47,77,97,116,114,105,120,51,68,59},21,1);
	aot_strings[171] = alloc_string_java(vm,(JCHAR[]){81,117,97,100,66,97,116,99,104},9,1);
	aot_strings[241] = alloc_string_java(vm,(JCHAR[]){40,76,100,105,103,105,112,108,97,121,47,77,97,116,114,105,120,50,68,59,41,86},22,1);
	aot_strings[220] = alloc_string_java(vm,(JCHAR[]){100,105,103,105,112,108,97,121,47,65,115,115,101,116},14,1);
	aot_strings[252] = alloc_string_java(vm,(JCHAR[]){115,97,102,101,82,105,103,104,116},9,1);
	aot_strings[188] = alloc_string_java(vm,(JCHAR[]){100,105,103,105,112,108,97,121,47,71,76,84,101,120,116,117,114,101},18,1);
	aot_strings[150] = alloc_string_java(vm,(JCHAR[]){105,100,101,110,116,105,116,121},8,1);
	aot_strings[338] = alloc_string_java(vm,(JCHAR[]){103,97,109,97,118,109,47,97,112,112,108,101,47,117,105,107,105,116,47,85,73,86,105,101,119},25,1);
	aot_strings[288] = alloc_string_java(vm,(JCHAR[]){103,101,116},3,1);
	aot_strings[322] = alloc_string_java(vm,(JCHAR[]){91,83},2,1);
	aot_strings[211] = alloc_string_java(vm,(JCHAR[]){105,110,105,116,105,97,108,105,122,101,100},11,1);
	aot_strings[66] = alloc_string_java(vm,(JCHAR[]){40,91,66,73,73,41,86},7,1);
	aot_strings[347] = alloc_string_java(vm,(JCHAR[]){109,97,107,101,75,101,121,65,110,100,86,105,115,105,98,108,101},17,1);
	aot_strings[235] = alloc_string_java(vm,(JCHAR[]){76,100,105,103,105,112,108,97,121,47,77,97,116,114,105,120,51,68,59},19,1);
	aot_strings[86] = alloc_string_java(vm,(JCHAR[]){92,63},2,1);
	aot_strings[21] = alloc_string_java(vm,(JCHAR[]){40,41,68},3,1);
	aot_strings[301] = alloc_string_java(vm,(JCHAR[]){103,97,109,97,118,109,47,106,110,105,47,74,110,105,67,108,97,115,115},19,1);
	aot_strings[183] = alloc_string_java(vm,(JCHAR[]){40,41,70},3,1);
	aot_strings[296] = alloc_string_java(vm,(JCHAR[]){103,97,109,97,118,109,47,97,112,112,108,101,47,83,101,108,101,99,116,111,114},21,1);
	aot_strings[282] = alloc_string_java(vm,(JCHAR[]){111,110,67,111,109,112,108,101,116,101},10,1);
	aot_strings[43] = alloc_string_java(vm,(JCHAR[]){40,41,74},3,1);
	aot_strings[242] = alloc_string_java(vm,(JCHAR[]){84,77,80,51,68},5,1);
	aot_strings[286] = alloc_string_java(vm,(JCHAR[]){76,106,97,118,97,47,117,116,105,108,47,77,97,112,59},15,1);
	aot_strings[180] = alloc_string_java(vm,(JCHAR[]){100,105,103,105,112,108,97,121,47,71,76,81,117,97,100,66,97,116,99,104},20,1);
	aot_strings[167] = alloc_string_java(vm,(JCHAR[]){113,117,97,100},4,1);
	aot_strings[139] = alloc_string_java(vm,(JCHAR[]){100,101,112,116,104},5,1);
	aot_strings[326] = alloc_string_java(vm,(JCHAR[]){76,103,97,109,97,118,109,47,97,112,112,108,101,47,115,116,111,114,101,107,105,116,47,83,75,80,97,121,109,101,110,116,81,117,101,117,101,59},38,1);
	aot_strings[2] = alloc_string_java(vm,(JCHAR[]){40,41,86},3,1);
	aot_strings[42] = alloc_string_java(vm,(JCHAR[]){99,117,114,114,101,110,116,84,105,109,101,77,105,108,108,105,115},17,1);
	aot_strings[121] = alloc_string_java(vm,(JCHAR[]){119,105,100,116,104},5,1);
	aot_strings[304] = alloc_string_java(vm,(JCHAR[]){102,105,110,97,108,105,122,101},8,1);
	aot_strings[140] = alloc_string_java(vm,(JCHAR[]){117,110,108,105,110,107,67,104,105,108,100},11,1);
	aot_strings[60] = alloc_string_java(vm,(JCHAR[]){103,101,116,79,117,116,112,117,116,83,116,114,101,97,109},15,1);
	aot_strings[316] = alloc_string_java(vm,(JCHAR[]){112,101,110,100,105,110,103,77,97,115,107},11,1);
	aot_strings[198] = alloc_string_java(vm,(JCHAR[]){115,101,116,83,99,97,108,101,89},9,1);
	aot_strings[317] = alloc_string_java(vm,(JCHAR[]){100,105,103,105,112,108,97,121,47,114,101,110,100,101,114,47,82,101,110,100,101,114,68,101,118,105,99,101},28,1);
	aot_strings[218] = alloc_string_java(vm,(JCHAR[]){108,97,115,116,84,105,109,101},8,1);
	aot_strings[344] = alloc_string_java(vm,(JCHAR[]){40,74,41,76,106,97,118,97,47,108,97,110,103,47,76,111,110,103,59},19,1);
	aot_strings[283] = alloc_string_java(vm,(JCHAR[]){103,97,109,97,118,109,47,97,112,112,108,101,47,78,83,79,98,106,101,99,116},21,1);
	aot_strings[94] = alloc_string_java(vm,(JCHAR[]){72,116,116,112,32,83,117,99,99,101,115,115,58,32},14,1);
	aot_strings[49] = alloc_string_java(vm,(JCHAR[]){104,116,116,112,84,105,109,101,114},9,1);
	aot_strings[160] = alloc_string_java(vm,(JCHAR[]){99,111,115},3,1);
	aot_strings[131] = alloc_string_java(vm,(JCHAR[]){117,112,100,97,116,101,87,111,114,108,100,65,108,112,104,97},16,1);
	aot_strings[6] = alloc_string_java(vm,(JCHAR[]){100,105,103,105,112,108,97,121,47,80,111,105,110,116,50,68},16,1);
	aot_strings[263] = alloc_string_java(vm,(JCHAR[]){115,99,97,108,101,90},6,1);
	aot_strings[116] = alloc_string_java(vm,(JCHAR[]){115,99,97,108,101,88},6,1);
	aot_strings[327] = alloc_string_java(vm,(JCHAR[]){83,75,80,97,121,109,101,110,116,81,117,101,117,101},14,1);
	aot_strings[118] = alloc_string_java(vm,(JCHAR[]){115,99,97,108,101,89},6,1);
	aot_strings[277] = alloc_string_java(vm,(JCHAR[]){40,70,70,70,70,41,86},7,1);
	aot_strings[314] = alloc_string_java(vm,(JCHAR[]){100,105,103,105,112,108,97,121,47,114,101,110,100,101,114,47,71,80,85},19,1);
	aot_strings[72] = alloc_string_java(vm,(JCHAR[]){115,112,108,105,116},5,1);
	aot_strings[258] = alloc_string_java(vm,(JCHAR[]){105,115,79,114,116,104,111},7,1);
	aot_strings[25] = alloc_string_java(vm,(JCHAR[]){100,105,103,105,112,108,97,121,47,77,97,105,110,65,99,116,105,118,105,116,121},21,1);
	aot_strings[99] = alloc_string_java(vm,(JCHAR[]){99,114,101,97,116,101},6,1);
	aot_strings[228] = alloc_string_java(vm,(JCHAR[]){40,70,70,70,70,70,70,90,41,86},10,1);
	aot_strings[30] = alloc_string_java(vm,(JCHAR[]){76,106,97,118,97,47,105,111,47,80,114,105,110,116,83,116,114,101,97,109,59},21,1);
	aot_strings[306] = alloc_string_java(vm,(JCHAR[]){98,117,102,102,101,114},6,1);
	aot_strings[104] = alloc_string_java(vm,(JCHAR[]){100,105,103,105,112,108,97,121,47,66,121,116,101,65,114,114,97,121,67,111,109,112,108,101,116,97,98,108,101},29,1);
	aot_strings[176] = alloc_string_java(vm,(JCHAR[]){68,101,102,97,117,108,116,83,104,97,100,101,114},13,1);
	aot_strings[170] = alloc_string_java(vm,(JCHAR[]){40,73,70,70,70,70,70,70,70,70,70,70,70,70,41,86},16,1);
	aot_strings[227] = alloc_string_java(vm,(JCHAR[]){116,97,110},3,1);
	aot_strings[76] = alloc_string_java(vm,(JCHAR[]){40,73,41,76,106,97,118,97,47,108,97,110,103,47,83,116,114,105,110,103,59},21,1);
	aot_strings[237] = alloc_string_java(vm,(JCHAR[]){40,76,100,105,103,105,112,108,97,121,47,77,97,116,114,105,120,51,68,59,41,86},22,1);
	aot_strings[63] = alloc_string_java(vm,(JCHAR[]){114,101,97,100},4,1);
	aot_strings[272] = alloc_string_java(vm,(JCHAR[]){108,111,111,107,65,116},6,1);
	aot_strings[159] = alloc_string_java(vm,(JCHAR[]){109,111,100,105,102,121,67,111,117,110,116,101,114},13,1);
	aot_strings[230] = alloc_string_java(vm,(JCHAR[]){112,114,101,112,101,110,100,84,114,97,110,115,108,97,116,105,111,110},18,1);
	aot_strings[324] = alloc_string_java(vm,(JCHAR[]){103,97,109,97,118,109,47,97,112,112,108,101,47,115,116,111,114,101,107,105,116,47,83,75,80,97,121,109,101,110,116,81,117,101,117,101},36,1);
	aot_strings[48] = alloc_string_java(vm,(JCHAR[]){70,80,83,58,32},5,1);
	aot_strings[12] = alloc_string_java(vm,(JCHAR[]){40,76,100,105,103,105,112,108,97,121,47,80,111,105,110,116,50,68,59,41,86},21,1);
	aot_strings[292] = alloc_string_java(vm,(JCHAR[]){67,97,110,39,116,32,102,105,110,100,32,79,98,106,67,32,99,108,97,115,115,58,32},23,1);
	aot_strings[3] = alloc_string_java(vm,(JCHAR[]){100,105,103,105,112,108,97,121,47,83,116,97,103,101,50,68},16,1);
	aot_strings[177] = alloc_string_java(vm,(JCHAR[]){76,100,105,103,105,112,108,97,121,47,71,76,83,104,97,100,101,114,50,68,59},21,1);
	aot_strings[284] = alloc_string_java(vm,(JCHAR[]){103,97,109,97,118,109,47,97,112,112,108,101,47,79,98,106,67,67,108,97,115,115},22,1);
	aot_strings[142] = alloc_string_java(vm,(JCHAR[]){100,105,115,112,111,115,101},7,1);
	aot_strings[346] = alloc_string_java(vm,(JCHAR[]){40,76,103,97,109,97,118,109,47,97,112,112,108,101,47,78,83,79,98,106,101,99,116,59,76,103,97,109,97,118,109,47,97,112,112,108,101,47,83,101,108,101,99,116,111,114,59,91,76,106,97,118,97,47,108,97,110,103,47,79,98,106,101,99,116,59,41,86},68,1);
	aot_strings[109] = alloc_string_java(vm,(JCHAR[]){106,97,118,97,47,108,97,110,103,47,82,117,110,116,105,109,101,69,120,99,101,112,116,105,111,110},26,1);
	aot_strings[193] = alloc_string_java(vm,(JCHAR[]){115,101,116,70,108,97,103,115},8,1);
	aot_strings[213] = alloc_string_java(vm,(JCHAR[]){103,97,109,101},4,1);
	aot_strings[145] = alloc_string_java(vm,(JCHAR[]){73,110,118,97,108,105,100,97,116,105,111,110,67,111,117,110,116,101,114},19,1);
	aot_strings[295] = alloc_string_java(vm,(JCHAR[]){106,97,118,97,47,117,116,105,108,47,72,97,115,104,77,97,112},17,1);
	aot_strings[291] = alloc_string_java(vm,(JCHAR[]){111,98,106,99,95,103,101,116,67,108,97,115,115},13,1);
	aot_strings[334] = alloc_string_java(vm,(JCHAR[]){103,97,109,97,118,109,47,97,112,112,108,101,47,117,105,107,105,116,47,85,73,65,112,112,108,105,99,97,116,105,111,110},32,1);
	aot_strings[102] = alloc_string_java(vm,(JCHAR[]){102,114,101,101,77,101,109},7,1);
	aot_strings[297] = alloc_string_java(vm,(JCHAR[]){115,101,108,101,99,116,111,114,115},9,1);
	aot_strings[75] = alloc_string_java(vm,(JCHAR[]){115,117,98,115,116,114,105,110,103},9,1);
	aot_strings[39] = alloc_string_java(vm,(JCHAR[]){112,114,105,110,116,108,110},7,1);
	aot_strings[56] = alloc_string_java(vm,(JCHAR[]){114,101,110,100,101,114},6,1);
	aot_strings[204] = alloc_string_java(vm,(JCHAR[]){105,110,118,97,108,105,100,97,116,101,67,111,110,116,101,110,116,73,102,82,101,113,117,105,114,101,100},27,1);
	aot_strings[115] = alloc_string_java(vm,(JCHAR[]){97,110,105,109,89},5,1);
	aot_strings[120] = alloc_string_java(vm,(JCHAR[]){97,110,105,109,82,111,116,97,116,105,111,110},12,1);
	aot_strings[331] = alloc_string_java(vm,(JCHAR[]){99,97,108,108,79,98,106,101,99,116},10,1);
	aot_strings[298] = alloc_string_java(vm,(JCHAR[]){115,101,108,95,114,101,103,105,115,116,101,114,78,97,109,101},16,1);
	aot_strings[113] = alloc_string_java(vm,(JCHAR[]){97,110,105,109,88},5,1);
	aot_strings[44] = alloc_string_java(vm,(JCHAR[]){77,121,71,97,109,101},6,1);
	aot_strings[303] = alloc_string_java(vm,(JCHAR[]){67,97,110,39,116,32,102,105,110,100,32,106,110,105,32,99,108,97,115,115,58,32},22,1);
	aot_strings[53] = alloc_string_java(vm,(JCHAR[]){100,105,103,105,112,108,97,121,47,78,101,116},12,1);
	aot_strings[229] = alloc_string_java(vm,(JCHAR[]){84,65,78,48,53},5,1);
	aot_strings[101] = alloc_string_java(vm,(JCHAR[]){103,97,109,97,118,109,47,86,77},9,1);
	aot_strings[311] = alloc_string_java(vm,(JCHAR[]){100,105,103,105,112,108,97,121,47,114,101,110,100,101,114,47,81,117,97,100,71,101,111,109,101,116,114,121},28,1);
	aot_strings[103] = alloc_string_java(vm,(JCHAR[]){40,74,41,86},4,1);
	aot_strings[68] = alloc_string_java(vm,(JCHAR[]){115,116,97,114,116,115,87,105,116,104},10,1);
}
NativeMethodInfo aot_native_methods[] = {
	{"MyGame:<init>:()V",&MyGame__init____V}
	,{"MyGame:begin:()V",&MyGame_begin___V}
	,{"MyGame:update:()V",&MyGame_update___V}
	,{"MyGame:render:()V",&MyGame_render___V}
	,{"Tmp:<init>:()V",&Tmp__init____V}
	,{"Tmp:work:(Ljava/net/Socket;)V",&Tmp_work__Ljava_net_Socket__V}
	,{"Tmp:main:([Ljava/lang/String;)V",&Tmp_main___Ljava_lang_String__V}
	,{"MyGame$1:<init>:(LMyGame;)V",&MyGame$1__init___LMyGame__V}
	,{"MyGame$1:onHttpSuccess:([B)V",&MyGame$1_onHttpSuccess___B_V}
	,{"MyGame$1:onHttpFail:()V",&MyGame$1_onHttpFail___V}
	,{"Main:<init>:()V",&Main__init____V}
	,{"Main:main:()V",&Main_main___V}
	,{"Main:main:([Ljava/lang/String;)V",&Main_main___Ljava_lang_String__V}
	,{"digiplay/MainActivity:<init>:()V",&digiplay_MainActivity__init____V}
	,{"digiplay/Mat2D:<init>:()V",&digiplay_Mat2D__init____V}
	,{"digiplay/Mat2D:finalize:()V",&digiplay_Mat2D_finalize___V}
	,{"digiplay/Net$Http:<init>:(Ljava/lang/String;Ljava/lang/String;)V",&digiplay_Net$Http__init___Ljava_lang_String_Ljava_lang_String__V}
	,{"digiplay/GLShader2D:<init>:(Ljava/lang/String;)V",&digiplay_GLShader2D__init___Ljava_lang_String__V}
	,{"digiplay/Sprite2D:<init>:()V",&digiplay_Sprite2D__init____V}
	,{"digiplay/Sprite2D:x:()F",&digiplay_Sprite2D_x___F}
	,{"digiplay/Sprite2D:x:(F)V",&digiplay_Sprite2D_x__F_V}
	,{"digiplay/Sprite2D:y:()F",&digiplay_Sprite2D_y___F}
	,{"digiplay/Sprite2D:y:(F)V",&digiplay_Sprite2D_y__F_V}
	,{"digiplay/Sprite2D:scaleX:()F",&digiplay_Sprite2D_scaleX___F}
	,{"digiplay/Sprite2D:scaleX:(F)V",&digiplay_Sprite2D_scaleX__F_V}
	,{"digiplay/Sprite2D:getScaleY:()F",&digiplay_Sprite2D_getScaleY___F}
	,{"digiplay/Sprite2D:setScaleY:(F)V",&digiplay_Sprite2D_setScaleY__F_V}
	,{"digiplay/Sprite2D:rotation:()F",&digiplay_Sprite2D_rotation___F}
	,{"digiplay/Sprite2D:rotation:(F)V",&digiplay_Sprite2D_rotation__F_V}
	,{"digiplay/Sprite2D:width:()F",&digiplay_Sprite2D_width___F}
	,{"digiplay/Sprite2D:width:(F)V",&digiplay_Sprite2D_width__F_V}
	,{"digiplay/Sprite2D:height:()F",&digiplay_Sprite2D_height___F}
	,{"digiplay/Sprite2D:height:(F)V",&digiplay_Sprite2D_height__F_V}
	,{"digiplay/Sprite2D:getSkewX:()F",&digiplay_Sprite2D_getSkewX___F}
	,{"digiplay/Sprite2D:setSkewX:(F)V",&digiplay_Sprite2D_setSkewX__F_V}
	,{"digiplay/Sprite2D:getSkewY:()F",&digiplay_Sprite2D_getSkewY___F}
	,{"digiplay/Sprite2D:setSkewY:(F)V",&digiplay_Sprite2D_setSkewY__F_V}
	,{"digiplay/Sprite2D:getAnimX:()F",&digiplay_Sprite2D_getAnimX___F}
	,{"digiplay/Sprite2D:setAnimX:(F)V",&digiplay_Sprite2D_setAnimX__F_V}
	,{"digiplay/Sprite2D:getAnimY:()F",&digiplay_Sprite2D_getAnimY___F}
	,{"digiplay/Sprite2D:setAnimY:(F)V",&digiplay_Sprite2D_setAnimY__F_V}
	,{"digiplay/Sprite2D:getAnimScaleX:()F",&digiplay_Sprite2D_getAnimScaleX___F}
	,{"digiplay/Sprite2D:setAnimScaleX:(F)V",&digiplay_Sprite2D_setAnimScaleX__F_V}
	,{"digiplay/Sprite2D:getAnimScaleY:()F",&digiplay_Sprite2D_getAnimScaleY___F}
	,{"digiplay/Sprite2D:setAnimScaleY:(F)V",&digiplay_Sprite2D_setAnimScaleY__F_V}
	,{"digiplay/Sprite2D:getAnimRotation:()F",&digiplay_Sprite2D_getAnimRotation___F}
	,{"digiplay/Sprite2D:setAnimRotation:(F)V",&digiplay_Sprite2D_setAnimRotation__F_V}
	,{"digiplay/Sprite2D:getAlpha:()F",&digiplay_Sprite2D_getAlpha___F}
	,{"digiplay/Sprite2D:setAlpha:(F)V",&digiplay_Sprite2D_setAlpha__F_V}
	,{"digiplay/Sprite2D:getAnimAlpha:()F",&digiplay_Sprite2D_getAnimAlpha___F}
	,{"digiplay/Sprite2D:setAnimAlpha:(F)V",&digiplay_Sprite2D_setAnimAlpha__F_V}
	,{"digiplay/Sprite2D:getPivotX:()F",&digiplay_Sprite2D_getPivotX___F}
	,{"digiplay/Sprite2D:setPivotX:(F)V",&digiplay_Sprite2D_setPivotX__F_V}
	,{"digiplay/Sprite2D:getPivotY:()F",&digiplay_Sprite2D_getPivotY___F}
	,{"digiplay/Sprite2D:setPivotY:(F)V",&digiplay_Sprite2D_setPivotY__F_V}
	,{"digiplay/Sprite2D:updateWorldAlpha:()V",&digiplay_Sprite2D_updateWorldAlpha___V}
	,{"digiplay/Sprite2D:getFlags:()I",&digiplay_Sprite2D_getFlags___I}
	,{"digiplay/Sprite2D:setFlags:(I)V",&digiplay_Sprite2D_setFlags__I_V}
	,{"digiplay/Sprite2D:cleatFlags:(I)V",&digiplay_Sprite2D_cleatFlags__I_V}
	,{"digiplay/Sprite2D:dispose:()V",&digiplay_Sprite2D_dispose___V}
	,{"digiplay/Sprite2D:unlinkChild:(Ldigiplay/Sprite2D;)V",&digiplay_Sprite2D_unlinkChild__Ldigiplay_Sprite2D__V}
	,{"digiplay/Sprite2D:linkChild:(Ldigiplay/Sprite2D;)V",&digiplay_Sprite2D_linkChild__Ldigiplay_Sprite2D__V}
	,{"digiplay/Sprite2D:removeChild:(Ldigiplay/Sprite2D;)V",&digiplay_Sprite2D_removeChild__Ldigiplay_Sprite2D__V}
	,{"digiplay/Sprite2D:addChild:(Ldigiplay/Sprite2D;)V",&digiplay_Sprite2D_addChild__Ldigiplay_Sprite2D__V}
	,{"digiplay/Sprite2D:markContentInvalid:()V",&digiplay_Sprite2D_markContentInvalid___V}
	,{"digiplay/Sprite2D:invalidateContent:()V",&digiplay_Sprite2D_invalidateContent___V}
	,{"digiplay/Sprite2D:invalidateContentIfRequired:()V",&digiplay_Sprite2D_invalidateContentIfRequired___V}
	,{"digiplay/Sprite2D:init:()V",&digiplay_Sprite2D_init___V}
	,{"digiplay/Sprite2D:setInStage:()V",&digiplay_Sprite2D_setInStage___V}
	,{"digiplay/Sprite2D:draw:()V",&digiplay_Sprite2D_draw___V}
	,{"digiplay/Texture2D:<init>:()V",&digiplay_Texture2D__init____V}
	,{"digiplay/Texture2D:create:(Ldigiplay/GLTexture;)Ldigiplay/Texture2D;",&digiplay_Texture2D_create__Ldigiplay_GLTexture__Ldigiplay_Texture2D_}
	,{"digiplay/Matrix2D:<init>:()V",&digiplay_Matrix2D__init____V}
	,{"digiplay/Matrix2D:set:(FFFFFF)V",&digiplay_Matrix2D_set__FFFFFF_V}
	,{"digiplay/Matrix2D:copyFrom:(Ldigiplay/Matrix2D;)V",&digiplay_Matrix2D_copyFrom__Ldigiplay_Matrix2D__V}
	,{"digiplay/Matrix2D:identity:()V",&digiplay_Matrix2D_identity___V}
	,{"digiplay/Matrix2D:updateRotAndSkew:(FFF)V",&digiplay_Matrix2D_updateRotAndSkew__FFF_V}
	,{"digiplay/Matrix2D:compose:(FFFFFF)V",&digiplay_Matrix2D_compose__FFFFFF_V}
	,{"digiplay/Matrix2D:multiply:(Ldigiplay/Matrix2D;Ldigiplay/Matrix2D;Ldigiplay/Matrix2D;)V",&digiplay_Matrix2D_multiply__Ldigiplay_Matrix2D_Ldigiplay_Matrix2D_Ldigiplay_Matrix2D__V}
	,{"digiplay/Point2D:<init>:()V",&digiplay_Point2D__init____V}
	,{"digiplay/Point2D:<init>:(FF)V",&digiplay_Point2D__init___FF_V}
	,{"digiplay/Image:<init>:()V",&digiplay_Image__init____V}
	,{"digiplay/Image:invalidateContent:()V",&digiplay_Image_invalidateContent___V}
	,{"digiplay/Image:draw:()V",&digiplay_Image_draw___V}
	,{"digiplay/QuadMesh:<init>:(I)V",&digiplay_QuadMesh__init___I_V}
	,{"digiplay/QuadMesh:set:(IFFLdigiplay/GLTexture;)V",&digiplay_QuadMesh_set__IFFLdigiplay_GLTexture__V}
	,{"digiplay/GLQuadBatch:<init>:(I)V",&digiplay_GLQuadBatch__init___I_V}
	,{"digiplay/Bag:<init>:()V",&digiplay_Bag__init____V}
	,{"digiplay/Bag:<init>:(I)V",&digiplay_Bag__init___I_V}
	,{"digiplay/Bag:getSize:()I",&digiplay_Bag_getSize___I}
	,{"digiplay/Stage2D:<init>:()V",&digiplay_Stage2D__init____V}
	,{"digiplay/Stage2D:setup:(Ldigiplay/Point2D;)V",&digiplay_Stage2D_setup__Ldigiplay_Point2D__V}
	,{"digiplay/Stage2D:resize:()V",&digiplay_Stage2D_resize___V}
	,{"digiplay/Stage2D:invalidateSprite:(Ldigiplay/Sprite2D;)V",&digiplay_Stage2D_invalidateSprite__Ldigiplay_Sprite2D__V}
	,{"digiplay/Stage2D:update:()V",&digiplay_Stage2D_update___V}
	,{"digiplay/Stage2D:render:()V",&digiplay_Stage2D_render___V}
	,{"digiplay/Stage2D:<clinit>:()V",&digiplay_Stage2D__clinit____V}
	,{"digiplay/Platform:<init>:()V",&digiplay_Platform__init____V}
	,{"digiplay/Platform:run:(Ldigiplay/Game;)V",&digiplay_Platform_run__Ldigiplay_Game__V}
	,{"digiplay/Platform:resize:(II)V",&digiplay_Platform_resize__II_V}
	,{"digiplay/Platform:step:()V",&digiplay_Platform_step___V}
	,{"digiplay/Platform:<clinit>:()V",&digiplay_Platform__clinit____V}
	,{"digiplay/Metal:<init>:()V",&digiplay_Metal__init____V}
	,{"digiplay/Mat3D:<init>:()V",&digiplay_Mat3D__init____V}
	,{"digiplay/Asset:<init>:()V",&digiplay_Asset__init____V}
	,{"digiplay/Asset:load:(Ljava/lang/String;)V",&digiplay_Asset_load__Ljava_lang_String__V}
	,{"digiplay/Asset:complete:(JI)V",&digiplay_Asset_complete__JI_V}
	,{"digiplay/Asset:loaded:(JI)V",&digiplay_Asset_loaded__JI_V}
	,{"digiplay/GLTexture:<init>:()V",&digiplay_GLTexture__init____V}
	,{"digiplay/Matrix3D:<init>:()V",&digiplay_Matrix3D__init____V}
	,{"digiplay/Matrix3D:identity:()V",&digiplay_Matrix3D_identity___V}
	,{"digiplay/Matrix3D:set:(FFFFFFFFFFFFFFFF)V",&digiplay_Matrix3D_set__FFFFFFFFFFFFFFFF_V}
	,{"digiplay/Matrix3D:set2:(FFFFFFFFFFFFFFFF)V",&digiplay_Matrix3D_set2__FFFFFFFFFFFFFFFF_V}
	,{"digiplay/Matrix3D:perspective:(FFFF)V",&digiplay_Matrix3D_perspective__FFFF_V}
	,{"digiplay/Matrix3D:orthographic:(FFFFFF)V",&digiplay_Matrix3D_orthographic__FFFFFF_V}
	,{"digiplay/Matrix3D:setup:(FFFFFF)V",&digiplay_Matrix3D_setup__FFFFFF_V}
	,{"digiplay/Matrix3D:setup:(FFFFFFZ)V",&digiplay_Matrix3D_setup__FFFFFFZ_V}
	,{"digiplay/Matrix3D:prepend:(Ldigiplay/Matrix3D;)V",&digiplay_Matrix3D_prepend__Ldigiplay_Matrix3D__V}
	,{"digiplay/Matrix3D:prependTranslation:(FFF)V",&digiplay_Matrix3D_prependTranslation__FFF_V}
	,{"digiplay/Matrix3D:copyFrom2D:(Ldigiplay/Matrix2D;)V",&digiplay_Matrix3D_copyFrom2D__Ldigiplay_Matrix2D__V}
	,{"digiplay/Matrix3D:copyTo2D:(Ldigiplay/Matrix2D;)V",&digiplay_Matrix3D_copyTo2D__Ldigiplay_Matrix2D__V}
	,{"digiplay/Matrix3D:to2D:()Ldigiplay/Matrix2D;",&digiplay_Matrix3D_to2D___Ldigiplay_Matrix2D_}
	,{"digiplay/Matrix3D:convertTo3D:(Ldigiplay/Matrix2D;)Ldigiplay/Matrix3D;",&digiplay_Matrix3D_convertTo3D__Ldigiplay_Matrix2D__Ldigiplay_Matrix3D_}
	,{"digiplay/Matrix3D:lookAt:(FFFFFFFFF)V",&digiplay_Matrix3D_lookAt__FFFFFFFFF_V}
	,{"digiplay/Matrix3D:compose:(FFFFFFFFF)V",&digiplay_Matrix3D_compose__FFFFFFFFF_V}
	,{"digiplay/Matrix3D:multiply:(Ldigiplay/Matrix3D;Ldigiplay/Matrix3D;Ldigiplay/Matrix3D;)V",&digiplay_Matrix3D_multiply__Ldigiplay_Matrix3D_Ldigiplay_Matrix3D_Ldigiplay_Matrix3D__V}
	,{"digiplay/Matrix3D:t:(FFF)V",&digiplay_Matrix3D_t__FFF_V}
	,{"digiplay/Matrix3D:<clinit>:()V",&digiplay_Matrix3D__clinit____V}
	,{"digiplay/Graphics:<init>:()V",&digiplay_Graphics__init____V}
	,{"digiplay/Graphics:resize:(IIIIII)V",&digiplay_Graphics_resize__IIIIII_V}
	,{"digiplay/Graphics:getScreenWidth:()I",&digiplay_Graphics_getScreenWidth___I}
	,{"digiplay/Graphics:getScreenHeight:()I",&digiplay_Graphics_getScreenHeight___I}
	,{"digiplay/Graphics:getSafeLeft:()I",&digiplay_Graphics_getSafeLeft___I}
	,{"digiplay/Graphics:getSafeRight:()I",&digiplay_Graphics_getSafeRight___I}
	,{"digiplay/Graphics:getSafeTop:()I",&digiplay_Graphics_getSafeTop___I}
	,{"digiplay/Graphics:getSafeBottom:()I",&digiplay_Graphics_getSafeBottom___I}
	,{"digiplay/Camera:<init>:()V",&digiplay_Camera__init____V}
	,{"digiplay/Camera:setTarget:(FFF)V",&digiplay_Camera_setTarget__FFF_V}
	,{"digiplay/Camera:getCombinedMatrix:()Ldigiplay/Matrix3D;",&digiplay_Camera_getCombinedMatrix___Ldigiplay_Matrix3D_}
	,{"digiplay/Camera:setupFor2D:(FF)Ldigiplay/Matrix3D;",&digiplay_Camera_setupFor2D__FF_Ldigiplay_Matrix3D_}
	,{"digiplay/Camera:<clinit>:()V",&digiplay_Camera__clinit____V}
	,{"digiplay/Net:<init>:()V",&digiplay_Net__init____V}
	,{"digiplay/ByteArrayCompletable:<init>:()V",&digiplay_ByteArrayCompletable__init____V}
	,{"digiplay/ByteArrayCompletable:complete:(JI)V",&digiplay_ByteArrayCompletable_complete__JI_V}
	,{"digiplay/ByteArrayCompletable:onComplete:()V",&digiplay_ByteArrayCompletable_onComplete___V}
	,{"gamavm/apple/NSDictionary:<init>:()V",&gamavm_apple_NSDictionary__init____V}
	,{"gamavm/apple/ObjC:<init>:()V",&gamavm_apple_ObjC__init____V}
	,{"gamavm/apple/ObjCClass:<init>:()V",&gamavm_apple_ObjCClass__init____V}
	,{"gamavm/apple/ObjCClass:get:(Ljava/lang/String;)Lgamavm/apple/ObjCClass;",&gamavm_apple_ObjCClass_get__Ljava_lang_String__Lgamavm_apple_ObjCClass_}
	,{"gamavm/apple/ObjCClass:register:(Ljava/lang/Class;)Lgamavm/apple/ObjCClass;",&gamavm_apple_ObjCClass_register__Ljava_lang_Class__Lgamavm_apple_ObjCClass_}
	,{"gamavm/apple/ObjCClass:<clinit>:()V",&gamavm_apple_ObjCClass__clinit____V}
	,{"gamavm/apple/Selector:<init>:()V",&gamavm_apple_Selector__init____V}
	,{"gamavm/apple/Selector:register:(Ljava/lang/String;)Lgamavm/apple/Selector;",&gamavm_apple_Selector_register__Ljava_lang_String__Lgamavm_apple_Selector_}
	,{"gamavm/apple/Selector:<clinit>:()V",&gamavm_apple_Selector__clinit____V}
	,{"gamavm/apple/NSObject:<init>:()V",&gamavm_apple_NSObject__init____V}
	,{"gamavm/apple/NSObject:getHandle:()J",&gamavm_apple_NSObject_getHandle___J}
	,{"gamavm/apple/NSObject:finalize:()V",&gamavm_apple_NSObject_finalize___V}
	,{"gamavm/apple/NSMutableObject:<init>:()V",&gamavm_apple_NSMutableObject__init____V}
	,{"gamavm/apple/NSMutableObject:finalize:()V",&gamavm_apple_NSMutableObject_finalize___V}
	,{"gamavm/jni/JniClass:<init>:()V",&gamavm_jni_JniClass__init____V}
	,{"gamavm/jni/JniClass:get:(Ljava/lang/String;)Lgamavm/jni/JniClass;",&gamavm_jni_JniClass_get__Ljava_lang_String__Lgamavm_jni_JniClass_}
	,{"gamavm/jni/JniClass:finalize:()V",&gamavm_jni_JniClass_finalize___V}
	,{"gamavm/jni/JniClass:<clinit>:()V",&gamavm_jni_JniClass__clinit____V}
	,{"gamavm/jni/JniBridge:<init>:()V",&gamavm_jni_JniBridge__init____V}
	,{"gamavm/jni/JniObject:<init>:()V",&gamavm_jni_JniObject__init____V}
	,{"gamavm/jni/URL:<init>:(Ljava/lang/String;)V",&gamavm_jni_URL__init___Ljava_lang_String__V}
	,{"gamavm/jni/JniMethod:<init>:()V",&gamavm_jni_JniMethod__init____V}
	,{"digiplay/net/Socket:<init>:()V",&digiplay_net_Socket__init____V}
	,{"digiplay/net/Socket:write:([B)V",&digiplay_net_Socket_write___B_V}
	,{"digiplay/net/Socket:append:([BII)V",&digiplay_net_Socket_append___BII_V}
	,{"digiplay/net/Socket:close:()V",&digiplay_net_Socket_close___V}
	,{"digiplay/net/Socket:available:()I",&digiplay_net_Socket_available___I}
	,{"digiplay/net/Socket:read:()I",&digiplay_net_Socket_read___I}
	,{"digiplay/render/QuadGeometry:alloc:(I)Ldigiplay/render/QuadGeometry;",&digiplay_render_QuadGeometry_alloc__I_Ldigiplay_render_QuadGeometry_}
	,{"digiplay/render/QuadGeometry:<init>:(I)V",&digiplay_render_QuadGeometry__init___I_V}
	,{"digiplay/render/QuadGeometry:set:(IFFFFFFFFFFFFFFFFFFFF)V",&digiplay_render_QuadGeometry_set__IFFFFFFFFFFFFFFFFFFFF_V}
	,{"digiplay/render/GPU:<init>:()V",&digiplay_render_GPU__init____V}
	,{"digiplay/render/GPU:commit:()V",&digiplay_render_GPU_commit___V}
	,{"digiplay/render/GPU:setViewport:(IIII)V",&digiplay_render_GPU_setViewport__IIII_V}
	,{"digiplay/render/GPU:setBlending:(II)V",&digiplay_render_GPU_setBlending__II_V}
	,{"digiplay/render/GPU:<clinit>:()V",&digiplay_render_GPU__clinit____V}
	,{"digiplay/render/VertexBuffer:<init>:(II)V",&digiplay_render_VertexBuffer__init___II_V}
	,{"digiplay/render/RenderDevice:<init>:()V",&digiplay_render_RenderDevice__init____V}
	,{"digiplay/render/RenderDevice:commit:()V",&digiplay_render_RenderDevice_commit___V}
	,{"digiplay/render/RenderDevice:resetStates:()V",&digiplay_render_RenderDevice_resetStates___V}
	,{"digiplay/render/RenderDevice:setViewPort:(IIII)V",&digiplay_render_RenderDevice_setViewPort__IIII_V}
	,{"digiplay/render/RenderDevice:setScissor:(IIII)V",&digiplay_render_RenderDevice_setScissor__IIII_V}
	,{"digiplay/render/Shader:<init>:(Ljava/lang/String;Ljava/lang/String;)V",&digiplay_render_Shader__init___Ljava_lang_String_Ljava_lang_String__V}
	,{"digiplay/render/IndexBuffer:<init>:(I)V",&digiplay_render_IndexBuffer__init___I_V}
	,{"digiplay/render/IndexBuffer:set:(II)V",&digiplay_render_IndexBuffer_set__II_V}
	,{"digiplay/render/IndexBuffer:set:(IIII)V",&digiplay_render_IndexBuffer_set__IIII_V}
	,{"digiplay/render/Texture:<init>:()V",&digiplay_render_Texture__init____V}
	,{"gamavm/apple/storekit/SKPaymentQueue:<init>:()V",&gamavm_apple_storekit_SKPaymentQueue__init____V}
	,{"gamavm/apple/storekit/SKPaymentQueue:defaultQueue:()Lgamavm/apple/storekit/SKPaymentQueue;",&gamavm_apple_storekit_SKPaymentQueue_defaultQueue___Lgamavm_apple_storekit_SKPaymentQueue_}
	,{"gamavm/apple/storekit/SKPaymentQueue:<clinit>:()V",&gamavm_apple_storekit_SKPaymentQueue__clinit____V}
	,{"gamavm/apple/uikit/UIView:<init>:()V",&gamavm_apple_uikit_UIView__init____V}
	,{"gamavm/apple/uikit/UIApplicationDelegate:<init>:()V",&gamavm_apple_uikit_UIApplicationDelegate__init____V}
	,{"gamavm/apple/uikit/UIApplicationDelegate:didFinishLaunching:()V",&gamavm_apple_uikit_UIApplicationDelegate_didFinishLaunching___V}
	,{"gamavm/apple/uikit/UIResponder:<init>:()V",&gamavm_apple_uikit_UIResponder__init____V}
	,{"gamavm/apple/uikit/UIViewController:<init>:()V",&gamavm_apple_uikit_UIViewController__init____V}
	,{"gamavm/apple/uikit/UIApplication:<init>:()V",&gamavm_apple_uikit_UIApplication__init____V}
	,{"gamavm/apple/uikit/UIApplication:sharedApplication:()Lgamavm/apple/uikit/UIApplication;",&gamavm_apple_uikit_UIApplication_sharedApplication___Lgamavm_apple_uikit_UIApplication_}
	,{"gamavm/apple/uikit/UIWindow:<init>:()V",&gamavm_apple_uikit_UIWindow__init____V}
	,{"gamavm/apple/uikit/UIWindow:setRootViewController:(Lgamavm/apple/uikit/UIViewController;)V",&gamavm_apple_uikit_UIWindow_setRootViewController__Lgamavm_apple_uikit_UIViewController__V}
	,{"gamavm/apple/uikit/UIWindow:makeKeyAndVisible:()V",&gamavm_apple_uikit_UIWindow_makeKeyAndVisible___V}
	,NULL
};
