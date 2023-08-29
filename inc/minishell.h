/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annamarianunes <annamarianunes@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 20:17:43 by pedro             #+#    #+#             */
/*   Updated: 2023/08/29 13:23:09 by annamarianu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL _H

# include "../libft/inc/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <stddef.h>
# include <unistd.h>


/* --- Macro Colors --- */

# define RED "\033[0;31m"
# define WHITE "\033[0;37m"
# define RESET "\033[0m"

/* --- Tokens --- */

#define TOKEN_IDENTIFIER 0 		// commands, program name and other user-defined (ex: ls, ./minishell)
#define TOKEN_OPERATOR 1			// operators	(ex: |, <, >)
#define TOKEN_LITERAL 2				// literals strings (ex: "hello 123")
#define TOKEN_ENV_VARIABLE 3	// environment variables (ex: $PATH)
#define TOKEN_ARG 4						// arguments (ex: ls -l, -l is an argument)
#define TOKEN_KEYWORD 5				// keywords (ex: exit, cd, export, unset, echo, env, pwd)
#define TOKEN_FILE 6					

/* --- Token Type Structure --- */

typedef struct s_token
{
	int	type;
	char content[100]; // Ajustar size depois
}		t_token;

/* --- Command Table Structure --- */

typedef struct s_cmd
{
	char			*path;
	char			**args;
	pid_t			pid;
	int				pipe_fd[2];
	int				dup2_fd[2];
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd_tb;

/* --- Lexical Analysis --- */

void	lex(char *prompt, char **envp);
void	create_token(t_token *token, int type, char *str, int len);
int	identify_token_type(char *str, int len, int *next_token_type, int *echo_flag, int prev_token_type);
int is_keyword(char *str, int len);
int is_literal_string(char *str, int len);
int parser(t_token *tokens, int token_count, char **envp);
// /* --- Checker Functions --- */

void				check_ac(int ac);
// int					*check_fd(int fd[], char **av, int ac);
// int					check_builtin(char *av);
// void				check_exit_status(t_cmd_tb *path_list);
// int					ask_for_exit_status(char **args);

// /* --- Global Variable --- */

// extern int			g_last_exit_status;

// /* --- Path Functions --- */

// char				**set_possible_paths(char **envp);
t_cmd_tb	*find_path(t_cmd_tb *path_list, char **possible_paths, char *cmd, char **args);
// t_cmd_tb				*define_path(t_cmd_tb *list, char *buf, char **envp);
// t_cmd_tb				*handle_str_error(char *buf, t_cmd_tb *path_list);
t_cmd_tb	*choose_handle(char *cmd, char **envp, t_cmd_tb *list, char **args);

// /* --- List Functions --- */

t_cmd_tb				*add_path(char *path, char **args);
void				add_tail(t_cmd_tb **list_head, t_cmd_tb *new_path);
t_cmd_tb				*find_last(t_cmd_tb *paths_list);
void				free_path_list(t_cmd_tb **paths_list);
t_cmd_tb				*set_cmd_tb_list(t_cmd_tb *path_list, char *path,
						char **args);

// /* --- Child Process Functions --- */

// void				child_process(t_cmd_tb *path_list, char **envp);
// void				bind_stdin(t_cmd_tb *curr);
// void				bind_stdout(t_cmd_tb *curr);
// int					ft_wait(t_cmd_tb *curr);
// int					start_process(t_cmd_tb *path_list, char **envp);
// void				exec_cmd(t_cmd_tb *path_list, char **envp);

// /* --- Heredoc Functions --- */

// int					is_here_doc(char *s);
// int					is_limiter(char *limiter, char *buf);
// void				handle_here_doc(char *av, int fd[]);

// /* --- Pipes Functions --- */

// t_cmd_tb				*define_multiple_path(t_cmd_tb *path_list, char **av,
// 						char **envp);
// t_cmd_tb				*choose_multiple_handle(char *av, char **envp,
// 						t_cmd_tb *path_list);
// t_cmd_tb				*find_multiple_path(t_cmd_tb *path_list, char **possible_paths,
// 						char *av, char **args);
// void				close_all_pipes(t_cmd_tb *list);

// /* --- Redirections --- */

// int	has_redirections(char *s);

// /* --- Utils Functions --- */

// char				*ft_strip(char *str);
// void				print_list(t_cmd_tb *list);
// int					has_pipe(char *s);

// char	*handle_variable(char *var, char **envp);

#endif