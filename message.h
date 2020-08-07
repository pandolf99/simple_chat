#ifndef _MESSAGE_H_
#define _MESSAGE_H_

/*
Max size of user and message. Actual usr and msg len that is sent
over socket might be smaller.
*/
#define USRLEN 35
#define MSGLEN 8192

char *pack(char *, char *);
#endif
