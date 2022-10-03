#include "execution.h"

void    execution(t_parse *data)
{
    t_parse *current;

    current = data;
    while (current)
    {
        if (run_as_builtin(current))
            break ;
        current = current->next;
    }
}