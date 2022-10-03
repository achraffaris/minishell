#ifndef EXECUTION_H
# define EXECUTION_H

#include "../header.h"
#include "builtins/builtins.h"
#define ERROR_RETURNED -1

void    execution(t_parse *data);
void    raise_error(char *err_msg, char *err_src);


#endif