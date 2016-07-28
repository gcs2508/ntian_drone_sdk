#include <tsk.h>
#include <tinynet.h>

#include <api/ntian_sdk_connect.h>
#include <utils/udp/udp.h>

tnet_socket_udp_t *ucp_socket;

int udp_init(NTIAN_INIT_PARAMS params) {

	int ret_val = 0;
	if(tnet_startup()) {

		return -1;
	}

	tnet_socket_type_t type;
	struct sockaddr_storage to;

	TNET_SOCKET_TYPE_SET_IPV4(type);
//	TNET_SOCKET_TYPE_SET_IPV6(type);

	TNET_SOCKET_TYPE_SET_UDP(type);

	ucp_socket = tnet_socket_create(TNET_SOCKET_HOST_ANY,TNET_SOCKET_PORT_ANY,type);
	if(!TNET_SOCKET_IS_VALID(ucp_socket)) {
		TSK_OBJECT_SAFE_FREE(ucp_socket);
		return TNET_NOT_VALID;
	}

	if(!(ret_val = tnet_sockaddr_init(params.param_info.net.ip_address,params.param_info.net.port,type,&to))) {
		ret_val = tnet_sockfd_connectto(ucp_socket->fd,(const struct socketaddr_storage *)&to);
		if(!ret_val) {
			ret_val = ucp_socket->fd;
		}
	}

	return ret_val;
}


int udp_send_message(int fd,const void *buf,int size) {

	return (int)tnet_sockfd_send(fd,buf,size,0);
} 


int udp_recv_message(int fd,void *buf,int size) {

	return (int)tnet_sockfd_recv(fd,buf,size,0);
}

int ucp_uninit() {

//	tnet_socket_close(tcp_socket);
	TSK_OBJECT_SAFE_FREE(ucp_socket);
//	tcp_socket = NULL;

	return 0;
}










