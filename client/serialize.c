#include "serialize.h"

#include <string.h>

void serialize(server_message in,char buffer[MESSAGE_SIZE]){
    buffer[0]=in.type;
    memcpy(buffer+1,in.username,21);
    memcpy(buffer+22,in.word,121);
}
