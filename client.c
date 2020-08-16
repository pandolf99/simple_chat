#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/types.h>
#include "socket.h"
#include "message.h"
#include "sig_hand.h"

int main(int argc, char *argv[]) {
  int port;
	char hostname[32];
  //Check imputs
	if (argc < 2 || argc > 3) {
    fprintf(stderr, "Usage: %s port [hostname]\n", argv[0]);
		exit(1);
	}
	if (argc == 3) {
    if (strlen(argv[2]) > 31) {
      fprintf(stderr, "Error: Hostname is too long");
      exit(1);
    }
		strncpy(hostname, argv[2], strlen(argv[2]) + 1);
	}
	else {
		strncpy(hostname, "localhost", strlen("localhost") + 1);
	}
  //Get user
	printf("Enter your user name \nMust be less than 32 characters\n");
  char *temp_usr = malloc(sizeof(char)*USRLEN);
  fgets(temp_usr, USRLEN, stdin); //TODO: check if usr is USRLEN or less
  int usr_len = strlen(temp_usr) + 1;
  char usr[usr_len];
  strncpy(usr, temp_usr, sizeof(char)*usr_len);
  usr[strlen(usr) - 1] = '\0';
  free(temp_usr);
  //Connect to server
  port = strtol(argv[1], NULL, 0);
  int peerfd;
  if ((peerfd = connect_to_server(port, hostname)) == -1){
    fprintf(stderr, "Error connecting to the gateway!\n");
    exit(1);
  }
  //Call handler to exit safely
  sig_action(peerfd);

  int true = 1;
  int r = fork();
  //parent sends message to server
  if (r > 0) {
    while(true) {
      fprintf(stderr, "You:\n");
      char *msg_temp = malloc(sizeof(char)*MSGLEN);
      fgets(msg_temp, MSGLEN, stdin); //TODO: check if msg < MSGLEN
      int msg_len = strlen(msg_temp) + 1;
      char msg[msg_len];
      strncpy(msg, msg_temp, sizeof(char)*msg_len);
      free(msg_temp);
      char *send_buf = pack(usr, msg);
      if (write(peerfd, send_buf, sizeof(char)*strlen(send_buf) + 1) <= 0) {
        perror("Client: Writing");
      }
      free(send_buf);
    }
  }
  //child recieves messages from server
  else if (r == 0){
    while(true) {
      //Get size of message
      char size[5]; //Assume size is 4 digits or less
      if (read(peerfd, size, sizeof(char)*5) < 0){
        perror("Server: Read:");
        exit(-1);
      }
      int msg_size = strtol(size, NULL, 10);
      //Read message
      char msg[msg_size];
      if (read(peerfd, msg, sizeof(char)*(msg_size + 5)) < 0){
        perror("Server: Read:");
        exit(-1);
      }
      //Print message
      char *t1 = strtok(msg, ":");
      char *t2 = strtok(NULL, ":");
      fprintf(stderr, "%s:\n%s\n", t1, t2);
      printf("You:\n");
    }
  }
  close(peerfd);
  return 0;
}
