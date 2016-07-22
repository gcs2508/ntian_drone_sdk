#ifndef __NTIAN_SDK_CONNECT_H
#define __NTIAN_SDK_CONNECT_H

typedef struct normal_connect_api{

	int (*rx_messages)(int fd,char *rx_buffer,int size);
	int (*tx_messages)(int fd,char *tx_buffer,int size);

}normal_connect_api_t;


typedef struct multi_connect_apis {
	
	/* not think all right */

}multi_connect_apis_t;


static normal_connect_api_t serial_api;
static normal_connect_api_t tcp_api;


normal_connect_api_t *get_serial_api();
normal_connect_api_t *get_tcp_api();
multi_connect_apis_t *get_multi_apis(int type);

#endif 
