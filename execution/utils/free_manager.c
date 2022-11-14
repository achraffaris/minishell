/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaris <afaris@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 23:20:53 by afaris            #+#    #+#             */
/*   Updated: 2022/11/09 18:59:29 by afaris           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	free_2d_buff(char **buff)
{
	int	i;

	i = 0;
	if (buff)
	{
		while (buff[i])
		{
			free(buff[i]);
			buff[i] = NULL;
			i++;
		}
		free(buff);
		buff = NULL;
	}
}

void	free_buff(char *buff)
{
	if (buff)
	{
		free(buff);
		buff = NULL;
	}
}

void	free_redirections(t_rdr *red)
{
	t_rdr	*current;
	t_rdr	*tmp;

	current = red;
	if (current)
	{
		while (current)
		{
			if (current->value)
			{
				free(current->value);
				current->value = NULL;
			}
			tmp = current;
			current = current->next;
			free(tmp);
			tmp = NULL;
		}
	}
}

void	free_cmds(t_parse *cmd)
{
	t_parse	*current;
	t_parse	*tmp;

	tmp = NULL;
	current = cmd;
	while (current)
	{
		free_buff(current->cmd);
		free_buff(current->path);
		free_2d_buff(current->env_2d);
		free_2d_buff(current->cmd_2d);
		free_redirections(current->rdr);
		free_2d_buff(current->arg);
		current = current->next;
	}
	current = cmd;
	while (current)
	{
		tmp = current;
		current = current->next;
		free(tmp);
		tmp = NULL;
	}
}

void	free_all(t_parse *data, t_exec *exe)
{
	int	i;

	i = 0;
	free_cmds(data);
	if (exe)
	{
		if (exe->pipes)
		{
			while (exe->pipes[i])
			{
				free(exe->pipes[i]);
				i++;
			}
			free(exe->pipes);
		}
		free(exe);
	}
}
