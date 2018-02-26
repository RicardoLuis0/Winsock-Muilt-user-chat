#include "unserialize.h"

#include <string.h>

void unserialize(char data_raw[MESSAGE_SIZE],server_message * out){
    if(out==NULL) return;
    out->type=data_raw[0];
    memcpy(out->username,data_raw+1,21);
    memcpy(out->word,data_raw+22,121);
}
