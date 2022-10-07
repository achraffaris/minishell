#include "../builtins.h"

void    free_env_item(t_env *item)
{
    if (item)
    {
        if (item->key)
        {
            free(item->key);
        }
        if (item->value)
        {
            free(item->value);
        }
    }
}

void    remove_env_item(char *item, t_env *env)
{
    t_env *current;
    t_env *found;

    current = env;
    while (current && current->next)
    {
        if (is_identical(item, current->next->key))
        {
            found = current->next;
            current->next = found->next;
            free_env_item(found);
        }
        current = current->next;
    }
}