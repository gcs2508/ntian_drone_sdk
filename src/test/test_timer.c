#include <api/ntian_sdk_api.h>
#include <tsk.h>


static int test_timer_callback(void * arg,tsk_timer_id_t timer_id) {


	printf("timer handler !\n");
//	tsk_timer_mgr_global_schedule(1000,test_timer_callback,tsk_null);
	return 0;
}

static int test_global_timer() {

	tsk_timer_mgr_global_ref();
	tsk_timer_mgr_global_start();

	tsk_timer_mgr_global_schedule(1000,test_timer_callback,tsk_null);

	tsk_thread_sleep(40000);
	
	tsk_timer_mgr_global_unref(tsk_null);

	return 0;
}

static int test_single_timer() {

	tsk_timer_manager_handle_t * handler = tsk_timer_manager_create();

	tsk_timer_manager_start(handler);
	tsk_timer_manager_schedule(handler,1000,test_timer_callback,tsk_null);

	tsk_thread_sleep(40000);

	TSK_OBJECT_SAFE_FREE(handler);

	return 0;
}

int main() {

	test_single_timer();
	return 0;

}



