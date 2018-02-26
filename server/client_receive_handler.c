#include <stdio.h>

#include "client_receive_handler.h"
#include "client_data.h"
#include "server_message.h"
#include "unserialize.h"
#include "multi_send.h"
#include "send_data.h"

DWORD WINAPI client_receive_handler(void * data_voidptr){
    client_data * data=(client_data*) data_voidptr;
    char buf[MESSAGE_SIZE];
    server_message message;
    int result;
    while(1){
        result=recv(data->s,buf,MESSAGE_SIZE,0);
        if(result==SOCKET_ERROR){
            printf("Socket receive error : %d\n",WSAGetLastError());
        }
        if(result<=0){
            if(data->connection->start==data->self){
                data->connection->start=data->self->next;
            }
            if(data->connection->end==data->self){
                data->connection->end=data->self->prev;
            }
            if(data->self->next!=NULL){
                data->self->next->prev=data->self->prev;
            }
            if(data->self->prev!=NULL){
                data->self->prev->next=data->self->next;
            }
            closesocket(data->s);
            free(data->self);
            free(data);
            printf("Connection Closed.\n");
            return 0;
        }else{
            unserialize(buf,&message);
            if(message.type==0){
                multi_send_data * sdata=malloc(sizeof(multi_send_data));
                sdata->message=message;
                sdata->connection=data->connection;
                CreateThread(NULL,0,multi_send_handler,sdata,0,NULL);
            }else if(message.type==1){
                if(data->connection->start==data->self){
                    data->connection->start=data->self->next;
                }
                if(data->connection->end==data->self){
                    data->connection->end=data->self->prev;
                }
                if(data->self->next!=NULL){
                    data->self->next->prev=data->self->prev;
                }
                if(data->self->prev!=NULL){
                    data->self->prev->next=data->self->next;
                }
                closesocket(data->s);
                free(data->self);
                free(data);
                printf("Connection Closed.\n");
                return 0;
            }else{
                printf("Unknown message type.\n");
            }
        }
    }
}
