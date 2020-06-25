//
// Created by mustafa on 2020-05-18.
//

#include <jni.h>
#include <string.h>
#include "vm.h"
#include "miniz.h"
#include <android/log.h>

VM *gamaVM;
JavaVM *androidJavaVM;
JNIEnv *getJNIEnv() {
    static JNIEnv * env;
    int getEnvStat = androidJavaVM->GetEnv((void**)&env, JNI_VERSION_1_4);
    if (getEnvStat == JNI_EDETACHED) {
        if (androidJavaVM->AttachCurrentThread(&env, 0) != 0) {
            //fatal!!
        }
    }
    return env;
}

//JNIEnv *ENV;
extern "C" JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    androidJavaVM = vm;
    return  JNI_VERSION_1_4;
}

extern "C" void *__platform_read_file(const char* path, int *size) {
    JNIEnv *ENV = getJNIEnv();
    jclass cls = ENV->FindClass("digiplay/MainActivity");
    jmethodID mth = ENV->GetStaticMethodID(cls, "readFile", "(Ljava/lang/String;)[B");
    jstring str = ENV->NewStringUTF( path );
    jbyteArray array = (jbyteArray)ENV->CallStaticObjectMethod(cls, mth, str);
    ENV->DeleteLocalRef(str);
    if (array==NULL)
    {
        return NULL;
    }

    jint len = ENV->GetArrayLength(array);
    jbyte* data = ENV->GetByteArrayElements(array, NULL);
    if (data != NULL && len > 0) {
        char* buffer = new char[len];
        memcpy((void*)buffer, (void*)data, len);
        ENV->ReleaseByteArrayElements(array, data, JNI_ABORT);
        *size = len;
        return buffer;
    }

    return NULL;
}

extern "C" void *read_class_file(JCHAR *name, int len) {
    int jarSize;
    void *jar = NULL;
    if(!jar) jar = __platform_read_file("boot.jar", &jarSize);
    if(!jar) return NULL;

    char tmp[512];
    char *str = tmp;
    mz_zip_archive zip = {0};
    if(mz_zip_reader_init_mem(&zip, jar, jarSize, 0) == MZ_FALSE) {
        free(jar);
        return NULL;
    }
    memcpy(str, jchar_to_ascii(name, len), len);
    str += len;
    memcpy(str, ".class", 6);
    len += 6;
    tmp[len] = 0;
    //sprintf(str, ".class");
    int file_index = mz_zip_reader_locate_file(&zip, tmp, NULL, 0);//
    mz_zip_archive_file_stat file_stat = {0};
    if (!mz_zip_reader_file_stat(&zip, file_index, &file_stat)) {
        free(jar);
        return NULL;
    }
    size_t uncompressed_size = (size_t) file_stat.m_uncomp_size;
    void *p = mz_zip_reader_extract_file_to_heap(&zip, file_stat.m_filename, &uncompressed_size, 0);
    if (!p) {
        free(jar);
        return NULL;
    } else {
        void *ret = malloc(uncompressed_size);
        memcpy(ret, p, uncompressed_size);
        mz_free(p);
        free(jar);
        return ret;
    }

    return NULL;
}

Object *digiplayPlatformStepMethod = NULL;
/*
extern "C" void Java_digiplay_Platform_run(VM *vm, Object *method, VAR *args) {
    digiplayPlatformStepMethod = resolve_method(vm, (JCHAR*)L"digiplay/Platform",17, (JCHAR*)L"step",4, (JCHAR*)L"()V", 3);
    JNIEnv *ENV = getJNIEnv();
    jclass cls = ENV->FindClass("digiplay/MainActivity");
    jmethodID mth = ENV->GetStaticMethodID(cls, "platformRun", "()V");
    ENV->CallStaticVoidMethod(cls, mth);
}
*/
extern "C" void java_lang_System_SystemOutStream_printImpl(VM *vm, Object *method, VAR *args) {
    if(!args[0].O) return;
    __android_log_print(ANDROID_LOG_INFO, "GamaVM", "%s", string_to_ascii(args[0].O));
}

extern "C" JNIEXPORT void JNICALL
Java_digiplay_MainActivity_gamaVMMain(
        JNIEnv *env,
        jclass /* this */) {

    gamaVM = vm_init();
    vm_main(gamaVM, (char*)"Main", (char*)"main", (char*)"()V");
    digiplayPlatformStepMethod = resolve_method(gamaVM, gamaVM->sysClassLoader, (JCHAR*)L"digiplay/Platform",17, (JCHAR*)L"step",4, (JCHAR*)L"()V", 3);
}

extern "C" JNIEXPORT void JNICALL
Java_digiplay_MainActivity_platformResize(
        JNIEnv *env,
        jclass /* this */, jint width, jint height) {
    Object *resize_method = resolve_method(gamaVM, gamaVM->sysClassLoader, (JCHAR*)L"digiplay/Platform",17, (JCHAR*)L"resize",6, (JCHAR*)L"(II)V", 5);
    VAR vargs[2] = {
            { .I = width },
            { .I = height },
    };
    CALLVM_V(gamaVM, resize_method, &vargs[0]);

}


extern "C" JNIEXPORT void JNICALL
Java_digiplay_MainActivity_platformStep(
        JNIEnv *env,
        jclass /* this */) {
    CALLVM_V(gamaVM, digiplayPlatformStepMethod, NULL);
}

extern "C" JNIEXPORT void JNICALL
Java_digiplay_MainActivity_completeCompletable(
        JNIEnv *env,
        jclass /* this */,
        jlong gamaHandle, jbyteArray response) {

    Object *target = (Object*)gamaHandle;
    gc_unprotect(gamaVM, target);

    static int methodIndex = -1;
    if(methodIndex == -1) {
        Object *m = resolve_method(gamaVM, gamaVM->sysClassLoader, (JCHAR*)L"digiplay/Completable",20, (JCHAR*)L"complete",8, (JCHAR*)L"(JI)V",5);
        if(!m) return;
        methodIndex = MTH(m, iTableIndex);
    }

    jbyte *data = NULL;
    int length = 0;
    void *buffer = NULL;

    if(response != NULL) {
        length = env->GetArrayLength(response);
        buffer = malloc(length);
        env->GetByteArrayRegion(response, 0, length, (jbyte*)buffer);
    }

    Object *method = CLS(target->cls, itable)[methodIndex];
    VAR args[3] = {{.O = target}, {.J = (JLONG)buffer}, {.I = length}};
    CALLVM_V(gamaVM, method, &args[0]);
}


extern "C" JNIEXPORT void JNICALL
Java_digiplay_MainActivity_protectGamaVMObject(
        JNIEnv *env,
        jclass /* this */, jlong handle) {
    gc_protect(gamaVM, (Object*)handle);
}

