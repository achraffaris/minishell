/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaris <afaris@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 23:07:56 by afaris            #+#    #+#             */
/*   Updated: 2022/11/09 18:02:10 by afaris           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	run_as_builtin(t_parse *data, t_env **env)
{
	if (run_echo(data)
		|| run_cd(data, env)
		|| run_pwd(data, *env)
		|| run_unset(data, env)
		|| run_env(data, env)
		|| run_exit(data)
		|| run_export(data, env))
		return (TRUE);
	return (FALSE);
}
