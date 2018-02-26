#ifndef CLIENT_DATA_H_INCLUDED
#define CLIENT_DATA_H_INCLUDED

#include "chat_line.h"

typedef struct client_data client_data;

struct client_data{
    SOCKET s;
    chat_line * start;
    chat_line * end;
};

#endif // CLIENT_DATA_H_INCLUDED
