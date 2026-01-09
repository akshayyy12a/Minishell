/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouron <mlouron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 14:30:39 by mlouron           #+#    #+#             */
/*   Updated: 2025/11/04 14:27:24 by mlouron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern char **environ;

static int	is_redir_char(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

static int	count_tokens(char *line)
{
	int		count;
	int		i;
	char	quote;

	count = 0;
	i = 0;
	while (line[i])
	{
		while (line[i] && line[i] == ' ')
			i++;
		if (line[i])
		{
			count++;
			quote = 0;
			if (!quote && is_redir_char(line[i]))
			{
				if (line[i] == line[i + 1])
					i++;
				i++;
				continue;
			}
			while (line[i] && (quote || (line[i] != ' ' && !is_redir_char(line[i]))))
			{
				if (!quote && (line[i] == '\'' || line[i] == '"'))
					quote = line[i];
				else if (quote && line[i] == quote)
					quote = 0;
				i++;
			}
		}
	}
	return (count);
}

static char	*extract_token(char *line, int *i)
{
	int		start;
	int		len;
	char	quote;
	char	*token;

	start = *i;
	quote = 0;
	if (!quote && is_redir_char(line[*i]))
	{
		if (line[*i] == line[*i + 1])
			(*i)++;
		(*i)++;
		len = *i - start;
		token = malloc(len + 1);
		if (!token)
			return (NULL);
		ft_strlcpy(token, line + start, len + 1);
		return (token);
	}
	while (line[*i] && (quote || (line[*i] != ' ' && !is_redir_char(line[*i]))))
	{
		if (!quote && (line[*i] == '\'' || line[*i] == '"'))
			quote = line[*i];
		else if (quote && line[*i] == quote)
			quote = 0;
		(*i)++;
	}
	len = *i - start;
	token = malloc(len + 1);
	if (!token)
		return (NULL);
	ft_strlcpy(token, line + start, len + 1);
	return (token);
}

char **split_line(char *line)
{
	char	**args;
	int		count;
	int		i;
	int		j;

	count = count_tokens(line);
	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);
	i = 0;
	j = 0;
	while (line[i])
	{
		while (line[i] && line[i] == ' ')
			i++;
		if (line[i])
		{
			args[j] = extract_token(line, &i);
			if (!args[j])
			{
				while (j > 0)
					free(args[--j]);
				free(args);
				return (NULL);
			}
			j++;
		}
	}
	args[j] = NULL;
	return (args);
}

t_token *parse_line(char *line)
{
	char	**args;
	t_token	*tokens;
	int		i;

	args = split_line(line);
	i = 0;
	if (!args)
		return NULL;
	tokens = tokenize(args);
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
	return tokens;
}

char	*get_env_value(const char *name)
{
	int i;
	size_t len;
	
	i = 0;
	len = ft_strlen(name);
	while (environ[i])
	{
		if (!ft_strncmp(environ[i], name, len) && environ[i][len] == '=')
			return (environ[i] + len + 1);
		i++;
	}
	return ("");
}

static char	*append_str(char *dst, const char *src)
{
	char	*new;
	size_t	len;

	len = strlen(dst) + strlen(src);
	new = malloc(len + 1);
	if (!new)
		return (NULL);
	strcpy(new, dst);
	strcat(new, src);
	free(dst);
	return (new);
}

static char	*expand_var(const char *str, int *i, int last_status)
{
	char	var[256];
	char	tmp[16];
	int		j;
	char	*value;

	if (str[*i] == '?')
	{
		snprintf(tmp, sizeof(tmp), "%d", last_status);
		(*i)++;
		return (strdup(tmp));
	}
	j = 0;
	while (str[*i] && (isalnum(str[*i]) || str[*i] == '_'))
		var[j++] = str[(*i)++];
	var[j] = '\0';
	value = get_env_value(var);
	if (!value)
		return (strdup(""));
	return (strdup(value));
}

char	*expand_variables(const char *str, int last_status)
{
	int		i;
	char	quote;
	char	*res;
	char	*tmp;

	i = 0;
	quote = 0;
	res = calloc(1, 1);
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"'))
		{
			if (!quote)
				quote = str[i];
			else if (quote == str[i])
				quote = 0;
			char c[2] = {str[i++], '\0'};
			res = append_str(res, c);
		}
		else if (str[i] == '$' && str[i + 1])
		{
			if (quote == '\'')
			{
				char c[2] = {str[i++], '\0'};
				res = append_str(res, c);
			}
			else
			{
				char next = str[i + 1];
				if (!(isalnum((unsigned char)next) || next == '_' || next == '?'))
				{
					char c[2] = {str[i++], '\0'};
					res = append_str(res, c);
				}
				else
				{
					i++;
					tmp = expand_var(str, &i, last_status);
					res = append_str(res, tmp);
					free(tmp);
				}
			}
		}
		else
		{
			char c[2] = {str[i++], '\0'};
			res = append_str(res, c);
		}
	}
	return (res);
}

