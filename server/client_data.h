#ifndef CLIENT_DATA_H_INCLUDED
#define CLIENT_DATA_H_INCLUDED

#include <winsock2.h>
#include "connection_node.h"
#include "connection_data.h"

typedef struct  client_data client_data;

struct client_data{
    SOCKET s;
    connection_node * self;
    connection_data * connection;
};

#endif // CLIENT_DATA_H_INCLUDED
