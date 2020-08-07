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
  if (argc != 2) {
    fprintf(stderr, "Usage: %s port\n", argv[0]);
    exit(1);
  }
  else {
    port = strtol(argv[1], NULL, 10);
  }
  //set up socket
  int serverfd = set_up_server_socket(port);
  printf("\nThe Server is now started on port: %d\n\n", port);


  int max_fd = serverfd;
  fd_set all_fds;
  FD_ZERO(&all_fds);
	FD_SET(serverfd, &all_fds);
  //Server loop
  while(1) {
    fd_set listen_fds = all_fds;
		int nready = select(max_fd + 1, &listen_fds, NULL, NULL, NULL);

    if (nready == -1) {
        perror("server: select");
        exit(1);
    }

    // Accept new connection.
    if (FD_ISSET(serverfd, &listen_fds)) {
        int peerfd = accept_connection(serverfd);
        if (peerfd > max_fd) {
            max_fd = peerfd;
        }
				if (peerfd > 0) {
					FD_SET(peerfd, &all_fds);
				}
				else {
          perror("Server: Connecting");
					exit(-1);
        }
    }
    //Iterate over clients
    for( int i = 3; i <= max_fd; i++) {
    			if (i == serverfd) continue;
    			if (FD_ISSET(i, &listen_fds)){
            //Get size of message,
            char size[5]; //Assume size is 4 digits or less
            if (read(i, size, sizeof(char)*5) < 0){
              perror("Server: Read:");
              exit(-1);
            }
            int msg_size = strtol(size, NULL, 10);
            //Read message
            char msg[msg_size];
    				if (read(i, msg, sizeof(char)*msg_size) < 0){
    					perror("Server: Read:");
    					exit(-1);
    				}
            //create final buf
            char buf[msg_size + 5];
            strcpy(buf, size);
            strcpy(buf+5, msg);
            //Relay to other clients
            for( int j = 3; j <= max_fd; j++) {
              if (j == serverfd || j == i) continue;
              if (write(j, buf, sizeof(char)*(msg_size + 5)) <= 0) {
                perror("Server: Write");
              }
            }
          }
    }
  }
}
