#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>

#define PORT 9000

char buffer[BUFSIZ] = "hello, world!";

main()
{
	int c_socket, s_socket;
	struct sockaddr_in s_addr, c_addr;
	int len;
	int n;

	s_socket = socket(PF_INET, SOCK_STREAM, 0);

	memset(&s_addr, 0, sizeof(s_addr));
	s_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	s_addr.sin_family = AF_INET;
	s_addr.sin_port = htons(PORT);
	
	if(bind(s_socket, (struct sockaddr *) &s_addr, sizeof(s_addr)) == -1) {
		printf("Can not Bind\n");
		return -1;
	}
	if(listen(s_socket, 5) == 1) {
		printf("listen Fail\n");
		return -1;
	}

	while(1) {
		int len2;
		len = sizeof(c_addr);
		c_socket = accept(s_socket, (struct sockaddr*) &c_addr, &len);
		n = strlen(buffer);
		len2 = write(c_socket, buffer, n);
		printf("%d\n", len2);

		close(c_socket);
	}

	close(s_socket);
}
