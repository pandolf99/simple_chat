#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "message.h"

/*
Returns a string in the form of "usr: message" given usr and message.
*/

char *pack(char *usr, char *message) {
  usr[strlen(usr) - 1] = '\0';
  char *packed = malloc(sizeof(char)*(MSGLEN + USRLEN));
  packed[0] = '\0';
  strcpy(packed, usr);
  strcat(packed, ":");
  strcat(packed, message);
  return packed;
}

/*Recieves a message in the form of: "usr: message"
and unpacks it to an array of strings
*/
char **unpack(char *message) {
  char **buf = malloc(sizeof(char*)*2);
  buf[0] = malloc(sizeof(char)*USRLEN);
  buf[1] = malloc(sizeof(char)*MSGLEN);
  strcpy(buf[0], strtok(message, ":"));
  strcpy(buf[1], strtok(NULL, ":"));
  return buf;
}
