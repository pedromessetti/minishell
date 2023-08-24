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
# define CYAN "\033[0;36m"
# define PURPLE "\033[0;35m"
# define WHITE "\033[0;37m"
# define RESET "\033[0m"

/* --- Main Structure --- */

typedef struct s_cmd
{
	char			*path;
	char			**p_f;
	pid_t			pid;
	int				pipe_fd[2];
	int				dup2_fd[2];
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd;

/* --- Global Variable --- */

extern int			g_last_exit_status;

/* --- Path Functions --- */

char				**set_possible_paths(char **envp);
t_cmd				*find_path(t_cmd *path_list, char **possible_paths,
						char *av, char **p_f);
t_cmd				*define_path(t_cmd *list, char *buf, char **envp);
t_cmd				*handle_str_error(char *buf, t_cmd *path_list);
t_cmd				*choose_handle(char *av, char **envp, t_cmd *path_list);

/* --- List Functions --- */

t_cmd				*add_path(char *path, char **p_f);
void				add_tail(t_cmd **list_head, t_cmd *new_path);
t_cmd				*find_last(t_cmd *paths_list);
void				free_path_list(t_cmd **paths_list);
t_cmd				*set_cmd_list(t_cmd *path_list, char *path,
						char **p_f);

/* --- Child Process Functions --- */

void				child_process(t_cmd *path_list, char **envp);
void				bind_stdin(t_cmd *curr);
void				bind_stdout(t_cmd *curr);
int					ft_wait(t_cmd *curr);
int					start_process(t_cmd *path_list, char **envp);
void				exec_cmd(t_cmd *path_list, char **envp);

/* --- Checker Functions --- */

void				check_ac(int ac);
int					*check_fd(int fd[], char **av, int ac);
int					check_builtin(char *av);
void				check_exit_status(t_cmd *path_list);
int					ask_for_exit_status(char **p_f);

/* --- Heredoc Functions --- */

int					is_here_doc(char *s);
int					is_limiter(char *limiter, char *buf);
void				handle_here_doc(char *av, int fd[]);

/* --- Pipes Functions --- */

t_cmd				*define_multiple_path(t_cmd *path_list, char **av,
						char **envp);
t_cmd				*choose_multiple_handle(char *av, char **envp,
						t_cmd *path_list);
t_cmd				*find_multiple_path(t_cmd *path_list, char **possible_paths,
						char *av, char **p_f);
void				close_all_pipes(t_cmd *list);

/* --- Redirections --- */

int	has_redirections(char *s);

/* --- Utils Functions --- */

char				*ft_strip(char *str);
void				print_list(t_cmd *list);
int					has_pipe(char *s);



char	*handle_variable(char *var, char **envp);

#endif // !MINISHELL.H