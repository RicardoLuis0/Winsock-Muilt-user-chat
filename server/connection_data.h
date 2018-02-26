#ifndef CONNECTION_THREAD_DATA_H_INCLUDED
#define CONNECTION_THREAD_DATA_H_INCLUDED

#include <winsock2.h>
#include "connection_node.h"

typedef struct  connection_data connection_data;

struct connection_data{
    SOCKET s;
    connection_node * start;
    connection_node * end;
};

#endif // CONNECTION_THREAD_DATA_H_INCLUDED
