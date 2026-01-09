/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouron <mlouron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:51:56 by shessoun          #+#    #+#             */
/*   Updated: 2025/11/04 17:04:47 by mlouron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tabs(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

char	*find_cmd_path(char **paths, char *cmd)
{
	int		i;
	char	*part_path;
	char	*path;
	char	*tmp;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strdup(paths[i]);
		if (!tmp)
			return (NULL);
		part_path = ft_strjoin(tmp, "/");
		if (!part_path)
			return (NULL);
		path = ft_strjoin(part_path, cmd);
		if (!path)
			return (NULL);
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

void	path_not_found(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
}

char	*get_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;

	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH=", 5) == NULL)
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		return (NULL);
	path = find_cmd_path(paths, cmd);
	if (!path)
	{
		free_tabs(paths);
		return (NULL);
	}
	free_tabs(paths);
	return (path);
}
