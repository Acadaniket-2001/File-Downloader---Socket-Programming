/*				THE CLIENT PROCESS

	Please read the file server.c before you read this file. To run this,
	you must first change the IP address specified in the line:

		serv_addr.sin_addr.s_addr = inet_addr("144.16.202.221");

	to the IP-address of the machine where you are running the server.
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <string.h>

int main()
{
	int i, sockfd;
	char buf[100];
	struct sockaddr_in sa;

	/* Opening a socket is exactly similar to the server process */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	/* Recall that we specified INADDR_ANY when we specified the server
	address in the server. Since the client can run on a different
	machine, we must specify the IP address of the server.

	TO RUN THIS CLIENT, YOU MUST CHANGE THE IP ADDRESS SPECIFIED
	BELOW TO THE IP ADDRESS OF THE MACHINE WHERE YOU ARE RUNNING
	THE SERVER.*/
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = inet_addr("127.0.0.1"); // Loop back IP address
	sa.sin_port = 60018;

	/* With the information specified in serv_addr, the connect()
	system call establishes a connection with the server process.*/

	int x = sizeof(sa);
	i = connect(sockfd, (struct sockaddr *)&sa, x);

	/* After connection, the client can send or receive messages.
	However, please note that recv() will block when the
	server is not sending and vice versa. Similarly send() will
	block when the server is not receiving and vice versa. For
	non-blocking modes, refer to the online man pages.*/

	// for (i = 0; i < 100; i++)
	// 	buf[i] = '\0';
	// recv(sockfd, buf, 100, 0);
	// printf("%s\n", buf);

	memset(buf, '\0', 100);
    
    // accepting : "list"
    printf("Enter the command : ");
	// strcpy(buf, "list");
    scanf("%s", buf);
    send(sockfd, buf, 100, 0);
    
    // receiving the file name list
	recv(sockfd, buf, 100, 0);
    printf("%s\n", buf);

    // reading and sending file name to be downloaded
    printf("Enter the file name to download : ");
	memset(buf, '\0', 100);
    scanf("%s", buf);
    send(sockfd, buf, 100, 0);

	printf("Downloading...0\n");
    printf("Downloading...50\n");

    FILE *file;
    char filename = "downloaded";
    // char content[1000];

    // Create a new file in write mode
    file = fopen(filename, "w");
    if (file == NULL) {
        printf("Failed to create the file.\n");
        return 1;
    }

    // printf("Enter the content (max 1000 characters):\n");
    // scanf(" %[^\n]", content);

    // Write the content to the file
    fprintf(file, "%s", buf);

    // Close the file
    fclose(file);

	printf("Downloading...100\n");
	close(sockfd);
	return 0;
}
