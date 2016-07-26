#include <api/ntian_sdk_api.h>
#include <tsk.h>



static int test_timer_callback(void * arg,tsk_timer_id_t timer_id) {


	printf("timer handler !\n");
	return 0;
}


int main() {


	tsk_timer_mgr_global_start();

	tsk_timer_mgr_global_schedule(1000,test_timer_callback,tsk_null);

	tsk_thread_sleep(40000);
	

	tsk_timer_mgr_global_unref(tsk_null);


	return 0;

}



