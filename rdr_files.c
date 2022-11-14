/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdr_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoukou <schoukou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 20:26:43 by schoukou          #+#    #+#             */
/*   Updated: 2022/11/07 00:18:54 by schoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "execution/execution.h"

void	check_fd(t_lexer *lexer, t_rdr	*tmpr)
{
	if (tmpr->fd == -1 || !tmpr->value[0])
	{
		raise_error(NULL, tmpr->value, EXIT_FAILURE, FALSE);
		lexer->flg_error = 1;
		tmpr->fd = ERROR_FILE;
	}
}

void	rdr_manager(t_lexer *lexer, t_rdr *tmpr)
{
	if (tmpr->type == 4 && !lexer->flg_error)
	{
		tmpr->fd = open(tmpr->value, O_RDWR, 0777);
		check_fd(lexer, tmpr);
	}
	if (tmpr->type == 5 && !lexer->flg_error)
	{
		tmpr->fd = open(tmpr->value, O_CREAT
				| O_WRONLY | O_TRUNC, 0777);
		check_fd(lexer, tmpr);
	}
	if (tmpr->type == 6 && !lexer->flg_error)
	{
		tmpr->fd = open(tmpr->value, O_CREAT | O_RDWR | O_APPEND, 0777);
		check_fd(lexer, tmpr);
	}
}

void	rdr_create_files(t_parse **parse, t_lexer *lexer)
{
	t_parse	*tmp;
	t_rdr	*tmpr;

	tmp = (*parse);
	while (tmp)
	{
		tmpr = tmp->rdr;
		lexer->flg_error = 0;
		while (tmpr)
		{
			rdr_manager(lexer, tmpr);
			tmpr = tmpr->next;
		}
		tmp = tmp->next;
	}
}
