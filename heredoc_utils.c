/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaris <afaris@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 22:26:54 by afaris            #+#    #+#             */
/*   Updated: 2022/11/09 22:27:20 by afaris           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	signal_listener(t_lexer *lexer)
{
	if (WIFSIGNALED(g_exitm))
	{
		lexer->here_doc_status = KO;
		g_exitm = EXIT_FAILURE;
	}
}
