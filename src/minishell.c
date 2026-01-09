/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouron <mlouron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 09:41:58 by mlouron           #+#    #+#             */
/*   Updated: 2025/11/05 14:02:30 by mlouron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int last_status = 0;

void	print_tokens(t_token *tokens)
{
	t_token *tmp = tokens;
	int i = 0;

	printf("===== TOKENS =====\n");
	while (tmp)
	{
		printf("[%d] value: '%s'\t", i, tmp->value);
		printf("type: %d\n", tmp->type);
		tmp = tmp->next;
		i++;
	}
	printf("==================\n");
}

void	print_commands(t_command *cmd)
{
	t_command	*tmp = cmd;
	t_redir		*redir;
	int			i;

	printf("===== COMMANDS =====\n");
	while (tmp)
	{
		printf("Command:\n");

		// Afficher les arguments
		i = 0;
		if (tmp->args)
		{
			while (tmp->args[i])
			{
				printf("  args[%d]: '%s'\n", i, tmp->args[i]);
				i++;
			}
		}
		redir = tmp->redirs;
		while (redir)
		{
			printf("  redir type:%d file:%s\n", redir->type, redir->file);
			redir = redir->next;
		}
		printf("---------------------\n");
		tmp = tmp->next;
	}
	printf("=====================\n");
}


int	main(int argc, char **argv, char **env)
{
	(void)argv;
	(void)argc;
	char		*line;
	t_token		*tokens;
	t_command	*cmd;
	int			exit_status;
	char		**shell_env;

	exit_status = 0;
	signal(SIGINT, sigint_handler);
	if (init_env(env, &shell_env))
		return (1);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			printf("exit\n");
			break;
		}
		if (*line)
			add_history(line);
		tokens = parse_line(line);
		if (!tokens)
		{
			free(line);
			continue;
		}
		cmd = parse_commands(tokens);
		if (!cmd)
		{
			free_tokens(tokens);
			free(line);
			continue;
		}
		if (init_heredocs(cmd))
		{
			free_tokens(tokens);
			free_commands(cmd);
			free(line);
			last_status = 1;
			continue;
		}
		exec_cmds(&shell_env, cmd, &exit_status);
		// print_tokens(tokens);
		// print_commands(cmd);
		free_tokens(tokens);
		free_commands(cmd);
		free(line);
		if (last_status < 0)
		{
			if (last_status == -1)
				exit_status = 0;
			else if (last_status == -2)
				exit_status = 2;
			else
				exit_status = -(last_status + 1000);
			break;
		}
		last_status = exit_status;
	}
	rl_clear_history();
	free_env(shell_env);
	return (exit_status);
}

