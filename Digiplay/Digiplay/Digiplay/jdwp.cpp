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

void jdwp_eventset_set(JdwpEventSet *set) {
    if(set) {
        switch(set->eventKind) {
            case JDWP_EVENTKIND_SINGLE_STEP: {
                printf("!!!!!!!!! JDWP_EVENTKIND_SINGLE_STEP\n");
            } break;
                
            case JDWP_EVENTKIND_BREAKPOINT: {
                printf("!!!!!!!!! JDWP_EVENTKIND_BREAKPOINT\n");
                for (int i = 0; i < set->modifiers; i++) {
                    JdwpEventSetMod *mod = set->mods[i];
                    if (mod->type == 7) {
                        int index = (int)mod->location.index;
                        MethodFields *mf = (MethodFields*)mod->location.method->instance;
                        mf->breakpoint++;
                        mf->lineNumberTable[index].breakpoint = set->requestId;
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

int jdwp_get_line_index(Object *method, int line) {
    if(!method) return -1;
    MethodFields *mf = (MethodFields*)method->instance;
    if(mf->lineNumberTableSize <= 0) return -1;
    for(int i=0; i<mf->lineNumberTableSize; i++)
        if(mf->lineNumberTable[i].line == line) return i;
    return -1;
}

void jdwp_process_packet(JdwpPacket *req,VM* vm, Object *method, int line) {
    JdwpPacket *resp = new JdwpPacket();
    resp->reset();
    
    int cmd = (req->commandSet << 8) + req->command;
    printf(">>> JDWP Command: 0x%x\n", cmd);
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
            
        case JDWP_CMD_ReferenceType_ClassLoader: //0x0202
            resp->writeLong(0);
            resp->complete(req->id, JDWP_ERROR_NONE);
            break;
            
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
                    resp->writeLong(mf->codeSize);
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
            int startFrame = req->readInt();
            int length = req->readInt();
            int deepth = jdwpVM->FP;
            if (length == -1) {//等于-1返回所有剩下的
                length = deepth - startFrame;
            } else if(length > jdwpVM->FP)
                length = jdwpVM->FP;
            resp->writeInt(length);
            for (int i = 0; i < deepth; i++) {
                if (i >= startFrame && i < startFrame + length) {//返回指定层级的stackframe
                    resp->writeLong(i+1);
                    JdwpLocation loc;
                    Object *method = jdwpVM->frames[i+1].method;
                    Object *cls = ((MethodFields*)method->instance)->declaringClass;
                    loc.type = jdwp_get_class_type(cls);
                    loc.clazz = cls;
                    loc.method = method;
                    loc.index = jdwp_get_line_index(method, jdwpVM->frames[i+1].line);
                    resp->writeLocation(&loc);
                }
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
                

        case JDWP_CMD_EventRequest_Set: { //0x0f01
            JdwpEventSet *set = new JdwpEventSet(req);
            jdwp_eventset_set(set);
            resp->writeInt(set->requestId);
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

void jdwp_start(char *host, int port) {
#if SERVER
    jdwp_server_fd = jdwp_listen(10000);
    if(!jdwp_server_fd) {
        printf("Can't start JDWP server on port : %d\n",port);
        return;
    }
#else
    int fd = jdwp_connect(host, port);
    if(fd <= 0) {
        printf("Can't connect to JDWP server %s:%d\n", host, port);
        return;
    }
    jdwp_client.fd = fd;
    printf("Connected to JDWP server %s:%d\n", host, port);
#endif
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
    //int suspended = 0;
    while(true) {
        if(jdwp_client.fd <= 0) return;
        JdwpPacket *req = jdwp_client.readPacket();
        while(req) {
            jdwp_process_packet(req, vm, method, line);
            req = jdwp_client.readPacket();
        }

        if(!jdwp_suspended) {
            MethodFields *mf = (MethodFields*)method->instance;
            if(mf->breakpoint && mf->lineNumberTableSize > 0) {
                for(int i=0; i<mf->lineNumberTableSize; i++)
                    if(mf->lineNumberTable[i].line == line && mf->lineNumberTable[i].breakpoint) {
                        if(jdwp_send_breakpoint_event(method, i)) {
                            jdwp_suspended = 1;
                            printf("!!!!! BREAKPOINT !!!! %d:%d\n",i,mf->lineNumberTable[i].line);
                        }
                        break;
                    }
            }
        }
        
        jdwp_client.flush();
        if(!jdwp_suspended) break;
    }
}

} //extern "C"
