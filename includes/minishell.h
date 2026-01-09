/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouron <mlouron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 09:40:11 by mlouron           #+#    #+#             */
/*   Updated: 2025/11/05 12:23:11 by mlouron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H
# include "../Libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

extern int last_status;

typedef enum TokenType {
	CMD,
	ARG,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC,
}	t_token_type;

typedef struct s_token {
	char *value;
	t_token_type type;
	struct s_token *next;
}		t_token;

typedef struct s_redir
{
	int					type;
	char				*file;
	struct s_redir		*next;
}	t_redir;

typedef struct s_command
{
	char				**args;
	t_redir				*redirs;
	char				*heredoc_delim;
	int					heredoc_fd;
	struct s_command	*next;
}	t_command;

//Parsing
t_token		*tokenize(char **args);
t_token		*parse_line(char *line);
t_command	*parse_commands(t_token *tokens);
char		*expand_variables(const char *str, int last_status);
char		*get_env_value(const char *name);
void		free_commands(t_command *cmd);
void		free_tokens(t_token *tokens);
int			process_heredoc(t_command *cmd);
int			init_heredocs(t_command *cmds);


// Signal
void		init_signals_heredoc(void);
void		init_signals_child(void);
void		init_signals_main(void);
void		heredoc_sigint_handler(int sig);
void		sigint_handler(int sig);

//Exec
void		exec(char ***env, t_command *cmds, int *exit_status);
void		exec_cmds(char ***env, t_command *cmds, int *exit_status);
void		exec_no_fork(char **env, t_command *cmds, int *exit_status);
char		*get_path(char *cmd, char **envp);
void		path_not_found(char *cmd);
int			handle_redirections(t_command *cmd);
void		exec_pipes(t_command *cmds, char **env, int *exit_status);
char		*resolve_path(t_command *cmds, char **env);
void		execve_error(char *path);
void		exit_code(int *exit_status, int status);
void		exec_builtin(t_command *cmds, char ***env, int *exit_status);
void		exec_simple_builtin_parent(t_command *cmds, char **env, int *exit_status);
void		restore_stdio(int saved_stdin, int saved_stdout);
int			init_env(char **envp, char ***out_env);
void		free_env(char **env);

//Builtin
int			is_builtin(char *cmd);
int			ft_cd(char **args, char ***env);
void		ft_echo(char **args);
void		ft_env(char **env);
int			ft_exit(char **args);
int			ft_export(char **args, char ***env);
void		ft_pwd(void);
void		ft_unset(char **args, char **env);
#endif
