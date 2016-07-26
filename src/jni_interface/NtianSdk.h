#include <jni.h>

#ifndef _Include_com_Ntian_sdk_API
#define _Include_com_Ntian_sdk_API


#ifdef __cpusplus
extern "C" {
#endif

/*********************************************
 * Class : Java_com_jni_Ntian
 * Method: Jni APIs
 * Signature:(I)V
 ********************************************/
JNIEXPORT void JNICALL Java_com_jni_Ntian_initSdk(JNIEnv *env,jobject obj,jint type);
JNIEXPORT void JNICALL Java_com_jni_Ntian_connectDrone(JNIEnv *env,jobject obj,jint comid);
JNIEXPORT void JNICALL Java_com_jni_Ntian_ChangeMode(JNIEnv *env,jobject obj,jint mode);

/*********************************************
 * Class : Java_com_jni_Ntian
 * Method: Jni APIs
 * Signature:()V
 ********************************************/
JNIEXPORT void JNICALL Java_com_jni_Ntian_unInitSdk(JNIEnv *env ,jobject obj);

/*********************************************
 * Class : Java_com_jni_Ntian
 * Method: Jni APIs
 * Signature:(DDD)V
 ********************************************/
JNIEXPORT void JNICALL Java_com_jni_Ntian_FollowMe(JNIEnv *env ,jobject obj,jdouble lat,jdouble lon ,jdouble alt);


#ifdef __cpusplus
}
#endif 
#endif

