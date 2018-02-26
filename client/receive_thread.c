#include <stdio.h>
#include <winsock2.h>

#include "receive_thread.h"
#include "client_data.h"
#include "server_message.h"
#include "unserialize.h"

DWORD WINAPI receive_thread(void* data_voidptr){
    client_data * data=(client_data*)data_voidptr;
    char received_data_raw[MESSAGE_SIZE];
    server_message received_data;
    chat_line * temp_line=NULL;
    int do_loop=1;
    int result;
    while(do_loop){
        result=recv(data->s,received_data_raw,MESSAGE_SIZE,0);
        if(result>0){
            unserialize(received_data_raw,&received_data);
            switch(received_data.type){
            case 0://message
                printf("\a");
                if(data->start==NULL){
                    temp_line=malloc(sizeof(chat_line));
                    temp_line->id=0;
                    temp_line->next=NULL;
                    memcpy(temp_line->username,received_data.username,21);
                    memcpy(temp_line->str,received_data.word,121);
                    data->start=temp_line;
                    data->end=temp_line;
                }else{
                    temp_line=malloc(sizeof(chat_line));
                    data->end->next=temp_line;
                    temp_line->id=data->end->id+1;
                    temp_line->next=NULL;
                    memcpy(temp_line->username,received_data.username,21);
                    memcpy(temp_line->str,received_data.word,121);
                    data->end=temp_line;
                    if(data->start->id+MAXLINES<=temp_line->id){
                        temp_line=data->start;
                        data->start=temp_line->next;
                        free(temp_line);
                    }
                }
                break;
            case 1://exit
                closesocket(data->s);
                return 0;
                break;
            }
        }else{
            exit((result==SOCKET_ERROR));
        }
    }
    return 0;
}
