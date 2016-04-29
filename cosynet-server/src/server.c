#include "server.h"

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "util.h"

Server* Server_Create(int port, Domain domain)
{
    Server* server = malloc(sizeof(Server));

    if ((server->socket = socket(domain, SOCK_STREAM, 0)) < 0) {
        error("Failed to create socket");
        Server_Destroy(server);
        exit(0);
    }

    memset(&server->address, 0, sizeof(Address));

    IPAddress* ip4addr = (IPAddress*)&server->address;
    IP6Address* ip6addr = (IP6Address*)&server->address;

    int bind_result = 0;

    switch (domain) {
    case PF_INET:
        ip4addr->sin_family = AF_INET;
        ip4addr->sin_port = htons(port);

        if (INADDR_ANY) {
            ip4addr->sin_addr.s_addr = htonl(INADDR_ANY);
        }

        bind_result = bind(server->socket, &server->address, sizeof(IPAddress));
    case PF_INET6:
        ip6addr->sin6_family = AF_INET6;
        ip6addr->sin6_port = htons(port);

         if (INADDR_ANY) {
            ip6addr->sin6_addr = in6addr_any;
        }

        bind_result = bind(server->socket, &server->address,
                           sizeof(IP6Address));
    }

    if (bind_result < 0) {
        error("Failed to bind socket");
    }

    listen(server->socket, SOMAXCONN);

    return server;
}

void Server_Destroy(Server* server)
{
    close(server->socket);
    free(server);
}

void Server_Cycle(Server* server)
{
    Address address;
    socklen_t socket_size = sizeof(address);
    Socket client;

    if ((client = accept(server->socket, (struct sockaddr *)&address,
                         &socket_size)) < 0) {
        error("Failed to accept incoming connection");
    }

    char* message = "Hello! We do not currently sustain connections. "
                    "You will be disconnected shortly.\n";

    send(client, message, strlen(message) + 1, 0);

    close(socket_size);
}

