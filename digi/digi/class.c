//
//  class.c
//  digi
//
//  Created by mustafa on 7.06.2020.
//  Copyright © 2020 mustafa. All rights reserved.
//

#include "vm.h"

jint get_prim_size(int chr) {
    switch(chr) {
        case 'B': return sizeof(jbyte);
        case 'Z': return sizeof(jbool);
        case 'C': return sizeof(jchar);
        case 'S': return sizeof(jshort);
        case 'I': return sizeof(jint);
        case 'F': return sizeof(jfloat);
        case 'J': return sizeof(jlong);
        case 'D': return sizeof(jdouble);
        default : return sizeof(Object*);
    }
}
jint get_signature_size(Object *signature) {
    return get_prim_size(STRCHARS(signature)[0]);
}
jint is_signature_ref(Object *signature) {
    jint chr = STRCHARS(signature)[0];
    return chr == 'L' || chr == '[';
}

int copy_jchar(jchar* target, jchar* src, int len) {
    memcpy(target, src, len * sizeof(jchar));
   return len;
}

Object *get_arrayclass_of(VM *vm, Object *cls) {
    Object *arrCls = CLS(cls, arrayClass);
    if(!arrCls) {
        arrCls = alloc_class(vm);
        CLS(arrCls, elementClass) = cls;
        CLS(cls, arrayClass) = arrCls;
        jchar tmp[256];
        int len = 0;
        tmp[len++] = '[';
        Object *name = CLS(cls, name);
        if(!name) { //boot classes doesn't have names yet
            if(cls == vm->jlClass) len += copy_jchar(&tmp[1], L"Ljava/lang/Class;", 17);
            else if(cls == vm->jlField) len += copy_jchar(&tmp[1], L"Ljava/lang/reflect/Field;", 25);
            else if(cls == vm->jlMethod) len += copy_jchar(&tmp[1], L"Ljava/lang/reflect/Method;", 26);
            else if(cls == vm->primClasses[PRIM_C]) len += copy_jchar(&tmp[1], L"C", 1);
        } else {
            jchar *src = (jchar*)STR(name,chars)->instance;
            if(CLS_PRIM(cls)) {
                tmp[len++] = src[0];
            } else {
                tmp[len++] = 'L';
                int clen = STR(name, length);
                for(int i=0; i<clen; i++) tmp[len++] = src[i] == '.' ? '/' : src[i];
                tmp[len++] = ';';
            }
        }
        
        //printf("--- array-class: %s\n", jchar_to_ascii(tmp, len));
        CLS(arrCls, name) = alloc_string_java(vm, tmp, len, 1);
        CLS(arrCls, superClass) = vm->jlObject;
        
        //add class to class list
        CLS(arrCls, next) = vm->classes;
        vm->classes = arrCls;
    }
    
    return arrCls;
}

Object *find_class(VM *vm, jchar *name, jint len) {
    //printf("------------------------ find: %s\n", jchar_to_ascii(name, len));
    Object *ptr = vm->classes;
    while(ptr) {
        Object *clsName = CLS(ptr, name);
        //printf("%s\n", string_to_ascii(clsName));
        if(len == STRLEN(clsName) &&
           compare_chars(name, STRCHARS(clsName), len))
            return ptr;
        ptr = CLS(ptr, next);
    }
    return NULL;
}

void link_class(VM *vm, Object *clsObject) {
    Class *cls = clsObject->instance;
    if(cls->linked) return;
    printf("linking: %p -> ", clsObject);
    printf("%s\n", string_to_ascii(cls->name));

    cls->linked = 1;
    cls->instanceSize = 0;
    int globalSize = 0;
    
    int ico[128];
    if(cls->superClass) {
        link_class(vm, cls->superClass);
        cls->instanceSize = CLS(cls->superClass,instanceSize);
        cls->instanceOffsetCount = CLS(cls->superClass,instanceOffsetCount);
        if(cls->instanceOffsetCount > 0) {
            memcpy(ico, CLS(cls->superClass, instanceOffsets), sizeof(int) * cls->instanceOffsetCount);
        }
    }
    
    if(cls->elementClass)
        link_class(vm, cls->elementClass);
    
    if(cls->interfaces) {
        for(int i=0; i<cls->interfaces->length; i++)
            link_class(vm, ((Object**)cls->interfaces->instance)[i]);
    }
    
    if(cls->fields) {
        for(int i=0; i<cls->fields->length; i++) {
            Field *f = ((Object**)cls->fields->instance)[i]->instance;
            int size = get_signature_size(f->signature);
            size = ((size + 3) / 4) * 4;
            if(IS_STATIC(f->flags)) {
                f->offset = globalSize;
                globalSize += size;
            } else {
                f->offset = cls->instanceSize;
                cls->instanceSize += size;
                if(is_signature_ref(f->signature)) {
                    ico[cls->instanceOffsetCount++] = f->offset;
                }
            }
        }
    }
    
    if(clsObject == vm->jlClass) {
        printf("!!!!cls: %d == %d\n", cls->instanceSize, sizeof(Class));
    } else if(clsObject == vm->jlMethod) {
        printf("!!!!mth: %d == %d\n", cls->instanceSize, sizeof(Method));
    } else if(clsObject == vm->jlField) {
        printf("!!!!fld: %d == %d\n", cls->instanceSize, sizeof(Field));
    }
    if(cls->instanceOffsetCount > 0) {
        cls->instanceOffsets = malloc(sizeof(int) * cls->instanceOffsetCount);
        memcpy(cls->instanceOffsets, ico, sizeof(int) * cls->instanceOffsetCount);
    }
    
    if(globalSize > 0) cls->global = vm_alloc(globalSize);
    
    if(cls->superClass) cls->maxMethodIndex = CLS(cls->superClass,maxMethodIndex);
    
    //Give methods an index
    if(cls->methods && IS_INTERFACE(cls->flags)) {
        for(int i=0; i<cls->methods->length; i++) {
            Object *mo = ((Object**)cls->methods->instance)[i];
            //printf(" ----m %d: %s\n", i, string2c(MTH_FIELD(mo, name)));
            Method *m = mo->instance;
            //printf("-- %s\n", string2c(m->name));
            //if(IS_INTERFACE(cls)) {
                m->iTableIndex = vm->iTableCounter++;
                if(cls->maxMethodIndex < m->iTableIndex) cls->maxMethodIndex = m->iTableIndex;
            //}
        }
    }
    
    //Setup Interface Table
    if(cls->superClass) {
        cls->itable = vm_alloc(sizeof(Object*) * CLS(cls->superClass,iTableSize));
        memcpy(cls->itable, CLS(cls->superClass,itable), sizeof(Object*) * CLS(cls->superClass,iTableSize));
        cls->iTableSize = CLS(cls->superClass,iTableSize);
    }
    if(cls->interfaces) {
        int maxIndex = 0;
        for(int i=0; i<cls->interfaces->length; i++) {
            Object *intf = ((Object**)cls->interfaces->instance)[i];
            if(CLS(intf,maxMethodIndex) > maxIndex) maxIndex = CLS(intf,maxMethodIndex);
        }
        if(maxIndex + 1 >= cls->iTableSize) {
            cls->itable = realloc(cls->itable, sizeof(Object*) * (maxIndex+1));
            cls->iTableSize = maxIndex+1;
        }
        for(int i=0; i<cls->interfaces->length; i++) {
            Object *intf = ((Object**)cls->interfaces->instance)[i];
            Object *imethods = CLS(intf, methods);
            if(imethods) {
                for(int k=0; k<imethods->length; k++) {
                    Object *om = ((Object**)imethods->instance)[k];
                    Method *m = om->instance;
                    Object *override = find_class_method(vm, clsObject, STRCHARS(m->name), STRLEN(m->name), STRCHARS(m->signature), STRLEN(m->signature));
                    if(override) {
                        Method *omm = override->instance;
                        if(!IS_ABSTRACT(omm->flags)) cls->itable[m->iTableIndex] = override;
                    }
                }
            }
        }
    }
    
    if(!IS_INTERFACE(cls->flags)) {
        //Setup Virtual Table
        if(cls->superClass) {
            cls->vtable = vm_alloc(sizeof(Object*) * CLS(cls->superClass,vTableSize));
            memcpy(cls->vtable, CLS(cls->superClass,vtable), sizeof(Object*) * CLS(cls->superClass,vTableSize));
            cls->vTableSize = CLS(cls->superClass,vTableSize);
        }
        if(cls->methods) {
            for(int i=0; i<cls->methods->length; i++) {
                Object *om = ((Object**)cls->methods->instance)[i];
                Method *m = om->instance;
                if(!IS_STATIC(m->flags) && STRCHARS(m->name)[0] != '<') {
                    Object *override = find_method(vm, cls->superClass, STRCHARS(m->name), STRLEN(m->name), STRCHARS(m->signature), STRLEN(m->signature));
                    if(override) {
                        Method *omm = override->instance;
                        m->vTableIndex = omm->vTableIndex;
                        //printf("----- %s override ",string2c(cls->name));
                        //printf(":%s",string2c(m->name));printf(":%s @%d\n",string2c(m->signature), m->vTableIndex);

                    } else {
                        m->vTableIndex = vm->vTableCounter++;
                    }
                    if(m->vTableIndex + 1 >= cls->vTableSize) {
                        cls->vTableSize = m->vTableIndex + 1;
                        cls->vtable = (Object**)realloc(cls->vtable, sizeof(Object*) * cls->vTableSize);
                    }
                    cls->vtable[m->vTableIndex] = om;
                }
            }
        }
    }
    
    Object *clInit = find_class_method(vm, clsObject, L"<clinit>", 8, L"()V", 3);
    if(clInit) {
        printf("clInit: %s\n", string_to_ascii(cls->name));
        CALLVM_V(vm, clInit, NULL);
    }
    
    //jdwp_send_classload_event(clso);
    
}

Object *resolve_class(VM *vm, jchar *name, jint len, int link, Object *target) {
    //printf("resolve: %s\n", jchar_to_ascii(name, len));
    Object *cls = find_class(vm, name, len);
    if(cls) {
        if(link) link_class(vm, cls);
        return cls;
    }
    
    //array class
    if(name[0] == '[') {
        Object *element = NULL;
        if(name[1] == 'L') {
            element = resolve_class(vm, name+2, len-3, link, NULL);
        } else {
            element = resolve_class(vm, name+1, len-1, link, NULL);
        }
        if(vm->exception) {
            throw_classnotfound(vm, name+1, len-1);
            return NULL;
        }
        return get_arrayclass_of(vm, element);
    }
    
    printf("load: %s\n", jchar_to_ascii(name, len));
    void *class_raw = read_class_file(name, len);
    if(!class_raw) {
        throw_classnotfound(vm, name, len);
        return NULL;
    }
    cls = !target ? alloc_class(vm) : target;
    int success = parse_class(vm, class_raw, cls);
    free(class_raw);
    if(!success) {
        throw_classnotfound(vm, name, len);
        return NULL;
    }
    
    CLS(cls, next) = vm->classes;
    vm->classes = cls;
    
    if(link) {
        link_class(vm, cls);
    }
    return cls;
}

Object *resolve_class_by_index(VM *vm, Object *cls, int index) {
    CPItem *cp = CLS(cls, cp);
    Object *name = cp[cp[index].index1].value.O;
    return resolve_class(vm, STRCHARS(name), STRLEN(name), 1, NULL);
}


Object *find_class_method(VM *vm, Object *cls, jchar *name, jint nlen, jchar *sign, int slen) {
    Object *methods = CLS(cls, methods);
    if(!methods || methods->length == 0) return NULL;
    for(int i=0; i<methods->length; i++) {
        Object *m = ((Object**)methods->instance)[i];
        Object *mname = MTH(m, name);
        Object *ssign = MTH(m, signature);
        
        if(STRLEN(mname) == nlen && STRLEN(ssign) == slen &&
           compare_chars(name, STRCHARS(mname), nlen) &&
           compare_chars(sign, STRCHARS(ssign), slen))
            return m;
    }
    return NULL;
}

Object *find_method(VM *vm, Object *cls, jchar *name, jint nlen, jchar *sign, int slen) {
    while(cls) {
        Object *method = find_class_method(vm, cls, name, nlen, sign, slen);
        if(method) return method;
        cls = CLS(cls, superClass);
    }
    return NULL;
}

Object *resolve_method(VM *vm, jchar *clsName, int clslen, jchar *name, int nlen, jchar *signature, int slen) {
    Object *cls = resolve_class(vm, clsName, clslen, 1, NULL);
    if(vm->exception) return NULL;
    Object *mth = find_method(vm, cls, name, nlen, signature, slen);
    if(mth) return mth;
    
    printf("NoSuchMethod: %s", jchar_to_ascii(clsName, clslen));
    printf(":%s", jchar_to_ascii(name, nlen));
    printf(":%s\n", jchar_to_ascii(signature, slen));
    
    return NULL;
}

Object *resolve_method_by_index(VM *vm,Object *cls, int index) {
    CPItem *cp = CLS(cls,cp);
    Object *clsName = cp[cp[cp[index].index1].index1].value.O;
    Object *name = cp[cp[cp[index].index2].index1].value.O;
    Object *signature = cp[cp[cp[index].index2].index2].value.O;
    return resolve_method(vm, STRCHARS(clsName), STRLEN(clsName),
                          STRCHARS(name), STRLEN(name),
                          STRCHARS(signature),STRLEN(signature));
}

Object *find_class_field(VM *vm, Object *cls, jchar *name, jint nlen, jchar *sign, int slen) {
    Object *fields = CLS(cls, fields);
    if(!fields || fields->length == 0) return NULL;
    for(int i=0; i<fields->length; i++) {
        Object *f = ((Object**)fields->instance)[i];
        Object *fname = FLD(f, name);
        Object *ssign = FLD(f, signature);
        
        if(STRLEN(fname) == nlen && STRLEN(ssign) == slen &&
           compare_chars(name, STRCHARS(fname), nlen) &&
           compare_chars(sign, STRCHARS(ssign), slen))
            return f;
    }
    return NULL;
}

Object *find_field(VM *vm, Object *cls, jchar *name, jint nlen, jchar *sign, int slen) {
    while(cls) {
        Object *field = find_class_field(vm, cls, name, nlen, sign, slen);
        if(field) return field;
        cls = CLS(cls, superClass);
    }
    return NULL;
}

Object *resolve_field(VM *vm, jchar *clsName, int clslen, jchar *name, int namelen, jchar *sign, int slen) {
    Object *cls = resolve_class(vm, clsName, clslen, 1, NULL);
    if(vm->exception) return NULL;
    Object *field = find_field(vm, cls, name, namelen, sign, slen);
    if(!field)
        throw_null(vm);
    
    return field;
}

Object *resolve_field_by_index(VM *vm,Object *cls, int index) {
    CPItem *cp = CLS(cls,cp);
    Object *clsName = cp[cp[cp[index].index1].index1].value.O;
    Object *name = cp[cp[cp[index].index2].index1].value.O;
    Object *signature = cp[cp[cp[index].index2].index2].value.O;
    /*printf("-- resolve field: %s", string2c(cls->name));
    printf(":%s", string2c(name));
    printf(":%s\n",string2c(signature));*/
    return resolve_field(vm, STRCHARS(clsName), STRLEN(clsName),
                         STRCHARS(name), STRLEN(name),
                         STRCHARS(signature), STRLEN(signature));
}


void build_all_parents(VM *vm, Object *cls) {
    Object *table[1024]; //enough?
    int count = 0;
    Object *c = cls;
    while(c) {
        //if(version != cls->iofVersion) {
        table[count++] = c;
        //printf(" iof-child: %s\n", string2c(CLS_FIELD(c,name)));
        //}
        Object *interfaces = CLS(c, interfaces);
        if(interfaces) {
            for(int i=0; i<interfaces->length; i++) {
                Object *ic = ARRAY_DATA_O(interfaces)[i];
                while(ic) {
                    //if(version != ic->iofVersion) {
                    if(ic != vm->jlObject)
                        table[count++] = ic;
                    //printf(" iof-child: %s\n", string2c(CLS_FIELD(ic,name)));
                    //}
                    ic = CLS(ic,superClass);
                }
            }
        }
        c = CLS(c,superClass);
    }
    
    Class *clsf = cls->instance;
    clsf->allParents = (Object**)malloc(sizeof(Object*) * count);
    memcpy(clsf->allParents, table, sizeof(Object*) * count);
    clsf->allParentCount = count;
}

jint is_class_child_of(VM *vm, Object *json, Object *jof) {
    if(!json || !jof) return 0;
    if(json == jof || jof == vm->jlObject) return 1;
    printf("check-cast: %s -> ",string_to_ascii(CLS(json,name)));
    printf("%s\n", string_to_ascii(CLS(jof,name)));
    Class *son = json->instance;
    if(!son->allParents) build_all_parents(vm, json);
    for(int i=0; i<son->allParentCount; i++) {
        printf("    %s\n", string_to_ascii(CLS(son->allParents[i],name)));
        if(son->allParents[i] == jof) return 1;
    }
    return 0;
}

