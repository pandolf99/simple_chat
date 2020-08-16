/*
A handler to safely terminate a client. 
*/
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "sig_hand.h"


int peerfd;

void term_handler(int sig){
    printf("Exited chat server");
    write(peerfd, "CLOSE", sizeof(char)*5);
    close(peerfd);
    exit(1);
}

void sig_action(int peer) {
    peerfd = peer;
    struct sigaction sa;
    sa.sa_handler = term_handler;    
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);
}
