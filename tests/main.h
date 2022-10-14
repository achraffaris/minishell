#ifndef MAIN_H
#define MAIN_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct list
{
    char *key;
    struct list *next;
}   t_list;

#endif