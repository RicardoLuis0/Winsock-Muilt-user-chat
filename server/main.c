#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <winsock2.h>
#include <string.h>
#include <conio.h>


#include "connection_handler.h"
#include "connection_data.h"
#include "server_message.h"
#include "multi_send.h"
#include "send_data.h"

int main(){
    connection_data data;
    data.start=NULL;
    data.end=NULL;
    int do_loop=1;
    WSADATA wsa;
    struct sockaddr_in server;

    printf("Initialising Winsock...");

    if(WSAStartup(MAKEWORD(2,2),&wsa)!=0){
        printf("Failed. Error Code : %d",WSAGetLastError());
        exit(1);
    }
    printf("Initialised.\n");

    printf("Creating Socket...");
    data.s=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

    if(data.s==INVALID_SOCKET){
        printf("Could not create socket : %d",WSAGetLastError());
        exit(1);
    }

    printf("Socket Created.\n");

    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port=htons(1400);

    printf("Binding socket to port 1400...");
    if(bind(data.s,(struct sockaddr*)&server,sizeof(server))==SOCKET_ERROR){
        printf("Bind failed with error code : %d",WSAGetLastError());
        exit(1);
    }

    printf("Bind Completed.\n");
    /*HANDLE connection_thread=*/CreateThread(NULL,0,connection_handler,&data,0,NULL);

    server_message ping;
    ping.type=0;
    strcpy(ping.username,"SERVER");
    strcpy(ping.word,"ping");
    multi_send_data * ping_data;
    while(do_loop){
        int input=getch();
        if(input==27)do_loop=0;
        if(input==13){
            printf("message_type ping: %d\n",ping.type);
            ping_data=malloc(sizeof(multi_send_data));
            memcpy(&(ping_data->message),&ping,sizeof(server_message));
            ping_data->connection=&data;
            printf("message_type ping_data: %d\n",ping_data->message.type);
            CreateThread(NULL,0,multi_send_handler,ping_data,0,NULL);
        }
    }
    closesocket(data.s);
    WSACleanup();
    return 0;
}
