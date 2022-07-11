/*	Simple udp sender.  */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#if !defined(_MSC_VER)
#include <unistd.h>
#include <fcntl.h>
#endif

#ifdef __WIN32__
#include <winsock2.h>
#include <ws2tcpip.h>
#define inet_aton(str, addr)	inet_pton(AF_INET, (str), (addr))
#else
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif

int main(int argc, char** argv)
{
	/* Config */
	char* addr = "127.0.0.1";
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
		perror("socket");
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

	/* Send 3 messages */
	puts("Sending 3 messages:");
	for (int i = 1; i <= 3; ++i) {

		/* Create the message */
		char buf[16];
		snprintf(buf, sizeof(buf), "Hi, there %d", i);
		size_t sz = strlen(buf);

		/* Send */
		printf("  Sending message \"%s\"\n", buf);
		int s = (int)sendto(fd, buf, strlen(buf), 0,
			(struct sockaddr*)&sock_addr, sizeof sock_addr);
		if (s != (int)sz) {
			if (s == -1) {
				perror("sendto()");
			} else {
				fprintf(stderr, "Problem: Expected to send "
				  "%zu bytes, actually sent %d.\n", sz, s);
			}
			return 1;
		}

		/* Wait a little */
#ifdef WIN32
		Sleep(1000);
#else
		sleep(1);
#endif
	}
	puts("Done.");
	close(fd);

	return 0;
}
