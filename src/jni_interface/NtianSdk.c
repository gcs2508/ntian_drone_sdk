#include <jni.h>
#include <android/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <api/ntian_sdk_api.h>
#include "NtianSdk.h"


#ifndef LOG_TAG
	#define LOG_TAG "NTIAN_LOG"
	#define LOGE(...) __android_log_printf(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
	#define LOGD(...) __android_log_printf(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#endif 

#ifdef __cpluplus
extern "C" {
#endif 

/*********************************************
 * Class : Java_com_jni_Ntian
 * Method: Jni APIs
 * Signature:()V
 ********************************************/
JNIEXPORT void JNICALL Java_com_jni_Ntian_initSdk(JNIENV *env,jobject obj,jint type) {
	
	NTIAN_INIT_PARAMS params;
	if(NTIAN_TRANSPORT_TYPE_SERIAL == type)  {
		params.type = NTIAN_TRANSPORT_TYPE_SERIAL;
		params.param_info.serial.baud_rate = SERIAL_BAUD;

		LOGD("type : serial-->%d",SERIAL_BAUD);
	} else if(NTIAN_TRANSPORT_TYPE_TCP == type) {
		params.type = NTIAN_TRANSPORT_TYPE_TCP;
		params.param_info.net.port = IP_PORT;

		params.param_info.net.ip_address = IP_ADDRESS;
		memset(params.param_info.net.ip,0,16);
		memcpy(params.param_info.net.ip_address,IP_ADDRESS,16);

		LOGD("type : tcp -->%s(%d)",params.param_info.net.ip_address,param.param_info.net.port);
	}

	ntian_sdk_init(params);
}

JNIEXPORT void JNICALL Java_com_jni_Ntian_connectDrone(JNIENV *env,jobject obj,jint comid) {


}

JNIEXPORT void JNICALL Java_com_jni_Ntian_unInitSdk(JNIENV *env jobject obj) {

}

JNIEXPORT void JNICALL Java_com_jni_Ntian_FollowMe(JNIENV *env jobject obj,jdouble lat,jdouble lon ,jdouble alt) {

}

JNIEXPORT void JNICALL Java_com_jni_Ntian_ChangeMode(JNIENV *env jobject obj,jint mode) {


}


#ifdef __cpluplus
}
#endif 







