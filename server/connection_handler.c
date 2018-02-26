#include "connection_handler.h"
#include "connection_data.h"
#include "client_data.h"
#include "client_receive_handler.h"

#include <stdio.h>

DWORD WINAPI connection_handler(void* data_voidptr){
    int do_loop=1;
    connection_data * data=(connection_data *)data_voidptr;
    connection_node * temp_node=NULL;
    client_data * cdata=NULL;
    SOCKET temp_socket;
    int sockaddr_in_len=sizeof(struct sockaddr_in);
    struct sockaddr_in temp_address;
    listen(data->s,10);
    while(do_loop){

        temp_socket=accept(data->s,(struct sockaddr *)&temp_address,&sockaddr_in_len);

        if(temp_socket==INVALID_SOCKET){
            printf("Client connection failed with error code : %d\n" , WSAGetLastError());
            continue;
        }

        if(data->start==NULL){
            temp_node=malloc(sizeof(connection_node));
            data->end=temp_node;
            data->start=temp_node;
            temp_node->next=NULL;
            temp_node->prev=NULL;
            temp_node->client_socket=temp_socket;
            temp_node->client_address=temp_address;
            cdata=malloc(sizeof(client_data));
            cdata->connection=data;
            cdata->self=temp_node;
            cdata->s=temp_socket;
            temp_node->client_receive=CreateThread(NULL,0,client_receive_handler,cdata,0,NULL);
        }else{
            temp_node=malloc(sizeof(connection_node));
            data->end->next=temp_node;
            temp_node->next=NULL;
            temp_node->prev=data->end;
            temp_node->client_socket=temp_socket;
            temp_node->client_address=temp_address;
            data->end=temp_node;
            cdata=malloc(sizeof(client_data));
            cdata->connection=data;
            cdata->self=temp_node;
            cdata->s=temp_socket;
            temp_node->client_receive=CreateThread(NULL,0,client_receive_handler,cdata,0,NULL);
        }
        printf("Connection Accepted.\n");

    }
    return 0;
}
