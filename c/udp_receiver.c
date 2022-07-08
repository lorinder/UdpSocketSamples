/*	Simple UDP receiver */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef __WIN32__
#include <winsock2.h>
#include <ws2tcpip.h>
#define inet_aton(str, addr)	inet_pton(AF_INET, (str), (addr))
#else
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <arpa/inet.h>
#endif

#define CSNIP_SHORT_NAMES
#include <csnip/clopts.h>
#include <csnip/log.h>
#include <csnip/mem.h>
#include <csnip/time.h>

#define CSNIP_LOG_COMPONENT		"udp_receiver"

int main(int argc, char** argv)
{
	/* Default settings */
	char* addr = "0.0.0.0";
	int port = 4321;
	size_t bufsize = 65536;

	/* Scan command line arguments */
	clopts opts = {
		.description = "Simple UDP receiver app."
	};
	clopts_add_defaults(&opts);

	clopts_Addvar(&opts, 'p', "port", "Receive end port", &port, _);
	clopts_Addvar(&opts, 'b', "bind", "Bind address", &addr, _);
	clopts_Addvar(&opts, 'S', "buf-size", "Packet buffer size", &bufsize, _);
	if(clopts_process(&opts, argc - 1, argv + 1, NULL, true) != 0) {
		return 1;
	}

	/* Initialize winsock */
#ifdef __WIN32__
	{
		static WSADATA wsaData;
		int res = WSAStartup(MAKEWORD(2,2), &wsaData);
		if (res != 0) {
			fprintf(stderr, "WSAStartup failed: %d\n", res);
			return 1;
		}
	}
#endif

	/* Create the socket */
	int fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (fd == -1) {
		log_Perror(LOG_PRIO_ERR,  "socket()");
		return 1;
	}

	/* Create the address */
	struct in_addr ia;
	if (inet_aton(addr, &ia) < 0) {
		log_Perror(LOG_PRIO_ERR, "inet_aton()");
		return 1;
	}
	struct sockaddr_in sock_addr = {
		.sin_family = AF_INET,
		.sin_port = htons(port),
		.sin_addr = ia,
	};

	/* Bind */
	if (bind(fd, (struct sockaddr*)&sock_addr, sizeof(sock_addr)) < 0)
	{
		log_Perror(LOG_PRIO_ERR, "bind()");
		return 1;
	}


	/* receiver buffer allocation */
	char* payload;
	mem_Alloc(bufsize, payload, _);

	/* Recv loop */
	while (1) {
		/* Receive data */
		ssize_t s = recv(fd, payload, bufsize, 0);
		if (s < 0) {
			log_Perror(LOG_PRIO_ERR, "recv()");
			break;
		}

		/* Report */
		printf("Received a packet of size %zd\n", s);
	}

	return 0;

}
