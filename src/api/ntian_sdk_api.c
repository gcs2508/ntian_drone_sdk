/* include the tinyASK */
#include <tsk.h>

#include <api/ntian_sdk_api.h>
#include <api/ntian_sdk_connect.h>

extern normal_connect_api_t *mavlink_normal_api;


NTIAN_SDK_API int ntian_sdk_init(NTIAN_INIT_PARAMS params) {

	int error = -1;

	switch (params.type) {

		case NTIAN_TRANSPORT_TYPE_USB:
		case NTIAN_TRANSPORT_TYPE_TCPSERVER:
		case NTIAN_TRANSPORT_TYPE_BT:
		case NTIAN_TRANSPORT_TYPE_XBEE:
		case NTIAN_TRANSPORT_TYPE_UDP:
			error = -1;	
			break;
		case NTIAN_TRANSPORT_TYPE_SERIAL :
			/* create the uart connect */
//			serial_init(params.param_info.serial.baud_rate);
			break;
		case NTIAN_TRANSPORT_TYPE_TCP:
			/* create the tcp connect */
			error = tcp_init(NTIAN_INIT_PARAMS params);
			if(error < 0) {
				/* Logger can't connect the server */
			}

			mavlink_normal_api = get_tcp_api();
			if(NULL == mavlink_normal_api) {
				/* Logger can't get the api */
			//	tcp_uninit();
			}

			break;
		default:
			error = -1;
			break;
	}

	return error;
}





