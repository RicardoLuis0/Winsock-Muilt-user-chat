#ifndef MESSAGE_DATA_H_INCLUDED
#define MESSAGE_DATA_H_INCLUDED

#include "client_data.h"
#include "server_message.h"

typedef struct message_data message_data;

struct message_data{
    server_message message;
    client_data * connection;
};

#endif // MESSAGE_DATA_H_INCLUDED
