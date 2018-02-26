#include "send_message.h"

#include "message_data.h"
#include "message_size.h"
#include "serialize.h"

DWORD WINAPI send_message(void* data_voidptr){
    message_data * data=(message_data*)data_voidptr;
    char buf[MESSAGE_SIZE];
    serialize(data->message,buf);
    send(data->connection->s,buf,MESSAGE_SIZE,0);
    free(data);
    return 0;
}
