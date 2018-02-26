#ifndef SERVER_MESSAGE_H_INCLUDED
#define SERVER_MESSAGE_H_INCLUDED

typedef struct server_message server_message;

//0 chat message
//1 shutdown message

struct server_message{
    char type;
    char username[21];
    char word[121];
};

#endif // SERVER_MESSAGE_H_INCLUDED
