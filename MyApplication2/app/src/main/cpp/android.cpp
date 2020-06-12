//
// Created by mustafa on 2020-05-18.
//

#include <jni.h>
#include <string.h>

extern JNIEnv *ENV;

extern "C" void *__platform_read_file(const char* path, int *size) {
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