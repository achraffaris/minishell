#include "../execution.h"

void    raise_error(char *err_msg, char *err_src)
{
    if (err_msg)
        printf("%s\n", err_msg);
    else
        perror(err_src);
}