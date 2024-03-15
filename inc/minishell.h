/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmessett <pmessett>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:50:07 by pmessett          #+#    #+#             */
/*   Updated: 2024/03/15 00:06:10 by pmessett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/inc/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <unistd.h>

/* --- MACROS --- */

# define TOKEN_IDENTIFIER 0
# define TOKEN_OPERATOR 1
# define TOKEN_LITERAL 2
# define TOKEN_VARIABLE 3
# define TOKEN_ARG 4
# define TOKEN_KEYWORD 5
# define TOKEN_FILE 6
# define PARSER_REDIR_IN 7
# define PARSER_REDIR_OUT 8
# define PARSER_REDIR_APPEND 9
# define PARSER_REDIR_HERE_DOC 10

/* Token List */
typedef struct s_token
{
	int				type;
	char			*content;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

/*I/O*/
typedef struct s_io
{
	int				in;
	int				out;
}					t_io;

/* Command Table */
typedef struct s_cmd
{
	char			*cmd_path;
	char			**args;
	pid_t			pid;
	int				pipe_fd[2];
	int				dup2_fd[2];
	t_io			io;
	t_token			*redirs;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd_tb;

/* Enviroment Variables */
typedef struct s_env
{
	char			*content;
	struct s_env	*next;
	struct s_env	*prev;
}					t_env;

/* --- Lexical Analysis --- */

void				lex(char *prompt, t_env **env);
int					is_keyword(char *str, int len);
int					is_literal_string(char *str, int len);
int					is_redirection(char *str);

/* --- Token List --- */

t_token				*set_token(t_token *tokens, int type, char *str, int len);
void				free_tokens(t_token **token_list);
void				print_token_list(t_token *token_list);
void				iter_tokens(t_token **tokens);
void				add_token_to_tail(t_token **head, t_token *new_node);
t_token				*duplicate_token(t_token *token);

/* --- Parsing --- */

void				parser(t_token *tokens, t_env **env);

/* --- Checkers --- */

void				check_ac(int ac);
void				check_exit_status(char *arg);

/* --- Command Path Functions --- */

t_cmd_tb			*find_path(t_cmd_tb *cmd_tb, char **possible_paths,
						char *cmd, char **args);
t_cmd_tb			*choose_handle(char *cmd, t_cmd_tb *list, char **args,
						t_env **env);

/* --- Command Table Functions --- */

t_cmd_tb			*find_cmd_tb_tail(t_cmd_tb *cmd_tb);
t_cmd_tb			*set_cmd_tb(t_cmd_tb *cmd_tb, char *cmd_path, char **args);
void				free_cmd_tb(t_cmd_tb **cmd_tb);
void				print_list(t_cmd_tb *list);

/* --- Executer --- */

void				exec_cd(const char *directory, t_env **env);
void				exec_echo(char *arg, int fd, t_env **env);
void				exec_identifier(t_token *token, t_cmd_tb **cmd_list,
						t_env **env, t_token *redirs);
void				exec_pwd(int fd);

/* --- Child Process --- */

int					start_process(t_cmd_tb *cmd_tb, t_env **env);
void				bind_stdin(t_cmd_tb *curr);
void				bind_stdout(t_cmd_tb *curr);
void				bind_redirs(t_cmd_tb *curr);
int					bind_redir_in(t_cmd_tb *cmd, t_token *redir);
int					bind_redir_out(t_cmd_tb *cmd, t_token *redir);
int					bind_redir_append(t_cmd_tb *cmd, t_token *redir);
int					bind_redir_here_doc(t_cmd_tb *cmd, t_token *redir);

/* --- Environment --- */

char				*ft_getenv(char *name, t_env **env);
char				**get_full_env(t_env **env);
void				set_env(char *var, t_env **env);
t_env				*create_env(t_env *env_list, char *envp);
void				print_env(t_env **list, int fd);
void				free_env(t_env **env_list);
void				add_env_tail(t_env **list_head, t_env *new_path);
t_env				*add_env_node(char *envp);
void				unset_env(char *var, t_env **env);

/* --- Signals --- */

void				signal_handler(int sig);

/* --- Utils --- */

int					is_valid_identifier(char *str);

#endif
