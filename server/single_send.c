#include "single_send.h"

#include "send_data.h"
#include "serialize.h"

DWORD WINAPI single_send_handler(void* data_voidptr){
    single_send_data * data=(single_send_data*)data_voidptr;
    char buf[MESSAGE_SIZE];
    serialize(data->message,buf);
    send(data->s,buf,MESSAGE_SIZE,0);
    free(data);
    return 0;
}
