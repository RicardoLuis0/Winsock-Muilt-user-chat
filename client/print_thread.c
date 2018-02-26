#include <stdio.h>

#include "print_thread.h"
#include "print_data.h"

DWORD WINAPI print_thread(void* data_voidptr){
    print_data * data=(print_data*)data_voidptr;
    int last_charcount=-1;
    int last_msg_id=(data->data->end==NULL)?0:data->data->end->id;
    while(1){
        if((last_charcount!=(*data->msg_charcount))||(last_msg_id!=((data->data->end==NULL)?0:data->data->end->id))){
            last_charcount=(*data->msg_charcount);
            last_msg_id=(data->data->end==NULL)?0:data->data->end->id;
            system("cls");
            for(chat_line * this=data->data->start;this!=NULL;this=this->next){
                printf("[%s]:%s\n",this->username,this->str);
            }
            printf("> %s\n",data->msg);
        }
    }
    return 0;
}
