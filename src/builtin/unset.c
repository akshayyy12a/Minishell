/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouron <mlouron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 12:25:18 by damalca           #+#    #+#             */
/*   Updated: 2025/11/04 14:10:51 by mlouron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	remove_env_var(char **env, int index)
{
	int		i;

	i = index;
	while (env[i])
	{
		env[i] = env[i + 1];
		i++;
	}
}

void ft_unset(char **args, char **env)
{
	int		i;
	int		j;
	int		len;
	char	*str;
	char	*eq_pos;

	i = 1;
	len = 0;
	while (args[i])
	{
		j = 0;
		while (env[j])
		{
			eq_pos = ft_strchr(env[j], '=');
			if (!eq_pos)
			{
				j++;
				continue;
			}
			str = ft_substr(env[j], 0, eq_pos - env[j]);
			if (ft_strcmp(str, args[i]) == 0)
			{
				free(str);
				remove_env_var(env, j);
				break;
			}
			free(str);
			j++;
		}
		i++;
	}
}
