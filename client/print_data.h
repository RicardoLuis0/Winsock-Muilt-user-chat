#ifndef PRINT_DATA_H_INCLUDED
#define PRINT_DATA_H_INCLUDED

#include "client_data.h"

typedef struct print_data print_data;

struct print_data{
    int * msg_charcount;
    char * msg;
    client_data * data;
};

#endif // PRINT_DATA_H_INCLUDED
