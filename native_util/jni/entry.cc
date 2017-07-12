#include <jni.h>
/**
 * jni层的入口，在这里将Java类里面的native***函数和jni函数对应上，然后通过jni函数调用C/C++接口
 *  主要关注类型转换，注意jni没有unsigned int这种类型，需要使用jlong，对应的是long long
 *
 *  Java类型      别名　　        C++本地类型　　      字节(bit)  
 *   boolean      jboolean       unsigned char　　  8, unsigned  
 *   byte         jbyte          signed char　　　　 8  
 *   char         jchar          unsigned short　　 16, unsigned  
 *   short        jshort         short　　　         16  
 *   int          jint           long　　　　         32  
 *   long         jlong          __int64　　　　      64  
 *   float        jfloat         float　　　          32  
 *   double       jdouble        double　　　         64   
 */

/*
 * Field Desciptor	Java Language Type
 *     Z                     	boolean
 *     B                     	byte
 *     C                     	char
 *     S                     	short
 *     I                     	int
 *     J                     	long
 *     F                     	floa
 *     D                     	double
引用类型

"Ljava/lang/String;"	String
"[Ljava/lang/Object;"	Object[]

数组类型
Descriptor	Java Langauage Type
"[[I"	int[][]
"[[[D"	double[][][]
 */
#define DEBUG 1

#if DEBUG
#include <android/log.h>
#  define  LOG(x...)  __android_log_print(ANDROID_LOG_INFO,"JniExample native",x)
#else
#  define  LOG(...)  do {} while (0)
#endif
extern "C" {
#include "math.h"
}
#define NELEM(x) ((int) (sizeof(x) / sizeof((x)[0])))

jint mathAdd(JNIEnv* env,jclass,jint x,jint y){
  jint result= add(x,y);
  LOG("result=%d",result);
  return result;
}


const char kClassName[] = "org/linux/jniexample/utils/NativeUtil";
//https://wenku.baidu.com/view/379afd6b4b35eefdc8d3339c.html
const JNINativeMethod kJniMethods[]={
        {"nativeAdd","(II)I",
                (void*)mathAdd},
};

JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved) {
  JNIEnv* env = 0;
  jint ret = vm->AttachCurrentThread(&env, 0);
  LOG("JNI_OnLoad");
  if(ret!=JNI_OK){
    LOG("JNI_OnLoad failed");
  }
  jclass clazz = env->FindClass(kClassName);
  int res=env->RegisterNatives(clazz,kJniMethods,NELEM(kJniMethods));
  if(res<0){
      LOG("RegisterNatives failed,res=%d",res);
  }
  return JNI_VERSION_1_4;
}
