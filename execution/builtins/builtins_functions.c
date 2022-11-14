/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaris <afaris@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 23:10:24 by afaris            #+#    #+#             */
/*   Updated: 2022/11/10 17:53:35 by afaris           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	run_echo(t_parse *data)
{
	int	i;
	int	n_flag_found;

	i = 0;
	n_flag_found = FALSE;
	if (!is_identical(cmd_lower(data->cmd), ECHO))
		return (FALSE);
	while (data->arg && data->arg[i]
		&& (ft_strlen(data->arg[i]) >= 2 && valid_echo_flag(data->arg[i])))
	{
		n_flag_found = TRUE;
		i++;
	}
	while (data->arg && data->arg[i])
	{
		printf("%s", data->arg[i]);
		i++;
		if (data->arg && data->arg[i])
			printf(" ");
	}
	if (!n_flag_found)
		printf("\n");
	return (TRUE);
}

int	run_cd(t_parse *data, t_env **env)
{
	if (!is_identical(cmd_lower(data->cmd), CD))
		return (FALSE);
	if (data->arg)
		cd_path(data, env);
	else if (!data->arg)
		cd_home(env);
	return (TRUE);
}

int	run_pwd(t_parse *data, t_env *env)
{
	char	*pwd;
	t_env	*pwd_instance;

	pwd_instance = get_env_item_or_none("PWD", env);
	pwd = NULL;
	if (!is_identical(cmd_lower(data->cmd), PWD))
		return (FALSE);
	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		printf("%s\n", pwd);
		free(pwd);
	}
	else
	{
		if (pwd_instance)
			printf("%s\n", pwd_instance->value);
	}
	return (TRUE);
}

int	run_unset(t_parse *data, t_env **env)
{
	int	i;

	i = 0;
	if (!is_identical(data->cmd, UNSET))
		return (FALSE);
	while (data->arg && data->arg[i])
	{
		if (env_key_valid(data->arg[i]))
			remove_env_item(data->arg[i], env);
		else
			raise_error("not a valid identifier", data->arg[i], 1, FALSE);
		i++;
	}
	return (TRUE);
}

int	run_export(t_parse *data, t_env **env)
{
	int	i;

	i = 0;
	if (!is_identical(data->cmd, EXPORT))
		return (FALSE);
	if (!data->arg)
		print_sorted_env_items(*env);
	else
	{
		while (data->arg[i])
		{
			create_or_update_env_item(env, data->arg[i]);
			i++;
		}
	}
	return (TRUE);
}
