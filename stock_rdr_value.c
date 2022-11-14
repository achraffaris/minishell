/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_rdr_value.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoukou <schoukou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 20:28:59 by schoukou          #+#    #+#             */
/*   Updated: 2022/11/08 16:52:25 by schoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*stock_rdr_value_dollar(char *a, char *str, t_lexer *lexer, int i)
{
	lexer_advance(lexer);
	if (lexer->c != '\'' && lexer->c != '"' && !i)
	{
		a = dollar_handler(lexer);
		str = ft_strjoin(str, a);
		free (a);
	}
	else if (lexer->c != '\'' && lexer->c != '"' && i)
		str = ft_strjoin(str, "$");
	return (str);
}

char	*stock_rdr_value_double_quotes(char *a, char *str, t_lexer *lexer)
{
	lexer->flg_quote = 1;
	lexer_advance(lexer);
	while (lexer->c != 0 && lexer->c != '"')
	{
		a = get_current_char_as_string(lexer);
		str = ft_strjoin(str, a);
		if (lexer->c != '\0' && lexer->c != '\"')
			lexer_advance(lexer);
		free(a);
	}
	return (str);
}

char	*stock_rdr_value(t_lexer *lexer, char *str, int i)
{
	char	*a;

	a = NULL;
	if (lexer->c == '$')
		str = stock_rdr_value_dollar(a, str, lexer, i);
	else if (lexer->c == '\'' || (lexer->c == '"' && !i))
	{
		lexer->flg_quote = 1;
		a = join_to_str(lexer);
		str = ft_strjoin(str, a);
		free (a);
		lexer_advance(lexer);
	}
	else if (lexer->c == '"' && i)
		str = stock_rdr_value_double_quotes(a, str, lexer);
	if (lexer->c != '\0' && lexer->c != '\'' && lexer->c != '"'
		&& lexer->c != '>' && lexer->c != '<'
		&& lexer->c != ' ' && lexer->c != '|' && lexer->c != '$')
	{
		a = get_current_char_as_string(lexer);
		str = ft_strjoin(str, a);
		free (a);
		lexer_advance(lexer);
	}
	return (str);
}
