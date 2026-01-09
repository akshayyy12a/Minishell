/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouron <mlouron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 15:56:09 by shessoun          #+#    #+#             */
/*   Updated: 2025/11/05 13:22:57 by mlouron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern char **environ;

static int	is_variable_assignment(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (str[i] == '=');
}

void	exec_cmds(char ***env, t_command *cmds, int *exit_status)
{
	if (!cmds)
		return ;
	if (cmds->next == NULL)
		exec(env, cmds, exit_status);
	else
		exec_pipes(cmds, *env, exit_status);
}

void	exec_command(char **env, t_command *cmds, int *exit_status)
{
	char	*path;
	pid_t	pid;
	int		status;

	path = resolve_path(cmds, env);
	if (!path)
	{
		if (ft_strchr(cmds->args[0], '/') && access(cmds->args[0], F_OK) == 0)
			*exit_status = 126;
		else
		{
			path_not_found(cmds->args[0]);
			*exit_status = 127;
		}
		return ;
	}
	pid = fork();
	if (pid == -1)
		return (free(path));
	if (pid == 0)
	{
		if (handle_redirections(cmds) == -1)
		{
			free(path);
			exit(1);
		}
		execve(path, cmds->args, env);
		execve_error(path);
	}
	waitpid(pid, &status, 0);
	exit_code(exit_status, status);
	free(path);
}

void	exec(char ***env, t_command *cmds, int *exit_status)
{
	int	builtin_type;

	if (!cmds || !cmds->args || !cmds->args[0])
	{
		*exit_status = 0;
		return ;
	}
	if (is_variable_assignment(cmds->args[0]))
	{
		*exit_status = 0;
		return ;
	}
	builtin_type = is_builtin(cmds->args[0]);
	if (builtin_type == 1)
	{
		exec_builtin(cmds, env, exit_status);
		return ;
	}
	if (builtin_type == 2)
	{
		exec_simple_builtin_parent(cmds, *env, exit_status);
		return ;
	}
	exec_command(*env, cmds, exit_status);
}

void	exec_no_fork(char **env, t_command *cmds, int *exit_status)
{
	char	*path;
	int		builtin_type;

	if (!cmds || !cmds->args || !cmds->args[0])
		exit(EXIT_SUCCESS);
	builtin_type = is_builtin(cmds->args[0]);
	if (builtin_type == 1)
		exit(EXIT_SUCCESS);
	if (builtin_type == 2)
	{
		exec_simple_builtin_parent(cmds, env, exit_status);
		exit(*exit_status);
	}
	path = resolve_path(cmds, env);
	if (!path)
	{
		if (ft_strchr(cmds->args[0], '/'))
		{
			if (access(cmds->args[0], F_OK) == 0)
				exit(126);
			else
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(cmds->args[0], 2);
				ft_putstr_fd(": No such file or directory\n", 2);
				exit(127);
			}
		}
		else
		{
			path_not_found(cmds->args[0]);
			exit(127);
		}
	}
	if (handle_redirections(cmds) == -1)
	{
		free(path);
		exit(1);
	}
	execve(path, cmds->args, env);
	execve_error(path);
}
