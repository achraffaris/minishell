#include "../builtins.h"

t_env *duplicate_env(t_env *env)
{
    t_env   *new;
    t_env   *new_head;
    t_env   *current;

    new = malloc(sizeof(t_env));
    if (!new)
        raise_error("Memory Allocation Failed!", "malloc");
    new_head = new;
    current = env;
    while (current)
    {
        new->key = ft_strdup(current->key);
        new->value = ft_strdup(current->value);
        if (current->next)
        {
            new->next = malloc(sizeof(t_env));
            if (!new->next)
                raise_error("Memory Allocation Failed!", "malloc");
        }
        else
            new->next = NULL;
        current = current->next;
        new = new->next;
    }
    return (new_head);
}

int env_size(t_env *env)
{
    t_env *current;
    int i;

    i = 0;
    current = env;
    while (current)
    {
        i++;
        current = current->next;
    }
    return (i);
}

int item_is_min(char *key, t_env *env)
{
    t_env *current;
    int i;

    current = env;
    i = 0;
    if (!current->next)
        return (TRUE);
    while (current)
    {
        if (ft_strcmp(key, current->key) < 0)
            i++;
        current = current->next;
    }
    if (i != 1)
        return (FALSE);
    return (TRUE);
}

void    rotate_env(t_env *env, t_env **head)
{
    t_env *old_top;
    t_env *new_top;
    t_env *current;

    current = env;
    old_top = env;
    new_top = env->next;
    if (current && current->next)
    {
        while (current && current->next)
            current = current->next;
        current->next = old_top;
        old_top->next = NULL;
        *head = new_top;
    }
}

t_env    *get_next_min_item(t_env *env)
{
    int size;
    t_env *current;

    current = env;
    while (current)
    {
        if (item_is_min(current->key, env))
            return (current);
        rotate_env(env, &env);
        current = env;
    }
    return (NULL);
}
