/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoukou <schoukou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 23:04:08 by afaris            #+#    #+#             */
/*   Updated: 2022/11/07 17:11:53 by schoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

char	*copy_sub_string(char *arg, int index)
{
	int		i;
	char	*copy;

	i = 0;
	copy = malloc(sizeof(char) * (index + 1));
	if (!copy)
		raise_error("Memory Allocation Failed!", "malloc", EXIT_FAILURE, TRUE);
	while (arg && arg[i] && i < index)
	{
		copy[i] = arg[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

void	create_or_update_env_item(t_env **env, char *arg)
{
	t_env	*found;
	char	*key;
	char	*value;
	int		index;

	index = get_index_or_none(arg, '=');
	value = NULL;
	found = NULL;
	key = extract_env_key(arg, index);
	if (key)
	{
		found = get_env_item_or_none(key, *env);
		if (!found)
			add_env_item(env, arg);
		else
		{
			value = extract_env_value(arg, index);
			update_env_value(found, value);
		}
	}
	free(key);
}
