/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmessett <pmessett@student.42.fr>                +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 09:15:32 by pmessett             #+#    #+#             */
/*   Updated: 2023/07/11 08:55:14 by pmessett            ###   ########.fr       */
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
# include <unistd.h>

/* --- Macro Colors --- */

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define BLUE "\033[0;34m"
# define YELLOW "\033[0;33m"
# define WHITE "\033[0;37m"
# define RESET "\033[0m"

/* --- Main Structure --- */

typedef struct s_token
{
	int	type;
	char content[100]; // Ajustar size depois
}		t_token;

typedef struct s_cmd
{
	char			*path;
	char			**args;
	pid_t			pid;
	int				pipe_fd[2];
	int				dup2_fd[2];
	char 			*input_redir;
	char 			*output_redir;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd_tb;

// /* --- Global Variable --- */

// extern int			g_last_exit_status;

// /* --- Path Functions --- */

// char				**set_possible_paths(char **envp);
// t_cmd_tb				*find_path(t_cmd_tb *path_list, char **possible_paths,
// 						char *av, char **args);
// t_cmd_tb				*define_path(t_cmd_tb *list, char *buf, char **envp);
// t_cmd_tb				*handle_str_error(char *buf, t_cmd_tb *path_list);
// t_cmd_tb				*choose_handle(char *av, char **envp, t_cmd_tb *path_list);

// /* --- List Functions --- */

// t_cmd_tb				*add_path(char *path, char **args);
// void				add_tail(t_cmd_tb **list_head, t_cmd_tb *new_path);
// t_cmd_tb				*find_last(t_cmd_tb *paths_list);
// void				free_path_list(t_cmd_tb **paths_list);
// t_cmd_tb				*set_cmd_tb_list(t_cmd_tb *path_list, char *path,
// 						char **args);

// /* --- Child Process Functions --- */

// void				child_process(t_cmd_tb *path_list, char **envp);
// void				bind_stdin(t_cmd_tb *curr);
// void				bind_stdout(t_cmd_tb *curr);
// int					ft_wait(t_cmd_tb *curr);
// int					start_process(t_cmd_tb *path_list, char **envp);
// void				exec_cmd(t_cmd_tb *path_list, char **envp);

// /* --- Checker Functions --- */

void				check_ac(int ac);
// int					*check_fd(int fd[], char **av, int ac);
// int					check_builtin(char *av);
// void				check_exit_status(t_cmd_tb *path_list);
// int					ask_for_exit_status(char **args);

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