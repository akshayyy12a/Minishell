/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouron <mlouron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 14:06:44 by shessoun          #+#    #+#             */
/*   Updated: 2025/11/04 15:34:34 by mlouron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <sys/stat.h>

char	*resolve_path(t_command *cmds, char **env)
{
	struct stat	path_stat;

	if (ft_strchr(cmds->args[0], '/'))
	{
		if (access(cmds->args[0], F_OK) == -1)
			return (NULL);
		if (stat(cmds->args[0], &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmds->args[0], 2);
			ft_putstr_fd(": Is a directory\n", 2);
			return (NULL);
		}
		if (access(cmds->args[0], X_OK) == -1)
		{
			perror(cmds->args[0]);
			return (NULL);
		}
		return (ft_strdup(cmds->args[0]));
	}
	return (get_path(cmds->args[0], env));
}

void	execve_error(char *path)
{
	perror("execve");
	free(path);
	exit(1);
}

void	exit_code(int *exit_status, int status)
{
	if (WIFEXITED(status))
		*exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		*exit_status = 128 + WTERMSIG(status);
	else
		*exit_status = 1;
}
