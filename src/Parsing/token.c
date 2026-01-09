/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouron <mlouron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 14:46:59 by mlouron           #+#    #+#             */
/*   Updated: 2025/11/04 14:27:31 by mlouron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*remove_quotes(const char *str)
{
	int		i;
	int		j;
	char	quote;
	char	*res;

	i = 0;
	j = 0;
	quote = 0;
	res = malloc(strlen(str) + 1);
	if (!res)
		return (NULL);
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"'))
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				res[j++] = str[i++];
			if (str[i] == quote)
				i++;
		}
		else
			res[j++] = str[i++];
	}
	res[j] = '\0';
	return (res);
}

void fill_type(char *arg, int i, t_token *token)
{
	if (strcmp(arg, "|") == 0)
		token->type = PIPE;
	else if (strcmp(arg, ">>") == 0)
		token->type = APPEND;
	else if (strcmp(arg, "<<") == 0)
		token->type = HEREDOC;
	else if (strcmp(arg, ">") == 0)
		token->type = REDIR_OUT;
	else if (strcmp(arg, "<") == 0)
		token->type = REDIR_IN;
	else if (i == 0)
		token->type = CMD;
	else
		token->type = ARG;
}

t_token *create_token(char *arg, int i)
{
	t_token *token;
	char *expanded;

	token = malloc(sizeof(t_token));
	if (!token)
		return NULL;
	expanded = expand_variables(arg, last_status);
	if (!expanded)
	{
		free(token);
		return NULL;
	}
	token->value = remove_quotes(expanded);
	free(expanded);
	if (!token->value)
	{
		free(token);
		return NULL;
	}
	token->next = NULL;
	fill_type(arg, i, token);
	return token;
}

t_token *tokenize(char **args)
{
	t_token	*head;
	t_token	*last;
	t_token	*new;
	int i;

	head = NULL;
	last = NULL;
	i = 0;
	while (args[i])
	{
		new = create_token(args[i], i);
		if (!new)
		{
			free_tokens(head);
			return NULL;
		}
		if (!head)
			head = new;
		else
			last->next = new;
		last = new;
		i++;
	}
	return head;
}
