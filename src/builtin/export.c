/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouron <mlouron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 15:06:20 by damalca           #+#    #+#             */
/*   Updated: 2025/11/05 13:29:55 by mlouron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern char **environ;

int	is_valid_variable(char *str)
{
	int	i;

	if (!str || !str[0] || ft_isdigit(str[0]) || str[0] == '=')
		return (0);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	update_or_add_env(char ***env, char *name, char *value)
{
	int		i;
	int		j;
	char	*new_var;
	char	**new_env;
	size_t	len;

	if (!env || !name || !*name)
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
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
	{
		free(new_var);
		return ;
	}
	j = 0;
	while (j < i)
	{
		new_env[j] = (*env)[j];
		j++;
	}
	new_env[i] = new_var;
	new_env[i + 1] = NULL;
	free(*env);
	*env = new_env;
	environ = *env;
}

static void	print_sorted_env(char **env)
{
	int		i;
	int		j;
	char	**sorted;
	char	*tmp;

	i = 0;
	while (env[i])
		i++;
	sorted = malloc(sizeof(char *) * (i + 1));
	if (!sorted)
		return ;
	i = -1;
	while (env[++i])
		sorted[i] = env[i];
	sorted[i] = NULL;
	i = -1;
	while (sorted[++i])
	{
		j = i;
		while (sorted[++j])
		{
			if (ft_strcmp(sorted[i], sorted[j]) > 0)
			{
				tmp = sorted[i];
				sorted[i] = sorted[j];
				sorted[j] = tmp;
			}
		}
		printf("export %s\n", sorted[i]);
	}
	free(sorted);
}

int	ft_export(char **args, char ***env)
{
	int		i;
	char	*eq_sign;
	char	*name;
	char	*value;
	int		ret;

	ret = 0;
	if (!args[1])
	{
		print_sorted_env(*env);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		eq_sign = ft_strchr(args[i], '=');
		if (eq_sign)
		{
			name = ft_substr(args[i], 0, eq_sign - args[i]);
			value = ft_strdup(eq_sign + 1);
		}
		else
		{
			name = ft_strdup(args[i]);
			value = NULL;
		}
		if (!is_valid_variable(name))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			ret = 1;
		}
		else if (value)
			update_or_add_env(env, name, value);
		free(name);
		if (value)
			free(value);
		i++;
	}
	return (ret);
}
