#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "message.h"

/*
Returns a string in the form of "length|usr: message" given usr and message.
Where length is the length of "usr: message" including null terminator.
Assume that length is 4 digits or less.
*/

char *pack(char *usr, char *msg) {
  //Remove newline chars
  usr[strlen(usr) - 1] = '\0';
  msg[strlen(msg) - 1] = '\0';
  //Formatting
  int len = strlen(usr) + strlen(msg) + 3;
  int digs = snprintf(NULL, 0,"%d", len);
  char size[6];
  if (4 - digs != 0) {
    sprintf(size, "%d", len);
    for (int i = digs; i <= 4; i++) {
      size[i] = '*';
    }
    strncpy(size + 4, "|", 2);
  }
  else {
      snprintf(size, 6, "%d|", len);
  }
  //pass new string
  char *packed = malloc(sizeof(char)*(len + 5));
  packed[0] = '\0';
  strncpy(packed, size, sizeof(char)*6);
  //This is safe cause size is known.
  strcat(packed, usr);
  strcat(packed, ": ");
  strcat(packed, msg);
  return packed;
}
