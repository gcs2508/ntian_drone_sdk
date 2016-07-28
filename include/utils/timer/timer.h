#ifndef ___NTIAN_TIMER_H__
#define ___NTIAN_TIMER_H__

#include <tsk.h>

typedef struct ntian_timer_s {
	tsk_timer_id_t id;
	uint64_t timeout;
	tsk_condwait_handle_t *condwait;				
	tsk_timer_callback_f timer_func;
	void *msg;
}ntian_timer_t;


/**************************************
 * function: global_timer_init
 * return : Error -1,OK:0 
 ************************************/
int ntian_global_timer_init();

/**************************************
 * function: ntian_global_timer_uninit
 * return : void
 ************************************/
void ntian_global_timer_uninit();

/**************************************
 * function:register_callback 
 * param (in):msg_data 
 * param (in): func(call_back)
 * return : Error:-1,OK:0 
 ************************************/
int register_timer_callback(ntian_timer_t *msg_data,tsk_timer_callback_f call_back);















#endif
