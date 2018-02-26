#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <winsock2.h>
#include <conio.h>

#include "receive_thread.h"
#include "client_data.h"
#include "message_data.h"
#include "send_message.h"
#include "print_data.h"
#include "print_thread.h"

void cls(){
    system("cls");
}

void print_intro_menu(int loc){
    cls();
    for(int i=0;i<2;i++){
        printf(i==loc?">":"-");
        switch(i){
        case 0:
            printf("Connect");
            break;
        case 1:
            printf("Exit");
            break;
        }
        printf("\n");
    }
}

int main(){
    int do_loop=1;
    char address[21];
    char username[21];
    char msg[121];
    int input=0;
    int loc=0;
    while(do_loop){
        print_intro_menu(loc);
        input=getch();
        switch(input){
        case 224://arrow keys
            input=getch();
            switch(input){
            case 72://up
                loc=!loc;
                break;
            case 75://left
                break;
            case 77://right
                break;
            case 80://down
                loc=!loc;
                break;
            }
            break;
        case 13://enter
            if(input==1){
                exit(1);
            }else{
                cls();
                printf("Enter IP: ");
                scanf("%s",address);
                do_loop=0;
            }
            break;
        case 27://esc
            exit(1);
        }
        printf("%d,",input);
    }
    
    
    
    WSADATA wsa;
    struct sockaddr_in server;

    client_data data;
    data.start=NULL;
    data.end=NULL;
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

    printf("Connecting to server at %s...",address);
    server.sin_addr.s_addr=inet_addr(address);
    server.sin_family= AF_INET;
    server.sin_port=htons(1400);

    if(connect(data.s,(struct sockaddr*)&server,sizeof(server))<0){
        printf("Connection Error.");
        exit(1);
    }
    printf("Connected.\n");
    printf("Enter Username: ");
    scanf("%s",username);

    CreateThread(NULL,0,receive_thread,&data,0,NULL);
    message_data * msg_data;
    int msg_loc=0;
    memset(msg,0,121);

    print_data * print_data_ptr=malloc(sizeof(print_data));
    print_data_ptr->data=&data;
    print_data_ptr->msg=msg;
    print_data_ptr->msg_charcount=&msg_loc;

    CreateThread(NULL,0,print_thread,print_data_ptr,0,NULL);

    while(1){
        input=getch();
        if(input==224){
            getch();
            continue;
        }else if(input==13){
            //send
            msg_data=malloc(sizeof(message_data));
            msg_data->connection=&data;
            msg_data->message.type=0;
            strcpy(msg_data->message.username,username);
            strcpy(msg_data->message.word,msg);
            CreateThread(NULL,0,send_message,msg_data,0,NULL);
            msg[0]='\0';
            msg_loc=0;
        }else if(input==27){
            //quit
            msg_data=malloc(sizeof(message_data));
            msg_data->connection=&data;
            msg_data->message.type=1;
            CreateThread(NULL,0,send_message,msg_data,0,NULL);
        }else if(input==8){
            //erase
            if(msg_loc>0) msg[--msg_loc]='\0';
        }else{
            //add char
            if(msg_loc<120){
                msg[msg_loc++]=input;
                msg[msg_loc]='\0';
            }
        }
    }

    closesocket(data.s);
    WSACleanup();
    return 0;
}
