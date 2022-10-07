#ifndef BUILTINS_H
#define BUILTINS_H

#define ECHO "echo"
#define CD "cd"
#define PWD "pwd"
#define EXPORT "export"
#define UNSET "unset"
#define ENV "env"
#define EXIT "exit"

#define FALSE 0
#define TRUE 1

#define UNSET_OPERATION 1
#define EXPORT_OPERATION 2

#define NULL_CHARACTER '\0'

#define ECHO_N_FLAG "-n"

# include "../execution.h"

int     is_identical(char *s1, char *s2);
int     start_with(char *word, char *str);

int     run_as_builtin(t_parse *data);
int     run_echo(t_parse *data);
int     run_cd(t_parse *data);
int     run_pwd(t_parse *data);
int     run_unset(t_parse *data);
int     run_echo(t_parse *data);
int     run_env(t_parse *data);
int     run_exit(t_parse *data);
int     env_key_valid(char *env_key);

void    remove_env_item(char *item, t_env *env);

#endif