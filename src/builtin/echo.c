/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouron <mlouron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 15:06:29 by damalca           #+#    #+#             */
/*   Updated: 2025/11/04 13:55:47 by mlouron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_flag(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-')
		i++;
	else
		return (0);
	if (arg[i] == 'n')
		while (arg[i] == 'n')
			i++;
	else
		return (0);
	if (arg[i] == '\0')
		return (1);
	return (0);
}

void	ft_echo(char **args)
{
	int	i;
	int	newline;

	newline = 0;
	i = 1;
	while (args[i] && is_flag(args[i]))
	{
		newline = 1;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (newline == 0)
		ft_putchar_fd('\n', 1);
}
