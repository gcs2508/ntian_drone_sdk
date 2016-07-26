#ifndef ___NTIAN_SDK_API_H____
#define ___NTIAN_SDK_API_H____

#include <api/ntian_sdk_connect.h>
#include <stdio.h>

/*
#ifdef NTIAN_EXPROTS
	#define NTIAN_SDK_API __declspec(dllexport)
#else
	#ifdef NTIAN_IMPORTS
		#define NTIAN_SDK_API __declspec(dllimport)
	#else
		#ifdef TARGET_OS_IPHONE
			#define NTIAN_SDK_API extern "C"
		#else 
			#define NTIAN_SDK_API 
		#endif
	#endif 
#endif
*/
#ifndef SERIAL_BAUD 	
	#define SERIAL_BAUD 115200
#endif

#ifndef IP_ADDRESS	
	#define  IP_ADDRESS "192.168.1.18"
#endif 
#ifndef IP_PORT
	#define IP_PORT 5050
#endif 


typedef enum NTIAN_RETURN_VALUE {
	NTIANSDK_SUCCESS = 0,
	NTIANSDK_FAILED = 1,
} NTIAN_RETURN_VALUE;

typedef enum NTIAN_CONNECT_TYPE {
	NTIAN_TRANSPORT_TYPE_SERIAL = 0,
	NTIAN_TRANSPORT_TYPE_USB,
	NTIAN_TRANSPORT_TYPE_UDP,
	NTIAN_TRANSPORT_TYPE_TCP,
	NTIAN_TRANSPORT_TYPE_TCPSERVER,
	NTIAN_TRANSPORT_TYPE_BT,
	NTIAN_TRANSPORT_TYPE_XBEE,
} NTIAN_CONNECT_TYPE;

typedef struct ntian_serial_params {
	int baud_rate;	
//	8 N 1
}ntian_serial_params;

////not used not define
typedef struct ntian_usb_params {
	/* to be learning more lessons about on-the-go */
}ntian_usb_params;

typedef struct ntian_net_params {
	int net_type;
	int port;
	char ip_address[16];
}ntian_net_params;

typedef struct NTIAN_INIT_PARAMS {
	union {
		ntian_net_params  net;
		ntian_serial_params serial;
	} param_info;
	unsigned char type;
} NTIAN_INIT_PARAMS;

//normal_connect_api_t *mavlink_normal_api = NULL;

/***********************************************
 * function: ntian_sdk_init
 * param (in) : type  
 * return (I) : Error :-1, OK : 0 
 **********************************************/
/*NTIAN_SDK_API*/int ntian_sdk_init(NTIAN_INIT_PARAMS params);

/***********************************************
 * function: ntian_msg_add_queue
 * param (in) : command	
 * param (in) : void *msg 
 * return (I) : Error :-1, OK : 0 
 **********************************************/
/*NTIAN_SDK_API */int ntian_msg_add_queue(int command,void *msg);
/*NTIAN_SDK_API*/ void init_connect_drone(int comid);


/***********************************************
 * function: ntian_msg_
 * param (in) : command	
 * param (in) : void *msg 
 * return (I) : Error :-1, OK : 0 
 **********************************************/
//NTIAN_SDK_API int ntian_msg_add_queue(int command,void *msg);




#endif 
