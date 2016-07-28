#ifndef ___NTIAN_DRONE_H__
#define ___NTIAN_DRONE_H__

#include <api/ntian_sdk_connect.h>
#include <utils/list/list.h>
#include <utils/timer/timer.h>
#include <tsk.h>

typedef struct drone {
	void *tx_thread;
	void *rx_thread;
	tsk_condwait_handle_t *list_condwait;
	messages_list_t *list_queue;	
	normal_connect_api_t *mavlink_normal_api;
	int type;
} drone_t;
























#endif
