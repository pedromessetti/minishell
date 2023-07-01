/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 09:15:32 by pedro             #+#    #+#             */
/*   Updated: 2023/07/01 09:13:39 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL _H

# include "../libft/inc/libft.h"
# include <errno.h>
# include <fcntl.h>
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
	char			**path_and_cmd;
	pid_t			pid;
	int				pipe_fd[2];
	int				dup2_fd[2];
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd;

/* --- Path Functions --- */

char				**set_possible_paths(char **envp);
t_cmd				*find_path(t_cmd *path_list, char **possible_paths,
						char *av, char **path_and_cmd);
t_cmd				*define_path(t_cmd *list, char *buf, char **envp);
t_cmd				*handle_str_error(char *buf, t_cmd *path_list);
t_cmd				*choose_handle(char *av, char **envp, t_cmd *path_list);

/* --- List Functions --- */

t_cmd				*add_path(char *path, char **path_and_cmd);
void				add_tail(t_cmd **list_head, t_cmd *new_path);
t_cmd				*find_last(t_cmd *paths_list);
void				free_path_list(t_cmd **paths_list);
t_cmd				*set_cmd_list(t_cmd *path_list, char *path,
						char **path_and_cmd);

/* --- Child Process Functions --- */

void				child_process(t_cmd *path_list, char **envp);
void				bind_stds(t_cmd *curr, int fd[]);
void				close_fds(int fd[], t_cmd *curr, int opt);
int					ft_wait(t_cmd *curr);
int					start_process(t_cmd *path_list, int fd[], char **envp,
						char **av);

/* --- Checker Functions --- */

void				check_ac(int ac);
int					*check_fd(int fd[], char **av, int ac);
int					check_builtin(char *av);
void				check_exit_status(t_cmd *path_list);
int					is_dir(char *s);

/* --- Heredoc Functions --- */

int					is_here_doc(char *s);
int					is_limiter(char *limiter, char *buf);
void				handle_here_doc(char *av, int fd[]);

/* --- Utils Functions --- */

char				*ft_strip(char *str);

#endif // !MINISHELL.H