/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouron <mlouron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 12:13:50 by mlouron           #+#    #+#             */
/*   Updated: 2025/11/04 15:24:03 by mlouron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_commands(t_command *cmd)
{
	t_command	*tmp;
	t_redir		*redir;
	t_redir		*redir_tmp;
	int			i;

	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->args)
		{
			i = 0;
			while (cmd->args[i])
				free(cmd->args[i++]);
			free(cmd->args);
		}
		redir = cmd->redirs;
		while (redir)
		{
			redir_tmp = redir->next;
			free(redir->file);
			free(redir);
			redir = redir_tmp;
		}
		free(cmd->heredoc_delim);
		if (cmd->heredoc_fd >= 0)
			close(cmd->heredoc_fd);
		free(cmd);
		cmd = tmp;
	}
}

void free_tokens(t_token *tokens)
{
	t_token *tmp;
	while (tokens)
	{
		tmp = tokens->next;
		free(tokens->value);
		free(tokens);
		tokens = tmp;
	}
}
