/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoukou <schoukou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 01:41:45 by schoukou          #+#    #+#             */
/*   Updated: 2022/11/08 15:28:41 by schoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	init_parse2(t_token *head, t_parse *tmp, t_lexer *lexer, t_rdr *rdr)
{
	if (head->e_type == 2 && head->next != NULL && head->next->e_type == 2)
		lexer->flg_error = 1;
	if (head->e_type == 0 && !lexer->flg_error)
		tmp->cmd = ft_strdup(head->value);
	else if (head->e_type == 1 && !lexer->flg_error)
	{
		if (!tmp->arg)
		{
			tmp->arg = malloc(sizeof(char *) * (count_arg(head) + 1));
			lexer->y = 0;
		}
		tmp->arg[lexer->y] = ft_strdup(head->value);
		tmp->arg[++lexer->y] = NULL;
	}
	if (((head->e_type == 4 || head->e_type == 5
				|| head->e_type == 6) && !lexer->flg_error)
		|| head->e_type == 3)
	{
		rdr = add_rdr(head->value, head->e_type, head->rdr_flg);
		add_back_rdr(&tmp->rdr, rdr);
	}
	return (lexer->y);
}

t_parse	*init_var(void)
{
	t_parse	*tmp;

	tmp = malloc(sizeof(t_parse));
	tmp->arg = NULL;
	tmp->cmd = NULL;
	tmp->rdr = NULL;
	tmp->next = NULL;
	return (tmp);
}

t_parse	*set_flg_error_quit(t_lexer *lexer)
{
	lexer->flg_error = 1;
	return (NULL);
}

int	syntax_is_valid(t_token *head, t_lexer *lexer)
{
	if (head->e_type == 2 && head->next == NULL)
	{
		lexer->flg_error = 1;
		return (0);
	}
	return (1);
}

t_parse	*init_parsing(t_token **token, t_lexer *lexer)
{
	t_token	*head;
	t_parse	*tmp;
	t_parse	*parse;
	t_rdr	*rdr;

	tmp = NULL;
	parse = NULL;
	rdr = NULL;
	head = *token;
	lexer->y = 0;
	if (head->e_type == 2)
		return (set_flg_error_quit(lexer));
	tmp = init_var();
	while (head && syntax_is_valid(head, lexer))
	{
		lexer->y = init_parse2(head, tmp, lexer, rdr);
		if (head->e_type == 2)
		{
			add_back_parse(&parse, tmp);
			tmp = init_var();
		}
		head = head->next;
	}
	add_back_parse(&parse, tmp);
	return (parse);
}
