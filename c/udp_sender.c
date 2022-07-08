/*	Simple udp sender.  */

#include <assert.h>
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
#include <csnip/util.h>

#define CSNIP_LOG_COMPONENT		"udp_sender"

int main(int argc, char** argv)
{
	/* Default settings */
	char* addr = "127.0.0.1";
	int port = 4321;
	int pktsize = 1280;

	/* Scan command line arguments */
	clopts opts = {
		.description = "UDP packet sender"
	};
	clopts_add_defaults(&opts);

	clopts_Addvar(&opts, 'p', "port", "Destination port", &port, _);
	clopts_Addvar(&opts, 'd', "destination", "Destination address", &addr, _);
	clopts_Addvar(&opts, 's', "pkt-size", "Packet size", &pktsize, _);
	if (clopts_process(&opts, argc - 1, argv + 1, NULL, true) != 0) {
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

	/* Buffer allocation */
	char* payload;
	mem_Alloc(pktsize, payload, _);
	for (int i = 0; i < pktsize; ++i) {
		payload[i] = i;
	}

	/* Recv loop */
	while (1) {

		/* Send the message */
		printf("Sending packet of size %d.\n", pktsize);
		ssize_t s = sendto(fd, payload, pktsize, 0,
			(struct sockaddr*)&sock_addr, sizeof sock_addr);
		if (s != pktsize) {
			if (s == -1) {
				log_Perror(LOG_PRIO_ERR, "sendto()");
			} else {
				log_Mesg(LOG_PRIO_ERR, "Expected to send %d "
				  "bytes, actually sent %zd", pktsize, s);
			}
			return 1;
		}

		/* Wait a little */
		time_Sleep(1.0, _);
	}

	return 0;
}
