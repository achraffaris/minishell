#include "../builtins.h"

int is_identical(char *s1, char *s2)
{
    int i;

    i = 0;
    if (!s1)
        return (FALSE);
    while (s1[i] && s2[i])
    {
        if (s1[i] != s2[i])
            return (FALSE);
        i++;   
    }
    return (TRUE);
}

