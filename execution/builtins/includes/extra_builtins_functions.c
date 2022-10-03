#include "../builtins.h"

int run_env(t_parse *data)
{
    if (!is_identical(data->cmd, ENV))
        return (FALSE);
    printf("its a builtin: env\n");
    return (TRUE);
}

int run_exit(t_parse *data)
{
    if (!is_identical(data->cmd, EXIT))
        return (FALSE);
    printf("its a builtin: exit\n");
    return (TRUE);
}