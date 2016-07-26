#include <tsk.h>
#include <utils/list/list.h>



messages_list_t *message_list_create() {


	messages_list_t *list;

	list = (messages_list_t *)malloc(sizeof(*list));
	if(tsk_null == list) {

		return tsk_null;
	}

	list->data = tsk_null;
	list->next = list;
	list->prev = list;

	return list;
}

int list_push_msg(messages_list_t *list,const void *data) {

	messages_list_t *item;

	item = (messages_list_t *)malloc(sizeof(*item));
	if(tsk_null == item) {

		return -1;
	}

	item->data = data;

	/* queue add */
	item->next = list;
	item->prev = list->prev;
	list->prev = item;
	list->prev->next = item;

	return 0;
}

int list_push_head_msg(messages_list_t *list,const void *data) {

	messages_list_t *item;

	item = (messages_list_t *)malloc(sizeof(*item));
	if(tsk_null == item) {

		return -1;
	}

	item->data = data;
	item->prev = list;
	item->next = list->next;
	list->next = item;
	list->next->prev= item;

	return 0;
}

void * list_pop_msg(messages_list_t *list) {

	void *data;
	messages_list_t *item;

	if((list->next == list) && (list->prev == list)) {

		return tsk_null;
	}

	item = list->next;
	data = item->data;

	list->next = item->next;
	list->next->prev = list;
	free(item);

	return data;
}

int message_list_destory(messages_list_t *list) {

	messages_list_t *item = list->next;		
	messages_list_t *item_temp = item;		

	while(item != list) {

		free(item->data);
		item->prev->next = item->next;
		item->next->prev = item->prev;
		item = item->next;
		free(item_temp);
	}

	free(list);

	return 0;
}





