/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouron <mlouron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 16:03:44 by shessoun          #+#    #+#             */
/*   Updated: 2025/11/05 14:05:45 by mlouron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_redirections(t_command *cmd)
{
	int		fd;
	int		last_in;
	int		last_out;
	t_redir	*redir;

	last_in = -1;
	last_out = -1;
	redir = cmd->redirs;
	while (redir)
	{
		if (redir->type == REDIR_IN)
		{
			if (last_in != -1)
				close(last_in);
			fd = open(redir->file, O_RDONLY);
			if (fd == -1)
				return (perror(redir->file), -1);
			last_in = fd;
		}
		else if (redir->type == HEREDOC)
		{
			if (last_in != -1)
				close(last_in);
			if (cmd->heredoc_fd == -1)
				return (-1);
			last_in = dup(cmd->heredoc_fd);
			if (last_in == -1)
			{
				perror("dup");
				return (-1);
			}
		}
		else if (redir->type == REDIR_OUT || redir->type == APPEND)
		{
			if (last_out != -1)
				close(last_out);
			if (redir->type == APPEND)
				fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			else
				fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
				return (perror(redir->file), -1);
			last_out = fd;
		}
		redir = redir->next;
	}
	if (last_in != -1)
	{
		dup2(last_in, STDIN_FILENO);
		close(last_in);
	}
	if (last_out != -1)
	{
		dup2(last_out, STDOUT_FILENO);
		close(last_out);
	}
	return (0);
}

void	restore_stdio(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}
