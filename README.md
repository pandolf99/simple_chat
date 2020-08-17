# simple_chat
A chat over terminal implemented in C with sockets. Accepts Multiple clients.

## Usage:
To use run the server first in the desired port (./server port).
Then connect the desired clients (./client port [hostname]).
If hostname is omitted, it will run in localhost.
If using different networks you must port-forward in the router.
To close a client session send a SIGINT signal (ctrl C)

## Bugs:
Still not tested in different networks. Dont exit the server without first exiting clients. 
