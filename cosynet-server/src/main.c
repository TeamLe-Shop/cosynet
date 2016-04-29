#include <stdio.h>

#include "server.h"

int main()
{
    int port = DEFAULT_PORT;

    Server* server = Server_Create(port, PF_INET);
    printf("CosyServer launched, port = %d\n", port);

    Server_Cycle(server);

    Server_Destroy(server);
    printf("CosyServer stopped\n");
    return 0;
}
