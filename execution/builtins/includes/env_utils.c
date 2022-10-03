#include "../builtins.h"

int start_with(char *word, char *str)
{
    int i;

    i = 0;
    if (!word || !str)
        return (FALSE);
    while (word[i])
    {
        if (str[i] != word[i])
            return (FALSE);
        i++;   
    }
    return (TRUE);
}

int env_key_valid(char *env_key)
{
    int i;

    i = 0;
    if (!env_key || ft_isdigit(env_key[0]))
        return (FALSE);
    while (env_key[i])
    {
        if (!(ft_isalnum(env_key[i])
                || ft_isdigit(env_key[i])
                || env_key[i] == '_'))
            return (FALSE);
        i++;
    }
    return (TRUE);
}

