#ifndef CHAT_LINE_H_INCLUDED
#define CHAT_LINE_H_INCLUDED

#define MAXLINES 20

typedef struct chat_line chat_line;

struct chat_line{
    char username[21];
    char str[121];
    int id;
    chat_line * next;
};

#endif // CHAT_LINE_H_INCLUDED
