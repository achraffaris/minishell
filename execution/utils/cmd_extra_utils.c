/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_extra_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoukou <schoukou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 23:17:05 by afaris            #+#    #+#             */
/*   Updated: 2022/11/09 23:40:59 by schoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	get_cmd_type(char *cmd_name)
{
	if (is_identical(cmd_lower(cmd_name), ECHO)
		|| is_identical(cmd_lower(cmd_name), CD)
		|| is_identical(cmd_lower(cmd_name), PWD)
		|| is_identical(cmd_name, EXPORT)
		|| is_identical(cmd_name, UNSET)
		|| is_identical(cmd_lower(cmd_name), ENV)
		|| is_identical(cmd_name, EXIT))
		return (BUILTIN_CMD);
	return (NORMAL_CMD);
}

void	wait_cmds(t_parse *cmds)
{
	t_parse	*current;

	current = cmds;
	while (current)
	{
		if (current->pid != NONE)
		{
			waitpid(current->pid, &g_exitm, WUNTRACED);
			if (WIFEXITED(g_exitm))
				g_exitm = WEXITSTATUS(g_exitm);
			else if (WIFSIGNALED(g_exitm))
				g_exitm = WTERMSIG(g_exitm) + 128;
		}
		current = current->next;
	}
}

void	cmds_initialization(t_parse *cmds)
{
	t_parse	*current;

	current = cmds;
	while (current)
	{
		current->cmd_2d = NULL;
		current->env_2d = NULL;
		current->path = NULL;
		current->pid = NONE;
		current->read_src = get_input_redirection(current);
		current->write_dst = get_output_redirection(current);
		current = current->next;
	}
}

void	check_cmd_path(char *path)
{
	struct stat	file_data;

	if (path)
	{
		if (stat(path, &file_data) != ERROR_RETURNED)
		{
			if (S_ISDIR(file_data.st_mode))
				raise_error("Is a directory", path, 126, TRUE);
		}
		if (path[0] == '.' || path[0] == '/')
		{
			if (access(path, X_OK) == ERROR_RETURNED)
				raise_error(NULL, path, 126, TRUE);
		}
	}
}
