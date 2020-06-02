//
//  jdwp.cpp
//  Digiplay
//
//  Created by mustafa on 31.05.2020.
//  Copyright © 2020 mustafa. All rights reserved.
//

#include "jdwp.h"

VM *jdwpVM;
int jdwp_suspended = 0;
int JdwpPacket::eventRequestSerial = 0x10000000;
JdwpEventSet *JdwpEventSet::head = nullptr;
JdwpEventSet *JdwpEventSet::tail = nullptr;
JdwpClient jdwp_client;
int jdwp_server_fd;
int jdwp_step_fp = -1;
int jdwp_skip_line = -1;
int jdwp_invoking = 0;

int jdwp_listen(int port) {
    struct sockaddr_in serv_addr;
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    int tmp = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &tmp, sizeof(int));
    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(port);

    bool fail = bind(fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0;
    if(fail) {
        close(fd);
        return 0;
    }
    listen(fd, 10);
    fcntl(fd, F_SETFL, fcntl(fd, F_GETFL, 0) | O_NONBLOCK);
    return fd;
}

int jdwp_accept(int fd) {
    struct sockaddr_in cli_addr;
    socklen_t clilen;
    int clientFd = ::accept(fd, (struct sockaddr *)&cli_addr, &clilen);
    if(clientFd < 0) return 0;
    fcntl(clientFd, F_SETFL, fcntl(fd, F_GETFL, 0) | O_NONBLOCK);
    return clientFd;
}

int jdwp_connect(char *hostname, int port) {
    struct hostent *host = gethostbyname(hostname);
    int fd = 0;
    if(host) {
        fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        struct sockaddr_in sock_addr;
        memset((char *) &sock_addr, 0, sizeof(sock_addr));
        sock_addr.sin_family = AF_INET;
        sock_addr.sin_port = htons(port);
        sock_addr.sin_addr = *((struct in_addr *) host->h_addr_list[0]);
        memset(&(sock_addr.sin_zero), 0, sizeof((sock_addr.sin_zero)));
        
        if(connect(fd, (struct sockaddr *) &sock_addr, sizeof(sock_addr)) == -1) {
            close(fd);
            fd = 0;
        }
        fcntl(fd, F_SETFL, fcntl(fd, F_GETFL, 0) | O_NONBLOCK);
    }
    return fd;
}

Object *jdwp_find_class(void *name, int isString) {
    if(!jdwpVM) return nullptr;
    Object *cls = jdwpVM->classes;
    while(cls) {
        ClassFields *cf = (ClassFields*)cls->instance;
        if(compare_string(cf->name, name, isString)) return cls;
        cls = (Object*)cf->listNext;
    }
    return nullptr;
}

int jdwp_get_class_type(Object *clazz) {
    ClassFields *cf = (ClassFields*)clazz->instance;
    if (cf->elementClass) {
        return JDWP_TYPETAG_ARRAY;
    } else if ((cf->accessFlags & ACC_INTERFACE) != 0) {
        return JDWP_TYPETAG_INTERFACE;
    } else {
        return JDWP_TYPETAG_CLASS;
    }
}

int jdwp_get_line_index(Object *method, int line) {
    if(!method) return -1;
    MethodFields *mf = (MethodFields*)method->instance;
    if(mf->lineNumberTableSize <= 0) return -1;
    for(int i=0; i<mf->lineNumberTableSize; i++)
        if(mf->lineNumberTable[i].line == line) return i;
    return -1;
}

int jdwp_method_count_args(Object *method) {
    Object *signature = ((MethodFields*)method->instance)->signature;
    Object *chars = ((StringFields*)signature->instance)->chars;
    jchar *ch = (jchar*)chars->instance;
    ch++; //(
    int count = 0;
    int jcount = 0;
    
    if((MTH_FIELD(method, accessFlags) & ACC_STATIC) == 0) {
        count++;
    }
    while(1) {
        if(*ch == ')') break;
        count++;
        while(*ch == '[') ch++;
        if(*ch == 'L') {
            while(*ch != ';') ch++;
        }
        if(*ch == 'D' || *ch == 'J') count++;
        ch++;
    }
    return count;
}


void jdwp_eventset_set(JdwpEventSet *set) {
    if(set) {
        switch(set->eventKind) {
            case JDWP_EVENTKIND_SINGLE_STEP: {
                printf("!!!!!!!!! SET JDWP_EVENTKIND_SINGLE_STEP\n");
                for (int i = 0; i < set->modifiers; i++) {
                    JdwpEventSetMod *mod = set->mods[i];
                    if (mod->type == 10) {
                        //jdwp_step_line_index = jdwp_current_line_index + mod->size;
                        switch(mod->depth) {
                            case 0: //into
                                jdwp_step_fp = jdwpVM->FP + 1;
                                break;
                            case 1: //over
                                jdwp_step_fp = jdwpVM->FP;
                                break;
                            case 2: //out
                                jdwp_step_fp = jdwpVM->FP - 1;
                                break;
                        }
                        //printf("!!!!!!!!! step: %d:%d\n", jdwp_step_line_index, jdwp_step_fp);
                        break;
                        /*
                        int index = (int)mod->location.index;
                        MethodFields *mf = (MethodFields*)mod->location.method->instance;
                        mf->breakpoint++;
                        mf->lineNumberTable[index].breakpoint = set->requestId;
                        printf("!!!!!!!! set breakpoint at %s:%d type:%d\n", string2c(mf->name), mf->lineNumberTable[index].line, mod->location.type);
                        //jdwp_set_breakpoint(JDWP_EVENTSET_SET, mod->loc.classID, mod->loc.methodID,
                        //                    mod->loc.execIndex);
                        */
                    }
                }
            } break;
                
            case JDWP_EVENTKIND_BREAKPOINT: {
                printf("!!!!!!!!! SET JDWP_EVENTKIND_BREAKPOINT\n");
                for (int i = 0; i < set->modifiers; i++) {
                    JdwpEventSetMod *mod = set->mods[i];
                    if (mod->type == 7) {
                        int index = (int)mod->location.index;
                        MethodFields *mf = (MethodFields*)mod->location.method->instance;
                        mf->breakpoint++;
                        mf->lineNumberTable[index].breakpoint = set->requestId;
                        jdwp_step_fp = -1;
                        printf("!!!!!!!! set breakpoint at %s:%d type:%d\n", string2c(mf->name), mf->lineNumberTable[index].line, mod->location.type);
                        //jdwp_set_breakpoint(JDWP_EVENTSET_SET, mod->loc.classID, mod->loc.methodID,
                        //                    mod->loc.execIndex);
                    }
                }

            } break;
                
            case JDWP_EVENTKIND_CLASS_PREPARE: {
                printf("!!!!!!!!! JDWP_EVENTKIND_CLASS_PREPARE\n");
            } break;
        }
    }
}

void jdwp_eventset_clear(JdwpEventSet *set) {
    if(set) {
        switch(set->eventKind) {
            case JDWP_EVENTKIND_SINGLE_STEP: {
                printf("!!!!!!!!! CLEAR JDWP_EVENTKIND_SINGLE_STEP\n");
                jdwp_step_fp = -1;
            } break;
                
            case JDWP_EVENTKIND_BREAKPOINT: {
                printf("!!!!!!!!! CLEAR JDWP_EVENTKIND_BREAKPOINT\n");
                for (int i = 0; i < set->modifiers; i++) {
                    JdwpEventSetMod *mod = set->mods[i];
                    if (mod->type == 7) {
                        int index = (int)mod->location.index;
                        MethodFields *mf = (MethodFields*)mod->location.method->instance;
                        mf->breakpoint--;
                        if(mf->breakpoint < 0) mf->breakpoint = 0;
                        mf->lineNumberTable[index].breakpoint = 0;
                        printf("!!!!!!!! clear breakpoint at %s:%d type:%d\n", string2c(mf->name), mf->lineNumberTable[index].line, mod->location.type);
                        //jdwp_set_breakpoint(JDWP_EVENTSET_SET, mod->loc.classID, mod->loc.methodID,
                        //                    mod->loc.execIndex);
                    }
                }

            } break;
                
            case JDWP_EVENTKIND_CLASS_PREPARE: {
                printf("!!!!!!!!! CLEAR JDWP_EVENTKIND_CLASS_PREPARE\n");
            } break;
        }
    }
}
int jdwp_send_breakpoint_event(Object *method, int index) {
    JdwpEventSet *set = JdwpEventSet::head;
    while(set) {
        for(int i=0; i<set->modifiers; i++) {
            JdwpEventSetMod *mod = set->mods[i];
            if(mod->type == 7 && mod->location.method == method && mod->location.index == index) {
                JdwpPacket *p = new JdwpPacket();
                p->reset();
                p->writeByte(set->suspendPolicy);
                p->writeInt(1);
                p->writeByte(set->eventKind);
                p->writeInt(set->requestId);
                p->writeLong(JDWP_THREAD_ID);
                p->writeLocation(&mod->location);
                p->completeEvent();
                jdwp_client.queuePacket(p);
                return 1;
            }
        }
        set = set->next;
    }
    return 0;
}

int jdwp_send_step_event(Object *method, int line) {
    JdwpEventSet *set = JdwpEventSet::head;
    while(set) {
        for(int i=0; i<set->modifiers; i++) {
            JdwpEventSetMod *mod = set->mods[i];
            if(mod->type == 10) {
                JdwpPacket *p = new JdwpPacket();
                p->reset();
                p->writeByte(set->suspendPolicy);
                p->writeInt(1);
                p->writeByte(set->eventKind);
                p->writeInt(set->requestId);
                p->writeLong(JDWP_THREAD_ID);
                JdwpLocation loc;
                loc.clazz = MTH_FIELD(method, declaringClass);
                loc.type = jdwp_get_class_type(loc.clazz);
                loc.method = method;
                loc.index = jdwp_get_line_index(method, line);
                p->writeLocation(&loc);
                p->completeEvent();
                jdwp_client.queuePacket(p);
                
                printf("!! single step: line=%d index=%d\n", line, loc.index);
                return 1;
            }
        }
        set = set->next;
    }
    return 0;
}

void jdwp_invoke_method(JdwpPacket *req, JdwpPacket *resp, int isStatic) {
    Object *cls = nullptr;
    Object *object = nullptr;
    if(isStatic) {
        cls = req->readObject();
        req->readObject(); //thread
    } else {
        object = req->readObject();
        req->readObject(); //thread
        cls = req->readObject();
    }
    Object *method = req->readObject();
    int argCount = req->readInt();
    int start = 0;
    if(!isStatic) {
        start = 1;
        argCount++;
    }
    VAR args[argCount];
    for(int i=start; i<argCount; i++) {
        int tag = req->readByte();
        switch(tag) {
            case 'B':
            case 'Z':
                args[i].I = req->readByte();
                break;
                
            case 'S':
            case 'C':
                args[i].I = req->readShort();
                break;
                
            case 'I':
                args[i].I = req->readInt();
                break;
                
            case 'F':
                args[i].F = req->readFloat();
                break;
                
            case 'J':
                args[i].J = req->readLong();
                break;
                
            case 'D':
                args[i].D = req->readDouble();
                break;
                
            default:
                args[i].O = req->readObject();
                break;
        }
    }
    if(!isStatic) args[0].O = object;
    jdwp_invoking = 1;
    ((JVM_CALL)((MethodFields*)method->instance)->entry)(jdwpVM, method, &args[0]);
    jdwp_invoking = 0;
    StringFields *str = (StringFields*)MTH_FIELD(method, signature)->instance;
    jchar *ch = (jchar*)str->chars->instance;
    while(*ch != ')') ch++;
    ch++;
    int kind = *ch=='L' || *ch=='[' ? 'O' : *ch;
    VAR *ret = &jdwpVM->frames[jdwpVM->FP].retVal;
    switch(kind) {
        case 'B':
        case 'Z':
            resp->writeByte(kind);
            resp->writeByte(ret->I);
            break;
        case 'C':
        case 'S':
            resp->writeByte(kind);
            resp->writeShort(ret->I);
            break;
        case 'I':
            resp->writeByte(kind);
            resp->writeInt(ret->I);
            break;
        case 'F':
            resp->writeByte(kind);
            resp->writeFloat(ret->F);
            break;
        case 'J':
            resp->writeByte(kind);
            resp->writeLong(ret->J);
            break;
        case 'D':
            resp->writeByte(kind);
            resp->writeDouble(ret->D);
            break;

        case 'V':
            resp->writeByte('L');
            resp->writeLong(0);
            break;
            
        default: {
            Object *o = ret->O;
            if(!o) resp->writeByte('L');
            else if(o->cls == &java_lang_String) resp->writeByte(JDWP_TAG_STRING);
            else if(o->cls == &java_lang_Class) resp->writeByte(JDWP_TYPETAG_CLASS);
            //todo: thread
            else resp->writeByte('L');
            resp->writeObject(o);
        } break;
    }
}

void jdwp_process_packet(JdwpPacket *req) {
    JdwpPacket *resp = new JdwpPacket();
    resp->reset();
    
    int cmd = (req->commandSet << 8) + req->command;
    //printf(">>> JDWP Command: 0x%x\n", cmd);
    switch(cmd) {
        case JDWP_CMD_VirtualMachine_Version: //0x0101
            resp->writeCString((char*)"jdwp 1.2");
            resp->writeInt(1); //major
            resp->writeInt(0); //minor
            resp->writeCString((char*)"1.0");
            resp->writeCString((char*)"GamaVM");
            resp->complete(req->id, JDWP_ERROR_NONE);
            break;
            
        case JDWP_CMD_VirtualMachine_ClassesBySignature: { //0x0102
            JdwpString *signature = req->readString();
            Object *cls = jdwp_find_class(signature->toClassName(), 1);
            printf("class: %s -> %p\n", string2c(signature->str), cls);
            if(cls) {
                resp->writeInt(1);
                resp->writeByte(jdwp_get_class_type(cls));
                resp->writeObject(cls);
                resp->writeInt(JDWP_CLASS_STATUS_INITIALIZED | JDWP_CLASS_STATUS_PREPARED | JDWP_CLASS_STATUS_VERIFIED);
                //todo: event_on_class_prepare(NULL, cl);

            } else {
                resp->writeInt(0);
            }
            delete signature;
            resp->complete(req->id, JDWP_ERROR_NONE);
        } break;
            
        case JDWP_CMD_VirtualMachine_AllThreads: //0x0104
            //GamaVM is single threaded
            resp->writeInt(1);
            resp->writeLong(JDWP_THREAD_ID);
            resp->complete(req->id, JDWP_ERROR_NONE);
            break;
            
        case JDWP_CMD_VirtualMachine_IDSizes: //0x0107
            resp->writeInt(8);
            resp->writeInt(8);
            resp->writeInt(8);
            resp->writeInt(8);
            resp->writeInt(8);
            resp->complete(req->id, JDWP_ERROR_NONE);
            break;
            
        case JDWP_CMD_VirtualMachine_Resume: //0x0109
            jdwp_suspended = 0;
            resp->complete(req->id, JDWP_ERROR_NONE);
            break;
            
        case JDWP_CMD_VirtualMachine_Capabilities: // 0x010c
            resp->writeByte(0);//canWatchFieldModification
            resp->writeByte(0);//canWatchFieldAccess
            resp->writeByte(0);//canGetBytecodes
            resp->writeByte(0);//canGetSyntheticAttribute
            resp->writeByte(0);//canGetOwnedMonitorInfo
            resp->writeByte(0);//canGetCurrentContendedMonitor
            resp->writeByte(0);//canGetMonitorInfo
            resp->complete(req->id, JDWP_ERROR_NONE);
            break;
            
        case JDWP_CMD_VirtualMachine_CapabilitiesNew: {//0x0111
            for (int i = 0; i < 32; i++) resp->writeByte(0);
            resp->complete(req->id, JDWP_ERROR_NONE);
        } break;
            
        case JDWP_CMD_ReferenceType_Signature: { //0x0201
            Object *cls = req->readObject();
            ClassFields *cf = (ClassFields*)cls->instance;
            if(!cf->elementClass) {
                char tmp[256];
                sprintf(tmp, "L%s;", string2c(cf->name));
                resp->writeCString(tmp);
                //resp->writeCString((char*)"L");
                //resp->writeCString(string2c(cf->name));
                //resp->writeCString((char*)";");
            } else resp->writeCString(string2c(cf->name));
            resp->complete(req->id, JDWP_ERROR_NONE);
        } break;
            
        case JDWP_CMD_ReferenceType_ClassLoader: //0x0202
            resp->writeLong(0);
            resp->complete(req->id, JDWP_ERROR_NONE);
            break;
            
        case JDWP_CMD_ReferenceType_Fields: {//0x0204
            Object *cls = req->readObject();
            Object *fields = CLS_FIELD(cls, fields);
            if(fields) {
                int len = fields->length;
                if(cls == &java_lang_Class) len = 10;
                resp->writeInt(len);
                for(int i=0; i<len; i++) {
                    Object *field = ((Object**)fields->instance)[i];
                    resp->writeObject(field);
                    resp->writeCString(string2c(FLD_FIELD(field,name)));
                    resp->writeCString(string2c(FLD_FIELD(field,signature)));
                    resp->writeInt(FLD_FIELD(field, accessFlags));
                }
            } else resp->writeInt(0);
            resp->complete(req->id, JDWP_ERROR_NONE);
        } break;
            
        case JDWP_CMD_ReferenceType_Methods: {//0x0205
            Object *cls = req->readObject();
            if(cls) {
                ClassFields *cf = (ClassFields*)cls->instance;
                int len = cf->methods ? cf->methods->length : 0;
                resp->writeInt(len);
                for(int i=0; i<len; i++) {
                    Object **methods = (Object**)cf->methods->instance;
                    Object *m = methods[i];
                    MethodFields *mf = (MethodFields*)m->instance;
                    resp->writeObject(m);
                    resp->writeCString(string2c(mf->name));
                    resp->writeCString(string2c(mf->signature));
                    resp->writeInt(mf->accessFlags);
                }
                resp->complete(req->id, JDWP_ERROR_NONE);
            } else resp->complete(req->id, JDWP_ERROR_INVALID_CLASS);
        } break;
            
        case JDWP_CMD_ReferenceType_GetValues: { //0x0206
            Object *cls = req->readObject();
            //Object *cls = o->cls;
            printf("GetValues for: %s\n",string2c(CLS_FIELD(cls, name)));
            int count = req->readInt();
            resp->writeInt(count);
            for(int i=0; i<count; i++) {
                Object *field = req->readObject();
                FieldFields *ff = (FieldFields*)field->instance;
                printf("-- field: %s", string2c(ff->name));
                printf(" %s\n", string2c(ff->signature));
                void *base = ((ClassFields*)cls->instance)->globals;
                resp->writeValue(ff->signature, (void*)((char*)base + ff->offset));
            }
            resp->complete(req->id, JDWP_ERROR_NONE);

            /*
            Object *o = req->readObject();
            int count = req->readInt();
            Object *fields = CLS_FIELD(o->cls, fields);
            resp->writeInt(count);
            for(int i=0; i<count; i++) {
                Object *field = ((Object**)fields->instance)[i];
                
            }*/
        } break;
            
        case JDWP_CMD_ReferenceType_SourceFile: { //0x0207
            Object *cls = req->readObject();
            Object *name = nullptr;
            if(cls) {
                ClassFields *cf = (ClassFields*)cls->instance;
                name = cf->source_file;
            }
            if(name) resp->writeCString(string2c(name)); else resp->writeCString((char*)"");
            resp->complete(req->id, JDWP_ERROR_NONE);
        } break;
            
        case JDWP_CMD_ReferenceType_Interfaces: { //0x020a
            Object *cls = req->readObject();
            Object *interfaces = CLS_FIELD(cls, interfaces);
            if(interfaces) {
                resp->writeInt(interfaces->length);
                for(int i=0; i<interfaces->length; i++)
                    resp->writeObject(((Object**)interfaces->instance)[i]);
            } else resp->writeInt(0);
            resp->complete(req->id, JDWP_ERROR_NONE);
        } break;
            
        case JDWP_CMD_ReferenceType_ClassObject: { //0x020b
            Object *ref = req->readObject();
            resp->writeObject(ref);
            resp->complete(req->id, JDWP_ERROR_NONE);
        } break;

        case JDWP_CMD_ClassType_Superclass: { //0x0301
            Object *cls = req->readObject();
            resp->writeObject(CLS_FIELD(cls, superClass));
            resp->complete(req->id, JDWP_ERROR_NONE);
        } break;
            
        case JDWP_CMD_Method_LineTable: { //0x0601
            Object *cls = req->readObject();
            Object *method = req->readObject();
            if(method) {
                MethodFields *mf = (MethodFields*)method->instance;
                LineNumberInfo *info = mf->lineNumberTable;
                printf("--- lines of %s\n", string2c(mf->name));
                if(!info) {
                    resp->writeLong(-1);
                    resp->writeLong(-1);
                    resp->writeInt(0);
                } else {
                    resp->writeLong(0);
                    resp->writeLong(mf->lineNumberTableSize);
                    resp->writeInt(mf->lineNumberTableSize);
                    for(int i=0; i<mf->lineNumberTableSize; i++) {
                        resp->writeLong(i);//info[i].pc);
                        resp->writeInt(info[i].line);
                        printf(" ------- %d:%d\n", i, info[i].line);
                    }
                }
                resp->complete(req->id, JDWP_ERROR_NONE);
            } else resp->complete(req->id, JDWP_ERROR_INVALID_METHODID);
        } break;
            
        case JDWP_CMD_Method_VariableTable: { // 0x602
            Object *cls = req->readObject();
            Object *mth = req->readObject();
            MethodFields *m = (MethodFields*)mth->instance;
            resp->writeInt(m->argCount);
            resp->writeInt(m->localVarTableSize);
            for(int i=0; i<m->localVarTableSize; i++) {
                LocalVarInfo *v = &m->localVarTable[i];
                int startline = get_line_number(m, v->start);
                int startindex = jdwp_get_line_index(mth, startline);
                int endline = get_line_number(m, v->start + v->length);
                int endindex = jdwp_get_line_index(mth, endline);
                resp->writeLong(startindex);
                resp->writeCString(string2c(v->name));
                resp->writeCString(string2c(v->signature));
                resp->writeInt(endindex - startindex + 1);
                resp->writeInt(v->index); //local var index
            }
            resp->complete(req->id, JDWP_ERROR_NONE);
        } break;
            
        case JDWP_CMD_ObjectReference_ReferenceType: { //0x0901
            Object *o = req->readObject();
            if((jlong)o == JDWP_THREAD_ID) {
                resp->writeByte(JDWP_TYPETAG_CLASS);
                resp->writeObject(&java_lang_Class);
            } else {
                resp->writeByte(jdwp_get_class_type(o->cls));
                resp->writeObject(o->cls);
            }
            resp->complete(req->id, JDWP_ERROR_NONE);
        } break;
            
        case JDWP_CMD_ObjectReference_GetValues: { //0x0902
            Object *o = req->readObject();
            Object *cls = o->cls;
            printf("GetValues for: %s\n",string2c(CLS_FIELD(cls, name)));
            int count = req->readInt();
            resp->writeInt(count);
            for(int i=0; i<count; i++) {
                Object *field = req->readObject();
                FieldFields *ff = (FieldFields*)field->instance;
                printf("-- field: %s", string2c(ff->name));
                printf(" %s\n", string2c(ff->signature));
                int isstatic = (ff->accessFlags & ACC_STATIC) != 0;
                void *base = isstatic ? ((ClassFields*)cls->instance)->globals : o->instance;
                resp->writeValue(ff->signature, (void*)((char*)base + ff->offset));
            }
            resp->complete(req->id, JDWP_ERROR_NONE);
        } break;
            
        case JDWP_CMD_ObjectReference_InvokeMethod: { //0x0906
            jdwp_invoke_method(req, resp, 0);
            resp->complete(req->id, JDWP_ERROR_NONE);
        } break;
            
        case JDWP_CMD_ObjectReference_DisableCollection: { //0x0907
            gc_pause();
            resp->complete(req->id, JDWP_ERROR_NONE);
        } break;
            
        case JDWP_CMD_ObjectReference_EnableCollection: { //0x0908
            gc_resume();
            resp->complete(req->id, JDWP_ERROR_NONE);
        } break;
            
        case JDWP_CMD_StringReference_Value: { //0x0a01
            Object *str = req->readObject();
            resp->writeString(str);
            resp->complete(req->id, JDWP_ERROR_NONE);
        } break;
            
        case JDWP_CMD_ThreadReference_Name: { //0x0b01
            jlong threadId = req->readLong();
            if(threadId == JDWP_THREAD_ID) {
                resp->writeCString((char*)"GamaVM");
                resp->complete(req->id, JDWP_ERROR_NONE);
            } else resp->complete(req->id, JDWP_ERROR_INVALID_THREAD);
        } break;
            
        case JDWP_CMD_ThreadReference_Resume: //0x0b03
            jdwp_suspended = 0;
            resp->complete(req->id, JDWP_ERROR_NONE);
            break;
            
        case JDWP_CMD_ThreadReference_Status: { //0x0b04
            jlong threadId = req->readLong();
            if(threadId == JDWP_THREAD_ID) {
                resp->writeInt(JDWP_THREAD_RUNNING);
                resp->writeInt(jdwp_suspended ? JDWP_SUSPEND_STATUS_SUSPENDED : 0);
                resp->complete(req->id, JDWP_ERROR_NONE);
            } else resp->complete(req->id, JDWP_ERROR_INVALID_THREAD);
        } break;
            
        case JDWP_CMD_ThreadReference_Frames: { //0x0b06
            jlong thread = req->readLong();
            int startFrame = req->readInt()+1;
            int length = req->readInt();
            startFrame = jdwpVM->FP;
            int endFrame = length <= 0 ? 1 : startFrame - length + 1;
            if(endFrame < 1) endFrame = 1;
            resp->writeInt(startFrame - endFrame + 1);
            for (int i = startFrame; i >= endFrame; i--) {
                //if (i >= startFrame && i < startFrame + length) {
                    Frame *frame = &jdwpVM->frames[i];
                    resp->writeLong((jlong)frame);
                    JdwpLocation loc;
                    Object *method = frame->method;
                    Object *cls = ((MethodFields*)method->instance)->declaringClass;
                    loc.type = jdwp_get_class_type(cls);
                    loc.clazz = cls;
                    loc.method = method;
                    loc.index = jdwp_get_line_index(method, frame->line);
                    resp->writeLocation(&loc);
                //}
            }
            resp->complete(req->id, JDWP_ERROR_NONE);
        } break;
            
        case JDWP_CMD_ThreadReference_FrameCount: //0x0b07
            resp->writeInt(jdwpVM->FP);
            resp->complete(req->id, JDWP_ERROR_NONE);
            break;
            
        case JDWP_CMD_ThreadReference_SuspendCount: { //0x0b0c
             jlong threadId = req->readLong();
             if(threadId == JDWP_THREAD_ID) {
                 resp->writeInt(jdwp_suspended);
                 resp->complete(req->id, JDWP_ERROR_NONE);
             } else resp->complete(req->id, JDWP_ERROR_INVALID_THREAD);
        } break;
                

        case JDWP_CMD_ArrayReference_Length: { //0x0d01
            Object *arr = req->readObject();
            resp->writeInt(arr ? arr->length : 0);
            resp->complete(req->id, JDWP_ERROR_NONE);
        } break;
            
        case JDWP_CMD_ArrayReference_GetValues: { //0x0d02
            Object *arr = req->readObject();
            int index = req->readInt();
            int len = req->readInt();
            resp->writeArray(arr, index, len);
            resp->complete(req->id, JDWP_ERROR_NONE);
        } break;
            
        case JDWP_CMD_EventRequest_Set: { //0x0f01
            JdwpEventSet *set = new JdwpEventSet(req);
            jdwp_eventset_set(set);
            resp->writeInt(set->requestId);
            resp->complete(req->id, JDWP_ERROR_NONE);
        } break;
            
        case JDWP_CMD_EventRequest_Clear: { //0x0f02
            int eventKind = req->readByte();
            int requestId = req->readInt();
            JdwpEventSet *set = JdwpEventSet::removeByRequestId(requestId);
            if(set) {
                jdwp_eventset_clear(set);
                delete set;
            }
            resp->complete(req->id, JDWP_ERROR_NONE);
        } break;
            
        case JDWP_CMD_StackFrame_GetValues: { //0x1001
            req->readObject(); //skip thread
            Frame *frame = (Frame*)req->readLong();
            int slots = req->readInt();
            resp->writeInt(slots);
            VAR *sp = frame->sp;
            //frame->stack
            for(int i=0; i<slots; i++) {
                int slot = req->readInt();
                int type = req->readByte();
                switch(type) {
                    case 'B':
                    case 'Z':
                        resp->writeByte(type);
                        resp->writeByte(sp[slot].I);
                        break;
                        
                    case 'S':
                    case 'C':
                        resp->writeByte(type);
                        resp->writeShort(sp[slot].I);
                        break;
                        
                    case 'I':
                        resp->writeByte(type);
                        resp->writeInt(sp[slot].I);
                        break;
                    case 'F':
                        resp->writeByte(type);
                        resp->writeFloat(sp[slot].F);
                        break;
                    case 'D':
                        resp->writeByte(type);
                        resp->writeDouble(sp[slot].D);
                        break;
                    case 'J':
                        resp->writeByte(type);
                        resp->writeLong(sp[slot].J);
                        break;
                    case 'L':
                    case '[': {
                        Object *o = sp[slot].O;
                        if(!o) resp->writeByte(JDWP_TAG_OBJECT);
                        else if(o->cls == &java_lang_String) resp->writeByte(JDWP_TAG_STRING);
                        else if(o->cls == &java_lang_Class) resp->writeByte(JDWP_TAG_CLASS_OBJECT);
                        else if(CLS_FIELD(o->cls, elementClass)) resp->writeByte(JDWP_TAG_ARRAY);
                        else resp->writeByte(JDWP_TAG_OBJECT);
                        resp->writeObject(o);
                    } break;
                }
            }
            resp->complete(req->id, JDWP_ERROR_NONE);
        } break;
            
        case JDWP_CMD_StackFrame_ThisObject: { //0x1003
            req->readObject(); //thread
            Frame *frame = (Frame*)req->readLong();
            if((MTH_FIELD(frame->method, accessFlags) & ACC_STATIC) != 0) {
                resp->writeByte(JDWP_TAG_OBJECT);
                resp->writeLong(0);
            } else {
                resp->writeValue(MTH_FIELD(frame->method, signature), &frame->sp[0].O);
            }
            resp->complete(req->id, JDWP_ERROR_NONE);
        } break;
            
        case JDWP_CMD_ClassObjectReference_ReflectedType: { //0x1101
            Object *cls = req->readObject();
            resp->writeByte(jdwp_get_class_type(cls));
            resp->writeObject(cls);
            resp->complete(req->id, JDWP_ERROR_NONE);
        } break;
            
        default:
            printf("!!!!!!!!!!!!!!!!!!!! Unknown JDWP command = 0x%x\n",cmd);
            delete resp;
            return;
    }
    
    jdwp_client.queuePacket(resp);
}


extern "C" {

int jdwp_process_client() {
    int count = 0;
    if(jdwp_client.fd <= 0) return 0;
    JdwpPacket *req = jdwp_client.readPacket();
    while(req) {
        count++;
        jdwp_process_packet(req);
        req = jdwp_client.readPacket();
    }
    return count;
}


void jdwp_start(char *host, int port) {
#if SERVER
    jdwp_server_fd = jdwp_listen(10000);
    if(!jdwp_server_fd) {
        printf("Can't start JDWP server on port : %d\n",port);
        return;
    }
#else
    printf("Connecting to JDWP server %s:%d\n", host, port);
    while(1) {
        int fd = jdwp_connect(host, port);
        if(fd <= 0) {
            //printf("Can't connect to JDWP server %s:%d\n", host, port);
            //return;
        } else {
            jdwp_client.fd = fd;
            break;
        }
    }
    printf("Connected to JDWP server %s:%d\n", host, port);
#endif
    jdwp_suspended = 1;
}

void jdwp_tick(VM *vm, Object *method, int line) {
    jdwpVM = vm;
#if SERVER
    int fd = jdwp_accept(jdwp_server_fd);
    if(fd > 0) {
        jdwp_client.reset();
        jdwp_client.fd = fd;
        printf("JDWP client connected\n");
        //server mode
        JdwpPacket *p = new JdwpPacket;
        /*char sign[] = "JDWP-Handshake";
        p->setBytes((void*)&sign[0], 0, 14);
        jdwp_client.queuePacket(p);
        jdwp_client.flush();
        */
    }
#endif
    //printf("-- jdwp tick\n");
    //int suspended = 0;
    jdwp_process_client();
    jdwp_client.flush();

    if(jdwp_invoking) return;
    
    if(jdwp_step_fp != -1) {
        if(line != jdwp_skip_line && vm->FP <= jdwp_step_fp) {
            if(jdwp_send_step_event(method, line)) {
                jdwp_suspended = 1;
                jdwp_skip_line = line;
                //jdwp_step_fp = -1;
                printf("!!!!! SINGLE STEP !!!!\n");
            }
        }
        /*
        MethodFields *mf = (MethodFields*)method->instance;
        if(mf->lineNumberTable && jdwp_step_line_index >= 0 && jdwp_step_line_index < mf->lineNumberTableSize &&
           line == mf->lineNumberTable[jdwp_step_line_index].line) {
            if(jdwp_send_step_event(method, jdwp_step_line_index)) {
                
            }
        }*/
    } else {
        MethodFields *mf = (MethodFields*)method->instance;
        if(mf->breakpoint && mf->lineNumberTableSize > 0) {
            for(int i=0; i<mf->lineNumberTableSize; i++)
                if(mf->lineNumberTable[i].line == line && mf->lineNumberTable[i].breakpoint) {
                    if(jdwp_send_breakpoint_event(method, i)) {
                        jdwp_suspended = 1;
                        jdwp_skip_line = mf->lineNumberTable[i].line;
                        printf("!!!!! BREAKPOINT !!!! %d:%d\n",i,mf->lineNumberTable[i].line);
                    }
                    break;
                }
        }
    }
    jdwp_client.flush();

    while(jdwp_suspended) {
        jdwp_process_client();
        jdwp_client.flush();
    }
}

} //extern "C"
