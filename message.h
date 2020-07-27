#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#define USRLEN 35
#define MSGLEN 8192

char *pack(char *, char *);
char **unpack(char *);
#endif
