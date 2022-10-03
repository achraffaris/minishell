#ifndef HEADER_H
#define HEADER_H

# include <unistd.h>
# include "token.h"
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

typedef struct s_lexer
{
    char    c;
    unsigned int    i;
    char    *contents;
    int     flg;
    int x;
    int flg_error;
    char **env;
}   t_lexer;

typedef struct s_rdr
{
    int type;
    char *value;
    struct s_rdr *next;
} t_rdr ;

// typedef struct s_herdoc
// {
//     char *value;
//     struct s_herdoc *next;
// }

typedef struct s_parse
{
    char *cmd;
    char **arg;
    t_rdr *rdr;
    char **env;
    int     i;
    struct s_parse *next;
} t_parse;

t_lexer *init_lexer(char *contents, t_lexer *lexer);
void    lexer_advance(t_lexer *lexer);
void    lexer_skip_space(t_lexer *lexer);
t_token *init_token(int type, char *value);
t_token *get_next_token(t_lexer *lexer);
char *collect_string(t_lexer *lexer);
char *get_current_char_as_string(t_lexer *lexer);
t_token *lexer_advance_with_token(t_lexer *lexer, t_token *token);
t_lexer *skip_single_quote(t_lexer *lexer, int sq);
t_token	*handle_single_quote(t_lexer *lexer);
int	check_single_quote(t_lexer *lexer);
char	*get_current_char_as_string_2(t_lexer *lexer);
t_token	*handle_double_quote(t_lexer *lexer);
char	*get_current_char_as_string_3(t_lexer *lexer);
int     redirect_check(t_lexer *lexer);
char	*get_current_char_as_string_redirection(t_lexer *lexer);
void	lexer_back(t_lexer *lexer);
char	*collect_string_2(t_lexer *lexer, char *join);
int     check_if_next_quote(t_lexer *lexer);
t_token *collect_pipe(t_lexer *lexer);
char** copy_env(char **env);
char    *dollar_handler(t_lexer *lexer);
t_parse *init_parsing(t_token **token, t_lexer *lexer);


#endif
