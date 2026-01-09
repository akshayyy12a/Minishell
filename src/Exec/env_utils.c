/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouron <mlouron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:40:00 by mlouron           #+#    #+#             */
/*   Updated: 2025/11/05 14:23:54 by mlouron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern char **environ;

static char	*find_env_var(char **env, const char *name)
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

static char	**add_env_var(char **env, const char *var)
{
	int		count;
	int		i;
	char	**new_env;

	count = 0;
	while (env && env[count])
		count++;
	new_env = malloc(sizeof(char *) * (count + 2));
	if (!new_env)
		return (env);
	i = 0;
	while (i < count)
	{
		new_env[i] = env[i];
		i++;
	}
	new_env[count] = ft_strdup(var);
	new_env[count + 1] = NULL;
	free(env);
	return (new_env);
}

static char	**update_env_var(char **env, const char *name, const char *value)
{
	int		i;
	size_t	name_len;
	char	*new_var;
	size_t	len;

	name_len = ft_strlen(name);
	len = name_len + ft_strlen(value) + 2;
	new_var = malloc(len);
	if (!new_var)
		return (env);
	ft_strlcpy(new_var, name, len);
	ft_strlcat(new_var, "=", len);
	ft_strlcat(new_var, value, len);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, name_len) == 0 && env[i][name_len] == '=')
		{
			free(env[i]);
			env[i] = new_var;
			return (env);
		}
		i++;
	}
	free(new_var);
	return (env);
}

static char	**increment_shlvl(char **env)
{
	char	*shlvl_str;
	int		shlvl;
	char	*new_shlvl;

	shlvl_str = find_env_var(env, "SHLVL");
	if (!shlvl_str)
		return (add_env_var(env, "SHLVL=1"));
	shlvl = ft_atoi(shlvl_str);
	shlvl++;
	new_shlvl = ft_itoa(shlvl);
	if (!new_shlvl)
		return (env);
	env = update_env_var(env, "SHLVL", new_shlvl);
	free(new_shlvl);
	return (env);
}

static char	**init_minimal_env(char **env)
{
	char	cwd[1024];
	char	*pwd_var;

	if (!find_env_var(env, "PWD"))
	{
		if (getcwd(cwd, sizeof(cwd)))
		{
			pwd_var = malloc(ft_strlen("PWD=") + ft_strlen(cwd) + 1);
			if (pwd_var)
			{
				ft_strlcpy(pwd_var, "PWD=", ft_strlen("PWD=") + 1);
				ft_strlcat(pwd_var, cwd, ft_strlen("PWD=") + ft_strlen(cwd) + 1);
				env = add_env_var(env, pwd_var);
				free(pwd_var);
			}
		}
	}
	env = increment_shlvl(env);
	if (!find_env_var(env, "_"))
		env = add_env_var(env, "_=/usr/bin/env");
	return (env);
}

void	free_env(char **env)
{
	int i;
	if (!env)
		return;
	i = 0;
	while (env[i])
		free(env[i++]);
	free(env);
}

int	init_env(char **envp, char ***out_env)
{
	int count;
	int i;
	char **dup;

	if (!out_env)
		return (1);
	count = 0;
	while (envp && envp[count])
		count++;
	dup = (char **)malloc(sizeof(char *) * (count + 1));
	if (!dup)
		return (1);
	i = 0;
	while (i < count)
	{
		dup[i] = ft_strdup(envp[i]);
		if (!dup[i])
		{
			while (i > 0)
				free(dup[--i]);
			free(dup);
			return (1);
		}
		i++;
	}
	dup[count] = NULL;
	*out_env = dup;
	*out_env = init_minimal_env(*out_env);
	environ = *out_env;
	return (0);
}
