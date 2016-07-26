/* include the tinyASK */
#include <tsk.h>

#include <api/ntian_sdk_api.h>
#include <api/ntian_sdk_connect.h>
#include <utils/list/list.h>

normal_connect_api_t *mavlink_normal_api = NULL;
messages_list_t *list_queue = NULL;


/*NTIAN_SDK_API*/ int ntian_sdk_init(NTIAN_INIT_PARAMS params) {

	int error = -1;

	switch (params.type) {

		case NTIAN_TRANSPORT_TYPE_USB:
		case NTIAN_TRANSPORT_TYPE_TCPSERVER:
		case NTIAN_TRANSPORT_TYPE_BT:
		case NTIAN_TRANSPORT_TYPE_XBEE:
			error = -1;	
			break;
		case NTIAN_TRANSPORT_TYPE_SERIAL :
			/* create the uart connect */
//			serial_init(params.param_info.serial.baud_rate);
			break;
		case NTIAN_TRANSPORT_TYPE_TCP:
			/* create the tcp connect */
			error = tcp_init(params);
			if(error < 0) {
				/* Logger can't connect the server */
			}

			mavlink_normal_api = get_tcp_api();
			if(NULL == mavlink_normal_api) {
				/* Logger can't get the api */
				tcp_uninit();
			}

			break;

		case NTIAN_TRANSPORT_TYPE_UDP:
			/* create the udp connect */	
//			error = udp_init(params);
//			if(error < 0) {
//				/* Logger can't connect the server */
//			}
//
//			mavlink_normal_api = get_tcp_api();
//		  	if(NULL == mavlink_normal_api) 	{
//				udp_uninit();	
//			}

			break;
		default:
			error = -1;
			break;
	}

	return error;
}

static int timer_heartbeart_callback(const void * arg, tsk_timer_id_t timer_id) {


	printf("send heart beat!\n");
	return 0;

}


/*NTIAN_SDK_API*/ void init_connect_drone(int comid) {

//	list_queue = message_list_create();
//	if(NULL == list_queue) {
//		/* no memory error */
//	}

}


/*NTIAN_SDK_API*/ void uninit_sdk() {


}

/*NTIAN_SDK_API*/ void ntian_changemode(int mode) {


}

/*NTIAN_SDK_API*/ void ntian_follow_me(double lat,double lon ,int alt) {


}


