/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_extra_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaris <afaris@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:27:05 by afaris            #+#    #+#             */
/*   Updated: 2022/11/10 18:38:57 by afaris           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

void	print_getcwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		printf("%s\n", cwd);
		free(cwd);
	}
}

void	raise_and_quit(char *old)
{
	raise_error(NULL, "cd", EXIT_FAILURE, FALSE);
	if (old)
		free(old);
	return ;
}
