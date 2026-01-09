/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouron <mlouron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 12:38:45 by shessoun          #+#    #+#             */
/*   Updated: 2025/11/04 14:21:29 by mlouron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	child_process(t_command *cmd, int prev_fd, int *fd)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (cmd->next)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
	}
}

static void	close_parent_fds(int *prev_fd, int *fd, t_command *cmd)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (cmd->next)
	{
		*prev_fd = fd[0];
		close(fd[1]);
	}
	else
		*prev_fd = -1;
}

void	exec_pipes(t_command *cmds, char **env, int *exit_status)
{
	int			fd[2];
	int			prev_fd;
	pid_t		pid;
	pid_t		last_pid;
	pid_t		wpid;
	t_command	*cur;
	int			status;

	prev_fd = -1;
	cur = cmds;
	last_pid = -1;
	while (cur)
	{
		if (cur->next && pipe(fd) == -1)
			return (perror("pipe"));
		pid = fork();
		if (pid == -1)
			return (perror("fork"));
		if (pid == 0)
		{
			child_process(cur, prev_fd, fd);
			exec_no_fork(env, cur, exit_status);
		}
		if (!cur->next)
			last_pid = pid;
		close_parent_fds(&prev_fd, fd, cur);
		cur = cur->next;
	}
	while ((wpid = waitpid(-1, &status, 0)) > 0)
	{
		if (wpid == last_pid)
			exit_code(exit_status, status);
	}
}
