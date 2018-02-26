#ifndef CONNECTION_NODE_H_INCLUDED
#define CONNECTION_NODE_H_INCLUDED

#include <winsock2.h>

typedef struct connection_node connection_node;

struct connection_node{
    SOCKET client_socket;
    struct sockaddr_in client_address;
    HANDLE client_receive;
    HANDLE client_send;
    connection_node * next;
    connection_node * prev;
};

#endif // CONNECTION_NODE_H_INCLUDED
