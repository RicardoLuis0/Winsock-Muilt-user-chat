#ifndef SERIALIZE_H_INCLUDED
#define SERIALIZE_H_INCLUDED

#include "server_message.h"
#include "message_size.h"

void serialize(server_message in,char buffer[MESSAGE_SIZE]);

#endif // SERIALIZE_H_INCLUDED
