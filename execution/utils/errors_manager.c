/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaris <afaris@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 23:19:11 by afaris            #+#    #+#             */
/*   Updated: 2022/11/06 23:19:54 by afaris           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	raise_error(char *err_msg, char *err_src,
			int exit_code, int should_exit)
{
	if (err_msg)
	{
		ft_putstr_fd(err_src, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(err_msg, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	else
		perror(err_src);
	if (should_exit)
		exit(exit_code);
	g_exitm = exit_code;
}
