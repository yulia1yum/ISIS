#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<sys/un.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
int main()
{
	int sockfd;
	int len;
	struct sockaddr_un address;
	int result;
	char inputString[1000];
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr("127.0.0.1");
	address.sin_port = htons(9734);
	len = sizeof(address);
	result = connect(sockfd, (struct sockaddr*)&address, len);
	if(result == -1){
		perror("oops:client");
		exit(1);
	}
	while(1){
		printf("Input text: ");
		cin.getline(inputString, 1000);
		write(sockfd, inputString, 1000);
		read(sockfd, inputString, 1000);
		printf("%c\n", inputString);
	}
	/*write(sockfd, &ch, 1);
	read(sockfd, &ch, 1);
	printf("char from server = %c\n", ch);*/
	close(sockfd);
	exit(0);
}