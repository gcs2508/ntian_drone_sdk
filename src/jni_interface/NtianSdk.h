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
JNIEXPORT void JNICALL Java_com_jni_Ntian_initSdk(JNIENV *env,jobject obj,jobject params);
JNIEXPORT void JNICALL Java_com_jni_Ntian_connectDrone(JNIENV *env,jobject obj,jint comid);
JNIEXPORT void JNICALL Java_com_jni_Ntian_ChangeMode(JNIENV *env jobject obj,jint mode);

/*********************************************
 * Class : Java_com_jni_Ntian
 * Method: Jni APIs
 * Signature:()V
 ********************************************/
JNIEXPORT void JNICALL Java_com_jni_Ntian_unInitSdk(JNIENV *env jobject obj);

/*********************************************
 * Class : Java_com_jni_Ntian
 * Method: Jni APIs
 * Signature:(DDD)V
 ********************************************/
JNIEXPORT void JNICALL Java_com_jni_Ntian_FollowMe(JNIENV *env jobject obj,jdouble lat,jdouble lon ,jdouble alt);


#ifdef __cpusplus
}
#endif 
#endif

