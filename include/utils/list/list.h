#ifndef ___NTIAN_LIST_H___
#define ___NTIAN_LIST_H___

typedef struct ntian_msgs_list {
	
	struct ntian_msgs_list *next;
	struct ntian_msgs_list *prev;
	void *data;
}messages_list_t;

messages_list_t *message_list_create();
int list_push_msg(messages_list_t *list,const void *data);
int list_push_head_msg(messages_list_t *list,const void *data);
void *list_pop_msg(messages_list_t *list);

int message_list_destory(messages_list_t *list);


#endif
