#include "../builtins.h"

int run_echo(t_parse *data)
{
    int i;
    int n_flag_found;

    i = 0;
    n_flag_found = is_identical(data->arg[0], ECHO_N_FLAG);
    if (!is_identical(data->cmd, ECHO))
        return (FALSE);
    if (n_flag_found)
        i++;
    while(data->arg && data->arg[i])
    {
        printf("%s", data->arg[i]);
        i++;
        if (data->arg && data->arg[i])
            printf(" ");
    }
    if (!n_flag_found)
        printf("\n");
    return (TRUE);
}

int run_cd(t_parse *data)
{
    if (!is_identical(data->cmd, CD))
        return (FALSE);
    if (chdir(*data->arg) == ERROR_RETURNED)
        raise_error(NULL, *data->arg);
    return (TRUE);
}

int run_pwd(t_parse *data)
{
    if (!is_identical(data->cmd, PWD))
        return (FALSE);
    printf("%s\n", getcwd(NULL, 0));
    return (TRUE);
}

int run_unset(t_parse *data)
{
    int i;

    i = 0;
    if (!is_identical(data->cmd, UNSET))
        return (FALSE);
    while (data->arg && data->arg[i])
    {
        if (env_key_valid(data->arg[i]))
            remove_env_item(data->arg[i], data->env);
        i++;
    }
    return (TRUE);
}

int run_export(t_parse *data)
{
    if (!is_identical(data->cmd, EXPORT))
        return (FALSE);
    printf("its a builtin: export\n");
    return (TRUE);
}