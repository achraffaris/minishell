#ifndef EXECUTION_H
# define EXECUTION_H

#include "../header.h"
#include "builtins/builtins.h"
#define ERROR_RETURNED -1
#define AFTER 1
#define BEFORE 0
#define NONE -1

void    execution(t_parse *data);
void    raise_error(char *err_msg, char *err_src);
int     substring_length(char *str, char to_stop, int mode);
t_env   *setup_env(char **env);


#endif