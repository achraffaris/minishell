/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaris <afaris@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 23:24:34 by afaris            #+#    #+#             */
/*   Updated: 2022/11/09 22:24:29 by afaris           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	execute_cmd(t_parse *cmd, t_env **env)
{
	if (cmd->type == BUILTIN_CMD)
	{
		g_exitm = 0;
		run_as_builtin(cmd, env);
		if (cmd->pid != NONE)
			exit(g_exitm);
	}
	else
	{
		if (cmd->cmd)
		{
			if (ft_strlen(cmd->cmd))
				check_cmd_path(cmd->path);
			if (execve(cmd->path, cmd->cmd_2d, cmd->env_2d) == ERROR_RETURNED)
				raise_error("command not found", cmd->cmd, 127, TRUE);
		}
	}
}

void	sig_handler(int sig)
{
	if (sig == SIGINT)
		g_exitm = SIGINT + 128;
	else if (sig == SIGQUIT)
		g_exitm = SIGQUIT + 128;
}

void	run_cmd(t_parse *data, t_env **env, t_exec *exe)
{
	t_parse	*current;

	current = data;
	if (current && current->status == OK)
	{
		if (exe->pipes || current->type == NORMAL_CMD)
			current->pid = fork();
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, SIG_IGN);
		if (current->pid == 0 || current->pid == NONE)
		{
			signal(SIGINT, sig_handler);
			signal(SIGQUIT, SIG_DFL);
			current->read_src = get_read_src(current, exe);
			current->write_dst = get_write_dst(current, exe);
			hold_standard_fds(exe);
			dup_close_fds(current, exe);
			execute_cmd(current, env);
			reset_standard_fds(exe);
			if (current->pid == 0)
				exit(g_exitm);
		}
	}	
}

void	setup_run_cmds(t_parse *data, t_env **env, t_exec *exe)
{
	t_parse	*current;
	int		i;

	i = 0;
	current = data;
	cmds_initialization(data);
	while (current)
	{
		current->id = i;
		current->type = get_cmd_type(current->cmd);
		if (current->type == NORMAL_CMD && ft_strlen(current->cmd))
		{
			current->path = find_cmd_path(current->cmd, *env);
			current->cmd_2d = get_full_cmd(current->cmd, current->arg);
			current->env_2d = env_converter(*env);
		}
		if (current->read_src != ERROR_FILE && current->write_dst != ERROR_FILE)
			current->status = OK;
		else
			current->status = KO;
		run_cmd(current, env, exe);
		current = current->next;
		i++;
	}
}

void	execution(t_parse *data, t_env **env)
{
	t_exec	*exe;

	exe = setup_exec(data);
	setup_run_cmds(data, env, exe);
	close_fds(exe, data);
	wait_cmds(data);
	free_all(data, exe);
}
