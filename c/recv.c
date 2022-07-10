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
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <arpa/inet.h>
#endif

int main(int argc, char** argv)
{
	/* Default settings */
	char* addr = "0.0.0.0";
	int port = 4321;

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
		perror("socket()");
		return 1;
	}

	/* Create the address */
	struct in_addr ia;
	if (inet_aton(addr, &ia) < 0) {
		perror("inet_aton()");
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
		perror("bind()");
		return 1;
	}

	/* Recv loop */
	puts("Awaiting 3 messages:");
	char buf[8192];
	for (int i = 0; i < 3; ++i) {
		/* Receive data */
		int s = (int)recv(fd, buf, (sizeof buf) - 1, 0);
		if (s < 0) {
			perror("recv()");
			return 1;
		}
		buf[s] = '\0';

		/* Report */
		printf("  Received \"%s\"\n", buf);
	}

	close(fd);
	return 0;
}
