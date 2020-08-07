# simple_chat
A chat over terminal implemented in C with sockets. Accepts Multiple clients.
Works pretty well in a local network. Still buggy in different networks.  

##Usage:
To use run the server first in the desired port (./server port).
Then connect the desired clients (./client port [hostname]).
If hostname is omitted, it will run in localhost.
If using different networks you must port-forward in the router. 
