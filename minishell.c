#include "header.h"
#include "execution/execution.h"

void add_back(t_token **list, t_token *tmp)
{
    if (*list == NULL)
        (*list) = tmp;
    else
    {
        t_token *tmp1 = *list;
        while(tmp1->next != NULL)
            tmp1 = tmp1->next;
        tmp1->next = tmp;
    } 
}

int main(int ac, char **av, char **env)
{
    (void) ac;
    (void) av;
    t_lexer  *lexer;
    t_token *token = NULL;
    t_token *tmp;
    t_parse *parse;
    t_env   *env_list;

    env_list = setup_env(env);
    char *str = NULL;
    lexer = malloc(sizeof(t_lexer));
    while(1)
    {
        printf("-------------------- BEGIN ------------------ \n");
        str = readline("minishell >$ ");
        if (str[0] != '\0')
        {
            lexer = init_lexer(str, lexer);
            while ((tmp = get_next_token(lexer)) != NULL)
                add_back(&token, tmp);
            if ((token) != NULL)
            {
                parse = init_parsing(&token, lexer);
            }
            if(!token)
            {
                free(parse->cmd);
                parse->cmd = NULL;
                free(parse->arg);
                parse->arg = NULL;
                free(parse->rdr);
                parse->rdr = NULL;
            }
            parse->env = env_list;
            //printf("%s------\n",parse->cmd);
            execution(parse);
            //t_parse *tmp1 = parse;
            //printf("%s------\n",tmp1->cmd);
            if (lexer->flg_error == 0)
            {
                /*
                while(tmp1)
                {
                    if (tmp1->cmd != NULL)
                    {
                        printf("cmd = %s\n", tmp1->cmd);
                        free(tmp1->cmd);
                    }
                    if (tmp1->arg != NULL)
                    {
                        int i = 0;
                        while(tmp1->arg[i])
                        {
                            printf("arg = %s\n", tmp1->arg[i]);
                            i++;
                        }
                    }
                    if (tmp1->rdr != NULL)
                    {
                        t_rdr *r = tmp1->rdr;
                        while(r)
                        {
                            printf("rdr->type = %d, rdr->value = %s\n", r->type, r->value);
                            r = r->next;
                        }
                    }
                    printf("-----------------------\n");
                    tmp1 = tmp1->next;
                }*/
            }
            else if (lexer->flg_error == 1)
                printf("syntax_error\n");
            if (ft_strlen(str) > 0)
                add_history(str);
            tmp = token;
            while(tmp)
            {
                token = token->next;
                free(tmp);
                tmp = token;
            }
            // tmp1 = parse;
            // while(tmp1)
            // {
            //     if (tmp1->cmd != NULL && tmp1->cmd[0] != '\0')
            //     {
            //         free(tmp1->cmd);
            //     }
            //     tmp1 = tmp1->next;
            // }
        }
       

    }
    return 0;
}