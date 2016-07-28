#include <utils/timer/timer.h>
#include <tsk.h>

/**************************************
 * function: global_timer_init
 * return : Error -1,OK:0 
 ************************************/
int ntian_global_timer_init() {

	tsk_timer_mgr_global_ref();
	tsk_timer_mgr_global_start();
}

/**************************************
 * function: ntian_global_timer_uninit
 * return : void
 ************************************/
void ntian_global_timer_uninit() {
	
	tsk_timer_mgr_global_unref(tsk_null);
}	

/**************************************
 * function:register_callback 
 * param (in):msg_data 
 * param (in): func(call_back)
 * return : Error:-1,OK:0 
 ************************************/
int register_timer_callback(ntian_timer_t *msg_data,tsk_timer_callback_f call_back) {

	msg_data->id = tsk_timer_mgr_global_schedule(msg_data->timeout,call_back,(void*)msg_data->msg);
	return 0;
}




