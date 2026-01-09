/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouron <mlouron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 12:09:15 by mlouron           #+#    #+#             */
/*   Updated: 2025/11/05 13:14:06 by mlouron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	t_command	*new_command(void)
{
	t_command	*cmd;
	
	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->redirs = NULL;
	cmd->heredoc_delim = NULL;
	cmd->heredoc_fd = -1;
	cmd->next = NULL;
	return (cmd);
}

static	int	add_arg(t_command *cmd, char *arg)
{
	int		i;
	char	**new_args;
	int		j;

	i = 0;
	j = 0;
	if (!cmd->args)
	{
		cmd->args = malloc(sizeof(char *) * 2);
		if (!cmd->args)
			return (0);
		cmd->args[0] = ft_strdup(arg);
		cmd->args[1] = NULL;
		return (1);
	}
	while (cmd->args[i])
		i++;
	new_args = malloc(sizeof(char *) * (i + 2));
	if (!new_args)
		return (0);
	j = 0;
	while (j < i)
	{
		new_args[j] = cmd->args[j];
		j++;
	}
	new_args[i] = ft_strdup(arg);
	new_args[i + 1] = NULL;
	free(cmd->args);
	cmd->args = new_args;
	return (1);
}

static int	handle_redir(t_command *cmd, t_token **t, t_command *head)
{
	t_redir	*new_redir;
	t_redir	*last;

	if (!(*t)->next || (*t)->next->type != ARG)
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		free_commands(head);
		return (1);
	}
	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return (1);
	new_redir->type = (*t)->type;
	new_redir->file = ft_strdup((*t)->next->value);
	new_redir->next = NULL;
	if (!cmd->redirs)
		cmd->redirs = new_redir;
	else
	{
		last = cmd->redirs;
		while (last->next)
			last = last->next;
		last->next = new_redir;
	}
	if ((*t)->type == HEREDOC)
	{
		free(cmd->heredoc_delim);
		cmd->heredoc_delim = ft_strdup((*t)->next->value);
	}
	(*t) = (*t)->next;
	return (0);
}

static int	handle_pipe(t_command **cur, t_token *tokens, t_command *head)
{
	if (!tokens->next)
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		free_commands(head);
		return (1);
	}
	(*cur)->next = new_command();
	*cur = (*cur)->next;
	return (0);
}

t_command	*parse_commands(t_token *tokens)
{
	t_command	*head;
	t_command *current;

	head = NULL;
	current = NULL;
	while (tokens)
	{
		if (!current && !(current = new_command()))
			return (NULL);
		if (!head) 
			head = current;
		if (tokens->type == CMD || tokens->type == ARG)
		{
			if (tokens->value && tokens->value[0] != '\0')
				add_arg(current, tokens->value);
		}
		else if (tokens->type == REDIR_IN || tokens->type == REDIR_OUT
			|| tokens->type == APPEND || tokens->type == HEREDOC)
		{
			if (handle_redir(current, &tokens, head))
				return (NULL);
		}
		else if (tokens->type == PIPE && handle_pipe(&current, tokens, head))
			return (NULL);
		tokens = tokens->next;
	}
	return (head);
}
