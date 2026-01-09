/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouron <mlouron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 15:06:32 by damalca           #+#    #+#             */
/*   Updated: 2025/11/05 13:37:23 by mlouron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern char **environ;

static char	*get_env_value_cd(char **env, const char *name)
{
	int		i;
	size_t	len;

	if (!env || !name)
		return (NULL);
	len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}

static char	*expand_tilde(char *path, char **env)
{
	char	*home;
	char	*expanded;
	size_t	len;

	if (!path || path[0] != '~')
		return (path);
	if (path[1] != '\0' && path[1] != '/')
		return (path);
	home = get_env_value_cd(env, "HOME");
	if (!home)
		return (path);
	if (path[1] == '\0')
		return (home);
	len = ft_strlen(home) + ft_strlen(path + 1) + 1;
	expanded = malloc(len);
	if (!expanded)
		return (path);
	ft_strlcpy(expanded, home, len);
	ft_strlcat(expanded, path + 1, len);
	return (expanded);
}

void	update_env_var(char ***env, char *name, char *value)
{
	int		i;
	int		count;
	char	*new_var;
	char	**new_env;
	size_t	len;

	if (!env || !*env || !name || !*name)
		return ;
	if (!value)
		value = "";
	len = ft_strlen(name) + ft_strlen(value) + 2;
	new_var = malloc(len);
	if (!new_var)
		return ;
	ft_strlcpy(new_var, name, len);
	ft_strlcat(new_var, "=", len);
	ft_strlcat(new_var, value, len);
	i = 0;
	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], name, ft_strlen(name)) == 0
			&& (*env)[i][ft_strlen(name)] == '=')
		{
			free((*env)[i]);
			(*env)[i] = new_var;
			environ = *env;
			return ;
		}
		i++;
	}
	// Variable doesn't exist, need to add it
	count = i;
	new_env = malloc(sizeof(char *) * (count + 2));
	if (!new_env)
	{
		free(new_var);
		return ;
	}
	i = 0;
	while (i < count)
	{
		new_env[i] = (*env)[i];
		i++;
	}
	new_env[count] = new_var;
	new_env[count + 1] = NULL;
	free(*env);
	*env = new_env;
	environ = *env;
}

int	ft_cd(char **args, char ***env)
{
	char	*oldpwd;
	char	*target;
	char	*newpwd;
	char	*expanded;
	int		need_free;

	if (!args || !env || !*env)
		return (1);
	if (args[1] && args[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		oldpwd = ft_strdup("");
	if (!oldpwd)
		return (1);
	need_free = 0;
	if (!args[1] || ft_strcmp(args[1], "~") == 0)
	{
		target = get_env_value_cd(*env, "HOME");
		if (!target)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			free(oldpwd);
			return (1);
		}
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		target = get_env_value_cd(*env, "OLDPWD");
		if (!target)
		{
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
			free(oldpwd);
			return (1);
		}
		ft_putstr_fd(target, 1);
		ft_putstr_fd("\n", 1);
	}
	else
	{
		expanded = expand_tilde(args[1], *env);
		if (expanded != args[1])
			need_free = 1;
		target = expanded;
	}
	if (chdir(target) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		free(oldpwd);
		if (need_free)
			free(expanded);
		return (1);
	}
	newpwd = getcwd(NULL, 0);
	if (!newpwd)
		newpwd = ft_strdup("");
	if (!newpwd)
	{
		free(oldpwd);
		if (need_free)
			free(expanded);
		return (1);
	}
	update_env_var(env, "OLDPWD", oldpwd);
	update_env_var(env, "PWD", newpwd);
	free(newpwd);
	free(oldpwd);
	if (need_free)
		free(expanded);
	return (0);
}

