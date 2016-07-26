#include <utils/tcp/tcp.h>
#include <utils/serial/serial.h>
#include <api/ntian_sdk_connect.h>


normal_connect_api_t *get_serial_api() {
	
//	serial_api.rx_messages = serial_read;
//	serial_api.tx_messages = serial_write;

	return &serial_api;
}

normal_connect_api_t *get_tcp_api() {

	tcp_api.rx_messages = tcp_recv_message;
	tcp_api.tx_messages = tcp_send_message;

	return &tcp_api;
}


/* zigbee And TCP server can used */
multi_connect_apis_t *get_multi_apis(int type) {


	return NULL;
}









