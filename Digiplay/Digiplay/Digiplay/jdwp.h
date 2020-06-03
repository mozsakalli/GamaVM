//
//  jdwp.hpp
//  Digiplay
//
//  Created by mustafa on 31.05.2020.
//  Copyright © 2020 mustafa. All rights reserved.
//

#ifdef JDWP_ENABLE

#ifndef jdwp_hpp
#define jdwp_hpp

#include <stdio.h>
#include "jvm.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <fcntl.h>

enum {
    JDWP_ERROR_INVALID_TAG = 500, //object type id or class tag
    JDWP_ERROR_ALREADY_INVOKING = 502, //previous invoke not complete
    JDWP_ERROR_INVALID_INDEX = 503,
    JDWP_ERROR_INVALID_LENGTH = 504,
    JDWP_ERROR_INVALID_STRING = 506,
    JDWP_ERROR_INVALID_CLASS_LOADER = 507,
    JDWP_ERROR_INVALID_ARRAY = 508,
    JDWP_ERROR_TRANSPORT_LOAD = 509,
    JDWP_ERROR_TRANSPORT_INIT = 510,
    JDWP_ERROR_NATIVE_METHOD = 511,
    JDWP_ERROR_INVALID_COUNT = 512,
    JDWP_ERROR_NONE = 0,
    JDWP_ERROR_INVALID_THREAD = 10,
    JDWP_ERROR_INVALID_THREAD_GROUP = 11,
    JDWP_ERROR_INVALID_PRIORITY = 12,
    JDWP_ERROR_THREAD_NOT_SUSPENDED = 13,
    JDWP_ERROR_THREAD_SUSPENDED = 14,
    JDWP_ERROR_INVALID_OBJECT = 20,
    JDWP_ERROR_INVALID_CLASS = 21,
    JDWP_ERROR_CLASS_NOT_PREPARED = 22,
    JDWP_ERROR_INVALID_METHODID = 23,
    JDWP_ERROR_INVALID_LOCATION = 24,
    JDWP_ERROR_INVALID_FIELDID = 25,
    JDWP_ERROR_INVALID_FRAMEID = 30,
    JDWP_ERROR_NO_MORE_FRAMES = 31,
    JDWP_ERROR_OPAQUE_FRAME = 32,
    JDWP_ERROR_NOT_CURRENT_FRAME = 33,
    JDWP_ERROR_TYPE_MISMATCH = 34,
    JDWP_ERROR_INVALID_SLOT = 35,
    JDWP_ERROR_DUPLICATE = 40,
    JDWP_ERROR_NOT_FOUND = 41,
    JDWP_ERROR_INVALID_MONITOR = 50,
    JDWP_ERROR_NOT_MONITOR_OWNER = 51,
    JDWP_ERROR_INTERRUPT = 52,
    JDWP_ERROR_INVALID_CLASS_FORMAT = 60,
    JDWP_ERROR_CIRCULAR_CLASS_DEFINITION = 61,
    JDWP_ERROR_FAILS_VERIFICATION = 62,
    JDWP_ERROR_ADD_METHOD_NOT_IMPLEMENTED = 63,
    JDWP_ERROR_SCHEMA_CHANGE_NOT_IMPLEMENTED = 64,
    JDWP_ERROR_INVALID_TYPESTATE = 65,
    JDWP_ERROR_NOT_IMPLEMENTED = 99,
    JDWP_ERROR_NULL_POINTER = 100,
    JDWP_ERROR_ABSENT_INFORMATION = 101,
    JDWP_ERROR_INVALID_EVENT_TYPE = 102,
    JDWP_ERROR_ILLEGAL_ARGUMENT = 103,
    JDWP_ERROR_OUT_OF_MEMORY = 110,
    JDWP_ERROR_ACCESS_DENIED = 111,
    JDWP_ERROR_VM_DEAD = 112,
    JDWP_ERROR_INTERNAL = 113,
    JDWP_ERROR_UNATTACHED_THREAD = 115,
};
//=============================      event   ==============================================

#define JDWP_EVENTKIND_SINGLE_STEP  1
#define JDWP_EVENTKIND_BREAKPOINT  2
#define JDWP_EVENTKIND_FRAME_POP  3
#define JDWP_EVENTKIND_EXCEPTION  4
#define JDWP_EVENTKIND_USER_DEFINED  5
#define JDWP_EVENTKIND_THREAD_START  6
#define JDWP_EVENTKIND_THREAD_DEATH  7
#define JDWP_EVENTKIND_CLASS_PREPARE  8
#define JDWP_EVENTKIND_CLASS_UNLOAD  9
#define JDWP_EVENTKIND_CLASS_LOAD  10
#define JDWP_EVENTKIND_FIELD_ACCESS  20
#define JDWP_EVENTKIND_FIELD_MODIFICATION  21
#define JDWP_EVENTKIND_EXCEPTION_CATCH  30
#define JDWP_EVENTKIND_METHOD_ENTRY  40
#define JDWP_EVENTKIND_METHOD_EXIT  41
#define JDWP_EVENTKIND_METHOD_EXIT_WITH_RETURN_VALUE  42
#define JDWP_EVENTKIND_VM_START  90
#define JDWP_EVENTKIND_VM_DEATH  99
#define JDWP_EVENTKIND_VM_DISCONNECTED  100  //Never sent by across JDWP

typedef unsigned char u8;
typedef char c8;

//=============================      event   ==============================================
static u8 JDWP_STEPDEPTH_INTO = 0;
static u8 JDWP_STEPDEPTH_OVER = 1;
static u8 JDWP_STEPDEPTH_OUT = 2;


static u8 JDWP_STEPSIZE_MIN = 0;
static u8 JDWP_STEPSIZE_LINE = 1;
//=============================      class status   ==============================================

#define JDWP_CLASS_STATUS_VERIFIED  1
#define JDWP_CLASS_STATUS_PREPARED  2
#define JDWP_CLASS_STATUS_INITIALIZED  4
#define JDWP_CLASS_STATUS_ERROR  8
//=============================      typetag   ==============================================

static u8 JDWP_TYPETAG_CLASS = 1; //ReferenceType is a class.
static u8 JDWP_TYPETAG_INTERFACE = 2; //ReferenceType is an interface.
static u8 JDWP_TYPETAG_ARRAY = 3; //ReferenceType is an array.
//=============================      Thread status   ==============================================
static c8 JDWP_THREAD_ZOMBIE = 0;
static c8 JDWP_THREAD_RUNNING = 1;
static c8 JDWP_THREAD_SLEEPING = 2;
static c8 JDWP_THREAD_MONITOR = 3;
static c8 JDWP_THREAD_WAIT = 4;
//=============================      suspend   ==============================================

static c8 JDWP_SUSPEND_STATUS_SUSPENDED = 0x1;


static c8 JDWP_SUSPENDPOLICY_NONE = 0;//Suspend no threads when this event is encountered.
static c8 JDWP_SUSPENDPOLICY_EVENT_THREAD = 1;//Suspend the event thread when this event is encountered.
#define JDWP_SUSPENDPOLICY_ALL 2
//=============================      tag   ==============================================

#define JDWP_TAG_ARRAY  91
// '[' - an array object (objectID size).
#define JDWP_TAG_BYTE  66
// 'B' - a byte value (1 byte).
#define JDWP_TAG_CHAR  67
// 'C' - a character value (2 bytes).
#define JDWP_TAG_OBJECT  76
// 'L' - an object (objectID size).
#define JDWP_TAG_FLOAT  70
// 'F' - a float value (4 bytes).
#define JDWP_TAG_DOUBLE  68
// 'D' - a double value (8 bytes).
#define JDWP_TAG_INT  73
// 'I' - an int value (4 bytes).
#define JDWP_TAG_LONG  74
// 'J' - a long value (8 bytes).
#define JDWP_TAG_SHORT  83
// 'S' - a short value (2 bytes).
#define JDWP_TAG_VOID  86
// 'V' - a void value (no bytes).
#define JDWP_TAG_BOOLEAN  90
// 'Z' - a boolean value (1 byte).
#define JDWP_TAG_STRING  115
// 's' - a String object (objectID size).
#define JDWP_TAG_THREAD  116
// 't' - a Thread object (objectID size).
#define JDWP_TAG_THREAD_GROUP  103
// 'g' - a ThreadGroup object (objectID size).
#define JDWP_TAG_CLASS_LOADER  108
// 'l' - a ClassLoader object (objectID size).
#define JDWP_TAG_CLASS_OBJECT  99
// 'c' - a class object object (objectID size).

//=============================      cmd   ==============================================


//VirtualMachine Command Set (1)
#define JDWP_CMD_VirtualMachine_Version   0x0101
#define JDWP_CMD_VirtualMachine_ClassesBySignature   0x0102
#define JDWP_CMD_VirtualMachine_AllClasses   0x0103
#define JDWP_CMD_VirtualMachine_AllThreads   0x0104
#define JDWP_CMD_VirtualMachine_TopLevelThreadGroups   0x0105
#define JDWP_CMD_VirtualMachine_Dispose   0x0106
#define JDWP_CMD_VirtualMachine_IDSizes   0x0107
#define JDWP_CMD_VirtualMachine_Suspend   0x0108
#define JDWP_CMD_VirtualMachine_Resume   0x0109
#define JDWP_CMD_VirtualMachine_Exit   0x010a
#define JDWP_CMD_VirtualMachine_CreateString   0x010b
#define JDWP_CMD_VirtualMachine_Capabilities   0x010c
#define JDWP_CMD_VirtualMachine_ClassPaths   0x010d
#define JDWP_CMD_VirtualMachine_DisposeObjects   0x010e
#define JDWP_CMD_VirtualMachine_HoldEvents   0x010f
#define JDWP_CMD_VirtualMachine_ReleaseEvents   0x0110
#define JDWP_CMD_VirtualMachine_CapabilitiesNew   0x0111
#define JDWP_CMD_VirtualMachine_RedefineClasses   0x0112
#define JDWP_CMD_VirtualMachine_SetDefaultStratum   0x0113
#define JDWP_CMD_VirtualMachine_AllClassesWithGeneric   0x0114
//ReferenceType Command Set (2)
#define JDWP_CMD_ReferenceType_Signature   0x0201
#define JDWP_CMD_ReferenceType_ClassLoader   0x0202
#define JDWP_CMD_ReferenceType_Modifiers   0x0203
#define JDWP_CMD_ReferenceType_Fields   0x0204
#define JDWP_CMD_ReferenceType_Methods   0x0205
#define JDWP_CMD_ReferenceType_GetValues   0x0206
#define JDWP_CMD_ReferenceType_SourceFile   0x0207
#define JDWP_CMD_ReferenceType_NestedTypes   0x0208
#define JDWP_CMD_ReferenceType_Status   0x0209
#define JDWP_CMD_ReferenceType_Interfaces   0x020a
#define JDWP_CMD_ReferenceType_ClassObject   0x020b
#define JDWP_CMD_ReferenceType_SourceDebugExtension   0x020c
#define JDWP_CMD_ReferenceType_SignatureWithGeneric   0x020d
#define JDWP_CMD_ReferenceType_FieldsWithGeneric   0x020e
#define JDWP_CMD_ReferenceType_MethodsWithGeneric   0x020f
//ClassType Command Set (3)
#define JDWP_CMD_ClassType_Superclass   0x0301
#define JDWP_CMD_ClassType_SetValues   0x0302
#define JDWP_CMD_ClassType_InvokeMethod   0x0303
#define JDWP_CMD_ClassType_NewInstance   0x0304
//ArrayType Command Set (4)
#define JDWP_CMD_ArrayType_NewInstance   0x0401
//InterfaceType Command Set (5)
//Method Command Set (6)
#define JDWP_CMD_Method_LineTable   0x0601
#define JDWP_CMD_Method_VariableTable   0x0602
#define JDWP_CMD_Method_Bytecodes   0x0603
#define JDWP_CMD_Method_IsObsolete   0x0604
#define JDWP_CMD_Method_VariableTableWithGeneric   0x0605
//Field Command Set (8)
//ObjectReference Command Set (9)
#define JDWP_CMD_ObjectReference_ReferenceType   0x0901
#define JDWP_CMD_ObjectReference_GetValues   0x0902
#define JDWP_CMD_ObjectReference_SetValues   0x0903
#define JDWP_CMD_ObjectReference_MonitorInfo   0x0905
#define JDWP_CMD_ObjectReference_InvokeMethod   0x0906
#define JDWP_CMD_ObjectReference_DisableCollection   0x0907
#define JDWP_CMD_ObjectReference_EnableCollection   0x0908
#define JDWP_CMD_ObjectReference_IsCollected   0x0909
//StringReference Command Set (10)
#define JDWP_CMD_StringReference_Value   0x0a01
//ThreadReference Command Set (11)
#define JDWP_CMD_ThreadReference_Name   0x0b01
#define JDWP_CMD_ThreadReference_Suspend   0x0b02
#define JDWP_CMD_ThreadReference_Resume   0x0b03
#define JDWP_CMD_ThreadReference_Status   0x0b04
#define JDWP_CMD_ThreadReference_ThreadGroup   0x0b05
#define JDWP_CMD_ThreadReference_Frames   0x0b06
#define JDWP_CMD_ThreadReference_FrameCount   0x0b07
#define JDWP_CMD_ThreadReference_OwnedMonitors   0x0b08
#define JDWP_CMD_ThreadReference_CurrentContendedMonitor   0x0b09
#define JDWP_CMD_ThreadReference_Stop   0x0b0a
#define JDWP_CMD_ThreadReference_Interrupt   0x0b0b
#define JDWP_CMD_ThreadReference_SuspendCount   0x0b0c
//ThreadGroupReference Command Set (12)
#define JDWP_CMD_ThreadGroupReference_Name   0x0c01
#define JDWP_CMD_ThreadGroupReference_Parent   0x0c02
#define JDWP_CMD_ThreadGroupReference_Children   0x0c03
//ArrayReference Command Set (13)
#define JDWP_CMD_ArrayReference_Length   0x0d01
#define JDWP_CMD_ArrayReference_GetValues   0x0d02
#define JDWP_CMD_ArrayReference_SetValues   0x0d03
//ClassLoaderReference Command Set (14)
#define JDWP_CMD_ClassLoaderReference_VisibleClasses   0x0e01
//EventRequest Command Set (15)
#define JDWP_CMD_EventRequest_Set   0x0f01
#define JDWP_CMD_EventRequest_Clear   0x0f02
#define JDWP_CMD_EventRequest_ClearAllBreakpoints   0x0f03
//StackFrame Command Set (16)
#define JDWP_CMD_StackFrame_GetValues   0x1001
#define JDWP_CMD_StackFrame_SetValues   0x1002
#define JDWP_CMD_StackFrame_ThisObject   0x1003
#define JDWP_CMD_StackFrame_PopFrames   0x1004
//ClassObjectReference Command Set (17)
#define JDWP_CMD_ClassObjectReference_ReflectedType   0x1101
//Event Command Set (64)
#define JDWP_CMD_Event_Composite   0x4064

#define JDWP_THREAD_ID 0x100000


class JdwpByteArray {
public:
    char *buffer;
    int length;
    JdwpByteArray(int len = 16) {
        buffer = (char*)malloc(len);
        memset(buffer, 0, len);
        length = len;
    }
    ~JdwpByteArray() {
        if(buffer) free(buffer);
    }
    void resize(int len) {
        buffer = (char*)realloc(buffer, len);
        length = len;
    }
};

typedef struct JdwpLocation {
    int type;
    Object *clazz;
    Object *method;
    jlong index;
} JdwpLocation;

class JdwpString {
public:
    Object *str = nullptr;
    JdwpString(Object *str) : str(str) {}
    ~JdwpString() {
        if(str) {
            StringFields *strf = (StringFields*)str->instance;
            free((void*)strf->chars->instance);
            free(strf->chars);
            free(strf);
            free(str);
        }
    }
    Object *toClassName() {
        StringFields *sf = (StringFields*)str->instance;
        jchar *chars = (jchar*)sf->chars->instance;
        if(chars[sf->start] == 'L') {
            sf->start++;
            sf->length -= 2;
        }
        return str;
    }
};

static int jdwpEventRequestSerial = 0x10000000;
class JdwpPacket {
public:
    JdwpByteArray buffer;
    int ptr;
    
    int payload;
    int id;
    int flags;
    int commandSet;
    int command;
    
    int sentPtr = 0;
    JdwpPacket *next;
    
    
    void start(JdwpByteArray& bytes, int ptr) {
        buffer = bytes;
        this->ptr = ptr;
        payload = readInt();
        id = readInt();
        flags = readByte();
        commandSet = readByte();
        command = readByte();
        
        //printf("packet: payload=%d id=%d cmd=0x%x\n", payload, id, (commandSet<<8)|command);
    }
    
    int readN(int len) {
        int result = 0;
        for(int i=0; i<len; i++)
            result = (result << 8) + (buffer.buffer[ptr++]&0xff);
        return result;
    }
    
    int readByte() {
        return buffer.buffer[ptr++]&0xff;
    }
    
    int readShort() {
        return readN(2);
    }
    
    int readInt() {
        return readN(4);
    }
    
    jlong readLong() {
        int h = readInt();
        int l = readInt();
        return (((jlong) h) << 32L) | ((jlong) l) & 0xffffffffL;
    }
    
    Object *readObject() {
        return (Object*)readLong();
    }
    
    jfloat readFloat() {
        int v = readInt();
        jfloat *f = (jfloat*)&v;
        return *f;
    }
    
    jdouble readDouble() {
        jlong l = readLong();
        double *d = (jdouble*)&l;
        return *d;
    }
    
    JdwpString *readString() {
        int len = readInt();
        Object *str = parse_utf8(NULL, buffer.buffer+ptr, len, 0);
        ptr += len;
        return new JdwpString(str);
    }

    void readLocation(JdwpLocation *loc) {
        loc->type = readByte();
        loc->clazz = (Object*)readLong();
        loc->method = (Object*)readLong();
        loc->index = readLong();
    }
    
    int getKey() {
        return (commandSet << 8) + command;
    }
    
    
    static int eventRequestSerial;
    
    void reset() {
        ptr = 11;
        memset(buffer.buffer, 0, buffer.length);
    }
    
    void ensure(int required) {
        if(ptr + required > buffer.length)
            buffer.resize(ptr + required);
    }
    
    void complete(int id, int errorCode) {
        setInt(0, ptr);
        setInt(4, id);
        buffer.buffer[8] = 0x80;
        buffer.buffer[9] = ((errorCode>>8)&0xff);
        buffer.buffer[10] = (errorCode&0xff);
        sentPtr = 0;
    }
    
    void completeEvent() {
        setInt(0, ptr);
        setInt(4, eventRequestSerial++);
        buffer.buffer[8] = 0;
        buffer.buffer[9] = 64;
        buffer.buffer[10] = 100;
        sentPtr = 0;
    }
    
    void onVMStartEvent() {
        reset();
        writeByte(JDWP_SUSPENDPOLICY_ALL);
        writeInt(1); //event count
        //event data
        writeByte(JDWP_EVENTKIND_VM_START); //event kind
        writeInt(0); //req id
        writeLong(JDWP_THREAD_ID); //thread id
        completeEvent();
    }
    
    int getSize() {
        return ptr;
    }
    
    
    void setInt(int pos, int v) {
        buffer.buffer[pos++] = ((v>>24)&0xff);
        buffer.buffer[pos++] = ((v>>16)&0xff);
        buffer.buffer[pos++] = ((v>>8)&0xff);
        buffer.buffer[pos] = ((v>>0)&0xff);
    }
    
    void writeLong(long v) {
        ensure(8);
        buffer.buffer[ptr++] = ((v>>56)&0xff);
        buffer.buffer[ptr++] = ((v>>48)&0xff);
        buffer.buffer[ptr++] = ((v>>40)&0xff);
        buffer.buffer[ptr++] = ((v>>32)&0xff);
        buffer.buffer[ptr++] = ((v>>24)&0xff);
        buffer.buffer[ptr++] = ((v>>16)&0xff);
        buffer.buffer[ptr++] = ((v>>8)&0xff);
        buffer.buffer[ptr++] = ((v>>0)&0xff);
    }
    
    void writeObject(Object *o) {
        writeLong((jlong)o);
    }
    
    void writeInt(int v) {
        ensure(4);
        buffer.buffer[ptr++] = ((v>>24)&0xff);
        buffer.buffer[ptr++] = ((v>>16)&0xff);
        buffer.buffer[ptr++] = ((v>>8)&0xff);
        buffer.buffer[ptr++] = ((v>>0)&0xff);
    }
    
    void writeShort(int v) {
        ensure(2);
        buffer.buffer[ptr++] = ((v>>8)&0xff);
        buffer.buffer[ptr++] = ((v>>0)&0xff);
    }

    void writeByte(int v) {
        ensure(1);
        buffer.buffer[ptr++] = (v&0xff);
    }
    
    void writeFloat(float v) {
        int *f = (int*)&v;
        writeInt(*f);
    }
    void writeDouble(double v) {
        jlong *l = (jlong*)&v;
        writeLong(*l);
    }
    void writeBoolean(int v) {
        writeByte(v ? 1 : 0);
    }
    void writeCString(char *str) {
        int len = (int)strlen(str);
        writeInt(len);
        ensure(len);
        memcpy(buffer.buffer+ptr, str, len);
        ptr += len;
    }
    void writeLocation(JdwpLocation *loc) {
        writeByte(loc->type);
        writeObject(loc->clazz);
        writeObject(loc->method);
        writeLong(loc->index);
    }

    void writeValue(Object *signature, void *ptr) {
        StringFields *str = (StringFields*)signature->instance;
        jchar *chars = (jchar*)str->chars->instance;
        switch(chars[0]) {
            case 'B':
            case 'Z':
                writeByte(chars[0]);
                writeByte(*(jbyte*)ptr);
                break;
                
            case 'S':
            case 'C':
                writeByte(chars[0]);
                writeShort(*(jshort*)ptr);
                break;

            case 'I':
            case 'F':
                writeByte(chars[0]);
                writeInt(*(jint*)ptr);
                break;

            case 'J':
            case 'D':
                writeByte(chars[0]);
                writeLong(*(jlong*)ptr);
                break;

            case '[':
                writeByte('[');
                writeObject(*(Object**)ptr);
                break;
                
            default:
                if(compare_string((void*)signature, (void*)"Ljava/lang/String;", 0))
                    writeByte(JDWP_TAG_STRING);
                else if(compare_string((void*)signature, (void*)"Ljava/lang/Class;", 0))
                    writeByte(JDWP_TYPETAG_CLASS);
                else if(compare_string((void*)signature, (void*)"Ljava/lang/Thread;", 0))
                    writeByte(JDWP_TAG_THREAD);
                else writeByte('L');
                writeObject(*(Object**)ptr);
                break;
        }
    }
    
    void writeArray(Object *arr, int index, int len) {
        jchar *chars = (jchar*)((StringFields*)CLS_FIELD(arr->cls, name)->instance)->chars->instance;
        writeByte(chars[1]);
        writeInt(len);
        switch(chars[1]) {
            case 'B':
            case 'Z': {
                jbyte *data = (jbyte*)arr->instance;
                for(int i=index; i<index+len; i++) writeByte(data[i]);
            } break;
            case 'C':
            case 'S': {
                jshort *data = (jshort*)arr->instance;
                for(int i=index; i<index+len; i++) writeShort(data[i]);
            } break;
            case 'I':
            case 'F': {
                jint *data = (jint*)arr->instance;
                for(int i=index; i<index+len; i++) writeInt(data[i]);
            } break;
            case 'J':
            case 'D': {
                jlong *data = (jlong*)arr->instance;
                for(int i=index; i<index+len; i++) writeLong(data[i]);
            } break;
            default: {
                Object **data = (Object**)arr->instance;
                for(int i=index; i<index+len; i++) {
                    Object *o = data[i];
                    if(!o) {
                        writeByte('L');
                        writeLong(0);
                    } else {
                        writeValue(CLS_FIELD(o->cls,name), (void*)&o);
                    }
                }
            } break;
        }
    }
    
    void writeString(Object *strobject) {
        StringFields *str = (StringFields*)strobject->instance;
        jchar *chars = (jchar*)str->chars->instance;
        int len = 0;
        for (int i = str->start; i < str->start+str->length; i++) {
            int c = chars[i] & 0xff;
            if (c <= 0x7F) {
                len += 1;
            } else if (c <= 0x7FF) {
                len += 2;
            } else if (c <= 0xFFFF) {
                len += 3;
            } else {
                len += 4;
            }
        }
        
        writeInt(len);
        ensure(len);
        for (int i = str->start; i < str->start+str->length; i++) {
            int c = chars[i] & 0xff;
            if (c <= 0x7F) {
                writeByte(c);
            } else if (c <= 0x7FF) {
                writeByte(0xC0 | (c >> 6));
                writeByte(0x80 | (c & 63));
            } else if (c <= 0xFFFF) {
                writeByte(0xE0 | (c >> 12));
                writeByte(0x80 | ((c >> 6) & 63));
                writeByte(0x80 | (c & 63));
            } else {
                writeByte(0xF0 | (c >> 18));
                writeByte(0x80 | ((c >> 12) & 63));
                writeByte(0x80 | ((c >> 6) & 63));
                writeByte(0x80 | (c & 63));
            }
        }
    }
    /*
    void writeString(String str) {
        byte[] buffer = str.getBytes();
        int len = buffer.length;
        ensure(len + 4);
        writeInt(len);
        for(int i=0; i<len; i++) this.buffer.buffer[ptr++] = buffer.buffer[i];
    }
    */
    //for handshake
    void setBytes(JdwpByteArray& bytes, int offset, int length) {
        ensure(length);
        memcpy(buffer.buffer, bytes.buffer, length);
        ptr = length;
    }
    void setBytes(void *bytes, int offset, int length) {
        ensure(length);
        memcpy(buffer.buffer, bytes, length);
        ptr = length;
    }
};

class JdwpEventSetMod {
public:
    int type, count,exprId, caught, uncaught, size, depth;
    jlong threadId;
    Object *clazz=nullptr, *exceptionOrNull = nullptr, *field = nullptr, *instance = nullptr;
    JdwpString *classPattern = nullptr, *sourceNamePattern = nullptr;
    JdwpLocation location;
    
    ~JdwpEventSetMod() {
        if(classPattern) delete classPattern;
        if(sourceNamePattern) delete sourceNamePattern;
    }
    
};
class JdwpEventSet {
public:
    int requestId, eventKind, suspendPolicy, modifiers;
    JdwpEventSetMod **mods;
    JdwpEventSet *next = nullptr;
    
    static JdwpEventSet *head, *tail;
    static JdwpEventSet *getByRequestId(int requestId) {
        JdwpEventSet *ptr = head;
        while(ptr) {
            if(ptr->requestId == requestId) return ptr;
            ptr = ptr->next;
        }
        return nullptr;
    }

    static JdwpEventSet *removeByRequestId(int requestId) {
        JdwpEventSet *pre = nullptr;
        JdwpEventSet *ptr = head;
        while(ptr) {
            if(ptr->requestId == requestId) {
                if(!pre) head = head->next;
                else pre->next = ptr->next;
                if(head == nullptr) tail = nullptr;
                else if(ptr == tail) {
                    tail = pre;
                    tail->next = nullptr;
                }
                return ptr;
            }
            pre = ptr;
            ptr = ptr->next;
        }
        return nullptr;
    }
    
    static void reset() {
        JdwpEventSet *ptr = head;
        while(ptr) {
            JdwpEventSet *n = ptr->next;
            delete ptr;
            ptr = n;
        }
        head = tail = nullptr;
    }

    JdwpEventSet(JdwpPacket *req) {
        requestId = jdwpEventRequestSerial++;
        eventKind = req->readByte();
        suspendPolicy = req->readByte();
        modifiers = req->readInt();
        mods = (JdwpEventSetMod**)malloc(sizeof(JdwpEventSetMod*) * modifiers);
        for(int i=0; i<modifiers; i++) {
            JdwpEventSetMod *mod = mods[i] = new JdwpEventSetMod;
            int imod = req->readByte();
            mod->type = imod;
            switch (imod) {
                case 1:
                    mod->count = req->readInt();
                    break;
                case 2:
                    mod->exprId = req->readInt();
                    break;
                case 3:
                    mod->threadId = req->readLong();
                    break;
                case 4:
                    mod->clazz = (Object*)req->readLong();
                    break;
                case 5:
                case 6:
                    mod->classPattern = req->readString();
                    //utf8_replace_c(mod->classPattern, ".", "/");
                    break;
                case 7:
                    req->readLocation(&mod->location);
                    break;
                case 8:
                    mod->exceptionOrNull = (Object*)req->readLong();
                    mod->caught = req->readByte();
                    mod->uncaught = req->readByte();
                    break;
                case 9:
                    mod->clazz = (Object*)req->readLong();
                    mod->field = (Object*)req->readLong();
                    break;
                case 10:
                    mod->threadId = req->readLong();
                    mod->size = req->readInt();
                    mod->depth = req->readInt();
                    break;
                case 11:
                    mod->instance = (Object*)req->readLong();
                    break;
                case 12:
                    mod->sourceNamePattern = req->readString();
                    break;
            }
        }
        
        if(tail) {
            tail->next = this;
            tail = this;
        } else {
            head = tail = this;
        }
    }
    ~JdwpEventSet() {
        if(mods) {
            for(int i=0; i<modifiers; i++)
                delete mods[i];
            delete mods;
        }
    }
};
class JdwpClient {
public:
    JdwpByteArray buf;
    int bufSize = 0;
    int fd = 0;
    int payload = 14;
    bool handsShaken = false;
    bool pending4 = false;
    JdwpPacket packet;
    JdwpPacket *qHead=nullptr, *qTail=nullptr;
    
    void reset() {
        while(qHead) {
            auto p = qHead;
            qHead = qHead->next;
            delete p;
        }
        qHead = qTail = nullptr;
        payload = 14;
        bufSize = 0;
        handsShaken = false;
        close(fd);
        fd = 0;
    }
    bool readSome(int len) {
        if(buf.length < bufSize + len) buf.resize(bufSize + len);
        size_t rr = (int)read(fd, buf.buffer + bufSize, len);
        int r = (int)rr;
        if(r >= 0) {
            bufSize += r;
            //printf("---- readsome: %d\n", r);
            return true;
        }
        //fd = 0;
        return false;
    }
    
    void queuePacket(JdwpPacket *p) {
        if(qTail) {
            qTail->next = p;
            qTail = p;
        } else {
            qHead = qTail = p;
        }
        p->next = nullptr;
    }
    
    JdwpPacket *readPacket() {
        if(!readSome(payload - bufSize)) return nullptr;
        if(bufSize != payload) return nullptr;
        if(!handsShaken) {
            JdwpPacket *hp = new JdwpPacket();
            hp->setBytes(buf, 0, 14);
            queuePacket(hp);
            handsShaken = true;
            
            //send vm start
            hp = new JdwpPacket();
            hp->onVMStartEvent();
            queuePacket(hp);
            
            bufSize = 0;
            payload = 4;
            pending4 = true;
            if(!readSome(4)) return nullptr;
            if(bufSize != payload) return nullptr;
        }
        
        if(pending4) {
            payload = ((buf.buffer[0]&0xff)<<24)|((buf.buffer[1]&0xff)<<16)|((buf.buffer[2]&0xff)<<8)|((buf.buffer[3]&0xff));
            pending4 = false;
            //printf("--- payload: %d\n", payload);
            if(!readSome(payload - bufSize)) return nullptr;
        }
        
        if(payload == bufSize) {
            packet.start(buf, 0);
            pending4 = true;
            payload = 4;
            bufSize = 0;
            return &packet;
        }
        return nullptr;
    }
    
    void flush() {
        while(qHead) {
            if(qHead->sentPtr >= qHead->ptr) {
                JdwpPacket *p = qHead;
                qHead = qHead->next;
                delete p;
                continue;
            }
            size_t written = write(fd, qHead->buffer.buffer+qHead->sentPtr, qHead->ptr - qHead->sentPtr);
            if(written < 0) {
                fd = 0;
                return;
            }
            qHead->sentPtr += written;
            if(qHead->sentPtr >= qHead->ptr) {
                JdwpPacket *p = qHead;
                qHead = qHead->next;
                delete p;
            }
        }
        
        if(!qHead) qTail = nullptr;

    }
};


#endif /* jdwp_hpp */

#endif
