/* include the tinyASK */
#include <tsk.h>

#include <api/ntian_sdk_api.h>
#include <api/ntian_sdk_connect.h>
#include <utils/list/list.h>
#include <utils/timer/timer.h>

normal_connect_api_t *mavlink_normal_api = NULL;
messages_list_t *list_queue = NULL;
tsk_condwait_handle_t * list_queue_condwait;
void * tx_thread,*rx_thread;


static int timer_heartbeart_callback(const void *arg, tsk_timer_id_t timer_id) {

	ntian_timer_t *heart_beart_timer = (ntian_timer_t *)arg;
	printf("timer_hander !\n");

	tsk_timer_mgr_global_schedule(heart_beart_timer->timeout,timer_heartbeart_callback,arg);
//	register_timer_callback(heart_beart_timer,heart_beart_timer->timer_func);
}

static void * rx_message_threadfun(void * arg) {


//	printf("rx_message_threadfunc!\n");
	return tsk_null;
}

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


/*NTIAN_SDK_API*/ void init_connect_drone(int comid) {

	ntian_timer_t heart_beart_timer;

	list_queue = message_list_create();
	if(NULL == list_queue) {
		/* no memory error */
	}

	ntian_global_timer_init();	
	list_queue_condwait = tsk_condwait_create();
	heart_beart_timer.condwait = list_queue_condwait;
	heart_beart_timer.msg = tsk_null;
	heart_beart_timer.timeout = 1000;
	heart_beart_timer.timer_func = timer_heartbeart_callback;

	heart_beart_timer.id = tsk_timer_mgr_global_schedule(heart_beart_timer.timeout,timer_heartbeart_callback,&heart_beart_timer);
//	register_timer_callback(&heart_beart_timer,heart_beart_timer.timer_func);

	tsk_thread_create(&rx_thread,rx_message_threadfun,list_queue_condwait);
//	tsk_thread_create(&tx_thread,tx_message_threadfun,list_queue_condwait);

	tsk_thread_sleep(10000);
	tsk_thread_join(&rx_thread);
}


/*NTIAN_SDK_API*/ void uninit_sdk() {

//	tsk_thread_join(&tx_thread);
//	tsk_thread_join(&rx_thread);

}

/*NTIAN_SDK_API*/ void ntian_changemode(int mode) {


}

/*NTIAN_SDK_API*/ void ntian_follow_me(double lat,double lon ,int alt) {


}


