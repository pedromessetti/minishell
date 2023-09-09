/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annamarianunes <annamarianunes@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 20:17:43 by pedro             #+#    #+#             */
/*   Updated: 2023/09/09 16:42:52 by annamarianu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/inc/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <unistd.h>
# include <signal.h>

/* --- Tokens --- */

# define TOKEN_IDENTIFIER 0
# define TOKEN_OPERATOR 1
# define TOKEN_LITERAL 2
# define TOKEN_ENV_VARIABLE 3
# define TOKEN_ARG 4
# define TOKEN_KEYWORD 5
# define TOKEN_FILE 6

/* Token List */
typedef struct s_token
{
	int				type;
	char			*content;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

/* Command Table */
typedef struct s_cmd
{
	char			*cmd_path;
	char			**args;
	pid_t			pid;
	int				pipe_fd[2];
	int				dup2_fd[2];
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd_tb;


/* --- Lexical Analysis --- */

void				lex(char *prompt);
int					is_keyword(char *str, int len);
int					is_literal_string(char *str, int len);

/* --- Token List --- */

t_token				*set_token(t_token *tokens, int type, char *str, int len);
void				free_tokens(t_token **token_list);
void				print_token_list(t_token *token_list);

/* --- Parsing --- */

int					parser(t_token *tokens);

/* --- Checkers --- */

void				check_ac(int ac);
void				check_exit_status(char *arg);

/* --- Command Path Functions --- */

t_cmd_tb			*find_path(t_cmd_tb *cmd_tb, char **possible_paths,
						char *cmd, char **args);
t_cmd_tb			*choose_handle(char *cmd, t_cmd_tb *list, char **args);

/* --- Command Table Functions --- */

t_cmd_tb			*set_cmd_tb(t_cmd_tb *cmd_tb, char *cmd_path, char **args);
void				free_cmd_tb(t_cmd_tb **cmd_tb);
void				print_list(t_cmd_tb *list);

/* --- Executer --- */

void				exec_cd(const char *directory);
void				exec_echo(const char **args);
void				exec_env(void);
void				exec_identifier(t_token *token, t_cmd_tb **cmd_list);

/* --- Child Process --- */

int					start_process(t_cmd_tb *cmd_tb);

/* --- Environment --- */

char				*ft_getenv(char *name);
int					create_env(char **envp);
char				**get_full_env(void);

/* --- Signals --- */

void	signal_handler(int sig);

#endif
