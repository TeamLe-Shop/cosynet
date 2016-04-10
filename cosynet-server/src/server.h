#ifndef SERVER_H
#define SERVER_H

#define DEFAULT_PORT 7000

#include <netinet/in.h>

#include <sys/socket.h>
#include <sys/types.h>

typedef int Socket;
typedef int Domain;
typedef struct sockaddr_storage Address;
typedef struct sockaddr_in IPAddress;
typedef struct sockaddr_in6 IP6Address;

typedef struct {
    Socket socket;
    Address address;
} Server;

/* Create a server. The pointer to the instance is returned. */
Server* Server_Create(int port, Domain domain);

/* Destroy a server instance and free all memory allocated to it */
void Server_Destroy(Server* server);

/* Accept pending connections. */
void Server_Cycle();

#endif
