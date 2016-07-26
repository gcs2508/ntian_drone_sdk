#ifndef ___NTIAN_TCP_H__
#define ___NTIAN_TCP_H__

#include <api/ntian_sdk_connect.h>
#include <api/ntian_sdk_api.h>
#include <utils/tcp/tcp.h>

enum {
	TNET_STACK_ERROR = 1,
	TNET_NOT_VALID,
	TNET_ADDR_ERROR,
};


int tcp_init(NTIAN_INIT_PARAMS params);
int tcp_send_message(int fd,const void *buf,int size);
int tcp_recv_message(int fd,void *buf,int size);






#endif
