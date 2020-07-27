#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/types.h>
#include "socket.h"
#include "message.h"

int main(int argc, char *argv[]) {
  int port;
	char hostname[32];
  char usr[USRLEN];
  //Check imputs
	if (argc < 2 || argc > 3) {
		fprintf(stderr, "Usage: %s port [hostname]\n", argv[0]);
		exit(1);
	}
	if (argc == 3) {
		strncpy(hostname, argv[2], strlen(argv[2]) + 1);
	}
	else {
		strncpy(hostname, "localhost", strlen("localhost"));
	}
  //Get user
	printf("Enter your user name \nMust be less than 32 characters\n");
  fgets(usr, USRLEN, stdin);
  //Connect to server
  port = strtol(argv[1], NULL, 0);
  int peerfd;
  if ((peerfd = connect_to_server(port, hostname)) == -1){
    fprintf(stderr, "Error connecting to the gateway!\n");
    exit(1);
  }
  //Loop to send messages to server.
  int true = 1;
  fflush(stdout);
  int r = fork();
  if (r > 0) {
    while(true) {
      char message[MSGLEN];
      printf("You:\n");
      fgets(message, MSGLEN, stdin);
      char *send_buf = pack(usr, message);
      write(peerfd, send_buf, sizeof(char)*(MSGLEN+USRLEN));
      free(send_buf);
    }
  }
  else if (r == 0){
    while(true) {
      char recieve_buf[(USRLEN + MSGLEN)];
      read(peerfd, recieve_buf, sizeof(char)*(USRLEN + MSGLEN));
      char **split_buf = unpack(recieve_buf);
      printf("%s:\n %s", split_buf[0], split_buf[1]);
      printf("You:\n");
      free(split_buf[0]);
      free(split_buf[1]);
      free(split_buf);
    }
  }
  close(peerfd);
  return 0;
}
