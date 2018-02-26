#ifndef SEND_DATA_H_INCLUDED
#define SEND_DATA_H_INCLUDED

#include "connection_data.h"
#include "server_message.h"

typedef struct multi_send_data multi_send_data;
typedef struct single_send_data single_send_data;

struct multi_send_data{
    connection_data * connection;
    server_message message;
};

struct single_send_data{
    SOCKET s;
    server_message message;
};


#endif // SEND_DATA_H_INCLUDED
