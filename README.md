# simple_chat
A chat over terminal implemented in C with sockets. Accepts Multiple clients.

## Usage:
To use run the server first in the desired port (./server port).
Then connect the desired clients (./client port [hostname]).
If hostname is omitted, it will run in localhost.
If using different networks you must port-forward in the router.

## Bugs:
There is no simple way for a client to exit yet. If the one of the clients close,
behaviour is unknown. Still not tested in different networks. 
