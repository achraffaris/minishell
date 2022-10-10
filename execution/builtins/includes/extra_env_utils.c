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

void    print_sorted_env_items(t_env *env)
{
    t_env *env_copy;
    t_env *min;

    env_copy = duplicate_env(env);
    min = get_next_min_item(env_copy);
    while(min)
    {
        if (min->value)
            printf("declare -x %s=\"%s\"\n", min->key, min->value);
        else
            printf("declare -x %s\n", min->key);
        remove_env_item(min->key, env_copy);
        min = get_next_min_item(env_copy);
    }
}

t_env   *get_env_item_or_none(char *key, t_env *env)
{
    t_env *current;

    current = env;
    while (current)
    {
        if (is_identical(key, current->key))
            return (current);
        current = current->next;
    }
    return (NULL);
}

void    update_env_item(t_env *item, char *arg)
{
    char *value;

    value = extract_env_value(arg);
    free(item->value);
    item->value = value;
}
