#include <stdio.h>

#include "multi_send.h"
#include "send_data.h"
#include "single_send.h"

DWORD WINAPI multi_send_handler(void* data_voidptr){
    multi_send_data * data=(multi_send_data*)data_voidptr;
    single_send_data * sdata;
    printf("message_type= %d\n",data->message.type);
    if(data->message.type==0){
        printf("[%s]: %s\n",data->message.username,data->message.word);
    }
    for(connection_node * this=(data->connection->start);this!=NULL;this=(this->next)){
        printf("node: %d ...\n",this);
        sdata=malloc(sizeof(single_send_data));
        sdata->s=this->client_socket;
        sdata->message=data->message;
        CreateThread(NULL,0,single_send_handler,sdata,0,NULL);
    }
    free(data);
    return 0;
}
