#ifndef ____NTIAN_UDP_H__
#define ____NTIAN_UDP_H__

#include <utils/tcp/tcp.h>





int udp_init(NTIAN_INIT_PARAMS params);
int udp_send_message(int fd, const void *buf,int size);
int udp_recv_message(int fd,void * buf,int size);










#endif

