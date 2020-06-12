#include <jni.h>
#include <string>
#include "vm.h"

JNIEnv *ENV;

extern "C" {
    extern int vm_test();
    extern int vm_test2();

    static int testField = 100;
    static int LINENO;

    class P {
    public:
         virtual int perf_test_val(double d, int i) {
            int *L = &LINENO;
            *L=0; return (int)d+12+i+testField;
        }

         int perf_test() {
            int *L = &LINENO;
            *L=0; int r = 0;
            *L=0; for(int k=0; k<1000000; k++) {
                *L=0; switch (k) {
                    case 0: r += 10;break;
                    case 1: r += 120;break;
                    case 10: r += 1200;break;
                    default: r += k + perf_test_val(3.5678, k);
                }
            }
            *L=0; return r;
        }

    };
    int perf_test_val(double d, int i) {
        int *L = &LINENO;
        *L=0; return (int)d+12+i+testField;
    }

    int perf_test() {
        int *L = &LINENO;
        *L=0; int r = 0;
        *L=0; for(int k=0; k<1000000; k++) {
            *L=0; switch (k) {
                case 0: r += 10;break;
                case 1: r += 120;break;
                case 10: r += 1200;break;
                default: r += k + perf_test_val(3.5678, k);
            }
        }
        *L=0; return r;
    }

    extern "C" JNIEXPORT jstring JNICALL
    Java_com_example_myapplication_MainActivity_stringFromJNI(
            JNIEnv *env,
            jobject /* this */) {
        std::string hello = "Hello from C++";
        return env->NewStringUTF(hello.c_str());
    }


    extern "C" JNIEXPORT jint JNICALL
    Java_com_example_myapplication_MainActivity_calc(
            JNIEnv *env,
            jclass /* this */,
            jint type) {

        ENV = env;
        if(type == 0)
            return vm_test();
        else if(type == 1){
            return 0;
            //P *p = new P;
            //for(int i=0; i<100; i++) p->perf_test();
        } else if(type == 2) {
            return vm_test2();
        }
        return 0;
    }
}