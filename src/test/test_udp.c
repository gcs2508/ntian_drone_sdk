#include <api/ntian_sdk_connect.h>

#include <utils/tcp/tcp.h>
#include <utils/udp/udp.h>

int main() {

	int fd;
	NTIAN_INIT_PARAMS params;
	int size;
	int n = 110;

	memcpy(params.param_info.net.ip_address,"127.0.0.1",10);
	params.param_info.net.port = 9999;

	printf("a!\n");
	fd = udp_init(params);

	char buf[32];
	while(n--) {
		memset(buf,0,32);
		sprintf(buf,"hello!!!!!");
		udp_send_message(fd,buf,strlen(buf));

		sleep(1);
		size = udp_recv_message(fd,buf,32);
		if(size > 0) {
			buf[size + 1] = '\0';
			printf("recv size : %d ,%s\n",size , buf);
		}
	}

	return 0;
}





