/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouron <mlouron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 14:53:45 by mlouron           #+#    #+#             */
/*   Updated: 2025/11/05 14:14:01 by mlouron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <sys/stat.h>

int	init_heredocs(t_command *cmds)
{
	t_command	*cur;

	cur = cmds;
	while (cur)
	{
		if (cur->heredoc_delim)
		{
			if (process_heredoc(cur))
				return (1);
		}
		cur = cur->next;
	}
	return (0);
}

static char	*read_line_heredoc(int is_tty)
{
	char	*line;
	char	buffer[1024];
	int		i;
	int		ret;

	if (is_tty)
		return (readline("> "));
	write(1, "> ", 2);
	i = 0;
	while (i < 1023)
	{
		ret = read(0, &buffer[i], 1);
		if (ret <= 0)
			return (NULL);
		if (buffer[i] == '\n')
		{
			buffer[i] = '\0';
			break;
		}
		i++;
	}
	buffer[i] = '\0';
	line = ft_strdup(buffer);
	return (line);
}

static int	write_heredoc_content(int fd, char *delim)
{
	char	*line;
	size_t	delim_len;
	int		is_tty;

	delim_len = ft_strlen(delim);
	is_tty = isatty(STDIN_FILENO);
	while (1)
	{
		line = read_line_heredoc(is_tty);
		if (!line)
		{
			if (is_tty)
			{
				ft_putstr_fd("minishell: warning: here-document delimited by end-of-file (wanted `", 2);
				ft_putstr_fd(delim, 2);
				ft_putstr_fd("')\n", 2);
			}
			break;
		}
		if (ft_strncmp(line, delim, delim_len) == 0 && line[delim_len] == '\0')
		{
			free(line);
			break;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	return (0);
}

int	process_heredoc(t_command *cmd)
{
	char	tmp_file[] = "/tmp/minishell_heredoc_XXXXXX";
	int		fd;

	if (!cmd->heredoc_delim)
		return (0);
	fd = mkstemp(tmp_file);
	if (fd == -1)
	{
		perror("minishell: mkstemp");
		return (1);
	}
	if (write_heredoc_content(fd, cmd->heredoc_delim))
	{
		close(fd);
		unlink(tmp_file);
		return (1);
	}
	close(fd);
	fd = open(tmp_file, O_RDONLY);
	unlink(tmp_file);
	if (fd == -1)
	{
		perror("minishell: open");
		return (1);
	}
	cmd->heredoc_fd = fd;
	return (0);
}
