/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouron <mlouron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 16:18:16 by shessoun          #+#    #+#             */
/*   Updated: 2025/11/04 14:09:47 by mlouron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "exit") == 0)
		return (1);
	if (ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "env") == 0)
		return (2);
	return (0);
}

void	exec_simple_builtin_parent(t_command *cmds, char **env, int *exit_status)
{
	int saved_stdin;
	int saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdin == -1 || saved_stdout == -1)
	{
		perror("dup");
		*exit_status = 1;
		return;
	}
	if (handle_redirections(cmds) == -1)
	{
		restore_stdio(saved_stdin, saved_stdout);
		*exit_status = 1;
		return;
	}
	if (ft_strcmp(cmds->args[0], "echo") == 0)
	{
		ft_echo(cmds->args);
		*exit_status = 0;
	}
	else if (ft_strcmp(cmds->args[0], "pwd") == 0)
	{
		ft_pwd();
		*exit_status = 0;
	}
	else if (ft_strcmp(cmds->args[0], "env") == 0)
	{
		ft_env(env);
		*exit_status = 0;
	}
	restore_stdio(saved_stdin, saved_stdout);
}

void	exec_builtin(t_command *cmds, char ***env, int *exit_status)
{
	int saved_stdin;
	int saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdin == -1 || saved_stdout == -1)
	{
		perror("dup");
		*exit_status = 1;
		return;
	}
	if (handle_redirections(cmds) == -1)
	{
		restore_stdio(saved_stdin, saved_stdout);
		*exit_status = 1;
		return;
	}
	if (ft_strcmp(cmds->args[0], "export") == 0)
		*exit_status = ft_export(cmds->args, env);
	else if (ft_strcmp(cmds->args[0], "cd") == 0)
		*exit_status = ft_cd(cmds->args, env);
	else if (ft_strcmp(cmds->args[0], "unset") == 0)
	{
		ft_unset(cmds->args, *env);
		*exit_status = 0;
	}
	else if (ft_strcmp(cmds->args[0], "exit") == 0)
		*exit_status = ft_exit(cmds->args);
	restore_stdio(saved_stdin, saved_stdout);
}
