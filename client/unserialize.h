#ifndef UNSERIALIZE_H_INCLUDED
#define UNSERIALIZE_H_INCLUDED

#include "server_message.h"
#include "message_size.h"

void unserialize(char data_raw[MESSAGE_SIZE],server_message * out);

#endif // UNSERIALIZE_H_INCLUDED
