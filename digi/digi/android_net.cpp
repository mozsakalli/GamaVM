#include <jni.h>
#include "vm.h"

extern JNIEnv *getJNIEnv();

extern "C" void Java_digiplay_Net_http(VM *vm, Object *method, VAR *args) {

}

extern "C" void Java_digiplay_Net_Http_start(VM *vm, Object *method, VAR *args) {
    if(!args[0].O || !args[1].O) {
        throw_null(vm);
        return;
    }
    /*
    gc_protect(vm, args[0].O);
    JNIEnv *ENV = getJNIEnv();
    jclass cls = ENV->FindClass("digiplay/Http");
    jmethodID mth = ENV->GetStaticMethodID(cls, "makeRequest", "(JLjava/lang/String;[B)V");

    int utfLen = get_utf8_encode_length(STRCHARS(args[1].O), STRLEN(args[1].O));
    char *utf8 = (char*)malloc(utfLen+1);
    encode_utf8(STRCHARS(args[1].O), STRLEN(args[1].O), utf8);
    utf8[utfLen] = 0;
    jstring url = ENV->NewStringUTF( utf8 );
    jbyteArray array = (jbyteArray)ENV->CallStaticObjectMethod(cls, mth, str);
    ENV->DeleteLocalRef(str);
    */

}