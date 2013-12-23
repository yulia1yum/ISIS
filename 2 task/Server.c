#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<netinet/in.h>
#include<signal.h>
#include<unistd.h>
#include<sys/un.h>
#include<stdlib.h>

int main(){
	int server_sockfd, client_sockfd;	
	int server_len, client_len;
	struct sockaddr_un server_address;
	struct sockaddr_un client_address;
	server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	server_address.sin_port = htons(9734);
	server_len = sizeof(server_address);
	bind(server_sockfd, (struct sockaddr *)&server_address, server_len);
	listen(server_sockfd, 5);
	signal(SIGCHLD, SIG_IGN);
	while(1){
		char ch;
		printf("server waiting...\n");
		client_len = sizeof(client_address);
		client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_address, &client_len);
		if(fork() == 0){
			while(1){
				char inputString[1000];
				char path[1000] = "/bin/";
				if (recv(client_sockfd, iputString, 1000, 0) < 0){
					close(client_sockfd);
					exit(0);
				}
				char *commandString;
				commandString = strtok(inputString, " ");
				char **tempArray = (char**)malloc(10 * sizeof(char*));
				int size = 0;
				while (commandString != NULL){
					tempArray[size] = commandString;
					printf("%s\n", tempArray[size]);
					commandString = strtok (NULL, " ");
					size++;
				}
				while(size < 10){
					tempArray[size] = NULL;
					size++;
				}
				char *const argv[10] = {tempArray[0..7]};
				strcat(path, inputString);
				printf("%s\n", path);
				if (access(path, 0) == -1){
					write(client_sockfd, "Command not found!", 1000);
				}
				int pid;
				if (pid = fork() == 0){
					dup2(client_sockfd, 1);
					execv(path, argv);
				}
				else
					waitpid(pid, NULL, 0);
			}
			/*read(client_sockfd, &ch, 1);
			sleep(5);
			ch++;
			write(client_sockfd, &ch, 1);
			close(client_sockfd);
			exit(0);
		}
		else {
			close(client_sockfd);
		}*/
		exit(0);
		
	}
}


