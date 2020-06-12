//
// Created by mustafa on 2020-05-18.
//

#include <jni.h>
#include <string.h>
#include "vm.h"
#include "miniz.h"

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
    jclass cls = ENV->FindClass("com/example/myapplication/MainActivity");
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
        //__android_log_print(ANDROID_LOG_INFO, \"digiplay\", \"bytearray-len is: %d\",len);
        return buffer;
    }

    return NULL;
}

extern "C" void *read_class_file(jchar *name, int len) {
    int jarSize;
    void *jar = __platform_read_file("jvm_test.jar", &jarSize);
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
        return ret;
    }

    return NULL;
}

Object *digiplayPlatform, *digiplayPlatformStepMethod;

extern "C" void Java_digiplay_Platform_run(VM *vm, Object *method, VAR *args) {
    digiplayPlatform = args[0].O;
    digiplayPlatformStepMethod = resolve_method(vm, (JCHAR*)L"digiplay/Platform",17, (JCHAR*)L"step",4, (JCHAR*)L"()V", 3);
    JNIEnv *ENV = getJNIEnv();
    jclass cls = ENV->FindClass("com/example/myapplication/MainActivity");
    jmethodID mth = ENV->GetStaticMethodID(cls, "platformRun", "()V");
    ENV->CallStaticObjectMethod(cls, mth);
}

extern "C" void java_lang_System_SystemOutStream_printImpl(VM *vm, Object *method, VAR *args) {

}

extern "C" JNIEXPORT void JNICALL
Java_com_example_myapplication_MainActivity_gamaVMMain(
        JNIEnv *env,
        jclass /* this */) {

    gamaVM = vm_init();
    vm_main(gamaVM, "Main", "main", "()V");
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_myapplication_MainActivity_platformResize(
        JNIEnv *env,
        jclass /* this */, jint width, jint height) {
    Object *resize_method = resolve_method(gamaVM, (JCHAR*)L"digiplay/Platform",17, (JCHAR*)L"resize",6, (JCHAR*)L"(II)V", 5);
    VAR vargs[3] = {
            { .O = digiplayPlatform },
            { .I = width },
            { .I = height },
    };
    CALLVM_V(gamaVM, resize_method, &vargs[0]);

}

extern "C" JNIEXPORT void JNICALL
Java_com_example_myapplication_MainActivity_platformStep(
        JNIEnv *env,
        jclass /* this */) {
    VAR args[1] = { {.O = digiplayPlatform} };
    CALLVM_V(gamaVM, digiplayPlatformStepMethod, &args[0]);
}
